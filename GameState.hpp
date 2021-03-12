//
// Created by Stephen on 3/7/2021.
//

#ifndef ECE141A_GAMESTATE_HPP
#define ECE141A_GAMESTATE_HPP

#include "Piece.hpp"
#include "Game.hpp"
#include <vector>

namespace ECE141
{
    class NewPiece
    {
    public:
        NewPiece(PieceColor aColor, Location aLoc, PieceKind aKind = PieceKind::pawn) : loc(aLoc), kind(aKind), color(aColor)
        {
        }

        bool operator==(NewPiece aNewPiece) const;

        Location getLocation() const {
            return loc;
        }

        void changeLocation(int row, int col) {
            loc.row = row;
            loc.col = col;
        }

        bool hasColor(PieceColor aColor) const { return color == aColor; }
        PieceKind getKind() { return kind; }
        const PieceColor getColor() { return color; }


        Location loc;
        PieceKind kind;
        PieceColor color;
    };

    class GameState
    {
    public:
        GameState() {}

        ~GameState() {
            //deleting board
            for(auto row: this->board)
                for (auto col: row)
                    delete col;

            this->board.clear();
            //deleting bluePieces
            this->bluePieces.clear();
            //deleting goldPieces
            this->goldPieces.clear();
            //deleting possibleMoves
            for(auto move: this->possibleMoves)
                delete move;

            this->possibleMoves.clear();
            //deleting original
            delete original;
            //deleting pieceMove
            delete pieceMove;
        }

        GameState(const GameState &aCopy);

        int score() {
            if(this->stateColor == PieceColor::blue)
                return this->bluePieces.size() - this->goldPieces.size();
            else
                return this->goldPieces.size() - this->bluePieces.size();
        }

        bool gameOver();

        bool validLocation(Location *aLocation)
        {
            if (aLocation->row >= 0 && aLocation->row < Game::kBoardHeight)
            {
                return (aLocation->col >= 0 && aLocation->col < Game::kBoardHeight);
            }
            return false;
        }

        void getMoves(PieceColor color);

        void getPieceMoves(NewPiece *aPiece);

        bool isValidDirection( NewPiece *aPiece,  Location aSrc,  Location *aDest)
        {
            if (PieceKind::pawn == aPiece->getKind())
            {
                return aPiece->hasColor(PieceColor::gold) ? aSrc.row < aDest->row : aSrc.row > aDest->row;
            }
            return true;
        }

        bool check_if_can_add_move(NewPiece *aPiece, Location *location);

        std::vector<std::vector<NewPiece *>> board;
        std::vector<NewPiece *> bluePieces;
        std::vector<NewPiece *> goldPieces;
        std::vector<GameState* > possibleMoves;

        bool jumpFlag = false;
        NewPiece *original;
        Location *pieceMove;
        PieceColor stateColor; //must implement in minimax we are using both players
    };

}

#endif //ECE141A_GAMESTATE_HPP
