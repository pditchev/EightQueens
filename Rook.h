#pragma once
#include "Figure.h"

class Rook : public Figure
 {
    virtual bool markImpactedFields(std::pair<int, int> position, Board* instance) override;

    public:
        Rook();
};
