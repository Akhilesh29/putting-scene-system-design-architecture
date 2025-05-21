#pragma once

#include <memory>
#include <vector>
#include <string>
#include "../models/Event.hpp"

namespace putting_scene {

class EventService {
public:
    virtual ~EventService() = default;

    // Core CRUD operations
    virtual std::shared_ptr<Event> createEvent(const Event& event) = 0;
    virtual std::shared_ptr<Event> getEvent(const std::string& id) = 0;
    virtual std::vector<std::shared_ptr<Event>> getAllEvents() = 0;
    virtual bool updateEvent(const Event& event) = 0;
    virtual bool deleteEvent(const std::string& id) = 0;

    // Search and Filter operations
    virtual std::vector<std::shared_ptr<Event>> searchEvents(
        const std::string& query,
        const std::string& category = "",
        const std::string& city = "",
        const std::chrono::system_clock::time_point& start_date = std::chrono::system_clock::time_point(),
        const std::chrono::system_clock::time_point& end_date = std::chrono::system_clock::time_point()
    ) = 0;

    // Location-based operations
    virtual std::vector<std::shared_ptr<Event>> getNearbyEvents(
        double latitude,
        double longitude,
        double radius_km
    ) = 0;

    // Category-based operations
    virtual std::vector<std::shared_ptr<Event>> getEventsByCategory(
        const std::string& category
    ) = 0;

    // Time-based operations
    virtual std::vector<std::shared_ptr<Event>> getUpcomingEvents() = 0;
    virtual std::vector<std::shared_ptr<Event>> getOngoingEvents() = 0;

    // Ticket management
    virtual bool reserveTickets(const std::string& event_id, int quantity) = 0;
    virtual bool releaseTickets(const std::string& event_id, int quantity) = 0;
};

} // namespace putting_scene 