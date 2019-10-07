#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/**
 * function main
 */
int main( int argc, char** argv ) {

    for (int i = 1; i < 3; i++) {
        Mat img, dst;
        string fileName = "images/image" + to_string(i) + ".bmp";
        img = imread(fileName, CV_LOAD_IMAGE_COLOR);
        fastNlMeansDenoising(img, dst, 5, 7, 21);
        imshow("Original", img);
        imshow("adjusted", dst);
        waitKey(0);
    }
}
