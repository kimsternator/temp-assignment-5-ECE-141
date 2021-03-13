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

                if(aPiece->color == PieceColor::blue)
                    state->bluePieces.push_back(aPiece);
                else
                    state->goldPieces.push_back(aPiece);
            }
        }

        size_t theOtherCount=aGame.countAvailablePieces((this->color == PieceColor::blue) ? PieceColor::gold : PieceColor::blue);
        for(int pos=0;pos<theOtherCount;pos++) {
            if (const Piece *thePiece = aGame.getAvailablePiece((this->color == PieceColor::blue) ? PieceColor::gold : PieceColor::blue, pos)) {
                auto location = thePiece->getLocation();
                NewPiece* aPiece = new NewPiece(thePiece->getColor(), thePiece->getLocation(), thePiece->getKind());
                board[location.row][location.col] = aPiece;

                if(aPiece->color == PieceColor::gold)
                    state->goldPieces.push_back(aPiece);
                else
                    state->bluePieces.push_back(aPiece);
            }
        }


        state->board = board;
        /*
         *       Game state is now initalized with state of real game
        */

        CheckersMinimax* mm = new CheckersMinimax(this->color);
        GameState* theMove = mm->minimax(state, 1, 0, 0, 1);
        std::cout << "finished planning" << std::endl;
        size_t mergeCount = (this->color == PieceColor::blue) ? theCount : theOtherCount;

        for(int pos=0;pos<mergeCount;pos++) {
            if(aGame.getAvailablePiece(this->color, pos)->getLocation().row == theMove->original->getLocation().row) {
                if(aGame.getAvailablePiece(this->color, pos)->getLocation().col == theMove->original->getLocation().col) {
                    std::cout << ((this->color == PieceColor::blue) ? "blue" : "gold") << std::endl;
                    std::cout << "(" << aGame.getAvailablePiece(this->color, pos)->getLocation().row <<
                    "," << aGame.getAvailablePiece(this->color, pos)->getLocation().col << ") -> (" <<
                    theMove->pieceMove->row << "," << theMove->pieceMove->col << ")" << std::endl;
                    std::cout << "move " << this->count << std::endl;
                    aGame.movePieceTo(*(aGame.getAvailablePiece(this->color, pos)), *(theMove->pieceMove));
                    break;
                }
            }
        }
        std::cout << "made move" << std::endl;
        std::cout << std::endl;


        //need to debug here now
        //need to fix copy of gamestate between blue/gold datamembers
        //they are supposed to all be linked
        while(std::abs(theMove->original->getLocation().row - theMove->pieceMove->row) == 2) {
            auto anotherMove = mm->minimax(theMove, 1, 0, 0, 1);

            if(std::abs(anotherMove->original->getLocation().row - anotherMove->pieceMove->row) == 2) {
                for (int pos = 0; pos < mergeCount; pos++) {
                    if (aGame.getAvailablePiece(this->color, pos)->getLocation().row ==
                            anotherMove->original->getLocation().row) {
                        if (aGame.getAvailablePiece(this->color, pos)->getLocation().col ==
                            anotherMove->original->getLocation().col) {
                            std::cout << ((this->color == PieceColor::blue) ? "blue" : "gold") << std::endl;
                            std::cout << "(" << aGame.getAvailablePiece(this->color, pos)->getLocation().row <<
                            "," << aGame.getAvailablePiece(this->color, pos)->getLocation().col << ") -> (" <<
                            anotherMove->pieceMove->row << "," << anotherMove->pieceMove->col << ")" << std::endl;
                            std::cout << "another move " << this->count << std::endl;
                            std::cout << std::endl;
                            aGame.movePieceTo(*(aGame.getAvailablePiece(this->color, pos)), *(anotherMove->pieceMove));
                            break;
                        }
                    }
                }

                theMove = anotherMove;
            }
            else
                break;
        }

        this->count++;

        delete state;
        delete mm;

        return true;
        return false; //if you return false, you forfeit!
    }
}


