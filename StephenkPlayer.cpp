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

        CheckersMinimax* mm = new CheckersMinimax(this->color);

        if(this->count == 2)
            std::cout << "here" << std::endl;

        state = mm->minimax(state, 3, 0, 0, 1);
        std::cout << "finished planning" << std::endl;
        if(this->color == PieceColor::blue) {
            for(int pos=0;pos<theCount;pos++) {
                if(aGame.getAvailablePiece(this->color, pos)->getLocation().row == state->original->getLocation().row) {
                    if(aGame.getAvailablePiece(this->color, pos)->getLocation().col == state->original->getLocation().col) {
                        std::cout << "(" << aGame.getAvailablePiece(this->color, pos)->getLocation().row <<
                        "," << aGame.getAvailablePiece(this->color, pos)->getLocation().col << ") -> (" <<
                        state->pieceMove->row << "," << state->pieceMove->col << std::endl;
                        this->count++;
                        aGame.movePieceTo(*(aGame.getAvailablePiece(this->color, pos)), *(state->pieceMove));
                        break;
                    }
                }
            }
        }
        else {
            for(int pos=0;pos<theOtherCount;pos++) {
                if(aGame.getAvailablePiece(this->color, pos)->getLocation().row == state->original->getLocation().row) {
                    if(aGame.getAvailablePiece(this->color, pos)->getLocation().col == state->original->getLocation().col) {
                        std::cout << "(" << aGame.getAvailablePiece(this->color, pos)->getLocation().row <<
                                  "," << aGame.getAvailablePiece(this->color, pos)->getLocation().col << ") -> (" <<
                                  state->pieceMove->row << "," << state->pieceMove->col << std::endl;
                        this->count++;
                        aGame.movePieceTo(*(aGame.getAvailablePiece(this->color, pos)), *(state->pieceMove));
                        break;
                    }
                }
            }
        }
        std::cout << "made move" << std::endl;

        while(state->jumpFlag) {
            for(auto move: state->possibleMoves)
                delete move;

            state->possibleMoves.clear();
            state = mm->minimax(state, 3, 0, 0, 1);
            // just the logic to move the darn piece
            if(this->color == PieceColor::blue) {
                for(int pos=0;pos<theCount;pos++) {
                    if(aGame.getAvailablePiece(this->color, pos)->getLocation().row == state->original->getLocation().row) {
                        if(aGame.getAvailablePiece(this->color, pos)->getLocation().col == state->original->getLocation().col) {
                            aGame.movePieceTo(*(aGame.getAvailablePiece(this->color, pos)), *(state->pieceMove));
                            break;
                        }
                    }
                }
            }
            else {
                for(int pos=0;pos<theOtherCount;pos++) {
                    if(aGame.getAvailablePiece(this->color, pos)->getLocation().row == state->original->getLocation().row) {
                        if(aGame.getAvailablePiece(this->color, pos)->getLocation().col == state->original->getLocation().col) {
                            aGame.movePieceTo(*(aGame.getAvailablePiece(this->color, pos)), *(state->pieceMove));
                            break;
                        }
                    }
                }
            }
            // end the dumb logic
        }

        delete state;

        return true;
        return false; //if you return false, you forfeit!
    }
}


