#include <iostream>
#include "opencv4/opencv2/opencv.hpp"
#include "filter.h"

using namespace cv;

const int KERNEL_SIZE = 5;

int main() {
    // task 1
    Mat img = imread("../image.jpg");
    imshow("task1 imag.jpg", img);

    Mat img_gray;
    cvtColor(img, img_gray, COLOR_RGB2GRAY);

    imwrite("../image_grayscale.jpg", img_gray);
    imshow("task1 image_grayscale.jpg", img_gray);

    // task 2
    Mat dst_max;
    dst_max.create(img_gray.size(), img_gray.type());
    max_filter(img_gray, dst_max, KERNEL_SIZE);

    imshow("task2 max filter", dst_max);

    Mat dst_min;
    dst_min.create(img_gray.size(), img_gray.type());
    min_filter(img_gray, dst_min, KERNEL_SIZE);

    imshow("task2 min filter", dst_min);

    // task 3
    Mat dst_gaussian;
    GaussianBlur(img, dst_gaussian, Size(KERNEL_SIZE, KERNEL_SIZE), 0, 0);
    imshow("task 3 gaussian filter", dst_gaussian);

    Mat dst_median;
    medianBlur(img, dst_median, KERNEL_SIZE);
    imshow("task 3 median filter", dst_median);

    // task 4
    int histSize = 256; // 256 bins
    float range[] = {0, 256}; // range 0 - 256
    const float* histRange[] = {range};

    Mat hist;
    calcHist(&img_gray, 1, 0, Mat(), hist, 1, &histSize, histRange, true, false);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 1; i < histSize; i++ ) {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0  );
    }

    imshow("task 4", histImage);


    // task 5
    Mat dst_eq;
    equalizeHist(img_gray, dst_eq);

    imshow("task 5", dst_eq);


    waitKey(0);

    return 0;
}