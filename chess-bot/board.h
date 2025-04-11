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
    Board(std::string fenInput);

    Piece GetPiece(BoardLetters letter, int number);

    Piece SetPiece(BoardLetters letter, int number, Piece piece);

private:

    void InitializeGrid(std::string fenInput);

    void SetPiece(Piece piece, int row, int &spacing, bool isWhite);

    std::unordered_map<int, Tile> board;
};



