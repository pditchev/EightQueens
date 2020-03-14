#include "Manager.h"

bool Manager::setFigure(Occupator& occupator) {  // place a figure on the board

    if (occupator.figure->increaseAttackedState(occupator.position, board)) { // if successfully 
                                                                    // implemented attack logic
        board.fields[occupator.position.first][occupator.position.second].status
            = Occupied::OccupiedByWhite;  // for now working only with white figures!!
                                          // to do: implement a switch for different game variants!
        return true;
    }
    return false;
}

void Manager::cleanFigure(Occupator& occupator) {

    occupator.figure->decreaseAttackedState(occupator.position, board);
    board.fields[occupator.position.first][occupator.position.second].status = Occupied::NotOccupied;
}

Manager::Manager(Board& board, FigureFactory& figFactory)
                : board(board),    figFactory(figFactory) {}

void Manager::place(std::pair<int, int> position) {
    auto figure = figFactory.getNextPiece();
    place(figure, position);
}

void Manager::place(std::shared_ptr<Figure> figure, std::pair<int, int> position) {

    static int level = 0;
    ++level;

    int startRow = position.first;
    int startCol = position.second;

    for (size_t i = startRow; i < board.getRows(); i++)
    {
        for (size_t j = 0; j < board.getCols(); j++)
        {
            if (i == startRow && j < startCol) continue;

            auto pos = std::make_pair(i, j);
            auto occupator = Occupator(figure, pos);

            if (board.fields[i][j].status == Occupied::NotOccupied
                && board.fields[i][j].whiteAttacks == 0     // different logic
                && board.fields[i][j].blackAttacks == 0     // for different variants
                && setFigure(occupator)) {

                solution.push_back(occupator);

                auto piece = figFactory.getNextPiece();

                if (!piece) {
                    distinctSolutions.push_back(solution);
                    ++count;
                }

                else place(piece, pos);   // recursion !!

                solution.pop_back();    // rolling back!

                cleanFigure(occupator);

                figFactory.returnPiece(piece);
            }
        }
    }

    --level;
    if (level == 0) {
        if (figFactory.dropPermutation()) {
            auto nextPiece = figFactory.getNextPiece();
            if (nextPiece)
                place(nextPiece, std::make_pair(0, 0)); // recursion!
        }
    }
}

int Manager::getCount() {
    return count;
}

std::vector<Solution> Manager::getDistinctSolutions() {
    return distinctSolutions;
}
