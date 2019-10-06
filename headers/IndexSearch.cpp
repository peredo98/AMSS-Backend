
// #include <iostream>
// #include <string>
// #include <vector>
// #include <map>
 
// #include <flann/flann.hpp>
// #include <flann/io/hdf5.h>

// using namespace std;

// class IndexSearch{
//     public: 
//         IndexSearch(){}


//         void convertInfo(Mat mymat){
//             cout << "Convert the mat into a Matrix<float> of flann" << endl; 
//         }

//         void runKnnSearch(
//             const flann::flann_algorithm_t indexType,
//             const size_t numKnn,
//             flann::Matrix<float>&amp;amp; dataset,
//             flann::Matrix<float>&amp;amp; query,
//             flann::Matrix<size_t>&amp;amp; resultIndex,
//             flann::Matrix<float>&amp;amp; resultDistance
//         ){
//             flann::IndexParams indexParams = flann::KDTreeIndexParams();
//             flann::SearchParams searchParams = flann::SearchParams(256);
//             flann::Index<flann::L2<float> > index(dataset, indexParams);

//             // t0 = clock();
//             index.buildIndex();
//             // t1 = clock();
//             // std::cout << &amp;quot;  buildIndex: &amp;quot; << static_cast<double>(t1-t0)/CLOCKS_PER_SEC << &amp;quot; sec.&amp;quot; << std::endl;

//             // t0 = clock();
//             index.knnSearch(query, resultIndex, resultDistance, numKnn, searchParams);
//             // t1 = clock();
//             // std::cout << &amp;quot;  knnSearch: &amp;quot; << static_cast<double>(t1-t0)/CLOCKS_PER_SEC << &amp;quot; sec.&amp;quot; << std::endl;

//             for(int n = 0; n < 2; ++n){
//                 std::cout << &amp;quot;  &amp;quot; << n << &amp;quot;-th query: &amp;quot;;
//                 for(int k = 0; k < numKnn; ++k)
//                 {
//                     std::cout << &amp;quot;(&amp;quot; << resultIndex[n][k] << &amp;quot;, &amp;quot; << resultDistance[n][k] << &amp;quot;), &amp;quot;;
//                 }
//                 std::cout << std::endl;
//             }

//         }



//         // Main method
//         void searchPerson(Mat vectorsearch, Mat dataDB, int numKnn){
//             cout << "Time to search.." << endl << endl;

//             flann::Matrix<float> dataset = convertInfo(vectorSearch);
//             flann::Matrix<float> query = convertInfo(dataDB);

//             flann::Matrix<size_t> resultIndex = flann::Matrix<size_t>(new size_t[query.rows*numKnn], query.rows, numKnn);
//             flann::Matrix<float> resultDistance = flann::Matrix<float>(new float[query.rows*numKnn], query.rows, numKnn);

//             runKnnSearch(flann::FLANN_INDEX_KDTREE, numKnn, dataset, query, resultIndex, resultDistance);
            
//         };

        

        



// };

