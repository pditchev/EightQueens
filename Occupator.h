#pragma once
#include <memory>
#include <iostream>
#include "Figure.h"

struct Occupator
{
	std::shared_ptr<Figure> figure;
	std::pair<int, int> position;

	Occupator(std::shared_ptr<Figure> figure, std::pair<int, int> position)
		: figure(figure), position(position) {}


	bool operator<(Occupator& other) {
		if (position.first < other.position.first) 
			return true;
		else if (position.first == other.position.first) 
			return position.second < other.position.second;
		return false;
	}


	friend std::ostream& operator<<(std::ostream& out, const Occupator& occupator) {

		out << "(" << occupator.position.first << ", "
			<< occupator.position.second << ") "
			<< occupator.figure->name;

		return out;
	}
};

template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {

	template<>
	struct hash<Occupator> {
		size_t operator()(const Occupator& occupator) const {
			size_t seed = 0;
			hash_combine(seed, occupator.figure->name);
			hash_combine(seed, occupator.position.first);
			hash_combine(seed, occupator.position.second);
			return seed;
		}
	};
}



