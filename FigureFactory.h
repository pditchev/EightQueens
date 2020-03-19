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
#include "Initializer.h"

enum class Piece { Queen, Rook, Bishop, Knight };

class FigureFactory {

private:

    Initializer& initializer;




public:
    static std::shared_ptr<Figure> produceFigure(Piece piece);

    FigureFactory(Initializer& initializer);

    std::shared_ptr<Figure> getNextPiece();

    void returnPiece(std::shared_ptr<Figure> piece);

    bool dropPermutation();
};