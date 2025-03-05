#include <stdio.h>   // for input and output
#include <stdlib.h>  // for system function like cls to clear the screen
#include <stdbool.h> // for bool data type
#include <time.h>    // for time function
#include <ctype.h>   // for handling characters
#include <string.h>  // for string functions

//suduko

#define SIZE 9
#define EMPTY 0

// Function to check if it's safe to place a number in a given cell
bool isSafe1(int puzzle[SIZE][SIZE], int row, int col, int num) {
    // Check if the number is not already present in the current row
    for(int i = 0; i < SIZE; i++)
        if(puzzle[row][i] == num)
            return false;

    // Check if the number is not already present in the current column
    for(int i = 0; i < SIZE; i++)
        if(puzzle[i][col] == num)
            return false;

    // Calculate the starting row and column indices of the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    // Check if the number is not already present in the current 3x3 subgrid
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(puzzle[i + startRow][j + startCol] == num)
                return false;

    // If the number is not found in the current row, column, or subgrid, it's safe to place
    return true;
}

// Function to find an empty cell in the puzzle
bool findEmptyLocation(int puzzle[SIZE][SIZE], int *row, int *col) {
    for (*row = 0; *row < SIZE; (*row)++)
        for (*col = 0; *col < SIZE; (*col)++)
            if (puzzle[*row][*col] == EMPTY)
                return true;

    return false; // Return false if no empty cell is found
}

// Function to solve the Sudoku puzzle recursively
bool solveSudoku(int puzzle[SIZE][SIZE]) {
    int row, col;

    // Check if there are any empty cells left in the puzzle
    if (!findEmptyLocation(puzzle, &row, &col)){
        // If no empty cell is found, Sudoku is solved
        return true;
    }

    // Generate a random permutation of numbers from 1 to 9
    int numbers[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; i++){
        int j = rand() % 9;
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // Try numbers from the random permutation
    for (int i = 0; i < 9; i++){
        int num = numbers[i];
        if (isSafe1(puzzle, row, col, num)){
            // Assign the number if it's safe
            puzzle[row][col] = num;

            // Recursively solve the remaining Sudoku
            if (solveSudoku(puzzle))
                return true;

            // If the assigned number doesn't lead to a solution,
            // backtrack and try a different number
            puzzle[row][col] = EMPTY;
        }
    }

    // No solution found
    return false;
}

// Function to generate a Sudoku puzzle with a given difficulty level
void generateSudoku(int puzzle[SIZE][SIZE], int difficulty) {
    // Clear the puzzle
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            puzzle[i][j] = EMPTY;
    }

    // Generate a random Sudoku puzzle
    solveSudoku(puzzle);

    // Remove numbers to create a playable Sudoku
    int numToRemove = difficulty;
    // Adjust this value to control the difficulty

    while (numToRemove > 0){
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (puzzle[row][col] != EMPTY){
            // Backup the number
            int backup = puzzle[row][col];
            puzzle[row][col] = EMPTY;

            // Check if the solution is unique
            int temp[SIZE][SIZE];
            for (int i = 0; i < SIZE; i++){
                for (int j = 0; j < SIZE; j++)
                    temp[i][j] = puzzle[i][j];
            }

            if (!solveSudoku(temp)){
                // If removing the number leads to a non-unique solution,
                // restore the number and try removing a different number
                puzzle[row][col] = backup;
            }
            else
                numToRemove--;
        }
    }
}

// Function to print the Sudoku puzzle
void printSudoku(int puzzle[SIZE][SIZE]) {
    printf("+------+-------+------+\n");
    for (int i = 1; i < 10; ++i){
        for (int j = 1; j < 10; ++j){
            printf("|%d", puzzle[i - 1][j - 1]);
            if (j % 3 == 0 && j != 9)
                printf("| ");
        }
        printf("|\n");
        if (i % 3 == 0)
            printf("+------+-------+------+\n");
    }
}

int main1(){
    // Prompt user to generate a random Sudoku puzzle
    printf("\nWelcome to Sudoku. This is free to play. Enjoy!");
    printf("To generate a random Sudoku puzzle, enter '1'. \n");
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1){
        int puzzle[SIZE][SIZE];
        srand(time(NULL));
        printf("Enter the difficulty of Sudoku puzzle on a scale of 0-65: ");
        int difficulty;
        scanf("%d", &difficulty);
        generateSudoku(puzzle, difficulty);
        printf("Generated Sudoku Puzzle:\n");
        printSudoku(puzzle);
        printf("\n");
        printf("Solve by putting numbers in place of 0s. To print the solved puzzle, enter 'Y'. To exit, enter 'N': ");

        char c;
        scanf(" %c", &c);

        if (c == 'Y' || c == 'y'){
            printf("\nSolved Sudoku Puzzle:\n");

            if (solveSudoku(puzzle))
                printSudoku(puzzle);
            else
                printf("\nNO SOLUTION\n");
        }
        else if (c == 'N' || c == 'n')
            printf("Enjoy solving the Sudoku Puzzle.");
    }

    return 0;
}

/*suduko ends */


//**************************************
//wordle
#define MAX_TRIES 6
#define WORD_LENGTH 5

// Function to check if the letter is present in the word
int isLetterPresent(char word[], char letter) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (word[i] == letter)
            return 1;
    }
    return 0;
}

