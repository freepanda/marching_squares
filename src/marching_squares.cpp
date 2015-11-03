//============================================================================
// Name        : marching_squares.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include "cell.cpp"

using namespace cv;
using namespace std;

//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\""   );
int main(void) {

	Mat scene(600, 1000, CV_8UC3, Scalar(0,0,0));
	int cell_size = 40;

	int rate = 25;
	int nb_circles = 3;
	Point centers[] = {Point(500, 300), Point(400, 400), Point(300, 200)};
	int radiuses[] = {60, 80, 100};

	// directions of circles' movement
	Point directions[] = {Point(-4, 1), Point(8, 1), Point(2,1)};


	//-----------------------------------------------------------------

	Point center;
	int radius;
	Cell cell(0, 0, cell_size);
    while(1) {

    	// control circles' movement
    	for(int i = 0; i < nb_circles; i++) {
			centers[i].x += directions[i].x;
			centers[i].y += directions[i].y;
			center = centers[i];
			radius = radiuses[i];
			if(center.x-radius < 0 || center.x+radius > scene.cols) {
				directions[i].x = -directions[i].x;
			}

			if(center.y-radius < 0 || center.y+radius > scene.rows) {
				directions[i].y = -directions[i].y;
			}
    	}


		// add grills in the scene
		for(int r = 0; r < scene.rows; r+=cell_size) {
			for(int c = 0; c < scene.cols; c+=cell_size) {
				scene.colRange(c, c+1).setTo(Scalar(255,0,0));//grill colon
			}
			scene.rowRange(r, r+1).setTo(Scalar(255,0,0));//grill row
		}


		// add circles in the scene
    	for(int i = 0; i < nb_circles; i++){
    		center = centers[i];
    		radius = radiuses[i];
    		circle(scene, center, radius, Scalar(0,0,255));
    	}


    	// cells' case
		for(int r = 0; r < scene.rows; r+=cell_size) {
			for(int c = 0; c < scene.cols; c+=cell_size) {
				cell.modify_coordinates(c, r);
				cell.render_16cases(scene, nb_circles, centers, radiuses);
			}
		}

		imshow("Demo", scene);
		if(waitKey(rate) > 0 || !cvGetWindowHandle("Demo")) break;
		scene.setTo(Scalar(0,0,0));

	}

    return 0;

}
