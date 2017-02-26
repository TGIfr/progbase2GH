//
// Created by tgifr on 26.02.17.
//

#ifndef PROGBASE2GH_CSV_H
#define PROGBASE2GH_CSV_H

#include "list.h"

int getcols(const char * const line, const char * const delim, char ***out_storage);
const char * const StandardDelimiter ;


List * readCsv(char * readFile);
void saveCsv(List * list, char * saveFile);


#endif //PROGBASE2GH_CSV_H
