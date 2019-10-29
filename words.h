#ifndef WORDS_H
#define WORDS_H

#include <stdio.h>
#include <stdlib.h>
#include "game.h"

#define WORDFILE "words.txt"
#define NUMWORDS 10000
#define MAXWORDSIZE 128

char** generatePuzzleToSolve(char **puzzle, unsigned numWords);
char** generatePuzzleSolution(unsigned numWords);
char* getRandomWord();
void freePuzzle(char **puzzle, unsigned numWords);

#endif
