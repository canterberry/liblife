#ifndef _LIFE_H_
#define _LIFE_H_

#include <boolean.h>
#include <grid.h>
#include <stdlib.h>

boolean Life_getNextCellValue(grid_t *grid, uint16_t cell);

void Life_onCell(grid_t *grid, uint16_t cell, void *data);

void Life_tick(grid_t *source, grid_t *target);

#endif
