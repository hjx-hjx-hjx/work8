#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;
int main() {
	Mat srcMat = imread("D:\\pic\\8_2.jpg");
	Mat srcMatg = imread("D:\\pic\\8_2.jpg", 0);
	Mat srcMat_th, dstMat, labMat, statMat, centMat;
	threshold(srcMatg, srcMat_th, 110, 255, THRESH_BINARY);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(9, 9));
	morphologyEx(srcMat_th, srcMat_th, MORPH_OPEN, kernel);
	//morphologyEx(srcMat_th, srcMat_th, MORPH_CLOSE, kernel);
	int number = connectedComponentsWithStats(srcMat_th, labMat, statMat, centMat);
	//cout << number << endl;
	int maxarea = statMat.at<int>(1, 4), no = 1;
	//cout << maxarea << endl;;
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
	rectangle(srcMat, rect, CV_RGB(255, 0, 0), 1, 8, 0);
	//cout << maxarea << "   " << no << endl;
	imshow("src", srcMat);
	waitKey(0);
}