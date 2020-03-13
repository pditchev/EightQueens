#pragma once
#include <vector>
#include <unordered_set>
#include "Occupator.h"
#include "Solution.h"



class FundamentalSolutions
{
	Board& board;
	std::vector<Solution>& distincts;
	std::unordered_set<Solution> fundamentals;


	bool isUnique(Solution& solution) {
		auto it = fundamentals.insert(solution);
		if (!it.second) return false;
		fundamentals.erase(it.first);
		return true;
	}

	void rotate(Solution& solution) {
		for (auto& occ : solution) {
			size_t temp = occ.position.first;
			occ.position.first = occ.position.second;
			occ.position.second = board.rows - temp - 1;
		}
		std::sort(solution.begin(), solution.end());
	}

	void flipHorizontally(Solution& solution) {
		for (auto& occupator : solution) {
			occupator.position.first = board.cols - occupator.position.first - 1;
		}
		std::sort(solution.begin(), solution.end());

	}

	void flipVertically(Solution& solution) {
		for (auto& occupator : solution) {
			occupator.position.second = board.rows - occupator.position.second - 1;
		}
		std::sort(solution.begin(), solution.end());

	}

	bool isFundamentalSolution(Solution& solution) {
		if (fundamentals.size() == 0) return true;

		for (size_t i = 0; i < 4; i++)
		{
			rotate(solution);
			if (!isUnique(solution)) return false;
			flipHorizontally(solution);
			if (!isUnique(solution)) return false;
			flipVertically(solution);
			if (!isUnique(solution)) return false;
			flipHorizontally(solution);
			flipVertically(solution);
		}
		return true;
	}

	void buildFundamentals(std::vector<Solution>& distincts) {

		for (auto& solution : distincts) {
			if (isFundamentalSolution(solution)) {
				fundamentals.insert(solution);
			}
		}	
	}

public:

	FundamentalSolutions(Board& board, std::vector<Solution> & distincts)
			: distincts(distincts), board(board) {
	
		buildFundamentals(distincts);
	}

	int getFundamentalSolutions() {
		return fundamentals.size();
	}

};



