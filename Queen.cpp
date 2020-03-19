#include "Queen.h"

bool Queen::markImpactedFields(std::pair<int, int> position, Board* instance) {

    for (size_t row = 0; row < instance->getRows(); row++)
    {
        if (row == position.first) continue;
        if (!check(std::make_pair(row, position.second), instance)) return false;
    }

    for (size_t col = 0; col < instance->getCols(); col++)
    {
        if (col == position.second) continue;
        if (!check(std::make_pair(position.first, col), instance)) return false;
    }

    for (int row = position.first + 1, col = position.second + 1;
        row < instance->getRows() && col < instance->getCols();
        ++row, ++col) {
        if (!check(std::make_pair(row, col), instance)) return false;
    }

    for (int row = position.first - 1, col = position.second - 1;
        row >= 0 && col >= 0;
        --row, --col) {
        if (!check(std::make_pair(row, col), instance)) return false;
    }

    for (int row = position.first + 1, col = position.second - 1;
        row < instance->getRows() && col >= 0;
        ++row, --col) {
        if (!check(std::make_pair(row, col), instance)) return false;
    }

    for (int row = position.first - 1, col = position.second + 1;
        row >= 0 && col < instance->getCols();
        --row, ++col) {
        if (!check(std::make_pair(row, col), instance)) return false;
    }

    return true;
}

Queen::Queen() : Figure("queen") {}