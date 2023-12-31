//
// Created by Anshul Sanghi on 31/12/23.
//

#ifndef DAY3_CONTENTS_H
#define DAY3_CONTENTS_H

#include <_stdio.h>
#include "stdlib.h"
#include "types.h"

void alloc_contents_grid(size_t x, size_t y, char(**contents)[x][y]);

void read_contents_grid(FILE* file_descriptor, size_t positions_count, struct SymbolPosition positions[positions_count], size_t rows, size_t columns, char contents[rows][columns]);

#endif //DAY3_CONTENTS_H