// Function to check if the guessed letter is in the correct position
int isLetterInCorrectPosition(char word[], char letter, int position) {
    if (word[position] == letter)
        return 1;
    return 0;
}

int wordle() {
    int b1=0;
    char secretWord[WORD_LENGTH + 1];
    char guess[WORD_LENGTH + 1];
    int tries = 0;
    printf("Welcome to wordle!\n");
    printf("\nThe rules of wordle are:\n");
    printf("You may only guess a five letter word.\n");
    printf("It tells you which letters are correct and which not.\n");
    printf("It also tells you if a letter is in the correct position.\n");
    printf("You have maximum 6 attempts.\n\n");
    // Player 1 enters the secret word
    printf("Player 1, enter a 5-letter word: ");
    scanf("%s", secretWord);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    // Clearing input buffer
    while (getchar() != '\n');

    // Player 2 starts guessing
    printf("\nPlayer 2, start guessing:\n\n");

    // Main game loop
    while (tries < MAX_TRIES) {
        // Input guess
        printf("Enter your guess: ");
        scanf("%s", guess);

        // Clearing input buffer
        while (getchar() != '\n');

        // Check if guess is correct
        if (strcmp(guess, secretWord) == 0) {
            printf("Congratulations! You guessed the word correctly: %s\n", secretWord);
            b1=1;
            break;
        }

        // Check closeness of guess
        printf("Try %d: ", tries + 1);
        for (int i = 0; i < WORD_LENGTH; i++) {
            if (isLetterPresent(secretWord, guess[i])) {
                if (isLetterInCorrectPosition(secretWord, guess[i], i))
                    printf("%c is at the correct position, ", guess[i]);
                else
                    printf("%c is in the word but in the wrong spot, ", guess[i]);
            } else {
                printf("%c is not in the word, ", guess[i]);
            }
        }
        printf("\n\n");
        tries++;
    }

    // If maximum tries are reached
    if (tries == MAX_TRIES) {
        printf("Sorry, you ran out of tries. The word was: %s\n", secretWord);
    }

    return b1;
}


//******************************************

//******************************************
//blackjack

// Function to generate a random number between min and max (inclusive)
int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to calculate the value of a card
int getCardValue(int card) {
    if (card >= 2 && card <= 10) {
        return card;
    } else if (card >= 11 && card <= 13) {
        return 10; // For Jack, Queen, and King
    } else {
        return 11; // For Ace
    }
}

int blackjack() {
    srand(time(NULL));
    int z1=0;

    int playerTotal = 0, dealerTotal = 0;
    int playerCard1 = getRandomNumber(2, 13);
    int playerCard2 = getRandomNumber(2, 13);
    int dealerCard1 = getRandomNumber(2, 13);
    int dealerCard2 = getRandomNumber(2, 13);

    playerTotal = getCardValue(playerCard1) + getCardValue(playerCard2);
    dealerTotal = getCardValue(dealerCard1) + getCardValue(dealerCard2);

    printf("\nWelcome to Blackjack!\n\n");
    printf("\nThe rules of blackjack are as follows:\n");
    printf("In Blackjack, everyone plays against the dealer.\n");
    printf("Players receive all cards face up and the dealer's "
    "first card is face up and the second is also face up.\n");
    printf("The dealer's next card are all face down.\n");
    printf("The objective  of the game is to get closer to 21 "
    "than the dealer without going over 21.\n\n");


    printf("Dealer's cards: %d, %d\n", dealerCard1, dealerCard2);
    printf("Your cards: %d, %d\n", playerCard1, playerCard2);
    printf("Your total: %d\n\n", playerTotal);

    // Player's turn
    while (playerTotal < 21) {
        char choice;
        printf("Do you want to Hit (H) or Stand (S)? ");
        scanf(" %c", &choice);

        if (choice == 'H' || choice == 'h') {
            int newCard = getRandomNumber(2, 13);
            playerTotal += getCardValue(newCard);
            printf("New card: %d\n", newCard);
            printf("Your total: %d\n\n", playerTotal);
        } else if (choice == 'S' || choice == 's') {
            break;
        }
    }

    // Dealer's turn
    while (dealerTotal < 17) {
        int newCard = getRandomNumber(2, 13);
        dealerTotal += getCardValue(newCard);
        printf("Dealer got a new card: %d\n", newCard);
    }

    printf("\nDealer's total: %d\n", dealerTotal);

    // Determine the winner
    if (playerTotal > 21) {
        printf("Bust! You lose.\n");
    } else if (dealerTotal > 21 || playerTotal > dealerTotal) {
        printf("Congratulations! You win!\n");
        z1=1;
    } else if (dealerTotal > playerTotal) {
        printf("Dealer wins!\n");
    } else {
        printf("It's a tie!\n");
    }

    return z1;
}
//******************************
//******************************
//hangman

#define MAX_TRIES 6
#define WORDS_COUNT 10
#define MAX_WORD_LENGTH 20

char* words[] = {"programming", "hangman", "computer", "keyboard", "algorithm", "variable", "function", "language", "compiler", "software"};

// Function to randomly select a word from the list
char* selectRandomWord() {
    return words[rand() % WORDS_COUNT];
}

// Function to check if the guessed character is in the word
int checkGuess(char guess, char* word, char* guessed) {
    int i, found = 0;
    for (i = 0; word[i] != '\0'; i++) {
        if (tolower(word[i]) == tolower(guess)) {
            guessed[i] = word[i];
            found = 1;
        }
    }
    return found;
}

