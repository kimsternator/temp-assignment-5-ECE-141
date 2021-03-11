//
// Created by Stephen on 3/7/2021.
//

#include "Game.hpp"
#include "StephenkPlayer.hpp"


namespace ECE141 {

    bool StephenkPlayer::takeTurn(Game &aGame, Orientation aDirection, std::ostream &aLog) {
        GameState *state = new GameState();
        std::vector<std::vector<NewPiece*>> board(Game::kBoardHeight, std::vector<NewPiece*>(Game::kBoardHeight, nullptr));
        size_t theCount=aGame.countAvailablePieces(this->color);
        for(int pos=0;pos<theCount;pos++) {
            if(const Piece *thePiece = aGame.getAvailablePiece(this->color, pos)) {
                auto location = thePiece->getLocation();
                NewPiece* aPiece = new NewPiece(thePiece->getColor(), const_cast<Tile*>(thePiece->getTile()), thePiece->getKind());
                board[location.row][location.col] = aPiece;

                if(this->color == PieceColor::blue) {
                    state->bluePieces.push_back(aPiece);
                }
                else {
                    state->goldPieces.push_back(aPiece);
                }
            }
            /*
             //NOTICE HOW WE CHECK FOR CAPTURED PIECES?
             if(const Piece *thePiece = aGame.getAvailablePiece(this->color, pos)) {
             // 1 get the game state into an object
             // 2 plug in minimax algorithm
             // 3 return highest score move
               //add logic here to find your best move, then move ONE piece per turn...

               aGame.movePieceTo(*thePiece, Location(1,2)); -- choose wisely...
             }
            */
        }

        size_t theOtherCount=aGame.countAvailablePieces((this->color == PieceColor::blue) ? PieceColor::gold : this->color);
        for(int pos=0;pos<theOtherCount;pos++) {
            if (const Piece *thePiece = aGame.getAvailablePiece((this->color == PieceColor::blue) ? PieceColor::gold : this->color, pos)) {
                auto location = thePiece->getLocation();
                NewPiece* aPiece = new NewPiece(thePiece->getColor(), const_cast<Tile*>(thePiece->getTile()), thePiece->getKind());
                board[location.row][location.col] = aPiece;

                if(this->color == PieceColor::blue) {
                    state->goldPieces.push_back(aPiece);
                }
                else {
                    state->bluePieces.push_back(aPiece);
                }
            }
        }


        state->board = board;
        std::cout << "\nhere";
        std::cout << "\n" << state->score() << std::endl;
        /*
         *       Game state is now initalized with state of real game
        */


        /* TOP LEVEL
         * BLUE PLAYER
         * vector of all BLUE pieces that can move
         * [P1L, P1R,
         *
         * auto maxScoringMove;
         * vector of all blue moves gamestates
         * for each blue move:
         *   if minimax(move) > maxScoringMove;
         *
         */



        /* auto maxPiece = P(1, 2)l
         *  vector (piece moves, (ie P(1, 2) ~ [P(0, 3), P(0, 1),.....
         *  aGame.movePieceTo(aGameindex(state->bluePieces(maxPiece)), Location(1,2));
         */
        /* size_t theCountOther = aGame.countAvailablePieces((pcount % 2) ? PieceColor::blue : PieceColor::gold);
         *
         */
        return false; //if you return false, you forfeit!
    }
}


