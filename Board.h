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

        iterator& operator++();

        Field& operator*();

        bool operator!=(const iterator& other);
    };

    Board::iterator begin();

    Board::iterator end();

    size_t getRows();
    size_t getCols();

private:
    size_t rows;
    size_t cols;
};

