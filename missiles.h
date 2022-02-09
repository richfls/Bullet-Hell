#pragma once
#include "globals.h"
#include "SFML/Graphics.hpp"

class missile {
private:
	int xpos;
	int ypos;
	bool alive;
	sf::Sprite image;

public:
	missile();
	~missile();
	missile(int x, int y, sf::Sprite sprite);
	missile(int x, int y);
	void move();
	void draw(sf::RenderWindow& window);
	void kill();
	bool offscreen();
	void shoot(int x, int y);
	bool isalive();
	bool collide(double x, double y);
	int getx();
	int gety();
};