#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <utility>
#include "Figure.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"

enum class Piece { Queen, Rook, Bishop, Knight };

class FigureFactory {

private:
    std::vector<Piece> initial;

    std::vector<std::stack<std::shared_ptr<Figure>>> piecesRepo;

    void makeInitial(std::vector<std::pair<Piece, int>> pieces);

    std::shared_ptr<Figure> produceFigure(Piece piece);

    void permute(int index);


public:
    FigureFactory(std::vector<std::pair<Piece, int>> pieces);

    std::shared_ptr<Figure> getNextPiece();

    void returnPiece(std::shared_ptr<Figure> piece);

    bool dropPermutation();
};