// Function to display the hangman figure
void drawHangman(int tries) {
    printf("\n");
    switch (tries) {
        case 1:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("       |\n");
            printf("       |\n");
            printf("       |\n");
            printf("       |\n");
            printf("=========\n");
            break;
        case 2:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("   O   |\n");
            printf("       |\n");
            printf("       |\n");
            printf("       |\n");
            printf("=========\n");
            break;
        case 3:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("   O   |\n");
            printf("   |   |\n");
            printf("       |\n");
            printf("       |\n");
            printf("=========\n");
            break;
        case 4:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("   O   |\n");
            printf("  /|   |\n");
            printf("       |\n");
            printf("       |\n");
            printf("=========\n");
            break;
        case 5:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("   O   |\n");
            printf("  /|\\  |\n");
            printf("       |\n");
            printf("       |\n");
            printf("=========\n");
            break;
        case 6:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("   O   |\n");
            printf("  /|\\  |\n");
            printf("  /    |\n");
            printf("       |\n");
            printf("=========\n");
            break;
        case 7:
            printf("   +---+\n");
            printf("   |   |\n");
            printf("   O   |\n");
            printf("  /|\\  |\n");
            printf("  / \\  |\n");
            printf("       |\n");
            printf("=========\n");
            break;
    }
}

int hangman() {
    srand(time(NULL));

    char* word = selectRandomWord();
    char guessed[MAX_WORD_LENGTH];
    int tries = 0;
    int i;
    int y1=0;

    // Initialize guessed array with underscores
    for (i = 0; word[i] != '\0'; i++) {
        guessed[i] = '_';
    }
    guessed[i] = '\0'; // Null terminate the string

    printf("\nWelcome to Hangman!\n");
    printf("\nThe rules of hangman are as follows:\n");
    printf("The computer is the executioner here.\n");
    printf("You shall guess a letter.\n");
    printf("If that letter is in the word(s) then write the letter will be displayed everywhere it would appear,"
    " an cross out that letter in the alphabet.\n");
    printf("If the letter isn't in the word then add a body part to the gallows "
    "(head, body, left arm, right arm, left leg, right leg).\n");
    printf("The player will continue guessing letters until they can either solve"
    " the word (or phrase) or all six body parts are on the gallows.\n");
    printf("The executioner wins if the full body is hanging from the gallows.\n");
    printf("The guesser(s) wins if they guess the word before the person is hung.\n\n");
    printf("Try to guess the word.\n");
    printf("You have 7 tries.\n");

    // Main game loop
    while (tries <= MAX_TRIES) {
        printf("\nWord: %s\n", guessed);
        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);

        // Check if the guessed letter is in the word
        if (checkGuess(guess, word, guessed)) {
            printf("Correct guess!\n");
        } else {
            printf("Incorrect guess!\n");
            tries++;
            drawHangman(tries);
        }

        // Check if the word has been completely guessed
        if (strcmp(word, guessed) == 0) {
            printf("\nCongratulations! You guessed the word: %s\n", word);
            y1=1;
            break;
        }
    }

    // If the player has used all tries
    if (tries > MAX_TRIES) {
        drawHangman(7);
        printf("\nSorry, you ran out of tries. The word was: %s\n", word);
        y1=0;
    }

    return y1;
}
//****************************
//number guessing game

int guess(int N)
{
    int number, guess, numberofguess = 0;
    int a12=0;
    //Seed random number generator
    srand(time(NULL));

    // Generate a random number
    number = rand() % N;

    printf("Guess a number between"
           " 1 and %d :",
           N);

    // Using a do-while loop that will
    // work until user guesses
    // the correct number
    do {

        if (numberofguess > 9) {
            printf("\nYou Loose!\n");
            break;
        }

        // Input by user
        scanf("%d", &guess);
        printf("\n");

        // When user guesses lower
        // than actual number
        if (guess > number)

        {
            printf("Lower number "
                   "please! :\n");
            numberofguess++;
        }

        // When user guesses higher
        // than actual number
        else if (number > guess)

        {
            printf("Higher number"
                   " please! :");
            numberofguess++;
        }

        // Printing number of times
        // user has taken to guess
        // the number
        else{
            printf("You guessed the"
                   " number in %d "
                   "attempts!\n",
                   numberofguess);
            a12=1;
        }

    } while (guess != number);
    return a12;
}

// Driver Code
int numberguessing()
{
    int N = 100;
    int a11=0;
    printf("\nHow to play NumberGuess:\n");
    printf("Choose a number between 1 and 100.\n");
    printf("You will be told if your guess "
    "is higher or lower.\n");
    printf("You have a total of 9 attempts "
    "to guess the number correctly.\n\n");

    // Function call
    if(guess(N)){
        a11=1;
    }

    return a11;
}
//****************************

//*****************************
//tic tac toe

#define COMPUTER 1
#define HUMAN 2
#define SIDE 3
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

// ---------------- Intelligent Moves start

struct Move {
	int row, col;
};

char player = 'x', opponent = 'o';

