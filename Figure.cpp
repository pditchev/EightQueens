#include "Figure.h"

bool Figure::check(std::pair<int, int> position, Board& instance)
{
    Field& field = instance.fields[position.first][position.second]; // for simplicity!!

    if (field.status == Occupied::NotOccupied)
    {
        field.attemptedAttack = true;

        return true;
    }
    else
        return false;
}

Figure::Figure(std::string name) : name(name) {}

bool Figure::increaseAttackedState(std::pair<int, int> position, Board& board) {

    bool success = markImpactedFields(position, board);

    for (auto& field : board) {
        if (success && field.attemptedAttack) {
            ++field.whiteAttacks;       // dealing only with white figures for now
        }
        field.attemptedAttack = false;
    }
    return success;
}

void Figure::decreaseAttackedState(std::pair<int, int> position, Board& board) {
    markImpactedFields(position, board);
    for (auto& field : board) {
        if (field.attemptedAttack) {
            --field.whiteAttacks;       // dealing only with white figures for now
        }
        field.attemptedAttack = false;
    }
}
