
#include <iostream>
#include <string>
#include <vector>

#include <opencv2/flann/flann.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace flann;

class IndexSearch
{ 
    flann::Index index;

public:
    

    IndexSearch(cv::Mat_<float> dataset) { 
        cout << "IndexSearch class created..." << endl << endl;
        updateIndex(dataset);
    }


    void updateIndex(cv::Mat_<float> dataset){
        cout << "Update the index..." << endl;
        // index(dataset, flann::KDTreeIndexParams());
        // index.buildIndex();
        cout << "Index created... READY!" << endl << endl;
    }

    // // Main method
    void searchPerson(cv::Mat_<float> query, int numKnn)
    {
        cout << "Time to search..." << endl << endl;

        // cv::Mat_<size_t> resultIndex = cv::Mat_(new size_t[query.rows * numKnn], query.rows, numKnn);
        // cv::Mat_<float> resultDistance = cv::Mat_(new float[query.rows * numKnn], query.rows, numKnn);

        // index.knnSearch(query, resultIndex, resultDistance, numKnn, flann::SearchParams(256));

        // for(int k = 0; k < numKnn; ++k){
        //     std::cout << &amp;quot;(&amp;quot; << resultIndex[n][k] << &amp;quot;, &amp;quot; << resultDistance[n][k] << &amp;quot;), &amp;quot;;
        // }
    };

    double distance(vector<float> p, vector<float> q){
        double d = 0;
        if(p.size() == q.size()){
            for(int i = 0; i<p.size(); i++){
                d += (p[i] - q[i])*(p[i] - q[i]);

            }
            d = sqrt(d);
            return d;
        }else{
            return 0x1.fffffffffffffp+1023;
        }
        
    }

};
