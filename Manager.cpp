#include "Manager.h"

bool Manager::setFigure(Occupator& occupator) {  // place a figure on the board

    std::pair<int, int> fromPosition = std::make_pair(occupator.field.row, occupator.field.col);

    if (occupator.figure->increaseAttackedState(fromPosition, board)) { // if successfully 
                                                                        // implemented attack logic
        board.at(occupator.field).status = Occupied::OccupiedByWhite;  // for now working only with white figures!!
                                          // to do: implement a switch for different game variants!
        return true;
    }
    return false;
}

void Manager::cleanFigure(Occupator& occupator) {
    std::pair<int, int> fromPosition = std::make_pair(occupator.field.row, occupator.field.col);

    occupator.figure->decreaseAttackedState(fromPosition, board);
    board.at(occupator.field).status = Occupied::NotOccupied;
}

Manager::Manager(Board& board, FigureFactory& figFactory)
                : board(board),    figFactory(figFactory) {}

void Manager::start() {
    if(auto figure = figFactory.getNextPiece())
        place(figure, FieldPtr(&board)); //start with fields[0][0] (default c'tor of iterator)
}

void Manager::place(std::shared_ptr<Figure> figure, FieldPtr passedField) {

    static int level = 0;
    ++level;

    for (auto field = passedField; field != board.end(); ++field){

        Occupator occupator{ figure, field };

        if (   field->status         == Occupied::NotOccupied
            && field->whiteAttacks   == 0     // change logic
            && field->blackAttacks   == 0     // for different variants!!!
            && setFigure(occupator)) {

            solution.push_back(occupator);

            auto nextFigure = figFactory.getNextPiece();

            if (!nextFigure) {
                distinctSolutions.push_back(solution);
                ++count;
            }

            else place(nextFigure, field);   // recursion !!

            solution.pop_back();    // rolling back!

            cleanFigure(occupator);

            figFactory.returnPiece(nextFigure);
        }       
    }

    --level;
    if (level == 0 && figFactory.dropPermutation())  start();
    
}

int Manager::getCount() {
    return count;
}

std::vector<Solution> Manager::getDistinctSolutions() {
    return distinctSolutions;
}
