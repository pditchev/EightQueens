#include "Board.h"

Board::Board(size_t rows, size_t cols) : rows(rows), cols(cols) {
    this->fields = new Field * [rows];
    for (int i = 0; i < rows; i++)
    {
        fields[i] = new Field[cols]{};
    }
}

Board::iterator Board::begin() {
    iterator it(this);
    it.row = 0;
    it.col = 0;
    return it;
}

Board::iterator Board::end() {
    iterator it(this);
    it.row = this->rows;
    it.col = 0;
    return it;
}

size_t Board::getRows() { return rows; }

size_t Board::getCols() { return cols; }

Board::iterator::iterator(Board* board) : board(board) {}

Board::iterator& Board::iterator::operator++() {
    if (col == board->cols - 1)
    {
        ++row;
        col = 0;
    }
    else {
        ++col;
    }
    return *this;
}

Field& Board::iterator::operator*() {
    return board->fields[row][col];
}

bool Board::iterator::operator!=(const iterator& other) {
    return row != other.row || col != other.col;
}
