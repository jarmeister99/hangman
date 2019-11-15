#ifndef GAME_H
#define GAME_H

#include "game.h"

typedef struct GameData{
   unsigned maxGuesses;
   char **puzzleSolution;
   char **puzzleToSolve;
   unsigned numWords;
} GameData;

int checkGuess(char guess, GameData *gd);
int checkVictory(GameData *gd);
void runGame(GameData *gd);

#endif
