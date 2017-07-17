#ifndef _LIFE_GRID_H_
#define _LIFE_GRID_H_

#include <stdlib.h>

#include <life/boolean.h>
#include <life/direction.h>

typedef struct Grid {
  uint8_t *blocks;
  uint16_t width;
  uint16_t height;
} grid_t;

grid_t *Grid_new(uint16_t width, uint16_t height);

void Grid_release(grid_t *grid);

void Grid_clear(grid_t *grid);

void Grid_eachCell(grid_t *grid, void (*onCell)(grid_t *, uint16_t, void *), void *data);

uint16_t Grid_getAdjacentCellIndex(grid_t *grid, uint16_t cell, direction_t direction);

uint16_t Grid_getBlockCount(grid_t *grid);

uint16_t Grid_getBlockCountX(grid_t *grid);

uint8_t Grid_getBlockValue(grid_t *grid, uint16_t index);

uint8_t Grid_getCellBitMask(grid_t *grid, uint16_t index);

uint16_t Grid_getCellBlockIndex(grid_t *grid, uint16_t index);

uint16_t Grid_getCellCount(grid_t *grid);

uint16_t Grid_getCellIndex(grid_t *grid, uint16_t x, uint16_t y);

uint16_t Grid_getCellOffsetX(grid_t *grid, uint16_t index);

uint16_t Grid_getCellOffsetY(grid_t *grid, uint16_t index);

boolean Grid_getCellValue(grid_t *grid, uint16_t index);

uint16_t Grid_getCellCount(grid_t *grid);

void Grid_printf(grid_t *grid);

void Grid_seed(grid_t *grid, uint8_t *seed);

void Grid_setBlockValue(grid_t *grid, uint16_t index, uint8_t value);

void Grid_setCellValue(grid_t *grid, uint16_t index, boolean value);

#endif
