#pragma once
#include <vector>
#include <string>
#include <stack>
#include <memory>
#include "Field.h"
#include "Board.h"

class Figure
{
private:

    std::vector<Field*> impacted;

	virtual bool markImpactedFields(std::pair<int, int> position, Board &instance) = 0;

protected:

    bool check(std::pair<int, int> position, Board& instance);

public:

    Figure(std::string name);

    std::string name;

    bool increaseAttackedState(std::pair<int, int> position, Board& board);

    void decreaseAttackedState(std::pair<int, int> position, Board& board);
};