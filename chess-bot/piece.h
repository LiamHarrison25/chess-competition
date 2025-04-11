#pragma once

enum PieceTypes
{
    King,
    Queen,
    Bishup,
    Castle,
    Knight,
    Pawn,
    Empty
};

struct Piece
{
    PieceTypes pieceType;
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
