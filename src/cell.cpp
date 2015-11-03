/*
 * cell.cpp
 *
 *  Created on: 2 nov. 2015
 *      Author: lidan_000
 */

#include "opencv2/opencv.hpp"
#include "circle.cpp"

using namespace cv;

class Cell {
	/* d4's coordinates(x, y) represent the cell
	 *
	 * d4____d3
	 *  |    |
	 *  |____|
	 * d1	 d2
	 */
	public :
		int cell_size;

		Cell(int x, int y, int size) {
			cell_size = size;
			modify_coordinates(x, y);
		}

		~Cell() {

		}

		void modify_coordinates(int x, int y) {
			d1.x = x; d1.y = y+cell_size;
			d2.x = x+cell_size; d2.y = y+cell_size;
			d3.x = x+cell_size; d3.y = y;
			d4.x = x; d4.y = y;
		}


		void draw_by_16cases(Mat&scene, vector<Circle>&circles_group) {

			double f1 = vertex_is_in_circles(d1, circles_group);
			double f2 = vertex_is_in_circles(d2, circles_group);
			double f3 = vertex_is_in_circles(d3, circles_group);
			double f4 = vertex_is_in_circles(d4, circles_group);

			/* simple interpolation
			d43.x = d4.x+cell_size/2, d43.y = d4.y;
			d32.x = d4.x+cell_size; d32.y = d4.y+cell_size/2;
			d21.x = d4.x+cell_size/2; d21.y = d4.y+cell_size;
			d14.x = d4.x, d14.y = d4.y+cell_size/2;
			*/

			int num_case = 0;
			if(f1 > 1){ num_case+=1; }
			if(f2 > 1){ num_case+=2; }
			if(f3 > 1){ num_case+=4; }
			if(f4 > 1){ num_case+=8; }


			// linear interpolation
			Scalar line_color(0,255,0);
			switch (num_case) {
			case 0:
				break;
			case 1:
				d21.x = d2.x - cell_size*(1-f2)/(f1-f2); d21.y = d2.y;
				d14.x = d1.x; d14.y = d4.y + cell_size*(1-f4)/(f1-f4);
			    line(scene, d21, d14, line_color);
			    break;
			case 2:
				d32.x = d3.x; d32.y = d3.y + cell_size*(1-f3)/(f2-f3);
				d21.x = d1.x + cell_size*(1-f1)/(f2-f1); d21.y = d2.y;
				line(scene, d32, d21, line_color);
				break;
			case 3:
				d14.x = d1.x; d14.y = d4.y + cell_size*(1-f4)/(f1-f4);
				d32.x = d3.x; d32.y = d3.y + cell_size*(1-f3)/(f2-f3);
				line(scene, d14, d32, line_color);
				break;
			case 4:
				d43.x = d4.x + cell_size*(1-f4)/(f3-f4); d43.y = d4.y;
				d32.x = d3.x; d32.y = d2.y - cell_size*(1-f2)/(f3-f2);
				line(scene, d43, d32, line_color);
				break;
			case 5:
				d43.x = d4.x + cell_size*(1-f4)/(f3-f4); d43.y = d4.y;
				d32.x = d3.x; d32.y = d2.y - cell_size*(1-f2)/(f3-f2);
				d21.x = d2.x - cell_size*(1-f2)/(f1-f2); d21.y = d2.y;
				d14.x = d1.x; d14.y = d4.y + cell_size*(1-f4)/(f1-f4);
				line(scene, d14, d43, line_color);
				line(scene, d32, d21, line_color);
				break;
			case 6:
				d43.x = d4.x + cell_size*(1-f4)/(f3-f4); d43.y = d4.y;
				d21.x = d1.x + cell_size*(1-f1)/(f2-f1); d21.y = d2.y;
				line(scene, d43, d21, line_color);
				break;
			case 7:
				d14.x = d1.x; d14.y = d1.y - cell_size*(1-f1)/(f4-f1);
				d43.x = d3.x - cell_size*(1-f3)/(f4-f3); d43.y = d4.y;
				line(scene, d14, d43, line_color);
				break;
			case 8:
				d14.x = d1.x; d14.y = d1.y - cell_size*(1-f1)/(f4-f1);
				d43.x = d3.x - cell_size*(1-f3)/(f4-f3); d43.y = d4.y;
				line(scene, d14, d43, line_color);
				break;
			case 9:
				d43.x = d4.x + cell_size*(1-f4)/(f3-f4); d43.y = d4.y;
				d21.x = d1.x + cell_size*(1-f1)/(f2-f1); d21.y = d2.y;
				line(scene, d43, d21, line_color);
				break;
			case 10:
				d43.x = d3.x + cell_size*(1-f3)/(f4-f3); d43.y = d4.y;
				d32.x = d3.x; d32.y = d3.y + cell_size*(1-f3)/(f2-f3);
				d21.x = d1.x + cell_size*(1-f1)/(f2-f1); d21.y = d2.y;
				d14.x = d1.x; d14.y = d1.y - cell_size*(1-f1)/(f4-f1);
				line(scene, d43, d32, line_color);
				line(scene, d21, d14, line_color);
				break;
			case 11:
				d43.x = d4.x + cell_size*(1-f4)/(f3-f4); d43.y = d4.y;
				d32.x = d3.x; d32.y = d2.y - cell_size*(1-f2)/(f3-f2);
				line(scene, d43, d32, line_color);
				break;
			case 12:
				d14.x = d1.x; d14.y = d4.y + cell_size*(1-f4)/(f1-f4);
				d32.x = d3.x; d32.y = d3.y + cell_size*(1-f3)/(f2-f3);
				line(scene, d14, d32, line_color);
				break;
			case 13:
				d32.x = d3.x; d32.y = d3.y + cell_size*(1-f3)/(f2-f3);
				d21.x = d1.x + cell_size*(1-f1)/(f2-f1); d21.y = d2.y;
				line(scene, d32, d21, line_color);
				break;
			case 14:
				d21.x = d2.x - cell_size*(1-f2)/(f1-f2); d21.y = d2.y;
				d14.x = d1.x; d14.y = d4.y + cell_size*(1-f4)/(f1-f4);
				line(scene, d21, d14, line_color);
				break;
			case 15:
				break;
			}
		}


	private :
		Point d1, d2, d3, d4;
		Point d43, d32, d21, d14;

		//if result > 1 => vertex in circles
		double vertex_is_in_circles( Point&vertex, vector<Circle>&circles_group ) {
			double result = 0;
			for(vector<Circle>::iterator it = circles_group.begin(), itend = circles_group.end(); it != itend; it++) {
				Point center = it->center;
				int radius = it->radius;
				//it is not good to use "sqrt"
				result += (double)pow(radius, 2)/(pow(vertex.y-center.y,2)+pow(vertex.x-center.x,2));
			}
			return result;
		}

};

//void render_whole_cell(Mat&scene, int row, int col, int cell_size){
//	scene.rowRange(row, row+cell_size).colRange(col, col+cell_size).setTo(Scalar(0,255,0));
//}


