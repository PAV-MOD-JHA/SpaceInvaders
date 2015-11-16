#include "SFML/Graphics.hpp"

sf::RectangleShape PB_Rect(int posX, int posY, int windth, int height)
{
	sf::RectangleShape rect(sf::Vector2f(windth, height));
	rect.setPosition(posX, posY);
	rect.setFillColor(sf::Color(255, 160, 0, 255));
	return rect;

}