// for OpenCV2
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

#ifdef _DEBUG
#pragma comment(lib, "opencv_core231d.lib")
#pragma comment(lib, "opencv_imgproc231d.lib")
#pragma comment(lib, "opencv_objdetect231d.lib")
#pragma comment(lib, "opencv_gpu231d.lib")
#pragma comment(lib, "opencv_highgui231d.lib")
#else
#pragma comment(lib, "opencv_core231.lib")
#pragma comment(lib, "opencv_imgproc231.lib")
#pragma comment(lib, "opencv_objdetect231.lib")
#pragma comment(lib, "opencv_gpu231.lib")
#pragma comment(lib, "opencv_highgui231.lib")
#endif

int main(int argc, char *argv[]) {
    cv::Mat src_img_gray, src_img, template_img_gray, template_img, edges;
    cv::Mat result_mat;
    cv::Mat debug_img;

    /*
     * Tested threshold values via threshold_test
     */

    template_img_gray = cv::imread("images/temp2.png", CV_LOAD_IMAGE_GRAYSCALE);
    if (template_img_gray.data == NULL) {
        printf("cv::imread() failed...\n");
        return -1;
    }
    threshold(template_img_gray, template_img, 120, 255, 1);
    cv::imshow("test",template_img);


    src_img_gray = cv::imread("images/Image04.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    if (template_img_gray.data == NULL) {
        printf("cv::imread() failed...\n");
        return -1;
    }
    threshold(src_img_gray, src_img, 120, 255, 1);
    cv::imshow("test2",src_img);
    cvWaitKey(0);

    cv::Canny(src_img, edges, 300, 500);
    cv::cvtColor(src_img, debug_img, CV_GRAY2BGR);

    while(true) {
        // method: CV_TM_SQDIFF, CV_TM_SQDIFF_NORMED, CV_TM _CCORR, CV_TM_CCORR_NORMED, CV_TM_CCOEFF, CV_TM_CCOEFF_NORMED
        int match_method = CV_TM_SQDIFF_NORMED;
        cv::matchTemplate(src_img, template_img, result_mat, match_method);
        cv::normalize(result_mat, result_mat, 100, 1, cv::NORM_MINMAX, -1, cv::Mat());

        double minVal = 800;
        double maxVal = 500;
        cv::Point minLoc, maxLoc, matchLoc;
        cv::minMaxLoc(result_mat, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );
        matchLoc = minLoc;

        cv::rectangle(
                debug_img,
                matchLoc,
                cv::Point(matchLoc.x + template_img.cols , matchLoc.y + template_img.rows),
                CV_RGB(255,0,0),
                2);


    if (debug_img.data == NULL) {
        printf("cv::imread() failed... on debug_img\n");
        return -1;
    }
        cv::imshow("debug_img", debug_img);

        int c = cv::waitKey(1);
        if (c == 27) break;
    }

    return 0;
}