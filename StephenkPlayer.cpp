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
                NewPiece* aPiece = new NewPiece(thePiece->getColor(), thePiece->getLocation(), thePiece->getKind());
                board[location.row][location.col] = aPiece;

                if(aPiece->color == PieceColor::blue) {
                    state->bluePieces.push_back(aPiece);
                }
                else {
                    state->goldPieces.push_back(aPiece);
                }
            }
        }

        size_t theOtherCount=aGame.countAvailablePieces((this->color == PieceColor::blue) ? PieceColor::gold : PieceColor::blue);
        for(int pos=0;pos<theOtherCount;pos++) {
            if (const Piece *thePiece = aGame.getAvailablePiece((this->color == PieceColor::blue) ? PieceColor::gold : PieceColor::blue, pos)) {
                auto location = thePiece->getLocation();
                NewPiece* aPiece = new NewPiece(thePiece->getColor(), thePiece->getLocation(), thePiece->getKind());
                board[location.row][location.col] = aPiece;

                if(aPiece->color == PieceColor::gold) {
                    state->goldPieces.push_back(aPiece);
                }
                else {
                    state->bluePieces.push_back(aPiece);
                }
            }
        }


        state->board = board;
//        std::cout << "\nhere";
//        std::cout << "\n" << state->score() << std::endl;
        /*
         *       Game state is now initalized with state of real game
        */

        CheckersMinimax* mm = new CheckersMinimax(this->color);

//        if(this->count == 2)
//            std::cout << "here" << std::endl;

        state = mm->minimax(state, 1, 0, 0, 1);
        std::cout << "finished planning" << std::endl;
        if(this->color == PieceColor::blue) {
            for(int pos=0;pos<theCount;pos++) {
                if(aGame.getAvailablePiece(this->color, pos)->getLocation().row == state->original->getLocation().row) {
                    if(aGame.getAvailablePiece(this->color, pos)->getLocation().col == state->original->getLocation().col) {
                        std::cout << "blue" << std::endl;
                        std::cout << "(" << aGame.getAvailablePiece(this->color, pos)->getLocation().row <<
                        "," << aGame.getAvailablePiece(this->color, pos)->getLocation().col << ") -> (" <<
                        state->pieceMove->row << "," << state->pieceMove->col << ")" << std::endl;
                        std::cout << "move " << this->count++ << std::endl;
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
                        std::cout << "gold" << std::endl;
                        std::cout << "(" << aGame.getAvailablePiece(this->color, pos)->getLocation().row <<
                                  "," << aGame.getAvailablePiece(this->color, pos)->getLocation().col << ") -> (" <<
                                  state->pieceMove->row << "," << state->pieceMove->col << ")" << std::endl;
                        std::cout << "move " << this->count++ << std::endl;
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
            state = mm->minimax(state, 1, 0, 0, 1);
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

        std::cout << std::endl;
        return true;
        return false; //if you return false, you forfeit!
    }
}


