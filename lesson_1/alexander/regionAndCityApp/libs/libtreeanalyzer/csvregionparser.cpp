//
// Created by alexander on 24.09.2024.
//

#include "csvregionparser.h"
#include "csvparserimpl.h"

#include <boost/iostreams/device/mapped_file.hpp>

CSVRegionParser::CSVRegionParser(): hasError_(false) {}

std::set<TRA::RegionNodePtr<TRA::StateRegion>> CSVRegionParser::parseFromMappingFile(const std::string& pathToSourceFile) {
    boost::iostreams::mapped_file_source csvSource(pathToSourceFile);
    auto&& res = CSVParserImpl::parseFromCsv(csvSource.begin(), csvSource.end());
    hasError_ = res.empty();
    return res;
}

std::set<TRA::RegionNodePtr<TRA::StateRegion>> CSVRegionParser::parseFromString(const std::string &csvString) {
    auto&& res = CSVParserImpl::parseFromCsv(csvString.begin(), csvString.end());
    hasError_ = res.empty();
    return res;
}

bool CSVRegionParser::hasError() const { return hasError_; }
