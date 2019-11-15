#ifndef WORDS_H
#define WORDS_H

#include <stdio.h>
#include <stdlib.h>
#include "game.h"

#define WORD_FILE "words.txt"
#define NUM_WORDS 10000
#define MAX_WORD_SIZE 128

char** generatePuzzleToSolve(char **puzzle, unsigned numWords);
char** generatePuzzleSolution(unsigned numWords);
char* getRandomWord();
void freePuzzle(char **puzzle, unsigned numWords);

#endif
