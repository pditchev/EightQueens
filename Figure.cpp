#include "Figure.h"

bool Figure::check(std::pair<int, int> position, Board& instance)
{
    Field& field = instance.fields[position.first][position.second]; // for simplicity!!

    if (field.status == Occupied::NotOccupied)
    {
       //field.attemptedAttack = true;

        impacted.push_back(&field);

        return true;
    }
    else
        impacted.clear();
        return false;
}

Figure::Figure(std::string name) : name(name) {
    //impacted.reserve(32);
}

bool Figure::increaseAttackedState(std::pair<int, int> position, Board& board) {

    if (markImpactedFields(position, board)) {
        for (auto& field : impacted) {
            ++field->whiteAttacks;       // dealing only with white figures for now
        }
        impacted.clear();
        return true;
    }
    return false;

    //bool success = markImpactedFields(position, board);

    ////for (auto& field : board) {
    //for (auto& field : impacted) {

    //    if (success/* && field->attemptedAttack*/) {
    //        ++field->whiteAttacks;       // dealing only with white figures for now
    //    }
    //    //field.attemptedAttack = false;
    //}
    //impacted.clear();
    //return success;
}

void Figure::decreaseAttackedState(std::pair<int, int> position, Board& board) {
    markImpactedFields(position, board);
    for (auto& field : impacted) {
    //for (auto& field : board) {

     //   if (field.attemptedAttack) {
            --field->whiteAttacks;       // dealing only with white figures for now
     //   }
     //   field.attemptedAttack = false;
    }
    impacted.clear();
}
