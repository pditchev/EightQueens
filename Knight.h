#pragma once
#include "Figure.h"

class Knight : public Figure {

    static constexpr std::pair<int, int> att[]{
        {-2, 1 },
        {-1, 2 },
        { 1, 2 },
        { 2, 1},
        {2, -1},
        {1, -2},
        {-1, -2},
        {-2, -1}
    };

    virtual bool markImpactedFields(std::pair<int, int> position, Board& instance) override;

public:
    Knight();
};

