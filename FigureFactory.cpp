#include "FigureFactory.h"

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

FigureFactory::FigureFactory(Initializer& initializer) : initializer(initializer){
    makeInitial(initializer.init);
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
