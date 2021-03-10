//
// Created by Stephen on 3/8/2021.
//

#ifndef ECE141A_CHECKERSMINIMAX_HPP
#define ECE141A_CHECKERSMINIMAX_HPP

#include "GameState.hpp"

namespace ECE141 {
    class CheckersMinimax {
    public:
        CheckersMinimax()=default;

        GameState* minimax(GameState *state, int depth, int alpha, int beta, int maximizingPlayer);
};
}


#endif //ECE141A_CHECKERSMINIMAX_HPP
