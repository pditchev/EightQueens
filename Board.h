#pragma once
#include "Field.h"



class Board {
public:
    Field** fields;

    Board(size_t rows, size_t cols);

    struct iterator {


        Board* board;
        size_t row, col;

        iterator(Board* board);

        Board::iterator& operator++();

        Field& operator*();

        Field* operator->();


        bool operator!=(const iterator& other) const;
        bool operator==(const iterator& other) const;

    };

    Board::iterator begin();

    Board::iterator end();

    Field& at(Board::iterator field);

    size_t getRows();
    size_t getCols();

private:
    size_t rows;
    size_t cols;
};

typedef Board::iterator FieldPtr;
