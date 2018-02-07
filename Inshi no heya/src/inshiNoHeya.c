#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inshiNoHeya.h"

struct cell_t {
  /* Value within the cell. */
  uint64_t value;
  /* Required product for cells in the current room. */
  unsigned long long roomProduct;
  /* Next cell in the current room. */
  Cell *next;
};

struct grid_t {
  /* Grid that we are working on. */
  Cell **cells;
  /* Size of this grid. */
  size_t size;
};

/* MAIN */
int
main (int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file> (ex: %s ../test/5x5_Easy)\n", argv[0], argv[0]);
    exit(EXIT_FAILURE);
  }

  printf("Program starting!\n");
  
  Grid *grid = readFile(argv[1]);
  
  printValuesInGrid(grid);
  
  freeGrid(grid);
  
  printf("Program ending!\n");
  
  return 0;
}

/* Lit une grille a partir d'un fichier. */
Grid*
readFile (const char *path) {
  const char rightDelimiter = 'r';
  const char bottomDelimiter = 'b';
  char line[256];
  
  unsigned long long roomValue = 0;
  unsigned short roomLength = 0;
  unsigned short gridSize = 0;
  
  unsigned int i = 0;
  unsigned int currentCell = 0;
  
    
  Grid *grid = NULL;
  FILE *inputFile = fopen(path, "r");
  
  if (inputFile != NULL) {
    fscanf(inputFile, "%s", line);
    
    gridSize = atoll(line);
    
    if (gridSize < MAX_SIZE)
      grid = initializeGrid(gridSize);
    
    while (fscanf(inputFile, "%s", line) != EOF) {
      while (line[i] >= '0' && line[i] <= '9') {
        roomValue = roomValue * 10 + line[i++] - '0';
      }
      
      if (roomValue == 0)
        printf("Error in input file format.\n");
      
      if (line[i] == rightDelimiter) {
        i++;
        
        while (line[i] >= '0' && line[i] <= '9') {
          roomLength = roomLength * 10 + line[i++] - '0';
        }
        
        currentCell = setRightwardRoom(grid, currentCell, roomValue, roomLength);
      }
        
      else if (line[i] == bottomDelimiter) {
        i++;
        
        while (line[i] >= '0' && line[i] <= '9') {
          roomLength = roomLength * 10 + line[i++] - '0';
        }
        
        currentCell = setDownwardRoom(grid, currentCell, roomValue, roomLength);
      }
        
      else
        printf("Error in input file format.\n");
      
      //DEBUG
      //printf("%s (%llu -> %d)\n", line, roomValue, roomLength);
      
      i = 0;
      roomValue = 0;
      roomLength = 0;      
    }
  }
  
  else
    printf("Error reading input file.\n");
  
  return grid;
}

/* Assigne une salle horizontale aux cases correspondantes et renvoie la nouvelle position dans la grille. */
unsigned int
setRightwardRoom (Grid *grid, unsigned int currentCell, unsigned long long roomValue, unsigned short roomLength) {
  while (grid->cells[currentCell]->roomProduct != 0)
    currentCell++;
  
  for (unsigned short i=0; i<roomLength; i++)
    grid->cells[currentCell+i]->roomProduct = roomValue;

  return currentCell+roomLength;
}

/* Assigne une salle verticale aux cases correspondantes et renvoie la nouvelle position dans la grille. */
unsigned int
setDownwardRoom (Grid *grid, unsigned int currentCell, unsigned long long roomValue, unsigned short roomLength) {
  while (grid->cells[currentCell]->roomProduct != 0)
    currentCell++;
  
  for (unsigned short i=0; i<roomLength; i++)
    grid->cells[currentCell+i*grid->size]->roomProduct = roomValue;

  return currentCell+1;
}

/* Creer une nouvelle grille vide et renvoie son pointeur. */
Grid*
initializeGrid (int size) {
  Grid *grid = malloc(sizeof(Grid));
  
  grid->size = size;  
  grid->cells = malloc(sizeof(Cell*) * grid->size * grid->size);
  
  for (unsigned int i=0; i<grid->size; i++)
    for (unsigned int j=0; j<grid->size; j++) {
      grid->cells[i*grid->size+j] = malloc(sizeof(Cell));
    
      grid->cells[i*grid->size+j]->value = 0;
      grid->cells[i*grid->size+j]->roomProduct = 0;
      grid->cells[i*grid->size+j]->next = NULL;
    }
    
  return grid;
}

/* Affiche une liste des valeurs de chaque cases de la grille. */
void
printValuesInGrid (Grid *grid) {
  printf("\nPrinting values in grid :\n");
  
  for (unsigned int i=0; i<grid->size; i++)
    for (unsigned int j=0; j<grid->size; j++)
      printf("Cell (%d,%d) = %lu [%llu]\n", i, j, grid->cells[i*grid->size+j]->value, grid->cells[i*grid->size+j]->roomProduct);
      
  printf("\n");
}

/* Libere l'espace en memoire utilise par la grille. */
void
freeGrid (Grid *grid) {
  for (unsigned int i=0; i<grid->size; i++)
    for (unsigned int j=0; j<grid->size; j++)
      free(grid->cells[i*grid->size+j]);
      
      
  free(grid->cells);
  free(grid);
}
