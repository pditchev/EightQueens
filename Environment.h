#pragma once
#include "Figure.h"


class Environment
{

public:
	Board board;

	Environment(int rows, int cols) {

		this->board =  Board(rows, cols);
	}


	//static const int cols = 6;
	//static const int rows = 6;

};

