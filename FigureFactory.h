#pragma once
#include <vector>
#include <set>
#include <memory>
#include <utility>
#include "Figure.h"

class FigureFactory {

    std::vector<Piece> initial;

    std::vector<std::stack<std::shared_ptr<Figure>>> piecesRepo;

    void makeInitial(std::vector<std::pair<Piece, int>> pieces) {
        for (auto p : pieces) {
            for (size_t i = 0; i < p.second; i++)
            {
                initial.push_back(p.first);
            }
        }
    }

    std::shared_ptr<Figure> produceFigure(Piece piece) {
        //std::unique_ptr<Figure> result;

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

        //return result;
    }

    void permute( int index) {
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


public:
    FigureFactory(std::vector<std::pair<Piece, int>> pieces) {

        makeInitial(pieces);
        permute(0);

    }

    std::shared_ptr<Figure> getNextPiece() {
        if (piecesRepo.back().empty()) {
            return nullptr;
        }
        else {
            auto result = piecesRepo.back().top();
            piecesRepo.back().pop();
            return result;
        }
    }

    void returnPiece(std::shared_ptr<Figure> piece) {
        if(piece)
            piecesRepo.back().push(piece);
    }

    bool dropPermutation() {

        piecesRepo.pop_back();

        if (piecesRepo.empty())
            return false;
        else
            return true;
    }
};