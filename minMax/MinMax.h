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

int minMax(chess::Board& board, int depth, int alpha, int beta, bool isMaximizingPlayer)
{
	if (depth == 0 || board.isGameOver().second != chess::GameResult::NONE) // checks if the depth is 0 or if the game is over
	{
		//TODO: Evaluate the state and return it
		return evaluateHeuristic(board);
	}

	chess::Movelist moves;
	chess::movegen::legalmoves(moves, board);
	
	// Gets the best possible value
	int bestValue = isMaximizingPlayer ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

	// Go through all of the moves

	int i;
	for (i = 0; i < moves.size(); i++)
	{
		board.makeMove(moves[i]); // test out a move

		int value = minMax(board, depth - 1, alpha, beta, !isMaximizingPlayer);

		// update the best value

		if (isMaximizingPlayer)
		{
			// Maximize
			bestValue = std::max(bestValue, value);
			alpha = std::max(alpha, bestValue);
		}
		else
		{
			// Minimize
			bestValue = std::min(bestValue, value);
			beta = std::min(beta, bestValue);
		}


		// Apply the alpha beta pruning
		if (beta <= alpha)
		{
			break; // do not go down this branch.
		}
	}
	return bestValue;

}

int evaluateHeuristic(chess::Board board, bool isWhite)
{
	//TODO: Evaluate the heuristic

	std::string fen = board.getFen();

	int score = 0;

	// Get all of the pieces on the board

	// Add to the score depending on the piece

	// Add Bishop score
	chess::Bitboard bitBoard =  board.pieces(chess::PieceType::BISHOP);
	score += CalculatePieceScore(bitBoard, chess::PieceType::BISHOP, isWhite) * bishopScore;

	// Add Knight score
	bitBoard = board.pieces(chess::PieceType::KNIGHT);
	score += CalculatePieceScore(bitBoard, chess::PieceType::KNIGHT, isWhite) * knightScore;

	// Add Castle score
	bitBoard = board.pieces(chess::PieceType::ROOK);
	score += CalculatePieceScore(bitBoard, chess::PieceType::ROOK, isWhite) * castleScore;

	// Add pawn score
	bitBoard = board.pieces(chess::PieceType::PAWN);
	score += CalculatePieceScore(bitBoard, chess::PieceType::PAWN, isWhite) * pawnScore;

	// Add Queen score
	bitBoard = board.pieces(chess::PieceType::QUEEN);
	score += CalculatePieceScore(bitBoard, chess::PieceType::QUEEN, isWhite) * queenScore;

	// Add King score
	bitBoard = board.pieces(chess::PieceType::KING);
	score += CalculatePieceScore(bitBoard, chess::PieceType::KING, isWhite) * kingScore;

	return score;
}

// Goes through a bitmap to determine how many pieces there are of a single type of piece
int CalculatePieceScore(chess::Bitboard bitBoard, chess::PieceType type, bool isWhite)
{
	int score = 0;
	//score += bitBoard.count() * bishopScore;

	while (bitBoard.count() > 0)
	{
		uint8_t pieceValue = bitBoard.pop();
		chess::Piece piece = static_cast<chess::Piece::underlying>(pieceValue);

		if (piece.color() == chess::Color::BLACK)
		{
			if (isWhite)
			{
				score += GetPieceScore(type);
			}
			else
			{
				score -= GetPieceScore(type);
			}
		}
		else
		{
			if (isWhite)
			{
				score -= GetPieceScore(type);
			}
			else
			{
				score += GetPieceScore(type);
			}
		}
	}
	return score;
}

int GetPieceScore(chess::PieceType type)
{
	if (type == chess::PieceType::BISHOP)
	{
		return bishopScore;
	}
	else if (type == chess::PieceType::KNIGHT)
	{
		return knightScore;
	}
	else if (type == chess::PieceType::PAWN)
	{
		return pawnScore;
	}
	else if (type == chess::PieceType::ROOK)
	{
		return castleScore;
	}
	else if (type == chess::PieceType::QUEEN)
	{
		return queenScore;
	}
	else if (type == chess::PieceType::KING)
	{
		return kingScore;
	}
}

//TODO: Function for applying the move