#pragma once

#include <iostream>
#include <unordered_map>


const int BOARD_SIZE = 8;

enum BoardLetters
{
    a, 
    b,
    c,
    d,
    e,
    f,
    g,
    h
};

enum PieceTypes
{
    King,
    Queen,
    Bishup,
    Castle,
    Knight,
    Pawn
};

class Board
{
public:

    Board()
    {
        board.reserve(BOARD_SIZE * 2);
    }

    //uses fen as the input
    Board(std::string fenInput)
    {

    }

    Piece GetPiece(BoardLetters letter, int number)
    {
        return board[(int)letter * BOARD_SIZE + number].piece;
    }

    Piece SetPiece(BoardLetters letter, int number, Piece piece)
    {
        Tile tile = board[(int)letter * BOARD_SIZE + number];
        tile.piece = piece;
    }

private:

    void InitializeGrid();

    std::unordered_map<int, Tile> board;
};

struct Tile
{
    void SetPiece(Piece piece)
    {
        this->piece = piece;
        containsPiece = true;
    }
    bool whiteTile;
    Piece piece;
    bool containsPiece;
};

struct Piece
{
    PieceTypes pieceType;
};

