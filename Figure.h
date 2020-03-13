#pragma once
#include <vector>
#include <string>
#include <stack>
#include <memory>

struct Board {
	int** board;
	size_t rows;
	size_t cols;
    Board() {}
	Board(size_t rows, size_t cols) : rows(rows), cols(cols) {
		this->board = new int* [rows];
		for (int i = 0; i < rows; i++)
		{
            board[i] = new int[cols] {0};
		}
	}
};

enum class Piece {Queen, Rook, Bishop, Knight};


class Figure
{

	virtual bool setAttackedFields(std::pair<int, int> position, Board &instance) = 0;

protected:
    std::vector<std::pair<int, int>> prepared;

    bool prep(std::pair<int, int> position, Board& instance )
    {
        if (instance.board[position.first][position.second] != -1)
        {
            prepared.push_back(position);
            return true;
        }
        else
            return false;
    }

public:

    Figure(std::string name) : name(name) {}

    std::string name;

	bool setFieldsUp(std::pair<int, int> position, Board& instance) {
        if (setAttackedFields(position, instance)) {
            for (auto p : prepared) {
                ++instance.board[p.first][p.second];
            }
            prepared.clear();
            return true;
        }
        else {
            prepared.clear();
		    return false;
        }
	}

	bool setFieldsDown(std::pair<int, int> position, Board& instance) {
        if (setAttackedFields(position, instance)) {
            for (auto p : prepared) {
                --instance.board[p.first][p.second];
            }
            prepared.clear();
            return true;
        }
        else {
            prepared.clear();
            return false;
        }
	}
};

class Queen : public Figure {
	virtual bool setAttackedFields(std::pair<int, int> position, Board& instance) {

        for (size_t row  = 0; row < instance.rows; row++)
        {
            if (row == position.first) continue;
            if (!prep(std::make_pair(row, position.second), instance)) return false;
        }

        for (size_t col = 0; col < instance.cols; col++)
        {
            if (col == position.second) continue;
            if (!prep(std::make_pair(position.first, col), instance)) return false;
        }

        for (int row = position.first + 1, col = position.second + 1;
                 row < instance.rows && col < instance.cols; 
                 ++row, ++col) {
            if (!prep(std::make_pair(row, col), instance)) return false;
        }

        for (int row = position.first - 1, col = position.second - 1;
                 row >= 0 && col >= 0;
                 --row, --col) {
            if (!prep(std::make_pair(row, col), instance)) return false;
        }

        for (int row = position.first + 1, col = position.second - 1;
                 row < instance.rows && col >= 0;
                 ++row, --col) {
            if (!prep(std::make_pair(row, col), instance)) return false;
        }

        for (int row = position.first - 1, col = position.second + 1;
            row >= 0 && col < instance.cols;
            --row, ++col) {
            if (!prep(std::make_pair(row, col), instance)) return false;
        }

        return true;
	}

public:
    Queen() : Figure("queen") {}
};

class Rook : public Figure {
    virtual bool setAttackedFields(std::pair<int, int> position, Board& instance) {

        for (size_t row = 0; row < instance.rows; row++)
        {
            if (row == position.first) continue;
            if (!prep(std::make_pair(row, position.second), instance)) return false;
        }

        for (size_t col = 0; col < instance.cols; col++)
        {
            if (col == position.second) continue;
            if (!prep(std::make_pair(position.first, col), instance)) return false;
        }
        return true;
    }
public:
    Rook() :Figure("rook") {}
};

class Bishop : public Figure {
    virtual bool setAttackedFields(std::pair<int, int> position, Board& instance) {
        for (int row = position.first + 1, col = position.second + 1;
            row < instance.rows && col < instance.cols;
            ++row, ++col) {
            if (!prep(std::make_pair(row, col), instance)) return false;
        }

        for (int row = position.first - 1, col = position.second - 1;
            row >= 0 && col >= 0;
            --row, --col) {
            if (!prep(std::make_pair(row, col), instance)) return false;
        }

        for (int row = position.first + 1, col = position.second - 1;
            row < instance.rows && col >= 0;
            ++row, --col) {
            if (!prep(std::make_pair(row, col), instance)) return false;
        }

        for (int row = position.first - 1, col = position.second + 1;
            row >= 0 && col < instance.cols;
            --row, ++col) {
            if (!prep(std::make_pair(row, col), instance)) return false;
        }

        return true;
    }
public:
    Bishop() : Figure("bishop"){} 
};

class Knight : public Figure {

    static constexpr std::pair<int, int> att[]  {
        {-2, 1 },
        {-1, 2 },
        { 1, 2 },
        { 2, 1},
        {2, -1},
        {1, -2},
        {-1, -2},
        {-2, -1}
    };

    virtual bool setAttackedFields(std::pair<int, int> position, Board& instance) {

        for (auto f : att) {
            int row = position.first + f.first;
            int col = position.second + f.second;
            if (row >= 0 && row < instance.rows && col >= 0 && col < instance.cols) {
                if (!prep(std::make_pair(row, col), instance)) return false;
            }
        }
        return true;
    }

public:
    Knight() : Figure("knight") {}
};