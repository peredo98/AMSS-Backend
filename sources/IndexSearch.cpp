
#include "./../headers/IndexSearch.h"

using namespace std;
using namespace cv;
using namespace flann;

IndexSearch::IndexSearch()
{
    cout << "IndexSearch class created..." << endl
         << endl;
    index = flann::Index();
}

void IndexSearch::updateIndex(cv::Mat_<float> dataset)
{
    cout << "Update the index..." << endl;
    index.build(dataset, flann::KDTreeIndexParams());
    cout << "done " << dataset.rows << " " << dataset.cols << endl;
}

// // Main method
vector<Mat> IndexSearch::searchPerson(cv::Mat_<float> query, int numKnn)
{
    Mat indices, dists;
    index.knnSearch(query, indices, dists, numKnn);
    vector<Mat> in_dis;
    in_dis.push_back(indices);
    in_dis.push_back(dists);

    return in_dis;
    // cv::Mat_<size_t> resultIndex = cv::Mat_(new size_t[query.rows * numKnn], query.rows, numKnn);
    // cv::Mat_<float> resultDistance = cv::Mat_(new float[query.rows * numKnn], query.rows, numKnn);

    // index.knnSearch(query, resultIndex, resultDistance, numKnn, flann::SearchParams(256));

    // for(int k = 0; k < numKnn; ++k){
    //     std::cout << &amp;quot;(&amp;quot; << resultIndex[n][k] << &amp;quot;, &amp;quot; << resultDistance[n][k] << &amp;quot;), &amp;quot;;
    // }
};
