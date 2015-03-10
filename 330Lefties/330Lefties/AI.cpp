#include "AI.h"

AI::AI(int* x, int* y)
{
	this->x = x;
	this->y = y;
	pacing = 0;
	pace_reverse = false;
	path_index = 0;
	path_step = 0;
	reverse_x = false;
	reverse_y = false;
	xrange = 0;
	yrange = 0;
}

AI::~AI(void)
{
}

/*AI::AI(unit* u)
{
	this->x = &u->x;
	this->y = &u->y;
	pacing = 0;
	pace_reverse = false;
	path_index = 0;
	path_step = 0;
	reverse_x = false;
	reverse_y = false;
	xrange = 0;
	yrange = 0;
}*/

void AI::move(int x, int y)
{
	move_x = x;
	move_y = y;
	pattern = 1;
}

void AI::movement_target(int s, int x_range, int y_range, bool only_x)
{
	speed = s;
	xrange = x_range;
	yrange = y_range;
	target_only_x = only_x;
}

void AI::patrol(int x, int y, int s)
{
	move_x = x;
	move_y = y;
	steps = s;
	pattern = 2;
}

void AI::movement_path()
{
	pattern = 3;
}

void AI::update()
{
	if (target_range(xrange, yrange))
	{
		if (target_only_x)
			move_to_targetX(speed);
		else
			move_to_target(speed);
	}
	else if (pattern == 1)
	{
		movex(move_x);
		movey(move_y);
	}
	else if (pattern == 2)
	{
		pacex(move_x, steps);
		pacey(move_y, steps);
	}
	else if (pattern == 3)
		move_path();
}

void AI::set_target(int* x, int* y)
{
	targetx = x;
	targety = y;
}

void AI::set_path(int x, int y, int steps)
{
	path p;
	p.move_x = x;
	p.move_y = y;
	p.steps = steps;
	pathway.push_back(p);
}

bool AI::target_range(int rangex, int rangey)
{
	if (rangex == 0 && rangey == 0)
		return false;
	return (abs(*targetx - *x) < rangex && abs(*targety - *y) < rangey);
}

void AI::flip_x()
{
	reverse_x = !reverse_x;
}

void AI::flip_y()
{
	reverse_y = !reverse_y;
}

void AI::movex(int movementx)
{
	if (reverse_x == true)
		movementx = -movementx;
	*x += movementx;
}

void AI::movey(int movementy)
{
	if (reverse_y == true)
		movementy = -movementy;
	*y += movementy;
}

void AI::move_to_targetX(int speed)
{
	if (!(*targetx == *x && *targety == *y))
	{
	double tempx = *targetx - *x;
	double tempy = *targety - *y;
	double hypotenus = sqrt(tempx*tempx + tempy*tempy);
	tempx = tempx / hypotenus;
	tempx = tempx * speed;
	int movementx;
	if (tempx > 0)
		movementx = ceil(tempx);
	else
		movementx = floor(tempx);
	if (reverse_x == true)
		movementx = -movementx;
	*x += movementx;
	}
}

void AI::move_to_target(int speed)
{
	if (!(*targetx == *x && *targety == *y))
	{
	double tempx = *targetx - *x;
	double tempy = *targety - *y;
	double hypotenus = sqrt(tempx*tempx + tempy*tempy);
	tempx = tempx / hypotenus;
	tempy = tempy / hypotenus;
	tempx = tempx * speed;
	tempy = tempy * speed;
	int movementx;
	int movementy;
	if (tempx > 0)
		movementx = ceil(tempx);
	else
		movementx = floor(tempx);
	if (tempy > 0)
		movementy = ceil(tempy);
	else
		movementy = floor(tempy);
	if (reverse_x == true)
		movementx = -movementx;
	if (reverse_y == true)
		movementy = -movementy;
	*x += movementx;
	*y += movementy;
	}
}

void AI::pacex(int speed, int steps)
{
	if (pacing == steps)
	{
		pace_reverse = !pace_reverse;
		pacing = 0;
	}
	if (pace_reverse == false)
		*x += speed;
	else
		*x -= speed;
	pacing+=1;
}

void AI::pacey(int speed, int steps)
{
	if (pacing == steps)
	{
		pace_reverse = !pace_reverse;
		pacing = 0;
	}
	if (pace_reverse == false)
		*y += speed;
	else
		*y -= speed;
	pacing+=1;
}

void AI::move_path()
{
	int movementx = pathway[path_index].move_x;
	int movementy = pathway[path_index].move_y;
	if (reverse_x == true)
		movementx = -movementx;
	if (reverse_y == true)
		movementy = -movementy;
	*x += movementx;
	*y += movementy;
	path_step += 1;
	if (path_step > pathway[path_index].steps)
	{
		path_step = 0;
		path_index += 1;
		if (path_index >= pathway.size())
			path_index = 0;
	}
}