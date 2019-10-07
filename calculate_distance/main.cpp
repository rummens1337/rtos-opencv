#include <iostream>
#include <vector>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <cv.hpp>

using namespace cv;
using namespace std;

// d(AB)=(xB−xA)2+(yB−yA)2
double distance(Vec<float, 3> a, Vec<float, 3> b) {
    return sqrt(pow(b[0] - a[0], 2) + pow(b[1] - a[1], 2));
}


int main() {
    static const string imageLocation = "images/Bracket";
    vector<Vec3f> circles;
    string name;
    int numOfImages = 6;
    Mat image, imageInGray;

    for (int i = 1; i <= numOfImages; ++i) {
        name = imageLocation + std::to_string(i) + ".jpg";
        image = imread(name);

        if (!image.data) {
            cout << "Could not open or find the image" << std::endl;
            return -1;
        }

        cvtColor(image, imageInGray, COLOR_BGR2GRAY);
        HoughCircles(imageInGray, circles, HOUGH_GRADIENT, 1,
                     imageInGray.rows /
                     16,  // change this value to detect circles with different distances to each other
                     100, 30, 20, 30 // change the last two parameters
                // (min_radius & max_radius) to detect larger circles
        );

        cout << i << " Distance between circles: " << distance(circles[0], circles[1]) << endl;
    }
    return 0;
}