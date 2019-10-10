
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <opencv2/flann/flann.hpp>
#include <opencv2/opencv.hpp>
// #include <flann/io/hdf5.h>

using namespace std;
using namespace cv;
using namespace flann;

class IndexSearch

{
public:
    bool firstTime;
    flann::Index index;

    IndexSearch() { 
        firstTime = true;
     }


    void updateIndex(){
        cout << "Update the index..." << endl;
        // index(dataset, flann::KDTreeIndexParams());
    }

    // // Main method
    void searchPerson(cv::Mat_<float> dataset, cv::Mat_<float> query, int numKnn)
    {
        cout << "Time to search..." << endl << endl;

        if(firstTime){
            // updateIndex(dataset);
            updateIndex();
            firstTime = false;
        }

        cv::Mat_<size_t> resultIndex = cv::Mat_(new size_t[query.rows * numKnn], query.rows, numKnn);
        cv::Mat_<float> resultDistance = cv::Mat_(new float[query.rows * numKnn], query.rows, numKnn);

        // index.buildIndex();
        // index.knnSearch(query, resultIndex, resultDistance, numKnn, flann::SearchParams(256));

    };


    // void runKnnSearch(
    //     const size_t numKnn,
    //     cv::Mat_<float> dataset,
    //     cv::Mat_<float> query,
    //     cv::Mat_<size_t>resultIndex,
    //     cv::Mat_<float> resultDistance)
    // {
        // flann::IndexParams indexParams =  cv::flann::KDTreeIndexParams();
        // flann::SearchParams searchParams = flann::SearchParams(256);


        // flann::Index index(dataset, flann::KDTreeIndexParams());

        // t0 = clock();
        // index.buildIndex();
        // t1 = clock();
        // std::cout << &amp;quot;  buildIndex: &amp;quot; << static_cast<double>(t1-t0)/CLOCKS_PER_SEC << &amp;quot; sec.&amp;quot; << std::endl;

        // t0 = clock();
        // index.knnSearch(query, resultIndex, resultDistance, numKnn, flann::SearchParams(256));
        // // t1 = clock();
        // // std::cout << &amp;quot;  knnSearch: &amp;quot; << static_cast<double>(t1-t0)/CLOCKS_PER_SEC << &amp;quot; sec.&amp;quot; << std::endl;

        // for (int n = 0; n < 2; ++n)
        // {
        //     std::cout << &amp;
        //     quot;
        //     &amp;
        //     quot;
        //     << n << &amp;
        //     quot;
        //     -th query : &amp;
        //     quot;
        //     ;
        //     for (int k = 0; k < numKnn; ++k)
        //     {
        //         std::cout << &amp;
        //         quot;
        //         (&amp; quot; << resultIndex[n][k] << &amp; quot;, &amp; quot; << resultDistance[n][k] << &amp; quot;), &amp;
        //         quot;
        //         ;
        //     }
        //     std::cout << std::endl;
        // }
    // }

    
};
