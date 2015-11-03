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

	vector<Circle> circles_group;

	Circle c1(Point(300, 200), 100, Point(2,1));
	circles_group.push_back(c1);

	Circle c2(Point(500, 300), 60, Point(-4, 1));
	circles_group.push_back(c2);

	Circle c3(Point(400, 400), 80, Point(8, 1));
	circles_group.push_back(c3);


	//-----------------------------------------------------------------

	Cell cell(0, 0, cell_size);
    while(1) {

		// add grills in the scene
		for(int r = 0; r < scene.rows; r+=cell_size) {
			for(int c = 0; c < scene.cols; c+=cell_size) {
				scene.colRange(c, c+1).setTo(Scalar(255,0,0));//grill colon
			}
			scene.rowRange(r, r+1).setTo(Scalar(255,0,0));//grill row
		}

    	// control circles' movement
    	for(vector<Circle>::iterator it = circles_group.begin(), itend = circles_group.end(); it != itend; it++) {
    		it->move_center(it->direction);
    		it->spring_at_edge(scene);

    		// add circles in the scene
    		circle(scene, it->center, it->radius, Scalar(0,0,255));
    	}

    	// cells' case
		for(int r = 0; r < scene.rows; r+=cell_size) {
			for(int c = 0; c < scene.cols; c+=cell_size) {
				cell.modify_coordinates(c, r);
				cell.draw_by_16cases(scene, circles_group);
			}
		}

		imshow("Demo", scene);
		if(waitKey(25) > 0 || !cvGetWindowHandle("Demo")) break;
		scene.setTo(Scalar(0,0,0));

	}

    return 0;

}
