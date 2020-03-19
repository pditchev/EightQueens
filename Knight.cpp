#include "Knight.h"

bool Knight::markImpactedFields(std::pair<int, int> position, Board* instance) {

    for (auto f : att) {
        int row = position.first + f.first;
        int col = position.second + f.second;
        if (row >= 0 && row < instance->getRows() && col >= 0 && col < instance->getCols()) {
            if (!check(std::make_pair(row, col), instance)) return false;
        }
    }
    return true;
}

Knight::Knight() : Figure("knight") {}
