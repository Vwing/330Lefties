#pragma once

#include <vector>
#include <math.h>
// #include "Unit.h"

class AI
{
public:
	//constructor currently takes a pointer to x and y. can use other constructor with unit class.
	AI(int x, int y);
	//this constructor takes a pointer to a unit
	// AI(Unit* u);
	~AI(void);

	//patterns
	//sets movement to move x and y pixels
	void move(int x, int y);
	//sets movement to target the set target at s speed when in x and y range. only x makes the unit only follow the x position
	//use with another movement pattern such as patrol and target if in range
	void movement_target(int s, int x_range, int y_range, bool only_x = false);
	//sets movement to move back and forth x,y pixels for s steps
	void patrol(int x, int y, int s);
	//sets movement to move sequentially through pathway vector and looping through it
	void movement_path();
	//updates according to the set movement
	void update();

	//sets a target given a pointer to x and y
	void set_target(int x, int y);
	//adds a path to pathway vector
	void set_path(int x, int y, int steps);

	bool target_range(int x, int y);
	int getX();
	int getY();
	//call to reverse x or y movement
	void flip_x();
	void flip_y();

private:
	void movex(int x);
	void movey(int y);
	void move_to_targetX(int speed);
	void move_to_target(int speed);
	void pacex(int speed, int steps);
	void pacey(int speed, int steps);
	void move_path();
	int x;
	int y;
	int targetx;
	int targety;
	int pacing;
	bool pace_reverse;
	struct path
	{
		int move_x;
		int move_y;
		int steps;
	};
	std::vector<path> pathway;
	int path_index;
	int path_step;
	int pattern;
	int move_x;
	int move_y;
	int speed;
	int steps;
	int xrange;
	int yrange;
	bool target_only_x;
	bool reverse_x;
	bool reverse_y;
};
