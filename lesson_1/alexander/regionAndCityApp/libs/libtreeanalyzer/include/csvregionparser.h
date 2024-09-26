//
// Created by alexander on 24.09.2024.
//

#ifndef CSVREGIONPARSER_H
#define CSVREGIONPARSER_H

#include <string>
#include <set>

#include "regions.h"

class CSVRegionParser {
public:
    [[nodiscard]] explicit CSVRegionParser();
    std::set<TRA::RegionNodePtr<TRA::StateRegion >> parseFromMappingFile(const std::string& pathToSourceFile);
    std::set<TRA::RegionNodePtr<TRA::StateRegion >> parseFromString(const std::string& csvString);
    [[nodiscard]] bool hasError() const;

private:
    bool hasError_;
};


#endif //CSVREGIONPARSER_H
