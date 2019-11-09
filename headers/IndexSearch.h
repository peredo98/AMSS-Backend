
#include <iostream>
#include <string>
#include <vector>

#include <opencv2/flann/flann.hpp>
#include <opencv2/opencv.hpp>

class IndexSearch
{
private:
    cv::flann::Index index;

public:
    IndexSearch();

    void updateIndex(cv::Mat_<float> dataset);

    std::vector<cv::Mat> searchPerson(cv::Mat_<float> query, int numKnn);
};
