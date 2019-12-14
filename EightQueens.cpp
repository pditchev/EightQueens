#include <iostream>
#include <vector>

const int rows = 7;
const int cols = 6;

const int queens = 6;
int queensLeft = queens;

int count = 0;

int board[rows][cols];


bool prep(int i, int j, std::vector<std::pair<int, int>>& prepared) {
    if (board[i][j] != -1) {
        prepared.emplace_back(i, j);
        return true;
    }
    else
        return false;
}

bool markAsAttacked(int i, int j, std::vector<std::pair<int,int>> & prepared) {

    for (size_t x = 0; x < rows; x++)
    {
        if (x == i) continue;
        if (!prep(x, j, prepared)) return false;
    }
    for (size_t y = 0; y < cols; y++)
    {
        if (y == j) continue;
        if (!prep(i, y, prepared)) return false;
    }

    for (int x = i + 1, y = j + 1; x < rows && y < cols; ++x, ++y) {
        if (!prep(x, y, prepared)) return false;
    }
    for (int x = i - 1, y = j - 1; x >= 0 && y >= 0; --x, --y) {
        if (!prep(x, y, prepared)) return false;
    }
    for (int x = i + 1, y = j - 1; x < rows && y >= 0; ++x, --y) {
        if (!prep(x, y, prepared)) return false;
    }
    for (int x = i - 1, y = j + 1; x >= 0 && y < cols; --x, ++y) {
        if (!prep(x, y, prepared)) return false;
    }

    for (auto p : prepared) {
        ++board[p.first][p.second];
    }
    return true;
}

void unmark(std::vector<std::pair<int, int>>& prepared) {
    for (auto p : prepared) {
        --board[p.first][p.second];
    }
    prepared.clear();
}

void place(int startRow, int startCol) {

    static int level = -1;
    ++level;

    std::vector<std::pair<int, int>> prepared;

    for (size_t i = startRow; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (i == startRow && j < startCol) continue;

            if (board[i][j] == 0 && markAsAttacked(i, j, prepared)) {

                board[i][j] = -1;

                if (!(--queensLeft)) {
                    ++count;
                } else place(i,j);

                board[i][j] = 0;
                unmark(prepared);
                ++queensLeft;
            }
        }
    }
    --level;
}

int main()
{

    place(0,0);

    if (true) {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                if (board[i][j] == -1) {
                    std::cout << " 0 ";
                }
                else {
                    std::cout << " - ";
                }
                std::cout << "  ";
            }
            std::cout << '\n' << '\n';
        }

    }

    std::cout << count << " different solution(s)!" << std::endl;

    return 0;
}

