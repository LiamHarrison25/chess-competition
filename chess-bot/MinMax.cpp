#include "MinMax.h"

static constexpr bool isValid(int c) { return c == 0 || c == 1 || c == -1; }

std::string MinMax::GetOptimalMove(std::string& fen, int depth)
{
	// Creates the board from the input
	chess::Board board(fen);
	chess::Movelist moves;
	chess::movegen::legalmoves(moves, board);

	//TODO: Change when I figure this out:
	bool isWhite = true;

	if (moves.size() == 0) // Has no possible moves to make
	{
		return "";
	}

	chess::Move optimalMove;
	int bestScore = std::numeric_limits<int>::min();

	// Run through all of the possible moves

	optimalMove = moves[0]; // Sets the default move

	int i;
	for (i = 0; i < moves.size() - 1; i++)
	{
		board.makeMove(moves[i]);
		int currentScore = minMax(board, depth, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), false, isWhite); //evaluateHeuristic(board, isWhite);

		// Undo the move so that the board does not get affected by a bad or not optimal move
		board.unmakeMove(moves[i]);

		if (currentScore > bestScore)
		{
			bestScore = currentScore;
			optimalMove = moves[i];
		}
	}


	return chess::uci::moveToUci(optimalMove);
}

int MinMax::minMax(chess::Board& board, int depth, int alpha, int beta, bool isMaxing, bool isWhite)
{
	if (depth == 0 || board.isGameOver().second != chess::GameResult::NONE) // checks if the depth is 0 or if the game is over
	{
		//TODO: Evaluate the state and return it
		return evaluateHeuristic(board, isWhite);
	}

	chess::Movelist moves;
	chess::movegen::legalmoves(moves, board);

	// Gets the best possible value
	int bestScore = isMaxing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

	// Go through all of the moves

	int i;
	for (i = 0; i < moves.size() - 1; i++)
	{
		board.makeMove(moves[i]); // test out a move

		int value = minMax(board, depth - 1, alpha, beta, !isMaxing, isWhite);

		board.unmakeMove(moves[i]);

		// update the best value

		if (isMaxing)
		{
			// Maximize
			bestScore = std::max(bestScore, value);
			alpha = std::max(alpha, bestScore);
		}
		else
		{
			// Minimize
			bestScore = std::min(bestScore, value);
			beta = std::min(beta, bestScore);
		}

		// Apply the alpha beta pruning
		if (beta <= alpha)
		{
			//board.unmakeMove(moves[i]);
			//break; // do not go down this branch.
		}

		
	}

	return bestScore;

}

int MinMax::evaluateHeuristic(chess::Board board, bool isWhite)
{
	//TODO: Evaluate the heuristic

	//std::string fen = board.getFen();

	int score = 0;

	// Get all of the pieces on the board

	// Add to the score depending on the piece

	//TODO: May have to change how I am calculating the number of pieces because it can randomly break


	// Add Bishop score
	chess::Bitboard bitBoard = board.pieces(chess::PieceType::BISHOP);
	score += bitBoard.count(); //CalculatePieceScore(bitBoard, chess::PieceType::BISHOP, isWhite) * bishopScore;

	// Add Knight score
	bitBoard = board.pieces(chess::PieceType::KNIGHT);
	score += bitBoard.count(); //CalculatePieceScore(bitBoard, chess::PieceType::KNIGHT, isWhite) * knightScore;

	// Add Castle score
	bitBoard = board.pieces(chess::PieceType::ROOK);
	score += bitBoard.count(); //CalculatePieceScore(bitBoard, chess::PieceType::ROOK, isWhite) * castleScore;

	// Add pawn score
	bitBoard = board.pieces(chess::PieceType::PAWN);
	score += bitBoard.count();//CalculatePieceScore(bitBoard, chess::PieceType::PAWN, isWhite) * pawnScore;

	// Add Queen score
	bitBoard = board.pieces(chess::PieceType::QUEEN);
	score += bitBoard.count(); //CalculatePieceScore(bitBoard, chess::PieceType::QUEEN, isWhite) * queenScore;

	// Add King score
	bitBoard = board.pieces(chess::PieceType::KING);
	score += bitBoard.count(); //CalculatePieceScore(bitBoard, chess::PieceType::KING, isWhite) * kingScore;

	return score;
}

int MinMax::CalculatePieceScore(chess::Bitboard bitBoard, chess::PieceType type, bool isWhite)
{
	int score = 0;
	//score += bitBoard.count() * bishopScore;

	while (bitBoard.count() > 0) // 
	{
		uint8_t pieceValue = bitBoard.pop();

		chess::Piece piece = static_cast<chess::Piece::underlying>(pieceValue);

		if (isValid(static_cast<int>(piece.color())))
		{
			if (piece.color() == chess::Color::BLACK) //BUG: Error here
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
	}
	return score;
}



int MinMax::GetPieceScore(chess::PieceType type)
{
	switch (type.internal())
	{
		case chess::PieceType::PAWN:
		{
			return pawnScore;
		}
		case chess::PieceType::BISHOP:
		{
			return bishopScore;
		}
		case chess::PieceType::KNIGHT:
		{
			return knightScore;
		}
		case chess::PieceType::ROOK:
		{
			return castleScore;
		}
		case chess::PieceType::QUEEN:
		{
			return queenScore;
		}
		case chess::PieceType::KING:
		{
			return kingScore;
		}
	}
}