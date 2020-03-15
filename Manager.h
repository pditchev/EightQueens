#pragma once
#include <vector>
#include <memory>
#include "Figure.h"
#include "FigureFactory.h"
#include "Occupator.h"
#include "Solution.h"


class Manager {

private:
    int count =             0;
    Board&                  board;
    FigureFactory&          figFactory;
    Solution                solution;
    std::vector<Solution>   distinctSolutions;

    bool setFigure(Occupator& occupator);   // function name may be inappropriate!!!

    void cleanFigure(Occupator& occupator);

public:

    Manager(Board& board, FigureFactory& figFactory);

    void start();

    void place(std::shared_ptr<Figure> figure, FieldPtr field);

    int getCount();

    std::vector<Solution> getDistinctSolutions();
};