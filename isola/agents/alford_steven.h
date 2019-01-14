/* Name: Steven Alford
 * Date: 11/10/18
 * File: alford_steven.h
 * Desc: An isola agent that utilizes the minimax function
 * 	 with alpha/beta pruning to determine a best move
 *	 from a given position.
 */

#ifndef ALFORD_STEVEN_H
#define ALFORD_STEVEN_H

#include "../isola.h" // Game logic (required as a parameter to next_move)
#include "../types.h" // Isola/tournament types.

namespace alford_steven {
	class agent {
	private:
		player color; // Required
		const static std::string agent_name; // Required
    
	public:
		agent(player c); // Required
		action next_move(isola current_board); // Required
		location location_to_remove(isola board, player color, direction move_to);
		isola future_board(isola board, player p, direction future_move);
		int blank_spaces(isola board);
		direction minimax(isola board, player p, int depth, double alpha, double beta);
		double min_value(isola board, player p, int depth, double alpha, double beta);
		double max_value(isola board, player p, int depth, double alpha, double beta);
		double get_score(isola board, player p);
		int legal_moves(isola board, player p);
		player get_opponent(player p);
		std::string name() { return agent_name; } // Required
	};
}

#endif