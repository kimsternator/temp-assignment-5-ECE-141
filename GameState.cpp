//
// Created by Stephen on 3/7/2021.
//

#include "GameState.hpp"
#include <algorithm>
namespace ECE141 {
    bool GameState::gameOver() {
        return this->bluePieces.size() == 0 || this->goldPieces.size() == 0;
    }

    GameState::GameState(const ECE141::GameState &aCopy) {
        for (int i = 0; i < aCopy.board.size(); i++) {
            std::vector<NewPiece *> row;

            for (int j = 0; j < aCopy.board[0].size(); j++)
                if (aCopy.board[i][j] != nullptr)
                    row.push_back(new NewPiece(aCopy.board[i][j]->getColor(),
                                               aCopy.board[i][j]->getTile(),
                                               aCopy.board[i][j]->getKind()));
                else
                    row.push_back(nullptr);

            board.push_back(row);
        }

        for (auto piece: aCopy.bluePieces)
            bluePieces.push_back(new NewPiece(piece->getColor(), piece->getTile(), piece->getKind()));

        for (auto piece: aCopy.goldPieces)
            goldPieces.push_back(new NewPiece(piece->getColor(), piece->getTile(), piece->getKind()));
    }

    std::vector<GameState *> GameState::getMoves(PieceColor color) { // need to implement jump move check
        std::vector<GameState *> children;
        // check this for jump flag
        //if flag not true
        if (color == PieceColor::blue) {
            for (auto piece: this->bluePieces)
                for (auto move: getPieceMoves(piece))
                    children.push_back(move);
        } else {
            for (auto piece: this->goldPieces)
                for (auto move: getPieceMoves(piece))
                    children.push_back(move);
        }
        // else flag is false
        //      piece = this-> getCurPiece()
        //      

        return children;
    }



    std::vector<GameState *> GameState::getPieceMoves(NewPiece *aPiece) {
        std::vector<GameState *> moves;
//        std::vector<std::pair<Location *, bool>> locationMoves; // <Location, jump flag>
        std::vector<Location *> locationMoves;


        // have all avail locations
        Location *upLeft = new Location(aPiece->getLocation().row - 1, aPiece->getLocation().col - 1);
        Location *upRight = new Location(aPiece->getLocation().row - 1, aPiece->getLocation().col + 1);
        Location *downLeft = new Location(aPiece->getLocation().row + 1, aPiece->getLocation().col - 1);
        Location *downRight = new Location(aPiece->getLocation().row + 1, aPiece->getLocation().col + 1);
        std::vector<Location*> locations = {upLeft,upRight,downLeft,downRight};

        for (auto loc : locations) {
            if (check_if_can_add_move(aPiece,loc)) {
                GameState* aGameState = new GameState(*this);
                // remove piece from old position
                auto oldLocation = aPiece->getLocation();
                aGameState->board[oldLocation.row][oldLocation.col] = nullptr;
                // move piece to new position
                aGameState->board[loc->row][loc->col] = aPiece;
                // if there was  a jump remove conquered piece
                if (std::abs(oldLocation.row-loc->row) ==2) {
                    // change piece location
                    int delrow = oldLocation.row + (loc->row - oldLocation.row) / 2;
                    int delcol = oldLocation.col + (loc->col- oldLocation.col) / 2;
                    // remove piece from the teams pieces
                    auto pieceToDelete = this->board[delrow][delcol];
                    if (pieceToDelete->getColor() == PieceColor::blue) {
                        auto foundPiece = std::find(aGameState->bluePieces.begin(),aGameState->bluePieces.end(),pieceToDelete );
                        if(foundPiece != aGameState->bluePieces.end()) {
                            delete *foundPiece;
                            aGameState->bluePieces.erase(foundPiece);
                        }
                    }
                    else {
                        auto foundPiece = std::find(aGameState->goldPieces.begin(),aGameState->goldPieces.end(),pieceToDelete );
                        if(foundPiece != aGameState->goldPieces.end()) {
                            delete *foundPiece;
                            aGameState->goldPieces.erase(foundPiece);
                        }
                    }
                    delete this->board[delrow][delcol];
                }
            }

        }

        return moves;
    }

    bool GameState::validMove(NewPiece* aPiece, Location* location) {
        return (validLocation(location) && validateMove(location,aPiece->getColor()));
    }
    bool GameState::check_if_can_add_move(NewPiece* aPiece, Location* location) {
        if (!validLocation(location)) return false;
        if(!isValidDirection(aPiece,aPiece->getLocation(),location)) return false;
        if (this->board[location->row][location->col] == nullptr) return true; //assuming board is nullptr in i,j th spot if no piece
        if (this->board[location->row][location->col]->getColor() == aPiece->getColor()) return false;
        location->row +=  aPiece->getLocation().row -  location->row;
        location->col +=  aPiece->getLocation().col -  location->col;
        if (!validLocation(location)) return false;
        if (this->board[location->row][location->col] == nullptr) return true; //assuming board is nullptr in i,j th spot if no piece
        return false;
    }
}