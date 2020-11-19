#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;
int main() {
	Mat src_color = imread("D:\\pic\\8_3.jpg");
	Size Resize = Size(src_color.cols / 10, src_color.rows / 10);
	Mat src, srcMat_th, src_th, srcg, labMat, statMat, centMat;
	resize(src_color, src, Resize, INTER_LINEAR);
	src.copyTo(srcMat_th);
	int height = srcMat_th.rows;
	int width = srcMat_th.cols;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			uchar p = 110;
			if (srcMat_th.at<Vec3b>(i, j)[2] > p && srcMat_th.at<Vec3b>(i, j)[0] < 105 && srcMat_th.at<Vec3b>(i, j)[1] < 105) {
				srcMat_th.at<Vec3b>(i, j)[0] = 255;
				srcMat_th.at<Vec3b>(i, j)[1] = 255;
				srcMat_th.at<Vec3b>(i, j)[2] = 255;
			}
			else {
				srcMat_th.at<Vec3b>(i, j)[0] = 0;
				srcMat_th.at<Vec3b>(i, j)[1] = 0;
				srcMat_th.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}

	Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
	morphologyEx(srcMat_th, srcMat_th, MORPH_CLOSE, kernel);
	cvtColor(srcMat_th, srcg, CV_BGR2GRAY);
	threshold(srcg, src_th, 110, 255, THRESH_BINARY);
	int number = connectedComponentsWithStats(src_th, labMat, statMat, centMat);
	int maxarea = statMat.at<int>(1, 4), no = 1;
	for (int i = 2; i < number; i++) {
		if (statMat.at<int>(i, 4) > maxarea) {
			maxarea = statMat.at<int>(i, 4);
			no = i;
		}
	}
	Rect rect;
	rect.x = statMat.at<int>(no, 0);
	rect.y = statMat.at<int>(no, 1);
	rect.width = statMat.at<int>(no, 2);
	rect.height = statMat.at<int>(no, 3);
	rectangle(src, rect, CV_RGB(255, 0, 0), 1, 8, 0);

	imshow("aa", src);
	waitKey(0);
}