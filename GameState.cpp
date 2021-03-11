//
// Created by Stephen on 3/7/2021.
//

#include "GameState.hpp"

namespace ECE141 {
    bool NewPiece::operator==(ECE141::NewPiece aNewPiece) const {
        if(this->hasColor(aNewPiece.getColor()))
            if(this->getLocation().row == aNewPiece.getLocation().row)
                if(this->getLocation().col == aNewPiece.getLocation().col)
                    return true;

        return false;
    }

    bool GameState::gameOver() {
        return this->bluePieces.empty() || this->goldPieces.empty();
    }

    GameState::GameState(const ECE141::GameState &aCopy) {
        for (int i = 0; i < aCopy.board.size(); i++) {
            std::vector<NewPiece *> row;

            for (int j = 0; j < aCopy.board[0].size(); j++)
                if (aCopy.board[i][j] != nullptr)
                    row.push_back(new NewPiece(aCopy.board[i][j]->getColor(),
                                               aCopy.board[i][j]->getLocation(),
                                               aCopy.board[i][j]->getKind()));
                else
                    row.push_back(nullptr);

            board.push_back(row);
        }

        for (auto piece: aCopy.bluePieces)
            bluePieces.push_back(new NewPiece(piece->getColor(), piece->getLocation(), piece->getKind()));

        for (auto piece: aCopy.goldPieces)
            goldPieces.push_back(new NewPiece(piece->getColor(), piece->getLocation(), piece->getKind()));

        stateColor = aCopy.stateColor;
    }

    void GameState::getMoves(PieceColor color) {
        if (color == PieceColor::blue) {
            for (auto piece: this->bluePieces)
                getPieceMoves(piece);
        }
        else {
            for (auto piece: this->goldPieces)
                getPieceMoves(piece);
        }
    }



    void GameState::getPieceMoves(NewPiece *aPiece) {
        std::vector<Location *> locationMoves;


        // have all avail locations
        Location *upLeft = new Location(aPiece->getLocation().row - 1, aPiece->getLocation().col - 1);
        Location *upRight = new Location(aPiece->getLocation().row - 1, aPiece->getLocation().col + 1);
        Location *downLeft = new Location(aPiece->getLocation().row + 1, aPiece->getLocation().col - 1);
        Location *downRight = new Location(aPiece->getLocation().row + 1, aPiece->getLocation().col + 1);
        std::vector<Location*> locations = {upLeft,upRight,downLeft,downRight};

        for (auto loc : locations) {
            if (check_if_can_add_move(aPiece,loc)) { // enter if it is a valid move
                GameState* aGameState = new GameState(*this);
                aGameState->original = new NewPiece(aPiece->getColor(), aPiece->loc, aPiece->getKind());
                aGameState->pieceMove = loc;
                // remove piece from old position
                auto oldLocation = aPiece->getLocation();
                aGameState->board[oldLocation.row][oldLocation.col] = nullptr;
                // move piece to new position
                aGameState->board[loc->row][loc->col] = aPiece;
                aPiece->changeLocation(loc->row, loc->col);
                // if there was  a jump remove conquered piece
                if (std::abs(oldLocation.row-loc->row) ==2) {
                    // change piece location
                    int delrow = oldLocation.row + (loc->row - oldLocation.row) / 2;
                    int delcol = oldLocation.col + (loc->col- oldLocation.col) / 2;
                    // remove piece from the teams pieces
                    auto pieceToDelete = aGameState->board[delrow][delcol];
                    if (pieceToDelete->getColor() == PieceColor::blue) {
                        auto foundPiece = std::find(aGameState->bluePieces.begin(),aGameState->bluePieces.end(),pieceToDelete);
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

                    delete pieceToDelete;
                    delete this->board[delrow][delcol];
                }

                this->possibleMoves.emplace_back(aGameState);
            }
        }
    }

//    bool GameState::validMove(NewPiece* aPiece, Location* location) {
//        return (validLocation(location) && validateMove(location,aPiece->getColor()));
//    }

    bool GameState::check_if_can_add_move(NewPiece* aPiece, Location* location) {
        if (validLocation(location)) {
            if (!isValidDirection(aPiece, aPiece->getLocation(), location)) return false;
            if(!this->jumpFlag)
                if (this->board[location->row][location->col] == nullptr)
                    return true; //assuming board is nullptr in i,j th spot if no piece
        }
        else
            return false;

        if (this->board[location->row][location->col] == nullptr) return false;
        if (this->board[location->row][location->col]->getColor() == aPiece->getColor()) return false;
        location->row +=  location->row - aPiece->getLocation().row;
        location->col +=  location->col - aPiece->getLocation().col;
        if (!validLocation(location)) return false;
        if (this->board[location->row][location->col] == nullptr) {
            if (!this->jumpFlag) {
                for (auto move: this->possibleMoves)
                    delete move;

                this->possibleMoves.clear();
                this->jumpFlag = true;
            }
            return true; //assuming board is nullptr in i,j th spot if no piece
        }
        return false;
    }
}

//*************************
//still an error with jumps
//*************************
//turn 11 for blue
//turn 8 for blue