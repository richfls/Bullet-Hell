#include "missiles.h"
#include "globals.h"
#include "SFML/Graphics.hpp"
#include<math.h>

missile::missile() {
	xpos = 0;
	ypos = 0;
	alive = false;
}

missile::~missile() {}

missile::missile(int x, int y, sf::Sprite sprite) {
	xpos = x;
	ypos = y;
	alive = false;
	image = sprite;
}

missile::missile(int x, int y) {
	xpos = x;
	ypos = y;
	alive = false;
}
void missile::move() {
	ypos -= 5;
}
void missile::draw(sf::RenderWindow& window) {
	if (alive) {
		image.setPosition(xpos, ypos);
		window.draw(image);
	}
}

void missile::kill() {
	alive = false;
}

bool missile::offscreen() {
	if (ypos < 0)
		return true;
	else
		return false;
}
void missile::shoot(int x, int y) {
	alive = true;
	xpos = x;
	ypos = y;
}

bool missile::isalive() {
	return alive;
}

bool missile::collide(double x, double y) {
	if (sqrt((x - xpos) * (x - xpos) + (y - ypos) * (y - ypos)) < 32) {
		return true;
	}
	else
		return false;
}
int missile::getx() {
	return xpos;
}
int missile::gety() {
	return ypos;
}