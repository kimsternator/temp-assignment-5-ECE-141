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
        NewPiece(PieceColor aColor, Tile *aTile, PieceKind aKind = PieceKind::pawn) : tile(aTile), kind(aKind), color(aColor)
        {
        }

        bool operator==(const NewPiece aNewPiece) const;

        Location getLocation()
        {
            return tile ? tile->getLocation() : Location(-1, -1);
        }

        Tile *getTile() { return (Tile *)tile; }
        bool hasColor(PieceColor aColor) { return color == aColor; }
        PieceKind getKind() { return kind; }
        PieceColor getColor() { return color; }

    private:
        Tile *tile;
        PieceKind kind;
        PieceColor color;
    };

    class GameState
    {
    public:
        GameState() {}

        GameState(const GameState &aCopy);

        int score() { return this->bluePieces.size() - this->goldPieces.size(); }

        bool gameOver();

        bool validLocation(Location *aLocation)
        {
            if (aLocation->row >= 0 && aLocation->row < Game::kBoardHeight)
            {
                return (aLocation->col >= 0 && aLocation->col < Game::kBoardHeight);
            }
            return false;
        }

        bool validateMove(Location *aMove, PieceColor color);
        //valid Location
        // valid move

        void movePiece(NewPiece *aPiece, Location *aMove);
        // move the piece
        //set piece to king if applicable
        // update blue/gold pieces
        //update original and pieceMove

        std::vector<GameState *> getMoves(PieceColor color);

        std::vector<GameState *> getPieceMoves(NewPiece *aPiece);

        std::vector<std::vector<NewPiece *>> board;
        std::vector<NewPiece *> bluePieces;
        std::vector<NewPiece *> goldPieces;

        bool validMove(NewPiece *aPiece, Location *location);
        bool check_if_can_add_move(NewPiece *aPiece, Location *location);

        bool jumpFlag = false;
        NewPiece *original;
        Location *pieceMove;
        //        int turn; //0 - blue : 1 - gold

        bool isValidDirection( NewPiece *aPiece,  Location aSrc,  Location *aDest)
        {
            if (PieceKind::pawn == aPiece->getKind())
            {
                return aPiece->hasColor(PieceColor::gold) ? aSrc.row < aDest->row : aSrc.row > aDest->row;
            }
            return true;
        }
    };

}

#endif //ECE141A_GAMESTATE_HPP
