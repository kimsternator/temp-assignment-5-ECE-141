//
// Created by Stephen on 3/8/2021.
//

#ifndef ECE141A_CHECKERSMINIMAX_HPP
#define ECE141A_CHECKERSMINIMAX_HPP

#include "GameState.hpp"
#include "StephenkPlayer.hpp"

namespace ECE141 {
    class CheckersMinimax {
    public:
        CheckersMinimax()=default;

        ~CheckersMinimax()=default;

        CheckersMinimax(PieceColor aColor) {
            playerColor = aColor;
        }

        int minimax(GameState *state, int depth, int alpha, int beta, int maximizingPlayer);

        PieceColor playerColor;
};
}


#endif //ECE141A_CHECKERSMINIMAX_HPP
