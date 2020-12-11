/**
 * Unit Tests for Piezas
 **/

#include <gtest/gtest.h>
#include "Piezas.h"

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, dropPieceValid)
{
	Piezas board;
	for (int i=0; i < BOARD_COLS; i++) {
		Piece droppedPiece = board.dropPiece(i);
		ASSERT_TRUE(droppedPiece != Invalid && droppedPiece != Blank);
	}
}

TEST(PiezasTest, dropPieceInvalidNegNum)
{
	Piezas board;
	ASSERT_TRUE(board.dropPiece(-3) == Invalid);
}

TEST(PiezasTest, dropPieceInvalidNumBig)
{
	Piezas board;
	ASSERT_TRUE(board.dropPiece(9) == Invalid);
}

TEST(PiezasTest, dropPieceBoardFull)
{
	Piezas board;
	for (int i=0; i < BOARD_ROWS; i++) {
		board.dropPiece(0);
	}
	ASSERT_TRUE(board.dropPiece(0) == Blank);
}

TEST(PiezasTest, pieceAtEmptyValid)
{
	Piezas board;
	for (int col=0; col < BOARD_COLS; col++) {
		for (int row=0; row < BOARD_ROWS; row++) {
			ASSERT_TRUE(board.pieceAt(row, col) == Blank);
		}
	}
}

TEST(PiezasTest, pieceAtFullValid)
{
	Piezas board;
	for (int col=0; col < BOARD_COLS; col++) {
		for (int row=0; row < BOARD_ROWS; row++) {
			board.dropPiece(col);
		}
	}

	for (int col=0; col < BOARD_COLS; col++) {
		for (int row=0; row < BOARD_ROWS; row++) {
			Piece droppedPiece = board.pieceAt(row, col);
			ASSERT_TRUE(droppedPiece != Invalid && droppedPiece != Blank);
		}
	}
}

TEST(PiezasTest, gameStateEmpty)
{
	Piezas board;
	ASSERT_TRUE(board.gameState() == Invalid);
}

TEST(PiezasTest, gameStateTie)
{
	Piezas board;
	for (int col=0; col < BOARD_COLS; col++) {
		for (int row=0; row < BOARD_ROWS; row++) {
			board.dropPiece(col);
		}
	}
	ASSERT_TRUE(board.gameState() == Blank);
}

TEST(PiezasTest, XwinCol)
{
	Piezas board;
	for (int col=1; col < BOARD_COLS; col++) {
		for (int row=0; row < BOARD_ROWS; row++) {
			board.dropPiece(col);
		}
	}
	for (int row=0; row < BOARD_ROWS; row++) {
		/* give O invalid piece */
		board.dropPiece(-1);
		/* give X valid piece */
		board.dropPiece(0);
	}
	ASSERT_TRUE(board.gameState() == X);
}

TEST(PiezasTest, OwinCol)
{
	Piezas board;
	for (int col=1; col < BOARD_COLS; col++) {
		for (int row=0; row < BOARD_ROWS; row++) {
			board.dropPiece(col);
		}
	}
	for (int row=0; row < BOARD_ROWS; row++) {
		/* give O valid piece */
		board.dropPiece(0);
		/* give X bad piece */
		board.dropPiece(-1);
	}
	ASSERT_TRUE(board.gameState() == O);
}

TEST(PiezasTest, XwinRow)
{
	Piezas board;
	for (int col=0; col < BOARD_COLS; col++) {
		board.dropPiece(col);
		board.dropPiece(-1);
	}

	board.dropPiece(0);
	board.dropPiece(0);
	board.dropPiece(2);
	board.dropPiece(2);

	board.dropPiece(-1);

	board.dropPiece(1);
	board.dropPiece(1);
	board.dropPiece(3);
	board.dropPiece(3);

	ASSERT_TRUE(board.gameState() == X);
}

TEST(PiezasTest, OwinRow)
{
	Piezas board;

	board.dropPiece(-1);

	for (int col=0; col < BOARD_COLS; col++) {
		board.dropPiece(col);
		board.dropPiece(-1);
	}
	board.dropPiece(0);
	board.dropPiece(0);
	board.dropPiece(2);
	board.dropPiece(2);

	board.dropPiece(-1);

	board.dropPiece(1);
	board.dropPiece(1);
	board.dropPiece(3);
	board.dropPiece(3);

	ASSERT_TRUE(board.gameState() == O);
}
