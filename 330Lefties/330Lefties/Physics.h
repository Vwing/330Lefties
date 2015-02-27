#ifndef PHYSICS_H
#define PHYSICS_H

class Physics{
public:
	int x, y, width, height;
	double gravity = -1;

	void setPos(int ex, int why){
		x = ex;
		y = why;
	}

	void set_width_height(int w, int h){
		width = w;
		height = h;
	}

	void check_collision(){
		if (y + height > 480){ //bottom
			y = 480 - height;
			gravity = -1;
		}
		else if (y < 0)  //top
			y = 0;
		if (x + width > 640)  //right
			x -= width / 20;
		else if (x < 0) //left
		x = 0;
	}

	void update(int& x, int& y){
		gravity = gravity*1.04;
		y -= gravity;
		check_collision();
	}

};


#endif
