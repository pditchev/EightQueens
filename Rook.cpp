#include "Rook.h"

bool Rook::markImpactedFields(std::pair<int, int> position, Board& instance) {

    for (size_t row = 0; row < instance.getRows(); row++)
    {
        if (row == position.first) continue;
        if (!check(std::make_pair(row, position.second), instance)) return false;
    }

    for (size_t col = 0; col < instance.getCols(); col++)
    {
        if (col == position.second) continue;
        if (!check(std::make_pair(position.first, col), instance)) return false;
    }
    return true;
}

Rook::Rook() : Figure("rook") {}
