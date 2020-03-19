#include <iostream>
#include <vector>
#include <algorithm>
#include "WorkHorse.h"
#include "FundamentalSolutions.h"
#include "Initializer.h"
#include "Manager.h"


int main()
{


    //FigureFactory figFactory(initializer);

    //WorkHorse workHorse(initializer.boardDimensions, figFactory);

    //workHorse.startIter();

    Manager manager;
    manager.work();

    auto solutions = manager.getDistinctSolutions();

    FundamentalSolutions fundaments(new Board(std::make_pair(manager.rows(), manager.cols()) ), solutions);


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