//
// Created by alexander on 23.09.2024.
//

#include "include/regions.h"

namespace TRA {
    BaseRegions::BaseRegions(const std::string &name, const TRA::BaseRegions::RegionType region_type): name_(name),
        regionType_(region_type) {
    }

    BaseRegions::~BaseRegions() {
    }

    std::string BaseRegions::getName() const {
        return name_;
    }

    BaseRegions::RegionType BaseRegions::getRegionType() const {
        return regionType_;
    }

    StateRegion::StateRegion(const std::string &name): BaseRegions(name, RegionType::State) {
    }

    CityRegion::CityRegion(const std::string &name): BaseRegions(name, RegionType::City) {
    }
} // TreeAnalyzer