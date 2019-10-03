#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/opencv.hpp"
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {

    string prefix = "0";
    for(int i = 1; i < 17; i ++) {

        if (i == 10)
            prefix = "";

        string fileName = "images/Image" + prefix + to_string(i) + ".jpg";
        cout << fileName;
        Mat im = imread(fileName, IMREAD_GRAYSCALE);
    }
}
