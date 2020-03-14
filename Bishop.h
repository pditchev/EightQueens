#pragma once
#include "Figure.h"

class Bishop : public Figure {
    virtual bool markImpactedFields(std::pair<int, int> position, Board& instance) override;
public:
    Bishop();
};