// This function returns true if there are moves
// remaining on the board. It returns false if
// there are no moves left to play.
bool isMovesLeft(char board[3][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (board[i][j] == '_')
				return true;
	return false;
}

// This is the evaluation function
int evaluate(char b[3][3])
{
	// Checking for Rows for X or O victory.
	for (int row = 0; row < 3; row++) {
		if (b[row][0] == b[row][1]
			&& b[row][1] == b[row][2]) {
			if (b[row][0] == player)
				return +10;
			else if (b[row][0] == opponent)
				return -10;
		}
	}

	// Checking for Columns for X or O victory.
	for (int col = 0; col < 3; col++) {
		if (b[0][col] == b[1][col]
			&& b[1][col] == b[2][col]) {
			if (b[0][col] == player)
				return +10;

			else if (b[0][col] == opponent)
				return -10;
		}
	}

	// Checking for Diagonals for X or O victory.
	if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
		if (b[0][0] == player)
			return +10;
		else if (b[0][0] == opponent)
			return -10;
	}

	if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
		if (b[0][2] == player)
			return +10;
		else if (b[0][2] == opponent)
			return -10;
	}

	// Else if none of them have won then return 0
	return 0;
}

// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board
int minimax(char board[3][3], int depth, bool isMax)
{
	int score = evaluate(board);

	// If Maximizer has won the game return his/her
	// evaluated score
	if (score == 10)
		return score;

	// If Minimizer has won the game return his/her
	// evaluated score
	if (score == -10)
		return score;

	// If there are no more moves and no winner then
	// it is a tie
	if (isMovesLeft(board) == false)
		return 0;

	// If this maximizer's move
	if (isMax) {
		int best = -1000;

		// Traverse all cells
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// Check if cell is empty
				if (board[i][j] == '_') {
					// Make the move
					board[i][j] = player;
					int val
						= minimax(board, depth + 1, !isMax);
					if (val > best) {
						best = val;
					}

					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		return best;
	}

	// If this minimizer's move
	else {
		int best = 1000;

		// Traverse all cells
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// Check if cell is empty
				if (board[i][j] == '_') {
					// Make the move
					board[i][j] = opponent;

					// Call minimax recursively and choose
					int val
						= minimax(board, depth + 1, !isMax);
					if (val < best) {
						best = val;
					}
					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		return best;
	}
}

// This will return the best possible move for the player
struct Move findBestMove(char board[3][3])
{
	int bestVal = -1000;
	struct Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	// Traverse all cells, evaluate minimax function for
	// all empty cells. And return the cell with optimal
	// value.
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// Check if cell is empty
			if (board[i][j] == '_') {
				// Make the move
				board[i][j] = player;

				// compute evaluation function for this
				// move.
				int moveVal = minimax(board, 0, false);

				// Undo the move
				board[i][j] = '_';

				// If the value of the current move is
				// more than the best value, then update
				// best/
				if (moveVal > bestVal) {
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}

	// printf("The value of the best Move is : %d\n\n",
	//	 bestVal);

	return bestMove;
}

// -----------------------------------Intelligent Moves end

// Function to display the game board
void showBoard(char board[][SIDE])
{
	printf("\n\n");
	printf("\t\t\t %c | %c | %c \n", board[0][0],
		board[0][1], board[0][2]);
	printf("\t\t\t--------------\n");
	printf("\t\t\t %c | %c | %c \n", board[1][0],
		board[1][1], board[1][2]);
	printf("\t\t\t--------------\n");
	printf("\t\t\t %c | %c | %c \n\n", board[2][0],
		board[2][1], board[2][2]);
}

// Function to show the instructions
void showInstructions()
{
	printf("\t\t\t Tic-Tac-Toe\n\n");
	printf("Choose a cell numbered from 1 to 9 as below "
		"and play\n\n");

	printf("\t\t\t 1 | 2 | 3 \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t 4 | 5 | 6 \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t 7 | 8 | 9 \n\n");

	printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
}

// Function to initialise the game
void initialise(char board[][SIDE], int moves[])
{
	srand(time(NULL));

	// Initially, the board is empty
	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++)
			board[i][j] = ' ';
	}

	// Fill the moves with numbers
	for (int i = 0; i < SIDE * SIDE; i++)
		moves[i] = i;

	// Randomize the moves
	for (int i = 0; i < SIDE * SIDE; i++) {
		int randIndex = rand() % (SIDE * SIDE);
		int temp = moves[i];
		moves[i] = moves[randIndex];
		moves[randIndex] = temp;
	}
}

// Function to declare the winner of the game
int declareWinner(int whoseTurn)
{
	if (whoseTurn == COMPUTER) {
		printf("COMPUTER has won\n");
        return 0; }
	else{
		printf("You have won\n");
        return 1;}
}

// Function to check if any row is crossed with the same
// player's move
int rowCrossed(char board[][SIDE])
{
	for (int i = 0; i < SIDE; i++) {
		if (board[i][0] == board[i][1]
			&& board[i][1] == board[i][2]
			&& board[i][0] != ' ')
			return 1;
	}
	return 0;
}

// Function to check if any column is crossed with the same
// player's move
int columnCrossed(char board[][SIDE])
{
	for (int i = 0; i < SIDE; i++) {
		if (board[0][i] == board[1][i]
			&& board[1][i] == board[2][i]
			&& board[0][i] != ' ')
			return 1;
	}
	return 0;
}

// Function to check if any diagonal is crossed with the
// same player's move
int diagonalCrossed(char board[][SIDE])
{
	if ((board[0][0] == board[1][1]
		&& board[1][1] == board[2][2]
		&& board[0][0] != ' ')
		|| (board[0][2] == board[1][1]
			&& board[1][1] == board[2][0]
			&& board[0][2] != ' '))
		return 1;

	return 0;
}

// Function to check if the game is over
int gameOver(char board[][SIDE])
{
	return (rowCrossed(board) || columnCrossed(board)
			|| diagonalCrossed(board));
}

// Function to play Tic-Tac-Toe
int playTicTacToe(int whoseTurn)
{
	// A 3*3 Tic-Tac-Toe board for playing
	char board[SIDE][SIDE];
	int moves[SIDE * SIDE];

	// Initialise the game
	initialise(board, moves);

	// Show the instructions before playing
	showInstructions();

	int moveIndex = 0, x, y;

	// Keep playing until the game is over or it is a draw
	while (!gameOver(board) && moveIndex != SIDE * SIDE) {
		if (whoseTurn == COMPUTER) {

			char tempBoard[3][3];
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (board[i][j] == 'X') {
						tempBoard[i][j] = 'x';
					}
					else if (board[i][j] == 'O') {
						tempBoard[i][j] = 'o';
					}
					else {
						tempBoard[i][j] = '_';
					}
				}
			}
			struct Move thisMove = findBestMove(tempBoard);
			x = thisMove.row;
			y = thisMove.col;

			board[x][y] = COMPUTERMOVE;
			printf("COMPUTER has put a %c in cell %d %d\n",
				COMPUTERMOVE, x, y);
			showBoard(board);
			moveIndex++;
			whoseTurn = HUMAN;
		}
		else if (whoseTurn == HUMAN) {
			int move;
			printf("Enter your move (1-9): ");
			scanf("%d", &move);
			if (move < 1 || move > 9) {
				printf("Invalid input! Please enter a "
					"number between 1 and 9.\n");
				continue;
			}
			x = (move - 1) / SIDE;
			y = (move - 1) % SIDE;
			if (board[x][y] == ' ') {
				board[x][y] = HUMANMOVE;
				showBoard(board);
				moveIndex++;
				if (gameOver(board)) {
					int x1=declareWinner(HUMAN);
					return x1;
				}
				whoseTurn = COMPUTER;
			}
			else {
				printf("Cell %d is already occupied. Try "
					"again.\n",
					move);
			}
		}
	}

	// If the game has drawn
	if (!gameOver(board) && moveIndex == SIDE * SIDE)
		printf("It's a draw\n");
	else {
		// Toggling the user to declare the actual winner
		if (whoseTurn == COMPUTER)
			whoseTurn = HUMAN;
		else if (whoseTurn == HUMAN)
			whoseTurn = COMPUTER;

		// Declare the winner
		int x2=declareWinner(whoseTurn);
        return x2;
	}
}
//*******************************

