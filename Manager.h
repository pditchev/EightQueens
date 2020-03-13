#pragma once
#include <vector>
#include <memory>
#include "Environment.h"
#include "Figure.h"
#include "FigureFactory.h"
#include "Occupator.h"
#include "Solution.h"


class Manager
{
    int count = 0;
    Board &board;
    FigureFactory& figFactory;
    Solution solution;
    std::vector<Solution> distinctSolutions;

    bool setFigure(Occupator& occupator) {

        if (occupator.figure->setFieldsUp(occupator.position, board)) {
            board.board[occupator.position.first][occupator.position.second] = -1;
            return true;
        }
        return false;
    }

    void cleanFigure(Occupator& occupator) {

        occupator.figure->setFieldsDown(occupator.position, board);
        board.board[occupator.position.first][occupator.position.second] = 0;
    }

public:


    Manager(Board &board, FigureFactory& figFactory) 
        : board(board), figFactory(figFactory) {

    }

    void place(std::pair<int, int> position) {
        auto figure = figFactory.getNextPiece();
        place(figure, position);
    }

    void place(std::shared_ptr<Figure> figure, std::pair<int, int> position) {

        static int level=0;
        ++level;

        int startRow = position.first;
        int startCol = position.second;

        for (size_t i = startRow; i < board.rows; i++)
        {
            for (size_t j = 0; j < board.cols; j++)
            {
                if (i == startRow && j < startCol) continue;


                auto pos = std::make_pair(i, j);
                auto occupator = Occupator(figure, pos);

                if (board.board[i][j] == 0 && setFigure(occupator)) {

                    solution.push_back(occupator);

                    auto piece = figFactory.getNextPiece();

                    if (!piece) {
                        distinctSolutions.push_back(solution);
                        ++count;
                    }

                    else place(piece, pos);   // recursion !!

                    solution.pop_back();    // rolling back!

                    cleanFigure(occupator);

                    figFactory.returnPiece(piece); 

                }
            }
        }


        --level;
        if (level == 0) {
            if (figFactory.dropPermutation()) {
                auto nextPiece = figFactory.getNextPiece();
                if (nextPiece) 
                    place(nextPiece, std::make_pair(0, 0)); // recursion!
            }
        }
    }

    int getCount() {
        return count;
    }

    std::vector<Solution> getDistinctSolutions() {
        return distinctSolutions;
    }
};