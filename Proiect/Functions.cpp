#include "Functions.h"

Mat hwnd2mat(HWND hwnd)
{
	HDC hwindowDC, hwindowCompatibleDC;

	int height, width, srcheight, srcwidth;
	HBITMAP hbwindow;
	Mat src;
	BITMAPINFOHEADER  bi;

	hwindowDC = GetDC(hwnd);
	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

	RECT windowsize;    // get the height and width of the screen
	GetClientRect(hwnd, &windowsize);

	//srcheight = windowsize.bottom;
	//srcwidth = windowsize.right;
	srcheight = 767;
	srcwidth = 1359;
	height = 767;  //change this to whatever size you want to resize to
	width = 1359;

	src.create(height, width, CV_8UC4);


	// create a bitmap
	hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
	bi.biWidth = width;
	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	// use the previously created device context with the bitmap
	SelectObject(hwindowCompatibleDC, hbwindow);
	// copy from the window device context to the bitmap device context
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

																									   // use the previously created device context with the bitmap
	DeleteObject(hbwindow);
	DeleteDC(hwindowCompatibleDC);
	ReleaseDC(hwnd, hwindowDC);

	return src;
}

void transform(Point2f* src_vertices, Point2f* dst_vertices, Mat& src, Mat &dst) {
	
	Mat M = getPerspectiveTransform(src_vertices, dst_vertices);
	warpPerspective(src, dst, M, dst.size(), INTER_LINEAR, BORDER_CONSTANT);
}

void GetAllWindowsFromProcessID(DWORD dwProcessID, std::vector <HWND> &vhWnds)
{
	// find all hWnds (vhWnds) associated with a process id (dwProcessID)
	HWND hCurWnd = NULL;
	do
	{
		hCurWnd = FindWindowEx(NULL, hCurWnd, NULL, NULL);
		DWORD dwProcID = 0;
		GetWindowThreadProcessId(hCurWnd, &dwProcID);
		if (dwProcID == dwProcessID)
		{
			vhWnds.push_back(hCurWnd);  // add the found hCurWnd to the vector
										//printf("Found hWnd %\n", hCurWnd);
		}
	} while (hCurWnd != NULL);
}
void Dilation(Mat src, Mat dilation_dst)
{
	int dilation_elem = 0;
	int dilation_type = 0;
	int dilation_size = 5;

	if (dilation_elem == 0)
	{
		dilation_type = MORPH_RECT;
	}
	else if (dilation_elem == 1)
	{
		dilation_type = MORPH_CROSS;
	}
	else if (dilation_elem == 2)
	{
		dilation_type = MORPH_ELLIPSE;
	}
	Mat element = getStructuringElement(dilation_type, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
	dilate(src, dilation_dst, element);
}
void Erozion(Mat src, Mat erozion_dst)
{
	int erozion_elem = 0;
	int erozion_type = 0;
	int erozion_size = 5;
	if (erozion_elem == 0)
	{
		erozion_type = MORPH_RECT;
	}
	else if (erozion_elem == 1)
	{
		erozion_type = MORPH_CROSS;
	}
	else if (erozion_elem == 2)
	{
		erozion_type = MORPH_ELLIPSE;
	}
	Mat element = getStructuringElement(erozion_type, Size(2 * erozion_size + 1, 2 * erozion_size + 1), Point(erozion_size, erozion_size));
	erode(src, erozion_dst, element);

}
Mat regionOfInterest(Mat src, Mat dst,int x1, int y1, int x2, int y2)
{
	Rect roi(x1, y1, x2, y2);
    dst = src(roi);
	return dst;
}
vector<Point> slidingWindow(Mat image, Rect window)
{
	Rect r_window(520, 0, 120, 60);
	Rect l_window(0, 420, 150, 60);
	Point start(20, 480);
	Point end(540, 480);
	
	vector<Point> points;
	//points.push_back(start);
	const Size imgSize = image.size();
	bool shouldBreak = false;
	while (true)
	{
		int x=0;
		int currentX = window.x + window.width/2;
		Mat roi = image(window);
		vector<Point> locations;
		locations.clear();
		
		findNonZero(roi, locations);
		
		int avgX = 0;
		
		for (int i = 0; i < locations.size(); ++i)
		{
			int x = locations[i].x;
			avgX +=window.x+x;
		}
		
		avgX = locations.empty() ? currentX : avgX / locations.size();
		Point point(avgX, window.y + window.height / 2);
		if (!locations.empty())
		{
			points.push_back(point);
		}

		if (shouldBreak==true)
 		{
			
		
			printf("\ncurrentx=%d", currentX);
			rectangle(image, Point(window.x, window.y), Point(window.x + window.width, window.y + window.height), Scalar(250, 0, 0), 3, 8);
			window.x =(point.x-(window.width/2));
			printf("\n0Hai sa vedem cat e inainte widnow.x=%d si punctul este %d \n", window.x, point.x);
			if (window.x < 400)
			{
				window.x = 520;
			}
			else if (window.x > 520)
			{
				window.x = 520;
			}
			printf("\n0Hai sa vedem cat e widnow.x=%d\n", window.x);
			
			

			window.y += window.height;
			if (window.y > 460)
			{
				window.y = 460;
				window = l_window;
				//points.push_back(end);
				break;
			}
			
		}
		else
		{
			rectangle(image, Point(window.x, window.y), Point(window.x + window.width, window.y + window.height), Scalar(250, 0, 0), 3, 8);
		
			window.x += (point.x - currentX);
			if (window.x < 0)
			{
				window.x = 0;
			}
			window.y -= window.height;
			if (window.y < 0)
			{
				window=r_window;
				shouldBreak = true;
			}
		
		}

	}
	return points;
}
