#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/opencv.hpp"
#include <string>

using namespace cv;
using namespace std;

// variables to store images
Mat dst, cimg, gray, img, img_tmp, edges;

int initThresh;
const int maxThresh = 1000;
double th1, th2;

// create a vector to store points of line
vector<Vec4i> lines;

void onTrackbarChange(int, void *) {
    cimg = img.clone();
    dst = img.clone();

    th1 = initThresh;
    th2 = th1 * 0.4;

    Canny(img, edges, th1, th2);

    // apply hough line transform
    HoughLinesP(edges, lines, 2, CV_PI / 180, 50, 10, 100);
    cout << lines.size();

    // draw lines on the detected points
    for (size_t i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];
        line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA);
    }

    cout << "here";
    // show the resultant image
    imshow("Result Image", dst);
    imshow("Edges", edges);
}


int main(int argc, char **argv) {

    string prefix = "0";
    for (int i = 1; i < 17; i++) {

        if (i == 10)
            prefix = "";

        string filename = "images/Image" + prefix + to_string(i) + ".jpg";
//        cout << filename;


        img_tmp = imread(filename, 1);
        threshold(img_tmp, img, 120, 255, 1);
        dst = img.clone();

        // Convert to gray-scale
        cvtColor(img, gray, COLOR_BGR2GRAY);

        // Detect edges using Canny Edge Detector
        // Canny(gray, dst, 50, 200, 3);

        // Make a copy of original image
        // cimg = img.clone();

        // Will hold the results of the detection
        namedWindow("Edges", 1);
        namedWindow("Result Image", 1);

        // Declare thresh to vary the max_radius of circles to be detected in hough transform
        initThresh = 500;

        // Create trackbar to change threshold values
        createTrackbar("threshold", "Result Image", &initThresh, maxThresh, onTrackbarChange);
        onTrackbarChange(initThresh, 0);

        while (true) {
            int key;
            key = waitKey(1);
            if ((char) key == 27) { break; }
        }
    }
}
