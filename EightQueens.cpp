#include <iostream>
#include <vector>
#include "Manager.h"


int main()
{
    std::vector<std::pair<Piece, int>> init{ {Piece::Queen, 6}, {Piece::Rock, 2} };
    Environment env(8,8);
    FigureFactory figFactory(init);

    Manager manager(env, figFactory);

    manager.place(std::make_pair(0,0));

    std::cout << manager.getCount() << " different solution(s)!" << std::endl;

    return 0;
}