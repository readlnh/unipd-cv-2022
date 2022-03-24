#include <iostream>
#include "opencv4/opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void max_filter(Mat &src, Mat &dst, int size) {
    if(size % 2 == 0) {
        cout << "The size is even." << endl;
        return;
    }

    int p = (size - 1) / 2;

    int row = src.rows;
    int col = src.cols;
    cout << row << "," << col << endl;
    for(int r = 0; r < row; r++) {
        for(int c = 0; c < col; c++) {
            int maxt = 0;
            for(int i = r - p; i <= r + p; i++) {
                for(int j = c - p; j <= c + p; j++) {
                    if(i >= 0 && i < row && j >= 0 && j < col) {
                        if(maxt < src.at<uchar>(i, j)) 
                            maxt = src.at<uchar>(i, j);
                    }
                }
            }
            dst.at<uchar>(r, c) = maxt;
        }
    }
}

void min_filter(Mat &src, Mat &dst, int size) {
    if(size % 2 == 0) {
        cout << "The size is even." << endl;
        return;
    }

    int p = (size - 1) / 2;

    int row = src.rows;
    int col = src.cols;
    cout << row << "," << col << endl;
    for(int r = 0; r < row; r++) {
        for(int c = 0; c < col; c++) {
            int mint = 255;
            for(int i = r - p; i <= r + p; i++) {
                for(int j = c - p; j <= c + p; j++) {
                    if(i >= 0 && i < row && j >= 0 && j < col) {
                        if(mint > src.at<uchar>(i, j)) 
                            mint = src.at<uchar>(i, j);
                    }
                }
            }
            dst.at<uchar>(r, c) = mint;
        }
    }
}