//******************************
//connect4

#define ROWS 6
#define COLS 7

char board[ROWS][COLS];

// Function to initialize the board
void initialize_board() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to display the board
void display_board() {
    printf("\n  1   2   3   4   5   6   7\n");
    printf("+---+---+---+---+---+---+---+\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
        printf("+---+---+---+---+---+---+---+\n");
    }
}

// Function to drop a piece into a column
int drop_piece(int col, char piece) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == ' ') {
            board[i][col] = piece;
            return i;
        }
    }
    return -1;
}

// Function to check if a player has won
int check_winner(char piece) {
    // Check horizontal
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j] == piece && board[i][j + 1] == piece &&
                board[i][j + 2] == piece && board[i][j + 3] == piece) {
                return 1;
            }
        }
    }
    // Check vertical
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == piece && board[i + 1][j] == piece &&
                board[i + 2][j] == piece && board[i + 3][j] == piece) {
                return 1;
            }
        }
    }
    // Check diagonals
    for (int i = 0; i <= ROWS - 4; i++) {
        for (int j = 0; j <= COLS - 4; j++) {
            if (board[i][j] == piece && board[i + 1][j + 1] == piece &&
                board[i + 2][j + 2] == piece && board[i + 3][j + 3] == piece) {
                return 1;
            }
            if (board[i][j + 3] == piece && board[i + 1][j + 2] == piece &&
                board[i + 2][j + 1] == piece && board[i + 3][j] == piece) {
                return 1;
            }
        }
    }
    return 0;
}

int connect4() {
    int b1=0;
    initialize_board();
    char player1 = 'X';
    char player2 = 'O';
    char current_player = player1;
    int winner = 0;

    printf("\nWelcome to Connect 4!\n");
    printf("\nYou must get 4 consecutive same symbol"
    " in a row column or diagonal to attain victory.\n");
    printf("Good luck!\n\n");
    printf("Player 1: X\n");
    printf("Player 2: O\n");

    while (!winner) {
        display_board();
        printf("Player %c's turn. Enter column (1-7): ", current_player);
        int column;
        scanf("%d", &column);
        column--; // Adjusting for zero-based indexing
        if (column < 0 || column >= COLS) {
            printf("Invalid column. Please try again.\n");
            continue;
        }
        int row = drop_piece(column, current_player);
        if (row == -1) {
            printf("Column is full. Please try again.\n");
            continue;
        }
        if (check_winner(current_player)) {
            display_board();
            printf("Player %c wins!\n", current_player);
            b1=1;
            winner = 1;
        } else {
            // Switch players
            current_player = (current_player == player1) ? player2 : player1;
        }
    }

    return b1;
}

//*******************************
//mines

#define BOARD_SIZE 5

char board1[BOARD_SIZE][BOARD_SIZE];
char revealed[BOARD_SIZE][BOARD_SIZE];

