#pragma once
#include <vector>
#include <unordered_set>
#include "Occupator.h"
#include "Solution.h"

class FundamentalSolutions
{
private:
	Board* board;
	std::vector<Solution>& distincts;
	std::unordered_set<Solution> fundamentals;

	bool isUnique(Solution& solution);

	void rotate(Solution& solution);

	void flipHorizontally(Solution& solution);

	void flipVertically(Solution& solution);

	bool isFundamentalSolution(Solution& solution);

	void buildFundamentals(std::vector<Solution>& distincts);

public:

	FundamentalSolutions(Board* board, std::vector<Solution>& distincts);

	int getFundamentalSolutions();
};