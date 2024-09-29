//
// Created by alexander on 26.09.2024.
//

#ifndef CSVPARSERIMPL_H
#define CSVPARSERIMPL_H

#include <boost/container/flat_map.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/include/qi.hpp>

#include <map>

#include "treeanalyzer/regions.h"

namespace qi = boost::spirit::qi;

namespace TRA::CSVParserImpl {

    using Column = std::string;
    using Columns = std::vector<Column>;
    using Record = Columns;
    using Table = std::vector<Record>;

    template<typename It>
    struct CsvGrammarRule : qi::grammar<It, Table(), qi::blank_type> {
        CsvGrammarRule() : CsvGrammarRule::base_type(start) {
            using namespace qi;

            static const char colsep = ',';

            start = -line % eol;
            line = column % colsep;
            column = quoted | *~char_(colsep);
            quoted = '"' >> *("\"\"" | ~char_('"')) >> '"';

            BOOST_SPIRIT_DEBUG_NODES((start)(line)(column)(quoted));
        }

    private:
        qi::rule<It, Table(), qi::blank_type> start;
        qi::rule<It, Record(), qi::blank_type> line;
        qi::rule<It, Column(), qi::blank_type> column;
        qi::rule<It, std::string()> quoted;
    };

    template<typename It>
    static std::set<RegionNodePtr<StateRegion> > parseFromCsv(It begin, It end) {
        std::map<std::string, RegionNodePtr<StateRegion> > states;

        CsvGrammarRule<It> p;
        Table parsed;

        if (bool ok = qi::phrase_parse(begin, end, p, qi::blank, parsed)) {
            for (auto &line: parsed) {
                auto &&cityName = std::move(line[0]);
                auto &&stateName = std::move(line[4]);
                auto itState = states.find(stateName);
                RegionNodePtr<StateRegion> curState;
                if (itState != states.end()) {
                    curState = itState->second;
                } else {
                    curState = std::make_shared<TreeNodeRegion<StateRegion> >(StateRegion(stateName));
                    states.insert(std::make_pair(stateName, curState));
                }
                curState->addChild(std::make_shared<TreeNodeRegion<CityRegion> >(CityRegion(cityName)));
            }
        } else {
            return {};
        }

        std::set<RegionNodePtr<StateRegion> > statesResult;
        for (auto &&[fst, snd]: states) {
            statesResult.emplace(std::move(snd));
        }

        return statesResult;
    }
};


#endif //CSVPARSERIMPL_H
