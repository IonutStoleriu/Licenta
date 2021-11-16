#include "Functions.h"
void MyFilledCircle(Mat img, Point center)
{
	
	circle(img,
		center,
		3,
		Scalar(0, 255, 255),
		FILLED,
		LINE_8);
}
void MyLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = LINE_8;
	line(img,
		start,
		end,
		Scalar(255, 255, 255),
		thickness,
		lineType);
}