#pragma once
#include <vector>
#include <memory>
#include <stack>
#include "Figure.h"
#include "FigureFactory.h"
#include "Occupator.h"
#include "Solution.h"


class WorkHorse {

private:

    Board*                  board;
    FigureFactory*          figFactory;
    Solution                solution;

    bool setFigure(const Occupator& occupator);   // function name may be inappropriate!!!

    void cleanFigure(const Occupator& occupator);

public:
    std::vector<Solution>   distinctSolutions;

    WorkHorse(std::pair<int, int> boardDimensions
        , std::vector<std::stack<std::shared_ptr<Figure>>> piecesForThread);

    ~WorkHorse();

    void start();

    void place(std::shared_ptr<Figure> figure, FieldPtr passedField);

    void startIter();

    std::vector<Solution> getDistinctSolutions();
};