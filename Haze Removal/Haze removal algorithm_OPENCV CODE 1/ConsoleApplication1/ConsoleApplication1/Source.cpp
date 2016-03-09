#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <vector>       // std::vector

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	// READ RGB color image and convert it to Lab
	Mat bgr_image = imread("15561507_0.jpg");
	Mat lab_image;
	cvtColor(bgr_image, lab_image, CV_BGR2Lab);

	// Extract the L channel
	vector<Mat> lab_planes(3);
	split(lab_image, lab_planes);  // now we have the L image in lab_planes[0]

	// apply the CLAHE algorithm to the L channel
	Ptr<CLAHE> clahe = createCLAHE();
	clahe->setClipLimit(4);
	Mat dst;
	clahe->apply(lab_planes[0], dst);

	// Merge the the color planes back into an Lab image
	dst.copyTo(lab_planes[0]);
	merge(lab_planes, lab_image);

	// convert back to RGB
	Mat image_clahe;
	cvtColor(lab_image, image_clahe, CV_Lab2BGR);

	// display the results  (you might also want to see lab_planes[0] before and after).
	imshow("image original", bgr_image);
	imshow("image CLAHE", image_clahe);

	imwrite("result.jpg",image_clahe);
	//Bluring Image
	Mat blurImg;
	blur(image_clahe, blurImg, Size(bgr_image.cols, bgr_image.rows));
	imshow("blurImg", blurImg);
	waitKey();
	return 0;
}