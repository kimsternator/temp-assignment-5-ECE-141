//
// Created by Stephen on 3/8/2021.
//

#include "CheckersMinimax.hpp"

namespace ECE141 {
    int CheckersMinimax::minimax(GameState *state, int depth, int alpha, int beta, int maximizingPlayer) {
        if(depth == 0 || state->gameOver())
            return state->score();

        if(this->playerColor == PieceColor::gold)
            state->stateColor = (maximizingPlayer == 0) ? PieceColor::blue : PieceColor::gold;
        else
            state->stateColor = (maximizingPlayer == 0) ? PieceColor::gold : PieceColor::blue;

        state->getMoves();

        if(maximizingPlayer) {
            int maxEval = -100;

            for(auto child: state->possibleMoves) {
                child->getMoves();
                int eval = minimax(child, depth - 1, alpha, beta, 0);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
//                if(beta <= alpha) break;
            }

            return maxEval;
        }
        else {
            int minEval = 100;

            for(auto child: state->possibleMoves) {
                child->getMoves();
                int eval = minimax(child, depth - 1, alpha, beta, 1);
                minEval = std::min(minEval, eval);
                alpha = std::min(alpha, eval);
//                if(beta <= alpha) break;
            }

            return minEval;
        }
    }
}