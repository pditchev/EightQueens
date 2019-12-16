#pragma once
#include <vector>
#include <memory>
#include "Environment.h"
#include "Figure.h"
#include "FigureFactory.h"


class Manager
{
    int count = 0;
    Environment &env;
    FigureFactory& figFactory;

    bool setFigure(std::shared_ptr<Figure> figure, std::pair<int, int> position) {
        if (figure->setFieldsUp(position, env.board)) {
            env.board.board[position.first][position.second] = -1;
            return true;
        }
        return false;
    }

    void cleanFigure(std::shared_ptr<Figure> figure, std::pair<int, int> position) {
        figure->setFieldsDown(position, env.board);
        env.board.board[position.first][position.second] = 0;
    }

public:
    Manager(Environment &env, FigureFactory& figFactory) 
        : env(env), figFactory(figFactory) {

    }

    void place(std::pair<int, int> position) {
        place(figFactory.getNextPiece(), position);
    }

    void place(std::shared_ptr<Figure> figure, std::pair<int, int> position) {

        static int level=0;
        ++level;

        int startRow = position.first;
        int startCol = position.second;

        for (size_t i = startRow; i < env.board.rows; i++)
        {
            for (size_t j = 0; j < env.board.cols; j++)
            {
                if (i == startRow && j < startCol) continue;

                auto pos = std::make_pair(i, j);

                if (env.board.board[i][j] == 0 && setFigure( figure, pos)) { //?????

                    auto piece = figFactory.getNextPiece();

                    if (!piece) {
                        ++count;
                    }

                    else place(piece, pos);

                    cleanFigure( figure, pos);

                    figFactory.returnPiece(piece); 

                }
            }
        }
        --level;
        //if (level == 0) {
        //    if (figFactory.dropPermutation()) {
        //        auto nextPiece = figFactory.getNextPiece();
        //        if (nextPiece) 
        //            place(nextPiece, std::make_pair(0, 0));
        //    }
        //}
    }

    int getCount() {
        return count;
    }

};

