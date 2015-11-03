/*
 * circle.cpp
 *
 *  Created on: 3 nov. 2015
 *      Author: lidan_000
 */


#include "opencv2/opencv.hpp"

using namespace cv;

class Circle {
	public :
		Point center;
		int radius;
		Point direction;

		Circle(Point center, int radius, Point direction) {
			this->center = center;
			this->radius = radius;
			this->direction = direction;
		}

		~Circle() {

		}

		void move_center(Point&displacement) {
			center.x += displacement.x;
			center.y += displacement.y;
		}

		void spring_at_edge(Mat&scene) {
			if(center.x-radius < 0 || center.x+radius > scene.cols) {
				direction.x = -direction.x;
			}

			if(center.y-radius < 0 || center.y+radius > scene.rows) {
				direction.y = -direction.y;
			}
		}

	private:

};

