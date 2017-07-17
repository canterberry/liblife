#ifndef _LIFE_LIFE_H_
#define _LIFE_LIFE_H_

#include <stdlib.h>

#include <life/boolean.h>
#include <life/grid.h>

boolean Life_getNextCellValue(grid_t *grid, uint16_t cell);

void Life_onCell(grid_t *grid, uint16_t cell, void *data);

void Life_tick(grid_t *source, grid_t *target);

#endif
