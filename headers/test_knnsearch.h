#include <iostream>
#include <string>
#include <vector>
#include <map>
 
#include <flann/flann.hpp>
#include <flann/io/hdf5.h>
 
std::vector<flann::flann_algorithm_t> indexFlannAlgorithm = {
    flann::FLANN_INDEX_LINEAR,
    flann::FLANN_INDEX_KDTREE,
    flann::FLANN_INDEX_KMEANS,
    flann::FLANN_INDEX_COMPOSITE,
    flann::FLANN_INDEX_KDTREE,
    flann::FLANN_INDEX_HIERARCHICAL,
//    flann::FLANN_INDEX_LSH,
    flann::FLANN_INDEX_AUTOTUNED
};
 
std::map<flann::flann_algorithm_t, std::string> flannAlgorithm =
{
    std::pair<flann::flann_algorithm_t, std::string>(flann::FLANN_INDEX_LINEAR, &amp;quot;linear&amp;quot;),
    std::pair<flann::flann_algorithm_t, std::string>(flann::FLANN_INDEX_KDTREE, &amp;quot;randomized kd-tree&amp;quot;),
    std::pair<flann::flann_algorithm_t, std::string>(flann::FLANN_INDEX_KMEANS, &amp;quot;k-means&amp;quot;),
    std::pair<flann::flann_algorithm_t, std::string>(flann::FLANN_INDEX_COMPOSITE, &amp;quot;composite&amp;quot;),
    std::pair<flann::flann_algorithm_t, std::string>(flann::FLANN_INDEX_KDTREE_SINGLE, &amp;quot;single kd-tree&amp;quot;),
    std::pair<flann::flann_algorithm_t, std::string>(flann::FLANN_INDEX_HIERARCHICAL, &amp;quot;hierarchical&amp;quot;),
    std::pair<flann::flann_algorithm_t, std::string>(flann::FLANN_INDEX_LSH, &amp;quot;LSH&amp;quot;),
    std::pair<flann::flann_algorithm_t, std::string>(flann::FLANN_INDEX_AUTOTUNED, &amp;quot;autotuned&amp;quot;)
};
 
void printMatrix(
    const flann::Matrix<float>&amp;amp; mat,
    const std::string str
)
{
    std::cout << str << std::endl;
    std::cout << &amp;quot;dim(data): &amp;quot; << mat.cols << std::endl;
    std::cout << &amp;quot;#data: &amp;quot; << mat.rows << std::endl;
}
 
void loadData(
    flann::Matrix<float>&amp;amp; dataset,
    flann::Matrix<float>&amp;amp; query
)
{
    flann::load_from_file(dataset, &amp;quot;../data/dataset.hdf5&amp;quot;, &amp;quot;dataset&amp;quot;);
    flann::load_from_file(query, &amp;quot;../data/dataset.hdf5&amp;quot;, &amp;quot;query&amp;quot;);
}
 
void setSearchResults(
    const size_t numQuery,
    const size_t numKnn,
    flann::Matrix<size_t>&amp;amp; resultIndex,
    flann::Matrix<float>&amp;amp; resultDistance
)
{
    resultIndex = flann::Matrix<size_t>(new size_t[numQuery*numKnn], numQuery, numKnn);
    resultDistance = flann::Matrix<float>(new float[numQuery*numKnn], numQuery, numKnn);
}
 
flann::SearchParams getSearchParams(
    const flann::flann_algorithm_t indexType
)
{
    switch (indexType)
    {
    case flann::FLANN_INDEX_KDTREE: return flann::SearchParams(256);
    case flann::FLANN_INDEX_KMEANS: return flann::SearchParams(128);
    case flann::FLANN_INDEX_COMPOSITE: return flann::SearchParams();
    case flann::FLANN_INDEX_KDTREE_SINGLE: return flann::SearchParams(-1);
    case flann::FLANN_INDEX_HIERARCHICAL: return flann::SearchParams(2000);
    case flann::FLANN_INDEX_LSH: return flann::SearchParams(-1);
    case flann::FLANN_INDEX_AUTOTUNED: return flann::SearchParams(-2);
    default: return flann::SearchParams(0);
    }
}
 
