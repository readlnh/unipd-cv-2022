#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Task1 {
public:
    Task1() {
        src = imread("../street_scene.png");
        namedWindow("street");
        imshow("street", src);

        dst.create( src.size(), src.type() );
        cvtColor( src, src_gray, COLOR_BGR2GRAY );
        namedWindow( window_name, WINDOW_AUTOSIZE );
        createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, callback_, this);
        callback_(0, this);
    }
    
    void CannyThreshold() {
        blur( src_gray, detected_edges, Size(3,3) );
        Canny( detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size );
        dst = Scalar::all(0);
        src.copyTo( dst, detected_edges);
        imshow( window_name, dst );
    }

    static void callback_(int, void* userdata) {
        Task1 *tmp = (Task1*)userdata;
        tmp->CannyThreshold(); 
    }
private:
    Mat src, src_gray;
    Mat dst, detected_edges;

    int lowThreshold = 0;
    const int max_lowThreshold = 100;
    const int ratio = 3;
    const int kernel_size = 3;
    const char* window_name = "Edge Map";
};

class Task3 {
public:
    Task3() {
        src = imread("../street_scene.png");

        src_threshold = src.clone();

        // only while line will be in the image after threshold
        colorThreshold(50, &src_threshold);

        cvtColor( src_threshold, src_gray, COLOR_BGR2GRAY );

        blur( src_gray, detected_edges, Size(3,3) );

        

        // Edge detection
        Canny( detected_edges, dst, 100, 300, 3 );
        imshow("dst", dst);

        cvtColor( dst, cdst, COLOR_GRAY2BGR );

        

        vector<Vec2f> lines;
        HoughLines( dst, lines, 1, CV_PI / 90, 120, 0, 0 );

        for( size_t i = 0; i < lines.size(); i++ ) {
            float rho = lines[i][0], theta = lines[i][1];
            Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            pt1.x = cvRound(x0 + 1000*(-b));
            pt1.y = cvRound(y0 + 1000*(a));
            pt2.x = cvRound(x0 - 1000*(-b));
            pt2.y = cvRound(y0 - 1000*(a));
            line( src, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
        }

        imshow("line", src);
    }

    void colorThreshold(int T, Mat *src) {
        int row = src->rows;
        int col = src->cols;
        int r, g, b;

        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                Vec3b pixel = (*src).at<Vec3b>(Point (j, i));
                b = pixel[0];
                g = pixel[1];
                r = pixel[2];
        
                if(abs(b - 255) < T && abs(g - 255) < T && abs(r - 255) < T ) {
                    (*src).at<Vec3b>(i, j) = Vec3b(255, 255, 255);
                } else {
                    (*src).at<Vec3b>(i, j) = Vec3b(0, 0, 0);
                }
            }
        }
    }
private:
    Mat src, src_threshold, src_gray;
    Mat dst, cdst, detected_edges;
};

class Task4 {
public:
    Task4() {
        src = imread("../street_scene.png");
        cvtColor(src, src_gray, COLOR_BGR2GRAY);
        medianBlur(src_gray, src_gray, 5);

        vector<Vec3f> circles;
        HoughCircles(src_gray, circles, HOUGH_GRADIENT_ALT, 1.5, src_gray.rows / 16, 500, 0.8, 1, 30);

        /***** HOUGH_GRADIENT works well too *****/
        // HoughCircles(src_gray, circles, HOUGH_GRADIENT, 1.5, src_gray.rows / 16, 300, 30, 5, 10);

        cout << circles.size() << endl;
        
        for( size_t i = 0; i < circles.size(); i++ ) {
            Vec3i c = circles[i];
            Point center = Point(c[0], c[1]);
            
            int radius = c[2];
            circle( src, center, radius, Scalar(0, 255, 0), -1, FILLED);
        }
        imshow("detected circles", src);
    }
private:
    Mat src, src_gray;
};







int main() {
    Task1 t1 = Task1();

    Task3 t3 = Task3();

    Task4 t4 = Task4();


    waitKey(0);

    return 0;
}
