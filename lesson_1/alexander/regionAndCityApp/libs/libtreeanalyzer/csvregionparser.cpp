//
// Created by alexander on 24.09.2024.
//

#include "treeanalyzer/csvregionparser.h"
#include "csvparserimpl.h"

#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/device/file.hpp>

#include <sstream>

//#define PERF_TEST_ON

#ifdef PERF_TEST_ON
    #define START_PERF_TEST(TESTNAME) \
        std::clock_t TESTNAME##_START = std::clock();

    #define END_PEFT_TEST(TESTNAME) \
        std::clock_t TESTNAME##_END = std::clock(); \
        double TESTNAME##_time_elapsed_ms = 1000.0 * (TESTNAME##_END - TESTNAME##_START) / CLOCKS_PER_SEC; \
        std::cout << #TESTNAME << " CPU time used:" << TESTNAME##_time_elapsed_ms << " ms\n";
#else
#   define START_PERF_TEST(TESTNAME) ((void) 0)
#   define END_PEFT_TEST(TESTNAME) ((void) 0)
#endif

CSVRegionParser::CSVRegionParser(): hasError_(false) {}

std::set<TRA::RegionNodePtr<TRA::StateRegion>> CSVRegionParser::parseFromFile(const std::string &pathToSourceFile) {
    START_PERF_TEST(READING_FILE);
    std::ifstream in(pathToSourceFile);

    std::stringstream ss;
    ss << in.rdbuf();
    std::string fileData = ss.str();

    END_PEFT_TEST(READING_FILE);

    START_PERF_TEST(PARSE__READING_FILE);
    auto&& res = TRA::CSVParserImpl::parseFromCsv(fileData.begin(), fileData.end());
    END_PEFT_TEST(PARSE__READING_FILE);

    hasError_ = res.empty();
    return res;
}

std::set<TRA::RegionNodePtr<TRA::StateRegion>> CSVRegionParser::parseFromMappingFile(const std::string& pathToSourceFile) {
    START_PERF_TEST(MAPPING_FILE);
    boost::iostreams::mapped_file_source csvSource(pathToSourceFile);
    END_PEFT_TEST(MAPPING_FILE);

    START_PERF_TEST(PARSE__MAPPING_FILE);
    auto&& res = TRA::CSVParserImpl::parseFromCsv(csvSource.begin(), csvSource.end());
    END_PEFT_TEST(PARSE__MAPPING_FILE);
    hasError_ = res.empty();
    return res;
}

std::set<TRA::RegionNodePtr<TRA::StateRegion>> CSVRegionParser::parseFromString(const std::string &csvString) {
    auto&& res = TRA::CSVParserImpl::parseFromCsv(csvString.begin(), csvString.end());
    hasError_ = res.empty();
    return res;
}

bool CSVRegionParser::hasError() const { return hasError_; }
