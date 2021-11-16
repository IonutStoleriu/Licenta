#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <Windows.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat hwnd2mat(HWND hwnd);
void transform(Point2f* src_vertices, Point2f* dst_vertices, Mat& src, Mat &dst);
void GetAllWindowsFromProcessID(DWORD dwProcessID, std::vector <HWND> &vhWnds);
void Dilation(Mat src, Mat dilation_dst);
void Erozion(Mat src, Mat erozion_dst);
Mat regionOfInterest(Mat src, Mat dst, int x1, int y1, int x2, int y2);
vector<Point> slidingWindow(Mat image, Rect window);
vector<Point> r_slidingWindow(Mat image, Rect window);