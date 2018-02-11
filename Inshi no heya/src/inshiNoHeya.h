#ifndef INSHI_H
#define INSHI_H

#define VERSION 0.1.1

#define MAX_SIZE 16

typedef struct cell_t Cell;
typedef struct grid_t Grid;

void printGrid (Grid* grid);
Grid* readFile (const char *path);
Grid* initializeGrid (int size);
unsigned int setRightwardRoom (Grid *grid, unsigned int currentCell, unsigned long long roomValue, unsigned short roomLength);
unsigned int setDownwardRoom (Grid *grid, unsigned int currentCell, unsigned long long roomValue, unsigned short roomLength);
void printValuesInGrid (Grid *grid);
void freeGrid (Grid *grid);

#endif /* INSHI_H */
