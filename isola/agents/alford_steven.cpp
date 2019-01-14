/* Name: Steven Alford
 * Date: 11/10/18
 * File: alford_steven.cpp
 * Desc: An isola agent implementing minimax.  For details see alford_steven.h
 */

#include "alford_steven.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <string>
#include <cmath>
#include <ctime>

namespace alford_steven {
	// The name of the agent to be displayed in the tournament
	const std::string agent::agent_name = "Agent 47";

	// Initializes the agent
	agent::agent(player c) : color(c)
	{
		// Now initialized: color value (white, black)
		// Stupid agent, no initialization necessary
	}
	
	// A method to get the opponent of the player
	player agent::get_opponent(player p)
	{
		player opponent;

		// Determine the opponent's pawn
		if(p == 'w')
		{	opponent = (player) 'b';	}
		else
		{	opponent = (player) 'w';	}

		return opponent;
	}

	// Takes the current board and returns the result after a move
	// has been made by a player
	isola agent::future_board(isola board, player p, direction future_move)
	{
		isola new_board = board;
		new_board.move(p, future_move, location_to_remove(board, p, future_move));

		return new_board;
	}

	// Counts from 0, 0 to max_rows(), max_cols() and determines
	// the total number of blank spaces (effectively number of
	// moves left for both players) and returns that number
	int agent::blank_spaces(isola board)
	{
		int num_spaces = 0;

		// For a row
		for(unsigned i = 0; i < board.max_rows(); i++)
		{
			// For a column
			for(unsigned j = 0; j < board.max_cols(); j++)
			{
				// If the space does not contain a player
				// or has not been removed, increment
				if(board[i][j] != 'X' && board[i][j] != 'b' && board[i][j] != 'w')
				{
					num_spaces++;
				}
			}
		}

		return num_spaces;
	}

	// Using the number of moves the player and their opponent has 
	// and restricting the aggressiveness of the next move based on
	// the number of blank spaces available, return the score of a
	// current position on the board
	double agent::get_score(isola board, player p)
	{
		double score = 0;

		// Legal moves for the player and their opponent
		int player_moves = legal_moves(board, p);
		int opponent_moves = legal_moves(board, get_opponent(p));

		// If there are more than 60% of the blank spaces remaining,
		// aggressively evaluate moves based on an opponent's moves
		// being worth 3 times as much
		if(blank_spaces(board) >= (ceil((board.max_cols() * board.max_rows() - 2) * 0.6)))
		{
			score = player_moves - (3 * opponent_moves);
		}
		// If there are more than 30% of the blank spaces remaining,
		// moderately evaluate moves based on an opponent's moves
		// being worth 2 times as much
		else if(blank_spaces(board) >= (ceil((board.max_cols() * board.max_rows() - 2) * 0.3)))
		{
			score = player_moves - (2 * opponent_moves);
		}
		// If there are less than 30% of the blank spaces remaining,
		// evaluate moves based on an opponent's moves being worth
		// exactly the same as the player's.
		else
		{
			score = player_moves - opponent_moves;
		}

		return score;
	}

	// Gets the number of legal moves that the player has from
	// a given position
	int agent::legal_moves(isola board, player p)
	{
		int legal_moves = 0;

		if(board.legal_move(p, north))
		{	legal_moves += 1;		}

		if(board.legal_move(p, south))
		{	legal_moves += 1;		}

		if(board.legal_move(p, east))
		{	legal_moves += 1;		}

		if(board.legal_move(p, west))
		{	legal_moves += 1;		}

		if(board.legal_move(p, northeast))
		{	legal_moves += 1;		}

		if(board.legal_move(p, northwest))
		{	legal_moves += 1;		}

		if(board.legal_move(p, southeast))
		{	legal_moves += 1;		}

		if(board.legal_move(p, southwest))
		{	legal_moves += 1;		}
		
		return legal_moves;
	}

	// Minimax function using alpha/beta pruning
	//
	// Checks through the possible board states up to a given depth
	// and evaluates them using the minimax function, pruning worse
	// states using alpha/beta pruning
	direction agent::minimax(isola board, player p, int depth, double alpha, double beta)
	{
		double best_score = -1000000000;
		direction best_move;
		double min_score;

		// If a move is legal, recursively loop through the possible moves,
		// min-ing and max-ing alternatively until the given depth is reached
		// then compare up through the tree to get the best possible move at
		// the current position
		if(board.legal_move(p, north))
		{
			min_score = min_value(future_board(board, p, north), p, depth - 1, alpha, beta);
			if(min_score > best_score)
			{
				best_score = min_score;
				best_move  = north;
			}

			if(best_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, best_score);	}
		}

