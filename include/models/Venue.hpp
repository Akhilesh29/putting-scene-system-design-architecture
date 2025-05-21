#pragma once

#include <string>
#include <memory>
#include <vector>

namespace putting_scene {

struct Location {
    double latitude;
    double longitude;
    std::string address;
    std::string city;
    std::string state;
    std::string country;
    std::string postal_code;
};

class Venue {
public:
    Venue() = default;
    ~Venue() = default;

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getName() const { return name_; }
    const Location& getLocation() const { return location_; }
    const std::string& getDescription() const { return description_; }
    int getCapacity() const { return capacity_; }
    const std::vector<std::string>& getAmenities() const { return amenities_; }
    const std::vector<std::string>& getImages() const { return images_; }

    // Setters
    void setId(const std::string& id) { id_ = id; }
    void setName(const std::string& name) { name_ = name; }
    void setLocation(const Location& location) { location_ = location; }
    void setDescription(const std::string& description) { description_ = description; }
    void setCapacity(int capacity) { capacity_ = capacity; }
    void setAmenities(const std::vector<std::string>& amenities) { amenities_ = amenities; }
    void setImages(const std::vector<std::string>& images) { images_ = images; }

    // Business Logic Methods
    double calculateDistance(const Location& other) const {
        // Implement Haversine formula for distance calculation
        // This is a placeholder - implement actual calculation
        return 0.0;
    }

    bool hasAmenity(const std::string& amenity) const {
        return std::find(amenities_.begin(), amenities_.end(), amenity) != amenities_.end();
    }

private:
    std::string id_;
    std::string name_;
    Location location_;
    std::string description_;
    int capacity_;
    std::vector<std::string> amenities_;
    std::vector<std::string> images_;
};

} // namespace putting_scene 