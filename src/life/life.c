#include <life/boolean.h>
#include <life/direction.h>
#include <life/grid.h>
#include <life/life.h>

boolean Life_getNextCellValue(grid_t *grid, uint16_t cell) {
  uint8_t livingNeighborCount = 0;

  livingNeighborCount += Grid_getCellValue(grid, Grid_getAdjacentCellIndex(grid, cell, NORTH | WEST));
  livingNeighborCount += Grid_getCellValue(grid, Grid_getAdjacentCellIndex(grid, cell, NORTH));
  livingNeighborCount += Grid_getCellValue(grid, Grid_getAdjacentCellIndex(grid, cell, NORTH | EAST));
  livingNeighborCount += Grid_getCellValue(grid, Grid_getAdjacentCellIndex(grid, cell, WEST));
  livingNeighborCount += Grid_getCellValue(grid, Grid_getAdjacentCellIndex(grid, cell, EAST));
  livingNeighborCount += Grid_getCellValue(grid, Grid_getAdjacentCellIndex(grid, cell, SOUTH | WEST));
  livingNeighborCount += Grid_getCellValue(grid, Grid_getAdjacentCellIndex(grid, cell, SOUTH));
  livingNeighborCount += Grid_getCellValue(grid, Grid_getAdjacentCellIndex(grid, cell, SOUTH | EAST));

  return livingNeighborCount == 3 || (livingNeighborCount == 2 && Grid_getCellValue(grid, cell));
}

void Life_tick(grid_t *source, grid_t *target) {
  Grid_eachCell(source, Life_onCell, target);
}

void Life_onCell(grid_t *source, uint16_t cell, void *target) {
  Grid_setCellValue((grid_t*) target, cell, Life_getNextCellValue(source, cell));
}