		if(board.legal_move(p, south))
		{
			min_score = min_value(future_board(board, p, south), p, depth - 1, alpha, beta);
			if(min_score > best_score)
			{
				best_score = min_score;
				best_move  = south;
			}

			if(best_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, best_score);	}
		}

		if(board.legal_move(p, east))
		{
			min_score = min_value(future_board(board, p, east), p, depth - 1, alpha, beta);
			if(min_score > best_score)
			{
				best_score = min_score;
				best_move  = east;
			}

			if(best_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, best_score);	}
		}

		if(board.legal_move(p, west))
		{
			min_score = min_value(future_board(board, p, west), p, depth - 1, alpha, beta);
			if(min_score > best_score)
			{
				best_score = min_score;
				best_move  = west;
			}

			if(best_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, best_score);	}
		}

		if(board.legal_move(p, northeast))
		{
			min_score = min_value(future_board(board, p, northeast), p, depth - 1, alpha, beta);
			if(min_score > best_score)
			{
				best_score = min_score;
				best_move  = northeast;
			}

			if(best_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, best_score);	}
		}
	
		if(board.legal_move(p, northwest))
		{
			min_score = min_value(future_board(board, p, northwest), p, depth - 1, alpha, beta);
			if(min_score > best_score)
			{
				best_score = min_score;
				best_move  = northwest;
			}

			if(best_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, best_score);	}
		}
	
		if(board.legal_move(p, southeast))
		{
			min_score = min_value(future_board(board, p, southeast), p, depth - 1, alpha, beta);
			if(min_score > best_score)
			{
				best_score = min_score;
				best_move  = southeast;
			}

			if(best_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, best_score);	}
		}
	
		if(board.legal_move(p, southwest))
		{
			min_score = min_value(future_board(board, p, southwest), p, depth - 1, alpha, beta);
			if(min_score > best_score)
			{
				best_score = min_score;
				best_move  = southwest;
			}

			if(best_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, best_score);	}
		}

		return best_move;
	}

	// Determines the minimum value for a given depth
	double agent::min_value(isola board, player p, int depth, double alpha, double beta)
	{
		double min_score = 1000000000;
		double max_score;

		// Base case: if depth is 0, or if there are no legal moves left
		if(depth == 0 || legal_moves(board, p) == 0)
		{
			return get_score(board, p);
		}

		if(board.legal_move(p, north))
		{
			max_score = max_value(future_board(board, p, north), p, depth - 1, alpha, beta);
			min_score = std::min(min_score, max_score);

			if(min_score <= alpha)
			{}
			else
			{	beta = std::min(beta, min_score);	}
		}

		if(board.legal_move(p, south))
		{
			max_score = max_value(future_board(board, p, south), p, depth - 1, alpha, beta);
			min_score = std::min(min_score, max_score);

			if(min_score <= alpha)
			{}
			else
			{	beta = std::min(beta, min_score);	}
		}

		if(board.legal_move(p, east))
		{
			max_score = max_value(future_board(board, p, east), p, depth - 1, alpha, beta);
			min_score = std::min(min_score, max_score);

			if(min_score <= alpha)
			{}
			else
			{	beta = std::min(beta, min_score);	}
		}

		if(board.legal_move(p, west))
		{
			max_score = max_value(future_board(board, p, west), p, depth - 1, alpha, beta);
			min_score = std::min(min_score, max_score);

			if(min_score <= alpha)
			{}
			else
			{	beta = std::min(beta, min_score);	}
		}

		if(board.legal_move(p, northeast))
		{
			max_score = max_value(future_board(board, p, northeast), p, depth - 1, alpha, beta);
			min_score = std::min(min_score, max_score);

			if(min_score <= alpha)
			{}
			else
			{	beta = std::min(beta, min_score);	}
		}

		if(board.legal_move(p, northwest))
		{
			max_score = max_value(future_board(board, p, northwest), p, depth - 1, alpha, beta);
			min_score = std::min(min_score, max_score);

			if(min_score <= alpha)
			{}
			else
			{	beta = std::min(beta, min_score);	}
		}

		if(board.legal_move(p, southeast))
		{
			max_score = max_value(future_board(board, p, southeast), p, depth - 1, alpha, beta);
			min_score = std::min(min_score, max_score);

			if(min_score <= alpha)
			{}
			else
			{	beta = std::min(beta, min_score);	}
		}

		if(board.legal_move(p, southwest))
		{
			max_score = max_value(future_board(board, p, southwest), p, depth - 1, alpha, beta);
			min_score = std::min(min_score, max_score);

			if(min_score <= alpha)
			{}
			else
			{	beta = std::min(beta, min_score);	}
		}

		return min_score;
	}

	// Determines the maximum value for a given depth
	double agent::max_value(isola board, player p, int depth, double alpha, double beta)
	{
		double max_score = -1000000000;
		double min_score;

		// Base case: if depth is 0, or if there are no legal moves left
		if(depth == 0 || legal_moves(board, p) == 0)
		{
			return get_score(board, p);
		}

		if(board.legal_move(p, north))
		{
			min_score = min_value(future_board(board, p, north), p, depth - 1, alpha, beta);
			max_score = std::max(max_score, min_score);

			if(max_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, max_score);		}
		}

		if(board.legal_move(p, south))
		{
			min_score = min_value(future_board(board, p, south), p, depth - 1, alpha, beta);
			max_score = std::max(max_score, min_score);

			if(max_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, max_score);		}
		}

		if(board.legal_move(p, east))
		{
			min_score = min_value(future_board(board, p, east), p, depth - 1, alpha, beta);
			max_score = std::max(max_score, min_score);

			if(max_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, max_score);		}
		}

		if(board.legal_move(p, west))
		{
			min_score = min_value(future_board(board, p, west), p, depth - 1, alpha, beta);
			max_score = std::max(max_score, min_score);

			if(max_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, max_score);		}
		}

		if(board.legal_move(p, northeast))
		{
			min_score = min_value(future_board(board, p, northeast), p, depth - 1, alpha, beta);
			max_score = std::max(max_score, min_score);

			if(max_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, max_score);		}
		}

		if(board.legal_move(p, northwest))
		{
			min_score = min_value(future_board(board, p, northwest), p, depth - 1, alpha, beta);
			max_score = std::max(max_score, min_score); 
		}

		if(board.legal_move(p, southeast))
		{
			min_score = min_value(future_board(board, p, southeast), p, depth - 1, alpha, beta);
			max_score = std::max(max_score, min_score);

			if(max_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, max_score);		}
		}

		if(board.legal_move(p, southwest))
		{
			min_score = min_value(future_board(board, p, southwest), p, depth - 1, alpha, beta);
			max_score = std::max(max_score, min_score);

			if(max_score >= beta)
			{}
			else
			{	alpha = std::max(alpha, max_score);		}
		}

		return max_score;
	}

	// Determines the best location to remove from the board
	// Finds a move close to the enemy player and removes it
	// The order is as follows: N, NE, NW, E, W, S, SE, SW
	location agent::location_to_remove(isola board, player color, direction move_to)
	{
		location to_remove;
		player opponent = get_opponent(color);

		if(board.legal_move(opponent, north, board.new_location(color, move_to)))
		{
			to_remove = board.new_location(opponent, north);
			return to_remove;
		}
		else if(board.legal_move(opponent, northeast, board.new_location(color, move_to)))
		{
			to_remove = board.new_location(opponent, northeast);
			return to_remove;
		}
		else if(board.legal_move(opponent, northwest, board.new_location(color, move_to)))
		{
			to_remove = board.new_location(opponent, northwest);
			return to_remove;
		}
		else if(board.legal_move(opponent, east, board.new_location(color, move_to)))
		{
			to_remove = board.new_location(opponent, east);
			return to_remove;
		}
		else if(board.legal_move(opponent, west, board.new_location(color, move_to)))
		{
			to_remove = board.new_location(opponent, west);
			return to_remove;
		}
		else if(board.legal_move(opponent, south, board.new_location(color, move_to)))
		{
			to_remove = board.new_location(opponent, south);
			return to_remove;
		}
		else if(board.legal_move(opponent, southeast, board.new_location(color, move_to)))
		{
			to_remove = board.new_location(opponent, southeast);
			return to_remove;
		}
		else if(board.legal_move(opponent, southwest, board.new_location(color, move_to)))
		{
			to_remove = board.new_location(opponent, southwest);
			return to_remove;
		}
		// If no move around the other player can be found,
		// find the first open space and remove it, starting at
		// 0, 0 and looping through the entire board
		else
		{
			// Find the first square that is valid to remove, starting with 0,0
			// Once found, return immediately
			for(unsigned i = 0; i < board.max_rows(); i++)
			{
				for(unsigned j = 0; j < board.max_cols(); j++)
				{
					if(board.legal_move(color, move_to, location(i, j)))
					{
						to_remove.row = i;
						to_remove.col = j;

						// Return found move
						return to_remove;
					}
				}
			}
		}

		return to_remove;
	}

	// Main driver for the agent
	// Calls minimax and the remove function
	action agent::next_move(isola current_board)
	{
		// The direction the pawn will move
		direction pawn_direction;

		// The location to remove from the play field
		location to_remove;

		// Depth the minimax function will search to
		int iterative_depth = 6;
		
		// Initializes alpha and beta values
		double alpha = -1000000000;
		double beta = 1000000000;

		// Calls minimax to determine the next move for the player
		pawn_direction = minimax(current_board, color, iterative_depth, alpha, beta);
		
		// Calls the remove function to determine the next space
		// to remove from the board
		to_remove = location_to_remove(current_board, color, pawn_direction);

		return action(pawn_direction, to_remove);
	}
}