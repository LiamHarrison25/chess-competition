#pragma once
#include <string>
#include "chess.hpp"
#include <limits>
#include "piece.h"

// Min max with alpha beta pruning

int pawnScore = 1;
int knightScore = 5;
int bishopScore = 10;
int castleScore = 15;
int queenScore = 50;
int kingScore = 1000;

class MinMax
{
public:

	// gets the optimal move
	std::string GetOptimalMove(std::string& fen, int depth);

private:

	int minMax(chess::Board& board, int depth, int alpha, int beta, bool isMaxing, bool isWhite); //TODO: Optimize for MASM. Last 2 variables will be going onto the dram instead of a register

	int evaluateHeuristic(chess::Board board, bool isWhite);

	// Goes through a bitmap to determine how many pieces there are of a single type of piece
	int CalculatePieceScore(chess::Bitboard bitBoard, chess::PieceType type, bool isWhite);

	int GetPieceScore(chess::PieceType type);

};
