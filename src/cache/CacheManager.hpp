#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <chrono>
#include <redis++/redis++.h>
#include <nlohmann/json.hpp>

namespace putting_scene {

class CacheManager {
public:
    CacheManager(
        std::shared_ptr<sw::redis::Redis> redis_client,
        size_t l1_cache_size = 1000
    ) : redis_client_(redis_client), l1_cache_size_(l1_cache_size) {}

    // Event caching
    void cacheEvent(const std::string& id, const nlohmann::json& event_data) {
        // L1 Cache (In-memory)
        l1_event_cache_[id] = {
            event_data,
            std::chrono::system_clock::now() + std::chrono::hours(1)
        };

        // L2 Cache (Redis)
        redis_client_->set(
            "event:" + id,
            event_data.dump(),
            std::chrono::hours(24)
        );
    }

    std::optional<nlohmann::json> getEvent(const std::string& id) {
        // Try L1 Cache first
        auto l1_it = l1_event_cache_.find(id);
        if (l1_it != l1_event_cache_.end()) {
            if (std::chrono::system_clock::now() < l1_it->second.expiry) {
                return l1_it->second.data;
            }
            l1_event_cache_.erase(l1_it);
        }

        // Try L2 Cache (Redis)
        auto redis_data = redis_client_->get("event:" + id);
        if (redis_data) {
            auto event_data = nlohmann::json::parse(*redis_data);
            
            // Update L1 Cache
            l1_event_cache_[id] = {
                event_data,
                std::chrono::system_clock::now() + std::chrono::hours(1)
            };

            // Maintain L1 cache size
            if (l1_event_cache_.size() > l1_cache_size_) {
                evictOldestL1Entry();
            }

            return event_data;
        }

        return std::nullopt;
    }

    // Search result caching
    void cacheSearchResults(
        const std::string& query_hash,
        const nlohmann::json& results
    ) {
        redis_client_->set(
            "search:" + query_hash,
            results.dump(),
            std::chrono::hours(1)
        );
    }

    std::optional<nlohmann::json> getSearchResults(const std::string& query_hash) {
        auto redis_data = redis_client_->get("search:" + query_hash);
        if (redis_data) {
            return nlohmann::json::parse(*redis_data);
        }
        return std::nullopt;
    }

    // Cache invalidation
    void invalidateEvent(const std::string& id) {
        // Invalidate L1 Cache
        l1_event_cache_.erase(id);

        // Invalidate L2 Cache
        redis_client_->del("event:" + id);
    }

private:
    struct CacheEntry {
        nlohmann::json data;
        std::chrono::system_clock::time_point expiry;
    };

    void evictOldestL1Entry() {
        auto oldest = l1_event_cache_.begin();
        for (auto it = l1_event_cache_.begin(); it != l1_event_cache_.end(); ++it) {
            if (it->second.expiry < oldest->second.expiry) {
                oldest = it;
            }
        }
        l1_event_cache_.erase(oldest);
    }

    std::shared_ptr<sw::redis::Redis> redis_client_;
    std::unordered_map<std::string, CacheEntry> l1_event_cache_;
    size_t l1_cache_size_;
};

} // namespace putting_scene 