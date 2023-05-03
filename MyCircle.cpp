#include "MyCircle.h"

MyCircle::MyCircle() { // default constructor
	posX = 0;
	posY = 0;
	radius = 10;
	velocity = 2;

	circle.setPosition(posX, posY);
	circle.setRadius(radius);
	circle.setFillColor(Color(0, 255, 0)); // circle color RGB
	circle.setPointCount(30);
}

MyCircle::MyCircle(double x, double y, double rad) { // constructor by x, y, rad
	posX = x;
	posY = y;
	radius = rad;
	velocity = 2;
	circle.setPosition(posX, posY);
	circle.setRadius(radius);
	circle.setFillColor(Color(0, 255, 0)); // circle color RGB
	circle.setPointCount(30);
}

void MyCircle::setVelocity(double vel) {
	velocity = vel;
}

double MyCircle::getVelocity() {
	return velocity;
}

void MyCircle::setRadius(double rad) {
	radius = rad;
}

void MyCircle::setPosition(double x, double y) {
	posX = x;
	posY = y;
	circle.setPosition(x, y);
}

double MyCircle::getPosX() {
	return posX;
}

double MyCircle::getPosY() {
	return posY;
}

void MyCircle::setColor(int r, int g, int b) {
	circle.setFillColor(Color(r, g, b));
}

void MyCircle::move(double dx, double dy) {
	posX += dx;
	posY += dy;
	circle.move(dx, dy);
}

double MyCircle::getdx() {
	return this->dx;
}

double MyCircle::getdy() {
	return this->dy;
}

void MyCircle::setdxdy(double dx, double dy) {
	this->dx = dx;
	this->dy = dy;
}

CircleShape MyCircle::getCircle() {
	return circle;
}

bool MyCircle::collisionTest(MyCircle obj) {
	double d = sqrt(pow(((posX + radius) - (obj.posX + obj.radius)), 2) + pow(((posY + radius) - (obj.posY + obj.radius)), 2));

	if (d <= (radius + obj.radius)) {
		return true;
	}
	else {
		return false;
	}
}