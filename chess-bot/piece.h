#pragma once

enum PieceTypes
{
    King,
    Queen,
    Bishop,
    Castle,
    Knight,
    Pawn,
    Empty
};

struct Piece
{
    PieceTypes pieceType;
    bool isWhite;
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
