#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
 **/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
 **/
Piezas::Piezas()
{
	/* build board */
	turn = X;
	for(int row = 0; row < BOARD_ROWS; row++) {
		for(int col = 0; col < BOARD_COLS; col++) {
			board[row][col] = Blank;
		}
	}
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
 **/
void Piezas::reset()
{
	for(int row = 0; row < BOARD_ROWS; row++) {
		for(int col = 0; col < BOARD_COLS; col++) {
			board[row][col] = Blank;
		}
	}
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
 **/ 
Piece Piezas::dropPiece(int column)
{
	/* store piece to drop */
	Piece droppedPiece = turn;

	/* check and assign turn */
	if(turn == X) {
		turn = O;
	}
	else {
		turn = X;
	}

	/* check bounds */
	if(column < 0 || column > BOARD_COLS) {
		return Invalid;
	}

	/* check column availability */
	for(int row = 0; row < BOARD_ROWS; row++) {
		if(pieceAt(row, column) == Blank) {
			return droppedPiece;
		}
	}

	/* Something real bad happened or the column is filled */
	return Blank;

}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
 **/
Piece Piezas::pieceAt(int row, int column)
{
	/* check bounds */
	if(row > BOARD_ROWS || column > BOARD_COLS) {
		return Invalid;
	}
	/* check occupancy */
	if(board[row][column] == X) {
		return X;
	}
	else if(board[row][column] == O) {
		return O;
	}

	/* no piece placed yet */
	return Blank;
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
 **/
Piece Piezas::gameState()
{
	/* is board filled? */
	bool blankFlag = false;
	for(int i = 0; i < BOARD_COLS; i++) {
		blankFlag = board[i].size() != BOARD_ROWS;
	}

	/* a blank indicates game still in play */
	if(blankFlag) {
		return Invalid;
	}

	/* winner counts vars */
	int numX = 0;
	int numO = 0;

	/* CHECK COLUMNS */
	/* check for X winner in columns */
	for(int col = 0; col < BOARD_COLS; col++) {
		int tempMax = 0;
		int tempCount = 0;
		Piece lastPlayed = X;

		/* check for x's in column */
		for(int row = 0; row < BOARD_ROWS; row++) {
			/* check for streak */
			if(board[col][row] == X && board[col][row] == lastPlayed) {
				tempCount++;
				/* if current streak longer than max, set it */
				if(tempCount > tempMax) {
					tempMax = tempCount;
				}
			}
			/* steak was broken */
			else {
				tempCount = 0;
			}
			/* set last played piece */
			lastPlayed = board[col][row];
		}
		/* set max X */
		if(tempMax > numX) {
			numX = tempMax;
		}
	}
	/* check for O winner in columns */
	for(int col = 0; col < BOARD_COLS; col++) {
		int tempMax = 0;
		int tempCount = 0;
		Piece lastPlayed = O;

		/* check for O's in column */
		for(int row = 0; row < BOARD_ROWS; row++) {
			/* check for streak */
			if(board[col][row] == O && board[col][row] == lastPlayed) {
				tempCount++;
				/* if current streak longer than max, set it */
				if(tempCount > tempMax) {
					tempMax = tempCount;
				}
			}
			/* streak was broken */
			else {
				tempCount = 0;
			}
			/* set last played piece */
			lastPlayed = board[col][row];
		}
		/* set max O */
		if(tempMax > numO) {
			numO = tempMax;
		}
	}

	/* CHECK ROWS */
	/* check for X winner in rows */
	for(int row = 0; row < BOARD_ROWS; row++) {
		int tempMax = 0;
		int tempCount = 0;
		Piece lastPlayed = X;

		/* check for x's in column */
		for(int col = 0; col < BOARD_COLS; col++) {
			/* check for streak */
			if(board[col][row] == X && board[col][row] == lastPlayed) {
				tempCount++;
				/* if current streak longer than max, set it */
				if(tempCount > tempMax) {
					tempMax = tempCount;
				}
			}
			/* steak was broken */
			else {
				tempCount = 0;
			}
			/* set last played piece */
			lastPlayed = board[col][row];
		}
		/* set max X */
		if(tempMax > numX) {
			numX = tempMax;
		}
	}
	/* check for O winner in rows */
	for(int row = 0; row < BOARD_ROWS; row++) {
		int tempMax = 0;
		int tempCount = 0;
		Piece lastPlayed = O;

		/* check for O's in column */
		for(int col = 0; col < BOARD_COLS; col++) {
			/* check for streak */
			if(board[col][row] == O && board[col][row] == lastPlayed) {
				tempCount++;
				/* if current streak longer than max, set it */
				if(tempCount > tempMax) {
					tempMax = tempCount;
				}
			}
			/* steak was broken */
			else {
				tempCount = 0;
			}
			/* set last played piece */
			lastPlayed = board[col][row];
		}
		/* set max O */
		if(tempMax > numO) {
			numO = tempMax;
		}
	}

	/* who won */
	if(numX > numO) {
		return X;
	}
	if(numO > numX) {
		return O;
	}
	/* tie */
	return Blank;
}
