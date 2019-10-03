#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/opencv.hpp"
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {

    string fileNames[6] =
            {
                 "dice-1-md.png",
                    "dice-2-md.png",
                    "dice-3-md.png",
                    "dice-4-md.png",
                    "dice-5-md.png",
                    "dice-6-md.png"
            };

    for(int i = 0; i < 6; i ++){
        Mat im = imread(fileNames[i], IMREAD_GRAYSCALE);

        // Setup SimpleBlobDetector parameters.
        SimpleBlobDetector::Params params;

        // Change thresholds
        params.minThreshold = 10;
        params.maxThreshold = 200;

        // Filter by Area.
        params.filterByArea = true;
        params.minArea = 1500;

        // Filter by Circularity
        params.filterByCircularity = true;
        params.minCircularity = 0.1;

        // Filter by Convexity
        params.filterByConvexity = true;
        params.minConvexity = 0.87;

        // Filter by Inertia
        params.filterByInertia = true;
        params.minInertiaRatio = 0.01;


        // Storage for blobs
        vector<KeyPoint> keypoints;

        // Set up detector with params
        Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

        // Detect blobs
        detector->detect(im, keypoints);

        // Draw detected blobs as red circles.
        // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
        // the size of the circle corresponds to the size of blob

        cout << std::hex << keypoints.size() << " blobs detected in: " << fileNames[i] << endl;

        Mat im_with_keypoints;

        drawKeypoints(im, keypoints, im_with_keypoints, Scalar(0, 0, 200), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        // Show blobs
        imshow("keypoints", im_with_keypoints);
        waitKey(0);
    }

}
