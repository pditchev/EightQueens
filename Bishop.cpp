#include "Bishop.h"

bool Bishop::markImpactedFields(std::pair<int, int> position, Board& instance) {
    for (int row = position.first + 1, col = position.second + 1;
        row < instance.getRows() && col < instance.getCols();
        ++row, ++col) {
        if (!check(std::make_pair(row, col), instance)) return false;
    }

    for (int row = position.first - 1, col = position.second - 1;
        row >= 0 && col >= 0;
        --row, --col) {
        if (!check(std::make_pair(row, col), instance)) return false;
    }

    for (int row = position.first + 1, col = position.second - 1;
        row < instance.getRows() && col >= 0;
        ++row, --col) {
        if (!check(std::make_pair(row, col), instance)) return false;
    }

    for (int row = position.first - 1, col = position.second + 1;
        row >= 0 && col < instance.getCols();
        --row, ++col) {
        if (!check(std::make_pair(row, col), instance)) return false;
    }

    return true;
}

Bishop::Bishop() : Figure("bishop") {}
