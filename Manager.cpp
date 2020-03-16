#include "Manager.h"

bool Manager::setFigure(const Occupator& occupator) {  // place a figure on the board

    std::pair<int, int> fromPosition = std::make_pair(occupator.field.row, occupator.field.col);

    if (occupator.figure->increaseAttackedState(fromPosition, board)) { // if successfully 
                                                                        // implemented attack logic
        board.at(occupator.field).status = Occupied::OccupiedByWhite;  // for now working only with white figures!!
                                          // to do: implement a switch for different game variants!
        return true;
    }
    return false;
}

void Manager::cleanFigure(const Occupator& occupator) {
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

void Manager::startIter() {

    struct SnapShotStruct {

        FieldPtr field;
        std::shared_ptr<Figure> figure;
        int stage = 0;

        SnapShotStruct(std::shared_ptr<Figure> figure, FieldPtr passedField)
            : figure(figure), field(passedField) {}

        SnapShotStruct(const SnapShotStruct& other) : figure(other.figure), field(other.field) {
            stage = other.stage;
            field.board = other.field.board;
            field.row = other.field.row;
            field.col = other.field.col;
        }

        SnapShotStruct& operator=(const SnapShotStruct& other) {
            if (this != &other) {
                stage = other.stage;
                figure = other.figure;
                field.board = other.field.board;
                field.col = other.field.col;
                field.row = other.field.row;
            }
            return *this;
        }
    };

    std::stack<SnapShotStruct> snapshots;

    SnapShotStruct currentSnapShot(nullptr, &board);

    snapshots.push(currentSnapShot);  // starts at [0][0]

    while (!snapshots.empty())
    {
        currentSnapShot = snapshots.top();
        snapshots.pop();

        if (!currentSnapShot.figure) currentSnapShot.figure = figFactory.getNextPiece();

        switch (currentSnapShot.stage) {
        case 0:
        {
            bool found = false;
            for (auto field = currentSnapShot.field; field != board.end(); ++field) {

                if (field->status == Occupied::NotOccupied
                    && field->whiteAttacks == 0     // change logic
                    && field->blackAttacks == 0     // for different variants!!!
                    && setFigure(Occupator(currentSnapShot.figure, field))) {

                    currentSnapShot.stage = 1;
                    currentSnapShot.field = field;
                    snapshots.push(currentSnapShot);

                    solution.push_back(Occupator(currentSnapShot.figure, field));    

                    if (auto nextFigure = figFactory.getNextPiece(); !nextFigure) {
                        distinctSolutions.push_back(solution);
                    }
                    else {
                        snapshots.push(SnapShotStruct(nextFigure, ++field));
                    }
                    found = true;
                    break;
                }
            }
            if (!found) figFactory.returnPiece(currentSnapShot.figure); 

            break;
        }
        case 1:

            solution.pop_back();    // rolling back!

            cleanFigure(Occupator(currentSnapShot.figure, currentSnapShot.field));

            ++currentSnapShot.field;
            currentSnapShot.stage = 0;
            snapshots.push(currentSnapShot);

            break;
        }

        if (snapshots.empty() && figFactory.dropPermutation())
            snapshots.push(SnapShotStruct(nullptr, &board));
    }
}

std::vector<Solution> Manager::getDistinctSolutions() {
    return distinctSolutions;
}
