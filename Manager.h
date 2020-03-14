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

    void place(std::pair<int, int> position);

    void place(std::shared_ptr<Figure> figure, std::pair<int, int> position);

    int getCount();

    std::vector<Solution> getDistinctSolutions();
};