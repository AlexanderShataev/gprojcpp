//
// Created by alexander on 9/26/24.
//
#include "gtest/gtest.h"

#include "csvregionparser.h"

#include <string>
#include <algorithm>
#include <set>
#include <ctime>


TEST(LIB_TRA_PARSER, VALID_LOAD_STRING) {
    std::string example =
            R"("Dhaka","Dhaka","23.7639","90.3889","Bangladesh","BD","BGD","Dhaka","primary","18627000","1050529279"
"Beijing","Beijing","39.9067","116.3975","China","CN","CHN","Beijing","primary","18522000","1156228865"
"Kolkāta","Kolkata","22.5675","88.3700","India","IN","IND","West Bengal","admin","18502000","1356060520"
"Bangkok","Bangkok","13.7525","100.4942","Thailand","TH","THA","Krung Thep Maha Nakhon","primary","18007000","1764068610"
"Shenzhen","Shenzhen","22.5415","114.0596","China","CN","CHN","Guangdong","minor","17619000","1156158707"
"Moscow","Moscow","55.7558","37.6172","Russia","RU","RUS","Moskva","primary","17332000","1643318494"
"Buenos Aires","Buenos Aires","-34.6033","-58.3817","Argentina","AR","ARG","Buenos Aires, Ciudad Autónoma de","primary","16710000","1032717330"
"Lagos","Lagos","6.4550","3.3841","Nigeria","NG","NGA","Lagos","minor","16637000","1566593751"
"Istanbul","Istanbul","41.0136","28.9550","Turkey","TR","TUR","İstanbul","admin","16079000","1792756324"
"Karachi","Karachi","24.8600","67.0100","Pakistan","PK","PAK","Sindh","admin","15738000","1586129469")";

    CSVRegionParser parser;
    auto res = parser.parseFromString(example);

    ASSERT_FALSE(res.empty());
    auto stateIt = std::find_if(res.begin(), res.end(), [](const TRA::RegionNodePtr<TRA::StateRegion> &region) {
        return region->getObject().getName() == "China";
    });

    ASSERT_FALSE(stateIt == res.end());
    ASSERT_TRUE(
        std::static_pointer_cast<TRA::TreeNodeRegion<TRA::CityRegion>>((*stateIt)->getChilds().front())->getObject().
        getName() == "Beijing");
}

TEST(LIB_TRA_PARSER, VALID_LOAD_FILE_MAPPING) {
    CSVRegionParser parser;

    std::clock_t c_start = std::clock();
    auto res = parser.parseFromMappingFile("../../../../../../../lesson_1/dataset/worldcities.csv");
    std::clock_t c_end = std::clock();

    double time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << "MAPPING CPU time used: "
            << time_elapsed_ms
            << " ms\n";
    ASSERT_FALSE(res.empty());
    auto stateIt = std::find_if(res.begin(), res.end(), [](const TRA::RegionNodePtr<TRA::StateRegion> &region) {
        return region->getObject().getName() == "China";
    });

    ASSERT_FALSE(stateIt == res.end());
    auto citiies = (*stateIt)->getChilds();
    auto beijingCityIt = std::find_if(citiies.begin(), citiies.end(), [](const std::shared_ptr<TRA::TreeNode> &city) {
        auto cityPtr = std::static_pointer_cast<TRA::TreeNodeRegion<TRA::CityRegion> >(city);
        return cityPtr->getObject().getName() == "Beijing";
    });
    ASSERT_FALSE(beijingCityIt == citiies.end());

    auto unknownCityIt = std::find_if(citiies.begin(), citiies.end(), [](const std::shared_ptr<TRA::TreeNode> &city) {
        auto cityPtr = std::static_pointer_cast<TRA::TreeNodeRegion<TRA::CityRegion> >(city);
        return cityPtr->getObject().getName() == "HrenTown";
    });

    ASSERT_TRUE(unknownCityIt == citiies.end());
}

TEST(LIB_TRA_PARSER, VALID_LOAD_FILE_READING) {
    CSVRegionParser parser;

    std::clock_t c_start = std::clock();
    auto res = parser.parseFromFile("../../../../../../../lesson_1/dataset/worldcities.csv");
    std::clock_t c_end = std::clock();

    double time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << "READING CPU time used: "
            << time_elapsed_ms
            << " ms\n";
    ASSERT_FALSE(res.empty());
    auto stateIt = std::find_if(res.begin(), res.end(), [](const TRA::RegionNodePtr<TRA::StateRegion> &region) {
        return region->getObject().getName() == "China";
    });

    ASSERT_FALSE(stateIt == res.end());
    auto citiies = (*stateIt)->getChilds();
    auto beijingCityIt = std::find_if(citiies.begin(), citiies.end(), [](const std::shared_ptr<TRA::TreeNode> &city) {
        auto cityPtr = std::static_pointer_cast<TRA::TreeNodeRegion<TRA::CityRegion> >(city);
        return cityPtr->getObject().getName() == "Beijing";
    });
    ASSERT_FALSE(beijingCityIt == citiies.end());

    auto unknownCityIt = std::find_if(citiies.begin(), citiies.end(), [](const std::shared_ptr<TRA::TreeNode> &city) {
        auto cityPtr = std::static_pointer_cast<TRA::TreeNodeRegion<TRA::CityRegion> >(city);
        return cityPtr->getObject().getName() == "HrenTown";
    });

    ASSERT_TRUE(unknownCityIt == citiies.end());
}
