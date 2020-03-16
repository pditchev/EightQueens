#pragma once

enum class Occupied { NotOccupied, OccupiedByWhite, OccupiedByBlack };

struct Field {

    int whiteAttacks;
    int blackAttacks;
    Occupied status;

    Field() : whiteAttacks(0)
        , blackAttacks(0)
        , status(Occupied::NotOccupied)
    {}
};