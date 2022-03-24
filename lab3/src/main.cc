#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace std;

using namespace cv;

// task 3
void segmentation_(int T, Mat *src, Mat *mask, int r_, int g_, int b_) {
    mask->create(src->size(), src->type());
    int row = src->rows;
    int col = src->cols;
    int r, g, b;
  
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            Vec3b pixel = (*src).at<Vec3b>(Point (j, i));
            b = pixel[0];
            g = pixel[1];
            r = pixel[2];
        
            if(abs(b - b_) < T && abs(g - g_) < T && abs(r - r_) < T ) {
                (*mask).at<Vec3b>(i, j) = Vec3b(0, 0, 0);
            } else {
                (*mask).at<Vec3b>(i, j) = Vec3b(255, 255, 255);
            }
        }
    }
}

// task 4
void changeColor(Mat *src, Mat *seg, Mat *dst, int r_, int g_, int b_) {
    *dst = src->clone();
    int row = src->rows;
    int col = src->cols;

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            Vec3b pixel = (*seg).at<Vec3b>(Point (j, i));
            
            if ( pixel == Vec3b( 0, 0, 0) ) {
                (*dst).at<Vec3b>(Point (j, i)) = Vec3b(r_, g_, b_);
            }
        }
    }

}

// task 2
void MouseCallback_(int event, int x, int y, int flags, void* userdata) {
    if(event == EVENT_LBUTTONDBLCLK) {
        cout << "position: " << x << "," << y << endl;
        
        Mat img = *(Mat*)userdata;
        
        int r_, g_, b_;
        r_ = g_ = b_ = 0;
        for(int i = -1; i <= 1; i++) {
            for(int j = -1; j <= 1; j++) {
                int xt = x + i;
                int yt = y + j;
                int b, g, r;
                Vec3b pixel = img.at<Vec3b>(Point (xt, yt));
                b = pixel[0];
                g = pixel[1];
                r = pixel[2];
                r_ += r;
                b_ += b;
                g_ += g;
            }
        }
        
        //Vec3b pixel = img.at<Vec3b>(Point (0, 0));
        
        // task 3
        r_ = r_ / 9;
        b_ = b_ / 9;
        g_ = g_ / 9;
        cout << "task3: ------------------------" << endl;
        cout << "r value:" << r_ << endl;
        cout << "g value:" << g_ << endl;
        cout << "b value:" << b_ << endl;
        
        // task 4
        Mat seg;
        segmentation_(110, &img, &seg, r_, g_, b_);
        imshow("task4", seg);
        
        // task 5
        Mat dst;
        changeColor(&img, &seg, &dst, r_, g_, b_);
        imshow("task5", dst);
    }
}



int main() {
    // task1
    Mat img = imread("../robocup.jpg");
    
    namedWindow("task1");
    setMouseCallback("task1", MouseCallback_, &img); 
    imshow("task1", img);


    waitKey(0);

    return 0;
}