void initializeBoard() {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board1[i][j] = '+';
            revealed[i][j] = 0;
        }
    }
}

void placeMines(int numMines) {
    int i, j, count = 0;
    while (count < numMines) {
        i = rand() % BOARD_SIZE;
        j = rand() % BOARD_SIZE;
        if (board1[i][j] != '*') {
            board1[i][j] = '*';
            count++;
        }
    }
}

void printBoard() {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (revealed[i][j]) {
                printf("%c ", board1[i][j]);
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int mines_game() {
    srand(time(NULL));
    initializeBoard();
    int ans1=0;

    int numMines;
    printf("\nEnter the number of mines (up to %d): ", BOARD_SIZE * BOARD_SIZE - 1);
    scanf("%d", &numMines);
    if (numMines >= BOARD_SIZE * BOARD_SIZE) {
        printf("Invalid number of mines. Exiting.\n");
        return 1;
    }

    placeMines(numMines);

    printf("Welcome to the Mines and Gems game!\n");
    printf("Try to find the gems without stepping on the mines.\n");
    printf("Enter row and column to reveal a cell.\n");

    int row, col;
    while (1) {
        printBoard();
        printf("Enter row and column (0-%d): ", BOARD_SIZE - 1);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
            printf("Invalid input. Please enter valid coordinates.\n");
            continue;
        }

        if (board1[row][col] == '*') {
            printf("Game Over! You stepped on a mine.\n\n");
            break;
        } else {
            printf("You revealed: %c\n", board[row][col]);
            revealed[row][col] = 1;
        }

        int count = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board1[i][j] == '+' && revealed[i][j] == 0)
                    count++;
            }
        }

        if (count == 0) {
            printf("Congratulations! You've found all the gems!\n\n");
            ans1=1;
            break;
        }
    }

    return ans1;
}


//******************************
//roshambo

int roshambo() {
    // Seed the random number generator
    srand(time(NULL));

    int cx=0;

    // Declare variables
    int playerChoice, computerChoice;

    // Display menu and get player's choice
    printf("\nWelcome to Rock-Paper-Scissors!\n");
    printf("Enter your choice:\n");
    printf("1. Rock\n2. Paper\n3. Scissors\n");
    scanf("%d", &playerChoice);

    // Generate random choice for computer
    computerChoice = rand() % 3 + 1;

    // Display choices
    printf("You chose: ");
    switch (playerChoice) {
        case 1:
            printf("Rock\n");
            break;
        case 2:
            printf("Paper\n");
            break;
        case 3:
            printf("Scissors\n");
            break;
        default:
            printf("Invalid choice\n");
            return 1;
    }
    printf("Computer chose: ");
    switch (computerChoice) {
        case 1:
            printf("Rock\n");
            break;
        case 2:
            printf("Paper\n");
            break;
        case 3:
            printf("Scissors\n");
            break;
    }

    // Determine the winner
    if (playerChoice == computerChoice)
        printf("It's a tie!\n");
    else if ((playerChoice == 1 && computerChoice == 3) ||
             (playerChoice == 2 && computerChoice == 1) ||
             (playerChoice == 3 && computerChoice == 2)){
            printf("You win!\n");
            cx=1;
            }
    else
        printf("Computer wins!\n");

    return cx;
}
//***************************************************************************************
//pacman
#define ROWS1 12
#define COLS1 12
#define NUM_FOOD 10 // Number of food items

