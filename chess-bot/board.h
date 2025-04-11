#pragma once

#include <iostream>
#include <unordered_map>
#include <piece.h>


const int BOARD_SIZE = 8;

enum BoardLetters;
enum PieceTypes;
struct Piece;
struct Tile;
class Board;

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

class Board
{
public:

    Board();
   

    //uses fen as the input
    Board(std::string fenInput)
    {
        InitializeGrid(fenInput);
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

    void InitializeGrid(std::string fenInput);

    std::unordered_map<int, Tile> board;
};



