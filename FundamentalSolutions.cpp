#include "FundamentalSolutions.h"

bool FundamentalSolutions::isUnique(Solution& solution) {
	auto it = fundamentals.insert(solution);
	if (!it.second) return false;
	fundamentals.erase(it.first);
	return true;
}

//void FundamentalSolutions::rotate(Solution& solution) {
//	for (auto& occ : solution) {
//		size_t temp = occ.position.first;
//		occ.position.first = occ.position.second;
//		occ.position.second = board.getRows() - temp - 1;
//	}
//	std::sort(solution.begin(), solution.end());
//}

void FundamentalSolutions::rotate(Solution& solution) {
	for (auto& occ : solution) {
		size_t temp = occ.field.row;
		occ.field.row = occ.field.col;
		occ.field.col = board.getRows() - temp - 1;
	}
	std::sort(solution.begin(), solution.end());
}

//void FundamentalSolutions::flipHorizontally(Solution& solution) {
//	for (auto& occupator : solution) {
//		occupator.position.first = board.getCols() - occupator.position.first - 1;
//	}
//	std::sort(solution.begin(), solution.end());
//}

void FundamentalSolutions::flipHorizontally(Solution& solution) {
	for (auto& occupator : solution) {
		occupator.field.row = board.getCols() - occupator.field.row - 1;
	}
	std::sort(solution.begin(), solution.end());
}

//void FundamentalSolutions::flipVertically(Solution& solution) {
//	for (auto& occupator : solution) {
//		occupator.position.second = board.getRows() - occupator.position.second - 1;
//	}
//	std::sort(solution.begin(), solution.end());
//}

void FundamentalSolutions::flipVertically(Solution& solution) {
	for (auto& occupator : solution) {
		occupator.field.col = board.getRows() - occupator.field.col - 1;
	}
	std::sort(solution.begin(), solution.end());
}

bool FundamentalSolutions::isFundamentalSolution(Solution& solution) {
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

void FundamentalSolutions::buildFundamentals(std::vector<Solution>& distincts) {

	for (auto& solution : distincts) {
		if (isFundamentalSolution(solution)) {
			fundamentals.insert(solution);
		}
	}
}

FundamentalSolutions::FundamentalSolutions(Board& board, std::vector<Solution>& distincts)
	: distincts(distincts), board(board) {

	buildFundamentals(distincts);
}

int FundamentalSolutions::getFundamentalSolutions() {
	return fundamentals.size();
}
