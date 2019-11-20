#include <iostream>

#include <string>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <exception>
#include <sstream>

#include <vector>

#include "./../include/rapidjson/document.h"
#include "./../sources/IndexSearch.cpp"
#include "./../sources/ValidateData.cpp"

class FaceDB
{
private:
    // init mongo vars
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};
    bsoncxx::builder::stream::document document{};
    mongocxx::collection collection = conn["testdb"]["testcollection"];

    //init global variables
    cv::Mat_<float> dataMatset;
    long totalPeople;

    // init classes
    ValidateData *validateData;
    IndexSearch *flannSearch;
    rapidjson::Document d;

public:
    FaceDB();

    void updateIndex();

    int searchPerson(cv::Mat_<float> query, int numKnn, std::vector<cv::Mat> &topMatches, std::vector<std::string> &topNames, std::vector<std::string> &topMatchesId);

    void makeDataSet();

    long getTotal();

    void increment(cv::Mat newMat);

    void makeRange(cv::Mat indexMat);

    int getMatById(std::string id, cv::Mat &mymat);

    int getNameByBiometricData(std::vector<float> myvector, std::string &name);

    int getNameByBiometricData(cv::Mat matSearch, std::string &name);

    int getIdByBioData(cv::Mat mymat, std::string &id);

    int getNameById(std::string id, std::string &name);

    int getImgById(std::string id, Mat &img);

    //to insert person in DB without photo
    void createPerson(std::string name, std::string lastName, std::string id, int age, std::string gender);

    //to insert person in DB with photo
    void createPerson(std::string name, std::string lastName, std::string id, int age, std::string gender, std::string imageURL);

    //to insert person in DB with biometrics
    void createPerson(std::string name, std::string lastName, std::string id, int age, std::string gender, cv::Mat mymat);

    void insertMany(std::vector<std::string> name, std::vector<std::string> lastName, std::vector<std::string> id, std::vector<int> age, std::vector<std::string> gender, cv::Mat auxMat);

    //to insert person in DB with photo and biometrics
    void createPerson(std::string name, std::string lastName, std::string id, int age, std::string gender, std::string imageURL, cv::Mat mymat);

    void deletePersonById(std::string id);

    void deleteAll();

    void saveImage(cv::Mat image, std::string fileName);

    //write image url into existing user
    void insertImage(std::string id, std::string fileName);

    //insert matrix with biometric data into existing user
    void insertBiometric(std::string id, cv::Mat mymat);

    std::vector<float> matToVector(cv::Mat mymat);

    cv::Mat vectorToMat(long rows, long col, std::vector<float> vtest);

    std::string matToString(cv::Mat mymat);

    cv::Mat stringToMat(std::string matStr);

    //Print all documents in DB
    void printDB();

    /* ALTERNATIVE KNNSEARCH 
    double distance(vector<float> p, vector<float> q)
    {
        double d = 0;
        if (p.size() == q.size())
        {
            for (int i = 0; i < p.size(); i++)
            {
                d += (p[i] - q[i]) * (p[i] - q[i]);
            }
            d = sqrt(d);
            return d;
        }
        else
        {
            return 0x1.fffffffffffffp+1023;
        }
    }

    vector<Mat> searchPersonKnn(cv::Mat_<float> query, int numKnn)
    {
        cout << "Time to search..." << endl
             << endl;

        vector<Mat> result;

        auto cursor = collection.find({});

        for (auto &&doc : cursor)
        {

            bsoncxx::document::element bio_element{doc["biometricData "]};
            if (bio_element)
            {
                auto arr = bio_element.get_array();
                vector<float> tempVector;
                for (int i = 0; i < arr.value.length(); i++)
                {
                    try
                    {
                        float tempVal = (float)arr.value[i].get_double();

                        tempVector.push_back(tempVal);
                    }
                    catch (exception e)
                    {
                        break;
                    }
                }

                cout << bsoncxx::to_json(arr.value) << distance(matToVector(query), tempVector) << endl
                     << endl;

                if (result.size() < numKnn)
                {
                    Mat tempMat = vectorToMat(1, tempVector.size(), tempVector);
                    result.push_back(tempMat);
                }
                else
                {
                    int farestVector = 0;
                    for (int i = 1; i < result.size(); i++)
                    {
                        if (distance(matToVector(query), matToVector(result[farestVector])) < distance(matToVector(query), matToVector(result[i])))
                        {
                            farestVector = i;
                        }
                    }
                    if (distance(matToVector(query), matToVector(result[farestVector])) > distance(matToVector(query), tempVector))
                    {
                        Mat tempMat = vectorToMat(1, tempVector.size(), tempVector);
                        result[farestVector] = tempMat;
                    }
                }
            }
        }
        return result;
    } 
    */
};
