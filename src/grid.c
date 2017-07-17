#include <boolean.h>
#include <direction.h>
#include <grid.h>
#include <stdlib.h>

grid_t *Grid_new(uint16_t width, uint16_t height) {
  grid_t *grid = malloc(sizeof(grid_t));
  if (grid == NULL) {
    return NULL;
  }

  grid->width = width;
  grid->height = height;

  uint16_t blockCount = Grid_getBlockCount(grid);
  grid->blocks = malloc(sizeof(uint8_t) * blockCount);
  if (grid->blocks == NULL) {
    free(grid);
    return NULL;
  }
  return grid;
}

void Grid_release(grid_t *grid) {
  if (grid != NULL) {
    if (grid->blocks != NULL) {
      free(grid->blocks);
    }
    free(grid);
  }
}

void Grid_clear(grid_t *grid) {
  uint16_t blockCount = Grid_getBlockCount(grid);
  for (uint16_t index = 0; index < blockCount; index++) {
    Grid_setBlockValue(grid, index, 0x00);
  }
}

void Grid_eachCell(grid_t *grid, void (*onCell)(grid_t *, uint16_t, void *), void *data) {
  uint16_t cellCount = Grid_getCellCount(grid);
  for (uint16_t index = 0; index < cellCount; index++) {
    onCell(grid, index, data);
  }
}

uint16_t Grid_getAdjacentCellIndex(grid_t *grid, uint16_t index, direction_t direction) {
  uint16_t x = Grid_getCellOffsetX(grid, index);
  uint16_t y = Grid_getCellOffsetY(grid, index);
  if (direction & NORTH) {
    if (y == 0) {
      y = grid->height - 1;
    } else {
      y--;
    }
  } else if (direction & SOUTH) {
    if (y == grid->height - 1) {
      y = 0;
    } else {
      y++;
    }
  }
  if (direction & WEST) {
    if (x == 0) {
      x = grid->width - 1;
    } else {
      x--;
    }
  } else if (direction & EAST) {
    if (x == grid->width - 1) {
      x = 0;
    } else {
      x++;
    }
  }
  return Grid_getCellIndex(grid, x, y);
}

uint16_t Grid_getBlockCount(grid_t *grid) {
  return Grid_getBlockCountX(grid) * grid->height;
}

uint16_t Grid_getBlockCountX(grid_t *grid) {
  uint16_t blockCountX = grid->width / 8;
  if (grid->width % 8 != 0) {
    blockCountX++;
  }
  return blockCountX;
}

uint8_t Grid_getBlockValue(grid_t *grid, uint16_t index) {
  return grid->blocks[index];
}

uint8_t Grid_getCellBitMask(grid_t *grid, uint16_t index) {
  return 0x01 << (7 - (Grid_getCellOffsetX(grid, index) % 8));
}

uint16_t Grid_getCellBlockIndex(grid_t *grid, uint16_t index) {
  return ((index / grid->width) * Grid_getBlockCountX(grid)) + ((index % grid->width) / 8);
}

uint16_t Grid_getCellCount(grid_t *grid) {
  return grid->width * grid->height;
}

uint16_t Grid_getCellIndex(grid_t *grid, uint16_t x, uint16_t y) {
  return (y * grid->width) + x;
}

uint16_t Grid_getCellOffsetX(grid_t *grid, uint16_t index) {
  return index % grid->width;
}

uint16_t Grid_getCellOffsetY(grid_t *grid, uint16_t index) {
  return index / grid->width;
}

boolean Grid_getCellValue(grid_t *grid, uint16_t index) {
  return (Grid_getBlockValue(grid, Grid_getCellBlockIndex(grid, index)) & Grid_getCellBitMask(grid, index)) != 0;
}

void Grid_seed(grid_t *grid, uint8_t *seed) {
  uint16_t blockCount = Grid_getBlockCount(grid);
  for (uint16_t index = 0; index < blockCount; index++) {
    Grid_setBlockValue(grid, index, seed[index]);
  }
}

void Grid_setBlockValue(grid_t *grid, uint16_t index, uint8_t value) {
  grid->blocks[index] = value;
}

void Grid_setCellValue(grid_t *grid, uint16_t index, boolean value) {
  uint16_t blockIndex = Grid_getCellBlockIndex(grid, index);
  uint8_t previousBlockValue = Grid_getBlockValue(grid, blockIndex);
  uint8_t bitMask = Grid_getCellBitMask(grid, index);
  uint8_t nextBlockValue;
  if (!value) {
    nextBlockValue = previousBlockValue & ~bitMask;
  } else {
    nextBlockValue = previousBlockValue | bitMask;
  }
  Grid_setBlockValue(grid, blockIndex, nextBlockValue);
}
