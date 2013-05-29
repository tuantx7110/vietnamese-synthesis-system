/*
 * unit_searcher.h
 *
 *  Created on: May 29, 2013
 *      Author: quangpham
 */

#include <vector>
#include <string>

using namespace std;

#include "recorded_database_reader.h"
#include "input_text_reader.h"

#ifndef UNIT_SEARCHER_H_
#define UNIT_SEARCHER_H_

class UnitSearcher {
public:
    UnitSearcher();
    virtual ~UnitSearcher();

    bool init();
    bool search_units_in_recorded_database(RecordedDatabaseReader& recorded_database_reader, InputTextReader& input_text_reader);
};

#endif /* UNIT_SEARCHER_H_ */
