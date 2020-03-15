#include "Board.h"



Board::Board(size_t rows, size_t cols) : rows(rows), cols(cols) {
    this->fields = new Field * [rows];
    for (int i = 0; i < rows; i++)
    {
        fields[i] = new Field[cols]{};
    }
}

FieldPtr Board::begin() {
    iterator it(this);
    it.row = 0;
    it.col = 0;
    return it;
}

FieldPtr Board::end() {
    iterator it(this);
    it.row = this->rows;
    it.col = 0;
    return it;
}

Field& Board::at(FieldPtr field)
{
    return fields[field.row][field.col];
}

size_t Board::getRows() { return rows; }

size_t Board::getCols() { return cols; }

Board::iterator::iterator(Board* board) : board(board), row(0), col(0) {}

FieldPtr& Board::iterator::operator++() {

    if (!(++col %= board->cols)) ++row;

    //if (col == board->cols - 1)
    //{
    //    ++row;
    //    col = 0;
    //}
    //else {
    //    ++col;
    //}
    return *this;
}

Field& Board::iterator::operator*() {
    return board->fields[row][col];
}

Field* Board::iterator::operator->()
{
    return &board->fields[row][col];
}

bool Board::iterator::operator!=(const iterator& other) const {
    return row != other.row || col != other.col;
}
