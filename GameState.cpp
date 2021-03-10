//
// Created by Stephen on 3/7/2021.
//

#include "GameState.hpp"

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

        if (color == PieceColor::blue) {
            for (auto piece: this->bluePieces)
                for (auto move: getPieceMoves(piece))
                    children.push_back(move);
        } else {
            for (auto piece: this->goldPieces)
                for (auto move: getPieceMoves(piece))
                    children.push_back(move);
        }

        return children;
    }

    std::vector<GameState *> GameState::getPieceMoves(NewPiece *aPiece) {
        std::vector<GameState *> moves;
//        std::vector<std::pair<Location *, bool>> locationMoves; // <Location, jump flag>
        std::vector<Location *> locationMoves;
        Location *upLeft = new Location(aPiece->getLocation().row - 1, aPiece->getLocation().col - 1);
        Location *upRight = new Location(aPiece->getLocation().row - 1, aPiece->getLocation().col + 1);
        Location *downLeft = new Location(aPiece->getLocation().row + 1, aPiece->getLocation().col - 1);
        Location *downRight = new Location(aPiece->getLocation().row + 1, aPiece->getLocation().col + 1);

        if(validMove(aPiece, upLeft))
            moves.emplace_back(createMove(aPiece, upLeft));
        else
            delete upLeft



//        if (validMove(aPiece, upLeft)) {
//            GameState *move = createMove(aPiece, upLeft);
//            moves.emplace_back(move);
//        }
//        else {
//            upLeft->row -= 1;
//            upLeft->col -= 1;
//
//            if (validMove(aPiece, upLeft)) {
//                GameState *move = createMove(aPiece, upLeft);
//                moves.emplace_back(move);
//            }
//            else
//                delete upLeft;
//        }
//            delete upLeft;



        if (validateMove(upLeft, aPiece->getColor()))
            locationMoves.emplace_back(std::make_pair(upLeft, false));
        else {
            if (this->board[upLeft->row][upLeft->col]->getColor() != aPiece->getColor()) {
                upLeft->row -= 1;
                upLeft->col -= 1;

                if (validateMove(upLeft, aPiece->getColor()))
                    locationMoves.emplace_back(std::make_pair(upLeft, true));
                else
                    delete upLeft;
            } else
                delete upLeft;
        }

        if (validateMove(upLeft, aPiece->getColor()) && !this->jumpFlag)
            locationMoves.emplace_back(upLeft);
        else if()








        if (validateMove(upRight, aPiece->getColor()))
            locationMoves.emplace_back(std::make_pair(upRight, false));
        else {
            if (this->board[upRight->row][upRight->col]->getColor() != aPiece->getColor()) {
                upRight->row -= 1;
                upRight->col += 1;

                if (validateMove(upRight, aPiece->getColor()))
                    locationMoves.emplace_back(std::make_pair(upRight, true));
                else
                    delete upRight;
            } else
                delete upRight;
        }

        if (validateMove(downLeft, aPiece->getColor()))
            locationMoves.emplace_back(std::make_pair(downLeft, false));
        else {
            if (this->board[downLeft->row][downLeft->col]->getColor() != aPiece->getColor()) {
                downLeft->row += 1;
                downLeft->col -= 1;

                if (validateMove(downLeft, aPiece->getColor()))
                    locationMoves.emplace_back(std::make_pair(downLeft, true));
                else
                    delete downLeft;
            } else
                delete downLeft;
        }

        if (validateMove(downRight, aPiece->getColor()))
            locationMoves.emplace_back(std::make_pair(downRight, false));
        else {
            if (this->board[downRight->row][downRight->col]->getColor() != aPiece->getColor()) {
                downRight->row += 1;
                downRight->col += 1;

                if (validateMove(downRight, aPiece->getColor()))
                    locationMoves.emplace_back(std::make_pair(downRight, true));
                else
                    delete downRight;
            } else
                delete downRight;
        }

        //remove all moves that aren't a jump if a jump move is present
        bool jumpFlag = false;
        for (int i = locationMoves.size() - 1; i >= 0; i--) {
            if (!jumpFlag) {
                if (locationMoves[i].second) {
                    jumpFlag = true;

                    for (int j = locationMoves.size() - 1; j > i; j--) {
                        delete locationMoves[j].first;

                        locationMoves.erase(locationMoves.begin() + j);
                    }
                }
            } else {
                if (!locationMoves[i].second) {
                    delete locationMoves[i].first;

                    locationMoves.erase(locationMoves.begin() + i);
                }
            }
        }

        for (int i = 0; i < locationMoves.size(); i++) {
            GameState *state(this);
            state->movePiece(aPiece, locationMoves[i].first);
            moves.emplace_back(state);
        }

        return moves;
    }
}