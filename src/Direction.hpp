#pragma once

#include <SFML/System/Vector2.hpp>

#include <array>
#include <random>
#include <stdexcept>
#include <algorithm>


namespace tf
{

class Direction
{
public:
	sf::Vector2f ToVector2f() const;
	int code() const;
	static int maxCode();

	Direction inversed() const;
	
	static Direction forward();
	static Direction backward();
	static Direction left();
	static Direction right();

	static Direction fromCode(int code);
	static Direction fromRandom();

	friend bool operator==(const Direction& lhs, const Direction& rhs)
	{
		return lhs.code() == rhs.code();
	}
	friend bool operator!=(const Direction& lhs, const Direction& rhs)
	{
		return !(lhs == rhs);
	}

private:
	explicit Direction(int code, sf::Vector2f dir);

private:
	static const std::array<sf::Vector2f, 4> directions;

private:
	int code_;
	sf::Vector2f dir_;
};

}
