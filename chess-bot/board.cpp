#include "board.h"

void Board::InitializeGrid()
{
    bool flipColor = true;
    int i, j;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Tile tile = board[i * BOARD_SIZE + j];
            tile.whiteTile = flipColor;
            tile.containsPiece = false;
            flipColor = !flipColor;
            //TODO: Initialize the piece type
        }
    }
}

//TODO: Set up the spawn positions
//TODO: Optimize the memory for this
//TODO: Make a way to submit moves to this and check if it is valid. Use the current chess library as an example

// rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR is the standard starting sequence for a board

/* 
*   Lowercase: black pieces
*   Uppercase: white pieces
*   Empty squares are denoted from 1 to 8, depending on how many empty squares are between two pieces
*   The sequence is stored by row
*   p/P: pawn
*   r/R: rook/castle
*   n/N: knight
*   b/B: bishop
*   q/Q: queen
*   k/K: king
*/
