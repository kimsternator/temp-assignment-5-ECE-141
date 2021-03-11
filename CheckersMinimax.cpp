//
// Created by Stephen on 3/8/2021.
//

#include "CheckersMinimax.hpp"

namespace ECE141 {
    GameState* CheckersMinimax::minimax(GameState *state, int depth, int alpha, int beta, int maximizingPlayer) {
        if(depth == 0 || state->gameOver())
            return state;

        if(this->playerColor == PieceColor::gold)
            state->stateColor = (maximizingPlayer == 0) ? PieceColor::blue : PieceColor::gold;
        else
            state->stateColor = (maximizingPlayer == 0) ? PieceColor::gold : PieceColor::blue;

        state->getMoves(state->stateColor);

        if(maximizingPlayer) {
            int maxEval = -100;
            GameState* maxState = nullptr;

            for(auto child: state->possibleMoves) {
                auto eval = minimax(child, depth - 1, alpha, beta, 0);
                int temp = maxEval;
                maxEval = std::max(maxEval, eval->score());
                alpha = std::max(alpha, eval->score());

                if(temp != maxEval) maxState = eval;
                if(beta <= alpha) break;
            }

            return maxState;
        }
        else {
            int minEval = 100;
            GameState* minState = nullptr;

            for(auto child: state->possibleMoves) {
                auto eval = minimax(child, depth - 1, alpha, beta, 1);
                int temp = minEval;
                minEval = std::min(minEval, eval->score());
                alpha = std::min(alpha, eval->score());

                if(temp != minEval) minState = eval;
                if(beta <= alpha) break;
            }

            return minState;
        }
    }
}