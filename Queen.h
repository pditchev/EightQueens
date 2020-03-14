#pragma once
#include "Figure.h"

class Queen : public Figure {
    virtual bool markImpactedFields(std::pair<int, int> position, Board& instance) override;

public:
    Queen();
};