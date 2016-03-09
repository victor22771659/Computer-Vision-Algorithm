#include <stdio.h>
#include <iostream>
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;
const char *windowDisparity = "Disparity";

int main(int argc, char** argv)
{
	//Read the images
	Mat imgLeft = imread("scene1.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat imgRight = imread("scene2.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	//Declare disparity map
	Mat imgDisparity = Mat::zeros(imgLeft.rows, imgLeft.cols, CV_8UC1);

	int windowSize = 3, searchRange = 32;

	int height = imgLeft.cols;
	int width = imgLeft.rows;
	double* localSAD = new double[searchRange];
	int x = 0, y = 0, d = 0, m = 0;


	Mat winImg(Size(3, 3),CV_8UC1);
	Mat leftROI(Size(3, 3),CV_8UC1);
	Mat rightROI(Size(3, 3),CV_8UC1);

	double sumation;
	for (y = 0; y < height-windowSize; y++)
	{
		for (x = searchRange-1; x < width-(searchRange-1); x++)
		{
			leftROI = imgLeft(Rect(x, y, windowSize, windowSize));
			d = 0;
			for (m = 0; m < searchRange; m++)
				localSAD[m] = 0;
			for (d = 0; d < searchRange; d++)
			{
				rightROI = imgRight(Rect(x - d, y, windowSize, windowSize));
				absdiff(leftROI, rightROI, winImg);
				sumation = sum(winImg)[0];
				localSAD[d] = sumation;
			}
			//to find the best d and store
			double min = localSAD[0];
			int minIndex = 0;
			for (int i = 0; i < searchRange; i++){
				if (localSAD[i] < min){
					min = localSAD[i];
					minIndex = i;
				}
			}
			imgDisparity.at<unsigned char>(y, x) = minIndex*(255 / searchRange);
		}
	}
	namedWindow(windowDisparity, 1);
	imshow(windowDisparity, imgDisparity);
	delete[] localSAD;
	return 0;
}