#include "FigureFactory.h"

void FigureFactory::makeInitial(std::vector<std::pair<Piece, int>> pieces) {
    for (auto p : pieces) {
        for (size_t i = 0; i < p.second; i++)
        {
            initial.push_back(p.first);
        }
    }
}

std::shared_ptr<Figure> FigureFactory::produceFigure(Piece piece) {

    switch (piece)
    {
    case Piece::Queen:
        return std::make_shared<Queen>();
        break;
    case Piece::Rook:
        return std::make_shared<Rook>();
        break;
    case Piece::Bishop:
        return std::make_shared<Bishop>();
        break;
    case Piece::Knight:
        return std::make_shared<Knight>();
        break;
    default:
        break;
    }
}

void FigureFactory::permute(int index) {
    if (index >= initial.size()) {
        std::stack<std::shared_ptr<Figure>> help_stack;
        for (auto p : initial)
        {
            //auto fig = produceFigure(p);
            help_stack.push(produceFigure(p));
        }
        piecesRepo.push_back(help_stack);
    }
    else {

        std::set<Piece> swapped;

        for (size_t i = index; i < initial.size(); i++)
        {
            if (swapped.count(initial[i]))   continue;

            std::swap(initial[index], initial[i]);

            permute(index + 1);

            std::swap(initial[index], initial[i]);

            swapped.insert(initial[i]);
        }
    }
}

FigureFactory::FigureFactory(std::vector<std::pair<Piece, int>> pieces) {
    makeInitial(pieces);
    permute(0);
    std::cout << "permutations: " << piecesRepo.size() << std::endl;
}

std::shared_ptr<Figure> FigureFactory::getNextPiece() {
    if (piecesRepo.back().empty()) {
        return nullptr;
    }
    else {
        auto result = piecesRepo.back().top();
        piecesRepo.back().pop();
        return result;
    }
}

void FigureFactory::returnPiece(std::shared_ptr<Figure> piece) {
    if (piece)
        piecesRepo.back().push(piece);
}

bool FigureFactory::dropPermutation() {

    piecesRepo.pop_back();

    if (piecesRepo.empty())
        return false;
    else
        return true;
}
