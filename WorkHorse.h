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
    FigureFactory&          figFactory;
    Solution                solution;
    std::vector<Solution>   distinctSolutions;

    bool setFigure(const Occupator& occupator);   // function name may be inappropriate!!!

    void cleanFigure(const Occupator& occupator);

public:

    WorkHorse(std::pair<int, int> boardDimensions, FigureFactory& figFactory);

    void start();

    void place(std::shared_ptr<Figure> figure, FieldPtr passedField);

    void startIter();

    std::vector<Solution> getDistinctSolutions();
};