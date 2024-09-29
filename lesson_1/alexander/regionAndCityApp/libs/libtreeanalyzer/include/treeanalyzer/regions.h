//
// Created by alexander on 23.09.2024.
//

#ifndef REGIONS_H
#define REGIONS_H

#include <string>
#include "treenode.h"

namespace TRA {

template <typename RegionItem>
class TreeNodeRegion;

template <typename RegType>
using RegionNodePtr = std::shared_ptr<TreeNodeRegion<RegType>>;


struct Coordinate {
    double longitude;
    double latitude;
};

    class BaseRegions {
    public:
        enum class RegionType { State, City, Undefined };

        [[nodiscard]] BaseRegions(const std::string &name, const ::TRA::BaseRegions::RegionType region_type);

        virtual ~BaseRegions();

        [[nodiscard]] std::string getName() const;
        [[nodiscard]] RegionType getRegionType() const;

    private:
        std::string name_;
        RegionType regionType_;
    };

    class StateRegion final : public BaseRegions {
    public:
        [[nodiscard]] explicit StateRegion(const std::string &name);
    };

    class CityRegion final : public BaseRegions {
    public:
        [[nodiscard]] explicit CityRegion(const std::string &name);

    private:
        int population_;
        Coordinate coordinate_;
    };

    template <typename RegionItem>
    class TreeNodeRegion: public TreeNode {
    public:
        explicit TreeNodeRegion(const RegionItem& item): regionItem_(item) {}
        RegionItem getObject() const { return regionItem_; }
        RegionItem& getObject() { return regionItem_; }

    private:
        RegionItem regionItem_;
    };


} // TreeAnalyzer

#endif //REGIONS_H
