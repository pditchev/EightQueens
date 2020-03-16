#include <iostream>
#include <vector>
#include <algorithm>
#include "Manager.h"
#include "FundamentalSolutions.h"


int main()
{
    std::vector<std::pair<Piece, int>> init{ {Piece::Queen,  6},
                                             {Piece::Rook,   0},
                                             {Piece::Bishop, 1},
                                             {Piece::Knight, 2}
                                            };

    Board board(8,8);
    FigureFactory figFactory(init);

    Manager manager(board, figFactory);

    manager.startIter();

    auto solutions = manager.getDistinctSolutions();

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