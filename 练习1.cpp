#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;
int main() {
	Mat srcMat = imread("D:\\pic\\8_1.png");
	Mat srcMatg = imread("D:\\pic\\8_1.png", 0);
	Mat srcMat_th, dstMat, labMat, statMat, centMat, erodMat, dilateMat, erod, dilate;
	threshold(srcMatg, srcMat_th, 120, 255, THRESH_BINARY);

	dstMat = 255 - srcMat_th;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat kerne2 = getStructuringElement(MORPH_RECT, Size(9, 9));
	morphologyEx(dstMat, dilateMat, MORPH_DILATE, kernel);
	morphologyEx(dilateMat, erodMat, MORPH_ERODE, kernel);
	morphologyEx(erodMat, erodMat, MORPH_ERODE, kerne2);
	morphologyEx(erodMat, erodMat, MORPH_DILATE, kerne2);
	int number = connectedComponentsWithStats(erodMat, labMat, statMat, centMat);
	vector<int> p(number);
	vector<int> cir(number);
	for (int i = 0; i < number; i++) {
		cir[i] = number;
	}
	int x = 0;
	for (int i = 0; i < number; i++) {
		if (statMat.at<int>(i, 2) - statMat.at<int>(i, 3) >= -5 && statMat.at<int>(i, 2) - statMat.at<int>(i, 3) <= 5) {
			cir[x] = i; x++;
		}
	}
	for (int i = 0; i < x; i++) {
		int r = (statMat.at<int>(cir[i], 2) + statMat.at<int>(cir[i], 3)) / 4;
		Point pt;
		pt.x = statMat.at<int>(cir[i], 0) + statMat.at<int>(cir[i], 2) / 2;
		pt.y = statMat.at<int>(cir[i], 1) + statMat.at<int>(cir[i], 3) / 2;
		circle(srcMat, pt, r, CV_RGB(255, 0, 0), -1, 8, 0);
	}
	imshow("src", srcMat);
	waitKey(0);
	return 0;
}