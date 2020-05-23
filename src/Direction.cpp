#include "Direction.hpp"


namespace tf
{

const std::array<sf::Vector2f, 4> Direction::directions = {
	Direction::forward().ToVector2f(),
	Direction::backward().ToVector2f(),
	Direction::left().ToVector2f(),
	Direction::right().ToVector2f()
};


Direction::Direction(int code, sf::Vector2f dir)
	: code_{code}
	, dir_{dir}
{}

sf::Vector2f Direction::ToVector2f() const { return dir_; }

int Direction::code() const { return code_; }

int Direction::maxCode() { return directions.size() - 1; }

Direction Direction::inversed() const
{
	const auto firstDir = std::begin(directions);
	const auto lastDir = std::end(directions);

	const auto inversedDir = -dir_;
	auto it = std::find(firstDir, lastDir, inversedDir);
	if(it == lastDir)
		throw std::runtime_error{"can't find inversed direction"};

	return Direction{static_cast<int>(std::distance(firstDir, it)), inversedDir};
}

Direction Direction::forward() { return Direction{0, sf::Vector2f{0.f, -1.f}}; }
Direction Direction::backward() { return Direction{1, sf::Vector2f{0.f, 1.f}}; }
Direction Direction::left() { return Direction{2, sf::Vector2f{-1.f, 0.f}}; }
Direction Direction::right() { return Direction{3, sf::Vector2f{1.f, 0.f}}; }

Direction Direction::fromCode(int code)
{
	if(code < 0 || code > maxCode())
		throw std::invalid_argument{"invalid Direction code"};

	return Direction{code, directions.at(code)};
}

Direction Direction::fromRandom() 
{  
	static std::random_device rd;
	static std::mt19937 gen{rd()};
	static std::uniform_int_distribution<> distr{0, maxCode()};

	return fromCode(distr(gen));
}

}
