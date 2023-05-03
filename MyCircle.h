#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>

using namespace std;
using namespace sf;

class MyCircle {
private:
	CircleShape circle;

	double radius;
	double posX;
	double posY;
	double velocity;
	double dx;
	double dy;

public:
	MyCircle(); // default constructor
	MyCircle(double x, double y, double rad); // constructor by x, y, rad

	void setVelocity(double vel);
	double getVelocity();
	void setRadius(double rad);
	void setPosition(double x, double y);
	double getPosX();
	double getPosY();
	void setColor(int r, int g, int b);
	void move(double dx, double dy);
	void setdxdy(double dx, double dy);
	double getdx();
	double getdy();
	CircleShape getCircle();
	bool collisionTest(MyCircle obj); // collision test -> return true if collision
};

