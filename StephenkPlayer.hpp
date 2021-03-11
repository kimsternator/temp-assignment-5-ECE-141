//
// Created by Stephen on 3/7/2021.
//

#ifndef ECE141A_STEPHENKPLAYER_HPP
#define ECE141A_STEPHENKPLAYER_HPP

#include "Player.hpp"
#include "GameState.hpp"
#include <vector>

namespace ECE141 {
    class StephenkPlayer : public Player {
    public:
        StephenkPlayer() : Player() {}

        bool takeTurn(Game &aGame, Orientation aDirection, std::ostream &aLog);
    };
}


#endif //ECE141A_STEPHENKPLAYER_HPP
