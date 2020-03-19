#include <iostream>
#include <vector>
#include <algorithm>
#include "WorkHorse.h"
#include "FundamentalSolutions.h"
#include "Initializer.h"


int main()
{
    Initializer initializer;
    initializer.getInput();

    FigureFactory figFactory(initializer);

    WorkHorse workHorse(initializer.boardDimensions, figFactory);

    workHorse.startIter();

    auto solutions = workHorse.getDistinctSolutions();

    FundamentalSolutions fundaments(board, solutions);


    std::cout << "size of allSolutions is : " <<  solutions.size() << std::endl;

    std::cout << "number of fundamental solutions: " << fundaments.getFundamentalSolutions() << std::endl;

    //for (auto& s : solutions) {

    //    std::sort(s.begin(), s.end());
    //    std::cout << "next solution:" << '\n';
    //    for (auto& p : s) {
    //        std::cout << " | " << p;
    //    }
    //    std::cout << "| \n";
    //}

    return 0;
}