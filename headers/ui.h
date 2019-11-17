#ifndef UI_H
#define UI_H

#define DATASOURCE_PROMPT "Enter the path to the text file to be used in puzzle generation: "
#define MAXGUESSES_PROMPT "Enter the number of incorrect guesses allowed: "
#define MAXGUESSES_PROMPT_HELP "The number of incorrect guesses allowed must be a positive integer value.\n\n"
#define GUESS_PROMPT "Enter your guess: "
#define GUESS_PROMPT_HELP "Your guess must be a number or letter.\n\n"

#define ERROR_CANT_FIND_FILE "Unable to open the file at the given path\n\n"
#define ERROR_CANT_RUN_SCRIPT "Unable to run the script at the given path\n\n"

#define PATH_MARKOV_SCRIPT "scripts/markov.py"

#define HANGMAN_STAGE_01   "    ______      \n"\
                           "    |    |      \n"\
                           "         |      \n"\
                           "         |      \n"\
                           "         |      \n"\
                           "         |      \n"\
                           "         |      \n"\
                           "     ____|____  \n"

#define HANGMAN_STAGE_02   "    ______      \n"\
                           "    |    |      \n"\
                           "    0    |      \n"\
                           "         |      \n"\
                           "         |      \n"\
                           "         |      \n"\
                           "         |      \n"\
                           "     ____|____  \n"

#define HANGMAN_STAGE_03   "    ______      \n"\
                           "    |    |      \n"\
                           "    0    |      \n"\
                           "   | |   |      \n"\
                           "   |_|   |      \n"\
                           "         |      \n"\
                           "         |      \n"\
                           "     ____|____  \n"

#define HANGMAN_STAGE_04   "    ______      \n"\
                           "    |    |      \n"\
                           "    0    |      \n"\
                           " ==| |   |      \n"\
                           "   |_|   |      \n"\
                           "         |      \n"\
                           "         |      \n"\
                           "     ____|____  \n"

#define HANGMAN_STAGE_05   "    ______      \n"\
                           "    |    |      \n"\
                           "    0    |      \n"\
                           " ==| |== |      \n"\
                           "   |_|   |      \n"\
                           "         |      \n"\
                           "         |      \n"\
                           "     ____|____  \n"

#define HANGMAN_STAGE_06   "    ______      \n"\
                           "    |    |      \n"\
                           "    0    |      \n"\
                           " ==| |== |      \n"\
                           "   |_|   |      \n"\
                           "   |     |      \n"\
                           "   |     |      \n"\
                           "     ____|____  \n"

#define HANGMAN_STAGE_07   "    ______      \n"\
                           "    |    |      \n"\
                           "    0    |      \n"\
                           " ==| |== |      \n"\
                           "   |_|   |      \n"\
                           "   | |   |      \n"\
                           "   | |   |      \n"\
                           "     ____|____  \n"
void displayGame();
unsigned promptUnsigned(const char *prompt, const char *promptHelp);
char promptGuess();
char* promptFile(const char *prompt);
void displayPuzzle(char **puzzle, unsigned numWords);
void displayGuessList(char guessList[], int numGuesses);
void displayHangman(unsigned incorrectGuesses, unsigned maxGuesses);

#endif
