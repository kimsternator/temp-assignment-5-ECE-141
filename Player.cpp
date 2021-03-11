//
//  Player.cpp
//  Checkers
//
//  Created by rick gessner on 2/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Player.hpp"
#include "Game.hpp"

namespace ECE141 {

  int Player::pcount = 0; //init our static member to track # of players...

  static PieceColor autoColor() { //auto assigns a color
    return (++Player::pcount % 2) ? PieceColor::blue : PieceColor::gold;
  }

  Player::Player() : color(autoColor()) {}

  bool Player::takeTurn(Game &aGame, Orientation aDirection, std::ostream &aLog) {
    size_t theCount=aGame.countAvailablePieces(color);
    std::cout << ((this->color == PieceColor::blue) ? "blue" : "gold") << std::endl;
//    std::cout << "post" << std::endl;
//    int post;
//    int x, y;
//    std::cin >> post;
//    std::cout << "x" << std::endl;
//    std::cin >> x;
//    std::cout << "y" << std::endl;
//    std::cin >> y;
    for(int pos=0;pos<theCount;pos++) {
        if(const Piece *thePiece = aGame.getAvailablePiece(this->color, pos)) {
//            if(pos == post) {
//                aGame.movePieceTo(*thePiece, Location(x,y));
//                return true;
//            }
//            return false;
        }
      /*
       //NOTICE HOW WE CHECK FOR CAPTURED PIECES?
       if(const Piece *thePiece = aGame.getAvailablePiece(this->color, pos)) {
       // 1 get the game state into an object
       // 2 plug in minimax algorithm
       // 3 return highest score move
         //add logic here to find your best move, then move ONE piece per turn...

         aGame.movePieceTo(*thePiece, Location(1,2)); -- choose wisely...
         aGame.movePieceTo(state->original, state->pieceMove->getLocation());
       }
      */
    }

    /* size_t theCountOther = aGame.countAvailablePieces((pcount % 2) ? PieceColor::blue : PieceColor::gold);
     *
     */
    return false; //if you return false, you forfeit!
  }
}
