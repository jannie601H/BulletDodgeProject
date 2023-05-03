#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <cmath>
#include <random>
#include <windows.h>
#include "MyCircle.h"

using namespace std;
using namespace sf;

MyCircle setEnemy(MyCircle player);

int main() { 
	cout << "GAME START" << endl;

	int nX = 1600; // display size
	int nY = 900;
	RenderWindow window(VideoMode(nX, nY), "Moving Ball");
	window.setFramerateLimit(100);

	// Player circle info
	double pRadius = 10;
	double pPosX = 800;
	double pPosY = 450;
	double pVelocity = 4;

	MyCircle player{ pPosX, pPosY, pRadius }; // set player circle
	player.setVelocity(pVelocity);
	player.setColor(52, 204, 255); // player color set blue

	// enemy list
	int enemyNum = 39; // enemy number
	vector <MyCircle> enemyLst;
	for (int i = 0; i < enemyNum; i++) {
		enemyLst.push_back(setEnemy(player));
	}
	int flag = 0; // flag for increasing enemyNum

	// magEnemy list
	double eRadius = 7;

	MyCircle magEnemy{ 0, 0, eRadius };
	magEnemy.setColor(225, 50, 50); // magEnemy color set red

	int magEnemyNum = 0; // player following enemy number
	vector <MyCircle> magEnemyLst;
	//for (int i = 0; i < magEnemyNum; i++) {
	//	magEnemyLst.push_back(magEnemy); //setmagenemy
	//}

	Text tTime; // display time
	Text tEnemy; // dispaly enemy

	Font font;
	int t = 0;
	int e = 0;

	if (!font.loadFromFile("C:\\Users\\qkqcu\\source\\repos\\Bullet Dodge\\Bullet Dodge\\arial.ttf")) { // check font file route!
		//C:\\Users\\qkqcu\\source\\repos\\Bullet Dodge\\Bullet Dodge\\arial.ttf"
		return 42; // Robust error handling!
	}

	// time text set
	tTime.setFont(font);
	tTime.setCharacterSize(25);
	tTime.setFillColor(Color::White);
	tTime.setPosition(1525, 860);

	// enemy num text set
	tEnemy.setFont(font);
	tEnemy.setCharacterSize(25);
	tEnemy.setFillColor(Color::Magenta);
	tEnemy.setPosition(0, 0);

	clock_t time = clock();

	// game loop
	while (window.isOpen()) {
		// check event
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
		}

		// move player circle by keyboard
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			player.move(0, -player.getVelocity());
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			player.move(0, player.getVelocity());
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			player.move(-player.getVelocity(), 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right)) {
			player.move(player.getVelocity(), 0);
		}
		

		// move enemy -> follows player
		for (int i = 0; i < magEnemyNum; i++) {
			double l = sqrt(pow(player.getPosX() - magEnemyLst[i].getPosX(), 2) + pow(player.getPosY() - magEnemyLst[i].getPosY(), 2));
			double dx = (player.getPosX() - magEnemyLst[i].getPosX()) / (l/2);
			double dy = (player.getPosY() - magEnemyLst[i].getPosY()) / (l/2);
			magEnemyLst[i].setdxdy(dx, dy);
			magEnemyLst[i].move(magEnemyLst[i].getdx(), magEnemyLst[i].getdy());
		}

		// move enemy -> toward player
		for (int i = 0; i < enemyNum; i++) {
			enemyLst[i].move(enemyLst[i].getdx(), enemyLst[i].getdy());
			if (enemyLst[i].getPosX() >= window.getSize().x || enemyLst[i].getPosX() <= 0 || enemyLst[i].getPosY() >= window.getSize().y || enemyLst[i].getPosY() <= 0) {
				
				// enemy 가 화면 밖으로 나갈 시 객체 소멸
				enemyLst.erase(enemyLst.begin() + i);
				enemyNum -= 1;

				// 새로운 enemy 객체 생성
				enemyLst.push_back(setEnemy(player));
				enemyNum += 1;
			}
		}

		//collision test . enemy
		for (int i = 0; i < enemyNum; i++) {
			if (player.collisionTest(enemyLst[i])) {
				// game over
				cout << "GAME OVER" << endl;
				cout << "Your score is " + to_string(time) << endl;
				window.close();
			}
		}
		//collision test . magEnemy
		for (int i = 0; i < magEnemyNum; i++) {
			if (player.collisionTest(magEnemyLst[i])) {
				// game over
				cout << "GAME OVER" << endl;
				cout << "Your score is " + to_string(time) << endl;
				window.close();
			}
		}

		time = clock();
		time = time / CLOCKS_PER_SEC;
		tTime.setString(to_string(time) + " sec");
		tEnemy.setString("Enemy: " + to_string(enemyNum + magEnemyNum));

		// 15초가 지나면 magEnemy 생성
		if (time == 15 && magEnemyNum == 0) {
			magEnemyLst.push_back(magEnemy);
			magEnemyNum += 1;
		}

		// 5초마다 enemy 객체 추가
		if (time % 5 == 0 && flag == 0) {
			enemyLst.push_back(setEnemy(player));
			enemyNum++;
			flag++;
		}

		// enemy 생성 제한
		if (time % 5 == 1) {
			flag = 0;
		}

		
		// erase monitor
		window.clear();

		// draw enemy
		for (int i = 0; i < enemyNum; i++) {
			window.draw(enemyLst[i].getCircle());
		}
		
		// draw magEnemy
		for (int i = 0; i < magEnemyNum; i++) {
			window.draw(magEnemyLst[i].getCircle());
		}

		// draw player
		window.draw(player.getCircle());
		
		// draw text
		window.draw(tTime);
		window.draw(tEnemy);

		// display monitor
		window.display();
	}
	
	return 0;
 }

 // function set enemy
 MyCircle setEnemy(MyCircle player) { // player 의 위치를 입력받아 enemy의 vector를 player를 향하도록 생성
	 //generate random device
	 random_device rd;
	 mt19937 gen(rd());
	 uniform_int_distribution<int> startposX(20, 1580); // starting x point seed
	 uniform_int_distribution<int> startposY(20, 880); // starting y point seed
	 uniform_int_distribution<int> randdirection(0, 3); // raandom direction 0 ~ 3
	 uniform_int_distribution<int> randomVel(100, 200); // random velocity

	 double eRadius = 4;
	 double eVelocity = 2;

	 MyCircle enemy{ 0, 0, eRadius }; // set enemy circle
	 enemy.setColor(255, 255, 0); // enemy color set yellow

	 int dir = randdirection(gen);
	 if (dir == 0) {
		enemy.setPosition(startposX(gen), 10); // set enemy position top
	 }
	 else if (dir == 1) {
		 enemy.setPosition(1590, startposY(gen)); // set enemy position right
	 }
	 else if (dir == 2) {
		 enemy.setPosition(startposX(gen), 890); // set enemy position bottom
	 }
	 else if (dir == 3) {
		 enemy.setPosition(10, startposY(gen)); // set enemy position left
	 }

	 // set enemy vector twoard player
	 double l = sqrt(pow(player.getPosX() - enemy.getPosX(), 2) + pow(player.getPosY() - enemy.getPosY(), 2));
	 double dx = (player.getPosX() - enemy.getPosX()) / (l / (randomVel(gen) / 50));
	 double dy = (player.getPosY() - enemy.getPosY()) / (l / (randomVel(gen) / 50));
	 enemy.setdxdy(dx, dy);

	 return enemy;
 }