// Function to print the game board
void printBoard2(char board[ROWS1][COLS1], int pacmanX, int pacmanY, int demonX, int demonY) {
    //system("clear"); // Clear the console (works on Unix-like systems)

    for (int i = 0; i < ROWS1; i++) {
        for (int j = 0; j < COLS1; j++) {
            if (i == pacmanX && j == pacmanY)
                printf("C "); // Pac-Man representation
            else if (i == demonX && j == demonY)
                printf("D "); // Demon representation
            else
                printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int main2() {
    int y123=0;
    printf("\nWelcome to pac-man. Keep away from the demon(D) and gather all the food(F) to win.");
    char board[ROWS1][COLS1] = {
        "############",
        "#          #",
        "#  ## ##   #",
        "#          #",
        "# ######   #",
        "#          #",
        "#   #####  #",
        "#          #",
        "#          #",
        "#          #",
        "#          #",
        "############"
    };

    int pacmanX = 1, pacmanY = 1; // Initial position of Pac-Man
    int demonX = ROWS1 - 2, demonY = COLS1 - 2; // Initial position of the demon

    srand(time(NULL)); // Seed for random number generation

    // Add food items
    int foodCount = 0;
    while (foodCount < NUM_FOOD) {
        int x = rand() % ROWS1;
        int y = rand() % COLS1;
        if (board[x][y] == ' ' && (x!=0 && y!=0)) {
            board[x][y] = 'F';
            foodCount++;
        }
    }

    char move;
    bool gameOver = false;
    do {
        printBoard2(board, pacmanX, pacmanY, demonX, demonY);
        printf("\nUse WASD to move (W=up, A=left, S=down, D=right): ");
        scanf(" %c", &move);

        // Move the demon randomly
        int demonMove = rand() % 4; // 0: up, 1: left, 2: down, 3: right
        switch (demonMove) {
            case 0:
                if (demonX > 0 && board[demonX - 1][demonY] != '#')
                    demonX--;
                break;
            case 1:
                if (demonY > 0 && board[demonX][demonY - 1] != '#')
                    demonY--;
                break;
            case 2:
                if (demonX < ROWS1 - 1 && board[demonX + 1][demonY] != '#')
                    demonX++;
                break;
            case 3:
                if (demonY < COLS1 - 1 && board[demonX][demonY + 1] != '#')
                    demonY++;
                break;
        }

        switch (move) {
            case 'W':
            case 'w':
                if (pacmanX > 0 && board[pacmanX - 1][pacmanY] != '#')
                    pacmanX--;
                break;
            case 'A':
            case 'a':
                if (pacmanY > 0 && board[pacmanX][pacmanY - 1] != '#')
                    pacmanY--;
                break;
            case 'S':
            case 's':
                if (pacmanX < ROWS1 - 1 && board[pacmanX + 1][pacmanY] != '#')
                    pacmanX++;
                break;
            case 'D':
            case 'd':
                if (pacmanY < COLS1 - 1 && board[pacmanX][pacmanY + 1] != '#')
                    pacmanY++;
                break;
        }

        // Check if Pac-Man eats food
        if (board[pacmanX][pacmanY] == 'F') {
            board[pacmanX][pacmanY] = ' '; // Remove food
            printf("\nPac-Man eats the food!\n");
            foodCount--;
            if (foodCount == 0) {
                printf("\nCongratulations! You ate all the food!\n\n");
                y123=1;
                gameOver = true;
            }
        }

        // Check if Pac-Man collides with the demon
        if (pacmanX == demonX && pacmanY == demonY) {
            printf("\nPac-Man is caught by the demon!\n\n");
            gameOver = true;
        }

    } while (move != 'q' && move != 'Q' && !gameOver);

    return y123;
}
//*****************************
//main code
#define TICKET_PRICE 50

// Global variables
int walletBalance=0;
int numTickets = 0;

void addbalance(){
    int n1;
    printf("\nPlease enter amount to credit to your account: $");
    scanf("%d",&n1);
    printf("\n");
    walletBalance+=n1;
}

// Product structure
typedef struct {
    char name[50];
    int tickets;
} Product;

// Sample products
Product products[] = {
    {"Crayons", 10},
    {"Bottle", 20},
    {"Socks", 25},
    {"Torch", 35},
    {"kitkat", 40},
    {"Books", 45},
    {"Lamp", 45},
    {"Shirt", 50},
    {"Glasses",60},
    {"Bag", 65},
    {"Racket", 80},
    {"Pants", 100},
    {"Case", 110},
    {"Teddy", 120},
    {"Shoes", 150},
    {"Mystery", 500},
    {"Jacket", 600},
    {"Airpods", 1000},
    {"Laptop", 1500},
    {"Rolex", 10000}
};


// Function to deduct amount from wallet
void deductFromWallet(int amount) {
    walletBalance -= amount;
}

// Function to add amount to wallet
void addToWallet(int amount) {
    walletBalance += amount;
}

// Function to print wallet balance
void printWallet() {
    printf("Wallet Balance: %d\n", walletBalance);
    printf("Tickets: %d\n", numTickets);
}

// Function to purchase tickets
void purchaseTickets(int quantity) {
    int totalPrice = TICKET_PRICE * quantity;
    if (totalPrice > walletBalance) {
        printf("Insufficient funds to purchase tickets.\n");
        return;
    }
    numTickets += quantity;
    deductFromWallet(totalPrice);
    printf("You purchased %d tickets.\n", quantity);
}

// Function to display the product list
void displayProducts() {
    printf("Available Products:\n");
    printf("ID\tName\t\tTickets\n");
    for (int i = 0; i < 20; i++) {
        printf("%d\t%s\t\t%d\n", i + 1, products[i].name, products[i].tickets);
    }
}

// Function to process shopping
void processShopping() {
    int productId, quantity;
    printf("Enter product ID and quantity (e.g., 1 2): ");
    scanf("%d %d", &productId, &quantity);
    if(productId==16){
        printf("You got a cash price of $500 in the mystery box.\n");
        walletBalance+=500;
    }
    if (productId < 1 || productId > sizeof(products) / sizeof(products[0])) {
        printf("Invalid product ID.\n");
        return;
    }
    Product selectedProduct = products[productId - 1];
    if (selectedProduct.tickets*quantity > numTickets) {
        printf("Insufficient tickets to purchase %s.\n", selectedProduct.name);
        return;
    }
    numTickets -= selectedProduct.tickets;
    printf("You purchased %d %s.\n", quantity, selectedProduct.name);
}

int main() {
    srand(time(NULL));

    printf("\nWelcome to the IIT Patna Game Center!\n");

    //adding money to ingame account
    addbalance();

    char choice;

    //running loop while user wants to interact
    while (true) {
        printf("0.  Play Suduko       FREE   FREE   FREE       \n");
        printf("1.  Play Hangman     ($100 per game) (Reward 100 tickets)\n");
        printf("2.  Play Tic Tac Toe ($50  per game) (Reward 50 tickets)\n");
        printf("3.  Play Blackjack   ($200 per game) (Reward 150 tickets)\n");
        printf("4.  Play NumberGuess ($100 per game) (Reward 100 tickets)\n");
        printf("5.  Play Mines       ($100 per game) (Reward 1000 tickets)\n");
        printf("6.  Play Roshambo    ($50  per game) (Reward 50 tickets)\n");
        printf("7.  Play Pac-man     ($100 per game) (Reward 100 tickets)\n");
        printf("8.  Play Connect 4   ($150 per game) (Reward 100 tickets) [Multiplayer]\n");
        printf("9.  Play Wordle      ($100 per game) (Reward 50 tickets)  [Multiplayer]\n");
        printf("10. Purchase Tickets (50 tickets for $2500)\n");
        printf("11. View Wallet\n");
        printf("12. View shop items\n");
        printf("13. Shop\n");
        printf("14. Credit bank account\n");
        printf("15. Exit\n");

        printf("Enter your choice: ");
        scanf(" %d", &choice);

        switch (choice) {
            case 0:
            // play suduko
            main1();
            break;
            case 1:
                //checking if user has enough money to play the game
                if (walletBalance < 100) {
                    printf("Insufficient funds to play Hangman.\n");
                    break;
                }

                int x3=hangman();

                //incrementing tickets if player won
                if(x3==1){
                    numTickets+=100;
                }

                //deducting money required to play game from wallet
                deductFromWallet(100);

                break;
            case 2:
                //checking if user has enough money to play the game
                if (walletBalance < 50) {
                    printf("Insufficient funds to play Tic Tac Toe.\n");
                    break;
                }

                int x4=playTicTacToe(COMPUTER);

                //incrementing tickets if player won
                if(x4==1){
                    numTickets+=50;
                }

                //deducting money required to play game from wallet
                deductFromWallet(50);

                break;
            case 3:
                //checking if user has enough money to play the game
                if (walletBalance < 200) {
                    printf("Insufficient funds to play Blackjack.\n");
                    break;
                }

                int x5=blackjack();

                //incrementing tickets if player won
                if(x5==1){
                    numTickets+=150;
                }

                //deducting money required to play game from wallet
                deductFromWallet(200);

                break;
            case 4:
                //checking if user has enough money to play the game
                if (walletBalance < 150) {
                    printf("Insufficient funds to play NumberGuess.\n");
                    break;
                }

                int x8=numberguessing();

                //incrementing tickets if player won
                if(x8==1){
                    numTickets+=100;
                }

                //deducting money required to play game from wallet
                deductFromWallet(100);

                break;
            case 5:
                //checking if user has enough money to play the game
                if (walletBalance < 100) {
                    printf("Insufficient funds to play mines.\n");
                    break;
                }

                int x1111=mines_game();

                //incrementing tickets if player won
                if(x1111==1){
                    numTickets+=1000;
                }

                //deducting money required to play game from wallet
                deductFromWallet(100);

                break;
            case 6:
                //checking if user has enough money to play the game
                if (walletBalance < 150) {
                    printf("Insufficient funds to play roshambo.\n");
                    break;
                }

                int x61=roshambo();

                //incrementing tickets if player won
                if(x61==1){
                    numTickets+=50;
                }

                //deducting money required to play game from wallet
                deductFromWallet(50);

                break;
            case 7:
                //checking if user has enough money to play the game
                if (walletBalance < 100) {
                    printf("Insufficient funds to play pac-man.\n");
                    break;
                }

                int x612=main2();

                //incrementing tickets if player won
                if(x612==1){
                    numTickets+=100;
                }

                //deducting money required to play game from wallet
                deductFromWallet(100);

                break;
            case 8:
                //checking if user has enough money to play the game
                if (walletBalance < 150) {
                    printf("Insufficient funds to play connect 4.\n");
                    break;
                }

                int x6=connect4();

                //incrementing tickets if player won
                if(x6==1){
                    numTickets+=100;
                }

                //deducting money required to play game from wallet
                deductFromWallet(150);

                break;
            case 9:
                //checking if user has enough money to play the game
                if (walletBalance < 100) {
                    printf("Insufficient funds to play Wordle.\n");
                    break;
                }

                int x7=wordle();

                //incrementing tickets if player won
                if(x7==1){
                    numTickets+=50;
                }

                //deducting money required to play game from wallet
                deductFromWallet(100);

                break;
            case 10:
                //calling function to purchase tickets
                purchaseTickets(50);

                break;
            case 11:
                //calling function to display wallet contents
                printWallet();

                break;
            case 12:
                //calling function to display shop products
                displayProducts();

                break;
            case 13:
                //calling function to carry out shopping and billing
                processShopping();

                break;
            case 14:
                //calling function for increasing bank balance
                addbalance();

                break;
            case 15:
                //printing that we are exiting the program
                printf("\nExiting the program. Goodbye!\n\n");
                printf("The Game cum Shopping system integration has been developed by \n" );
                printf(" 1. Aekampreet Singh Dhir \n");
                printf(" 2. Khushi Suresh Yadav \n");
                printf(" 3. Aditya Tukaram Satpute \n");
                printf(" 4. Mayank Singh \n");
                printf(" 5. Rishabh Singh \n");
                printf(" 6. Remanshu Sharma \n");
                printf(" 7. Gargi Tiwari \n");
                printf(" 8. Shibhanshu Soubhagya Das \n");
                printf(" 9. Uday Srivastava \n");
                printf(" 10.Tarushi Singh \n\n");
                //exiting the program
                return 0;
            default:
                //if invalid choice entered
                printf("Invalid choice! Please enter a number between 0 and 15.\n");

                break;
        }

        printf("\n\n");
    }

    return 0;
}