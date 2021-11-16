#include "opencv2/opencv.hpp"
#include <iostream>
#include "Functions.h"
#include "Drawing.h"
using namespace std;
using namespace cv;

int main() {

	/*
	//Video load
	VideoCapture cap("lane_fd.mp4");
	if (!cap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -1;
	}
	*/
	
	//Echo load

	HWND hwndDesktop = GetDesktopWindow();
	Mat frame = hwnd2mat(hwndDesktop);



	
	//Declarations
	Mat left_mirror, right_mirror, front_view;
	Mat wrap(480, 640, CV_8UC3);
	Mat maskYellow(480, 640, CV_8UC3);
	Point2f src_vertices[4];
	Mat whiteMask;
	Mat front;
	Mat f1, f2;
	
	const Size kernelSize = Size(9, 9);
	Mat kernel = Mat::ones(15, 15, CV_8U);
	const int thresholdVal = 115;

	vector<Point>allPts;
	vector<Point2f>outPts;

	src_vertices[0] = Point(350, 130);
	src_vertices[1] = Point(530, 130);
	
	src_vertices[2] = Point(800, 330);
	src_vertices[3] = Point(120, 330);
	
	
	Point2f dst_vertices[4];
	dst_vertices[0] = Point(0, 0);
	dst_vertices[1] = Point(640, 0);
	dst_vertices[2] = Point(640, 480);
	dst_vertices[3] = Point(0, 480);

	
	Mat maskWhite;
	
	Rect left_lane(0,420, 120, 60);
	Rect right_lane(520, 420, 120, 60);
	vector<Point>lane_points;

	int key = 0;
	while (key != 27) 
	{
		HWND hwndDesktop = GetDesktopWindow();
		Mat frame = hwnd2mat(hwndDesktop);
		/*Mat frame; 
		cap >> frame;
		if (frame.empty())
			break;
		*/

		//Selectarea zonelor de interes
		left_mirror = regionOfInterest(frame, left_mirror, 20, 99, 147, 225);
		right_mirror = regionOfInterest(frame, right_mirror, 1192, 99, 147, 225);
		front_view = regionOfInterest(frame, front_view, 225, 313, 910, 394);
		front= regionOfInterest(frame, front_view, 225, 313, 910, 394);
		whiteMask= regionOfInterest(frame, whiteMask, 225, 313, 910, 394);
		cvtColor(front_view, front_view, COLOR_RGB2GRAY);
		


		//threshold(front_view, front_view, thresholdVal, 255, THRESH_BINARY);
		transform(src_vertices, dst_vertices, front_view, wrap);
		transform(src_vertices, dst_vertices, front_view, maskYellow);
		
		
		
		//Drawing
		MyFilledCircle(front_view, src_vertices[0]);
		MyFilledCircle(front_view, src_vertices[1]);
		MyFilledCircle(front_view, src_vertices[2]);
		MyFilledCircle(front_view, src_vertices[3]); 
		MyLine(front_view, src_vertices[0], src_vertices[1]);
		MyLine(front_view, src_vertices[1], src_vertices[2]);
		MyLine(front_view, src_vertices[2], src_vertices[3]);
		MyLine(front_view, src_vertices[0], src_vertices[3]);
		
		//inRange(wrap, Scalar(0, 0, 0), Scalar(255, 255, 255), maskYellow);
		//inRange(wrap, Scalar(115, 115, 115), Scalar(255, 255, 255), maskWhite);
		
		//bitwise_and(maskYellow, maskWhite, wrap);
		//GaussianBlur(wrap, wrap, kernelSize, 0);
		dilate(wrap, wrap, kernel);
		erode(wrap, wrap, kernel);
		//morphologyEx(wrap, wrap, MORPH_CLOSE, kernel);
		threshold(wrap, wrap, thresholdVal, 255, THRESH_BINARY);
		threshold(wrap, maskYellow, thresholdVal, 255, THRESH_BINARY);

		//part2
		
		//vector<Point2f> pts = slidingWindow(wrap, Rect(0, 420, 150, 60));
		vector<Point> l_points; //Used for the end polygon at the end. 
		vector<Point> r_points;
		//perspectiveTransform(pts, outPts, wrap);
		//rectangle(wrap, Point(0, 480), Point(120,420 ),Scalar(250,0,0), 3, 8);
		
		//lane_points=slidingWindow(wrap, left_lane);
		lane_points =slidingWindow(wrap, left_lane);

		for (int i = 0; i < lane_points.size(); i++)
		{
			if (lane_points[i].x < 300)
			{
				l_points.push_back(lane_points[i]);
			}
			else
			{
				r_points.push_back(lane_points[i]);
			}
		}
		if(l_points.size()>=2)
		{ 
			for (int i = 0; i < l_points.size()-1; i++)
			{
				MyLine(wrap, l_points[i], l_points[i + 1]);
			}
		}
		if (r_points.size() >= 2)
		{
			for (int i = 0; i < r_points.size() - 1; i++)
			{
				MyLine(wrap, r_points[i], r_points[i + 1]);
			}
		}



		transform(dst_vertices, src_vertices, wrap, front_view);
		//Afisarea imaginilor 
		//imshow("LeftMirror", left_mirror);
	    //imshow("RightMirror", right_mirror);

		cvtColor(front_view,front_view, COLOR_GRAY2BGR);
		namedWindow("window3", WINDOW_NORMAL);
		resizeWindow("window3", 300, 225);
		//imshow("window3", frame);
		cvtColor(front_view, front_view, COLOR_BGR2GRAY);
		cvtColor(front, front, COLOR_BGR2GRAY);
		imshow("front_view",front_view+front);
		imshow("bird_eye_view",maskYellow);
	
		
		
		char c = (char)waitKey(100);
	
		if (c == 27)
			break;
	}
	//cap.release();
	cv::destroyAllWindows(); 
	return 0;
}