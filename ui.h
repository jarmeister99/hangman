#ifndef UI_H
#define UI_H

#define NUMWORDS_PROMPT "Enter the number of words for the puzzle: "
#define NUMWORDS_PROMPT_HELP "The number of words must be a positive integer value.\n"
#define MAXGUESSES_PROMPT "Enter the number of guesses allowed: "
#define MAXGUESSES_PROMPT_HELP "The number of guesses allowed must be a positive integer value.\n"
#define GUESS_PROMPT "Enter your guess: "
#define GUESS_PROMPT_HELP "Your guess must be a letter.\n"

void displayGame();
unsigned promptUnsigned(const char *prompt, const char *promptHelp);
char promptGuess();
void displayPuzzle(char **puzzle, unsigned numWords);

#endif