flann::IndexParams getIndexParams(
    const flann::flann_algorithm_t indexType
)
{
    switch (indexType)
    {
    case flann::FLANN_INDEX_KDTREE: return flann::KDTreeIndexParams();
    case flann::FLANN_INDEX_KMEANS: return flann::KMeansIndexParams();
    case flann::FLANN_INDEX_COMPOSITE: return flann::CompositeIndexParams();
    case flann::FLANN_INDEX_KDTREE_SINGLE: return flann::KDTreeSingleIndexParams();
    case flann::FLANN_INDEX_HIERARCHICAL: return flann::HierarchicalClusteringIndexParams();
    case flann::FLANN_INDEX_LSH: return flann::LshIndexParams();
    case flann::FLANN_INDEX_AUTOTUNED: return flann::AutotunedIndexParams();
    default: return flann::LinearIndexParams();
    }
}
 
void testKnnSearch(
    const flann::flann_algorithm_t indexType,
    const size_t numKnn,
    flann::Matrix<float>&amp;amp; dataset,
    flann::Matrix<float>&amp;amp; query,
    flann::Matrix<size_t>&amp;amp; resultIndex,
    flann::Matrix<float>&amp;amp; resultDistance
)
{
    std::cout << flannAlgorithm[indexType] << std::endl;
    clock_t t0, t1;
    flann::IndexParams indexParams = getIndexParams(indexType);
    flann::SearchParams searchParams = getSearchParams(indexType);
    flann::Index<flann::L2<float> > index(dataset, indexParams);
    t0 = clock();
    index.buildIndex();
    t1 = clock();
    std::cout << &amp;quot;  buildIndex: &amp;quot; << static_cast<double>(t1-t0)/CLOCKS_PER_SEC << &amp;quot; sec.&amp;quot; << std::endl;
 
    t0 = clock();
    index.knnSearch(query, resultIndex, resultDistance, numKnn, searchParams);
    t1 = clock();
    std::cout << &amp;quot;  knnSearch: &amp;quot; << static_cast<double>(t1-t0)/CLOCKS_PER_SEC << &amp;quot; sec.&amp;quot; << std::endl;
 
//    for(int n = 0; n < query.rows; ++n)
    for(int n = 0; n < 2; ++n)
    {
        std::cout << &amp;quot;  &amp;quot; << n << &amp;quot;-th query: &amp;quot;;
        for(int k = 0; k < numKnn; ++k)
        {
            std::cout << &amp;quot;(&amp;quot; << resultIndex[n][k] << &amp;quot;, &amp;quot; << resultDistance[n][k] << &amp;quot;), &amp;quot;;
        }
        std::cout << std::endl;
    }
}
/*
int  main ()
{
    int numKnn = 6;
    flann::Matrix<float> dataset;
    flann::Matrix<float> query;
    loadData(dataset, query);
    printMatrix(dataset, &amp;quot;Reference&amp;quot;);
    printMatrix(query, &amp;quot;Query&amp;quot;);
 
//    std::vector< std::vector<int> > indices;
//    std::vector<std::vector<float> > dists;
 
    flann::Matrix<size_t> resultIndex;
    flann::Matrix<float> resultDistance;
    setSearchResults(query.rows, numKnn, resultIndex, resultDistance);
 
    for(int n = 0; n < indexFlannAlgorithm.size(); ++n)
    {
        testKnnSearch(
            indexFlannAlgorithm[n], numKnn,
            dataset, query, resultIndex, resultDistance
        );
    }
 
//    flann::save_to_file(resultIndex, &amp;quot;result.hdf5&amp;quot;, &amp;quot;result&amp;quot;);
 
    delete [] dataset.ptr();
    delete [] query.ptr();
    delete [] resultIndex.ptr();
    delete [] resultDistance.ptr();
 
    return 0;
}*/