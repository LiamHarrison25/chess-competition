#include "board.h"
#include <iostream>

void Board::InitializeGrid(std::string fenInput)
{

    // take in the fenInput and initialize the grid using it

    board.reserve(8 * 8);

    int row = 8; // starts at the top left
    int spacing = 0;

    int i;
    for (i = 0; i < fenInput.length(); i++)
    {
        
        //TODO: Fix this so that it works with the rest of FEN. w for white, b for black, k for kingside castling, q for queenside castling, - no castling, 

        char input = fenInput[i];

        CheckSpacing(spacing);

        //checks if the input is a number
        if (input >= 49 && input <= 57)
        {
            spacing += (((int)input - 48) - 1);
            continue;
        }

        switch (input)
        {
            case 'r':
            {
                Piece piece;
                piece.pieceType = PieceTypes::Castle;
                piece.isWhite = false;
                SetPiece(piece, row, spacing, false);
                break;
            }
            case 'R':
            {
                Piece piece;
                piece.pieceType = PieceTypes::Castle;
                piece.isWhite = true;
                SetPiece(piece, row, spacing, true);
                break;
            }
            case 'n':
            {
                Piece piece;
                piece.pieceType = PieceTypes::Knight;
                piece.isWhite = false;
                SetPiece(piece, row, spacing, false);
                break;
            }
            case 'N':
            {
                Piece piece;
                piece.pieceType = PieceTypes::Knight;
                piece.isWhite = true;
                SetPiece(piece, row, spacing, true);
                break;
            }
            case 'b':
            {
                Piece piece;
                piece.pieceType = PieceTypes::Bishop;
                piece.isWhite = false;
                SetPiece(piece, row, spacing, false);
                break;
            }
            case 'B':
            {
                Piece piece;
                piece.pieceType = PieceTypes::Bishop;
                piece.isWhite = true;
                SetPiece(piece, row, spacing, true);
                break;
            }
            case 'q':
            {
                Piece piece;
                piece.pieceType = PieceTypes::Queen;
                piece.isWhite = false;
                SetPiece(piece, row, spacing, false);
                break;
            }
            case 'Q':
            {
                Piece piece;
                piece.pieceType = PieceTypes::Queen;
                piece.isWhite = true;
                SetPiece(piece, row, spacing, true);
                break;
            }
            case 'k':
            {
                Piece piece;
                piece.pieceType = PieceTypes::King;
                piece.isWhite = false;
                SetPiece(piece, row, spacing, false);
                break;
            }
            case 'K':
            {
                Piece piece;
                piece.pieceType = PieceTypes::King;
                piece.isWhite = true;
                SetPiece(piece, row, spacing, true);
                break;
            }
            case 'p':
            {
                Piece piece;
                piece.pieceType = PieceTypes::Pawn;
                piece.isWhite = false;
                SetPiece(piece, row, spacing, false);
                break;
            }
            case 'P':
            {
                Piece piece;
                piece.pieceType = PieceTypes::Pawn;
                piece.isWhite = true;
                SetPiece(piece, row, spacing, true);
                break;
            }
            case '/':
            {
                row--;
                spacing = 0;
                if (row <= 0)
                {
                    break;
                }
                break;
            }
            case 'w':
            {
                
                break;
            }
        }
    }

    //bool flipColor = true;
    //int j;
    //for (int i = 0; i < BOARD_SIZE; i++)
    //{
    //    for (int j = 0; j < BOARD_SIZE; j++)
    //    {
    //        Tile tile = board[i * BOARD_SIZE + j];
    //        tile.whiteTile = flipColor;
    //        tile.containsPiece = false;
    //        flipColor = !flipColor;
    //        //TODO: Initialize the piece type


    //    }
    //}
}

void Board::CheckSpacing(int& spacing)
{
    if (spacing >= 8)
    {
        spacing = 0;
    }
}

void Board::SetPiece(Piece piece, int row, int& spacing, bool isWhite)
{
    board[8 * row + spacing] = piece;
    spacing++; // Increments the spacing in the row
}

Board::Board()
{
    board.reserve(BOARD_SIZE * 2);
}

Board::Board(std::string fenInput)
{
    InitializeGrid(fenInput);
}

Piece Board::GetPiece(BoardLetters letter, int number)
{
    return board[(int)letter * BOARD_SIZE + number];
}

//void Board::SetPiece(BoardLetters letter, int number, Piece piece)
//{
//    Tile tile = board[(int)letter * BOARD_SIZE + number];
//    tile.piece = piece;
//}


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
