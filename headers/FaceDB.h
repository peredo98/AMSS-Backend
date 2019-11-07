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

#include "ValidateData.cpp"
#include <exception>
#include <sstream>

#include <vector>

#include "./../include/rapidjson/document.h"
#include "./IndexSearch.h"

using namespace std;
using namespace cv;
using namespace rapidjson;

class FaceDB
{
    //init mongo
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};
    bsoncxx::builder::stream::document document{};

    //init global variables
    ValidateData validateData;
    IndexSearch flannSearch;
    Document d;

    mongocxx::collection collection = conn["testdb"]["testcollection"];

    cv::Mat_<float> dataMatset;
    long totalPeople;

public:
    FaceDB()
    {
        cout << "FaceDB class created..." << endl;
        totalPeople = getTotal();
        makeDataSet();
        updateIndex();
    }

    void updateIndex()
    {
        flannSearch.updateIndex(dataMatset);
    }

    Mat searchPerson(cv::Mat_<float> query, int numKnn)
    {
        vector<Mat> in_dis = flannSearch.searchPerson(query, numKnn);

        Mat indices = in_dis[0];
        Mat dist = in_dis[1];
        Mat nearestNeighbors;

        for(int i=0; i<numKnn; i++){
            Mat neigh = dataMatset.row(indices.at<int>(0, i));
            cout << neigh << endl;
            nearestNeighbors.push_back(neigh);
        }
        return nearestNeighbors;
    }

    void makeDataSet()
    {

        Mat_<double> mymat(totalPeople, 5);

        int i = 0;
        auto cursor = collection.find({});
        for (auto &&doc : cursor)
        {
            bsoncxx::document::element bio_element{doc["biometricData "]};
            if (bio_element)
            {
                vector<float> tempVector;
                auto arr = bio_element.get_array();
                for (int j = 0; j < arr.value.length(); j++)
                {
                    try
                    {
                        float tempVal = (float)arr.value[j].get_double();
                        tempVector.push_back(tempVal);
                        mymat(i, j) = tempVal;
                    }
                    catch (exception e)
                    {
                        break;
                    }
                }
                i++;
            }
        }

        dataMatset = mymat;
        cout << "The Mat is: " << endl
             << dataMatset << endl;
    }

    long getTotal()
    {
        auto cursor = collection.find({});
        long total = 0;
        for (auto &&doc : cursor)
        {
            total++;
        }
        return total;
    }

    void increment(Mat newMat)
    {
        totalPeople++;
        dataMatset.push_back(newMat);
        cout << "The new DataMatSet is: " << endl
            << dataMatset << endl;
        updateIndex();
    }

    void makeRange(Mat indexMat)
    {
        int index = 0;

        for (int i=0; i<dataMatset.rows; i++){
            cout << "an element: " << (i+1) << endl;
            cv::Mat diff = dataMatset.row(i) != indexMat;
            if(cv::countNonZero(diff) == 0){
                index = i;
                break;
            }
        }

        totalPeople--;

        Mat newRangeMat;

        if(index == 0){
            cv::Range range(1, dataMatset.rows);
             Mat_<double> tempMat(dataMatset, range);
             newRangeMat.push_back(tempMat);

        }else if(index == dataMatset.rows-1){
            cv::Range range(0, dataMatset.rows-1);
             Mat_<double> tempMat(dataMatset, range);
             newRangeMat.push_back(tempMat);

        }else{
            cv::Range range(0, index);
            cv::Range range2(index+1, dataMatset.rows);
            Mat_<double> tempMat(dataMatset, range);
            Mat_<double> tempMat2(dataMatset, range2);
            newRangeMat.push_back(tempMat);
            newRangeMat.push_back(tempMat2);
        }
        
        dataMatset = newRangeMat;
        cout
            << "The new DataMatSet is: " << endl
            << dataMatset << endl;
        

        updateIndex();
    }

    Mat getMatById(string id){
        bsoncxx::builder::stream::document filter;
        filter << "studentId" << id;
        auto cursor = collection.find({filter.view()});
        vector<float> tempVector;
        Mat myMat;
        for (auto &&doc : cursor)
        {
            bsoncxx::document::element bio_element{doc["biometricData "]};
            if (bio_element)
            {
                auto arr = bio_element.get_array();

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
                myMat = vectorToMat(1, tempVector.size(), tempVector);
            }
        }
        return myMat;
    }

    string getNameByBiometricData(vector<float> myvector)
    {

        bsoncxx::builder::stream::document filter;

        auto array = filter << "biometricData " << bsoncxx::builder::stream::open_array;
        for (int i = 0; i < myvector.size(); i++)
        {
            array << myvector[i];
        }
        array << bsoncxx::builder::stream::close_array;

        bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            collection.find_one(filter.view());
        if (maybe_result)
        {
             
            d.Parse(bsoncxx::to_json(*maybe_result).c_str());
            Value& val = d["name"];
            string name = val.GetString();
            return name;
        }
        return "NULL";
    }

    string getNameByBiometricData(Mat matSearch)
    {

        bsoncxx::builder::stream::document filter;
        vector<float> myvector = matToVector(matSearch);
        auto array = filter << "biometricData " << bsoncxx::builder::stream::open_array;
        for (int i = 0; i < myvector.size(); i++)
        {
            array << myvector[i];
        }
        array << bsoncxx::builder::stream::close_array;

        bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            collection.find_one(filter.view());
        if (maybe_result)
        {
            d.Parse(bsoncxx::to_json(*maybe_result).c_str());
            Value& val = d["name"];
            string name = val.GetString();
            return name;
        }
        return "NULL";
    }

    // to retrieve person from DB
    string getNameById(string id)
    {
        bsoncxx::builder::stream::document filter;

        filter << "studentId" << id;

        bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            collection.find_one(filter.view());
        if (maybe_result)
        {
            d.Parse(bsoncxx::to_json(*maybe_result).c_str());
            Value& val = d["name"];
            return val.GetString();
        }
        return "NULL";
    }

    //to insert person in DB without photo
    void createPerson(string name, string lastName, string id, int age, string gender)
    {
        if (validateData.validate_all(name, lastName, id, gender))
        {
            document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender;
            collection.insert_one(document.view());
            Mat null;
            increment(null);
        }
    }

    //to insert person in DB with photo
    void createPerson(string name, string lastName, string id, int age, string gender, string imageURL)
    {
        if (validateData.validate_all(name, lastName, id, gender))
        {
            document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender << "imageUrl" << imageURL;
            collection.insert_one(document.view());
            Mat null;
            increment(null);
        }
    }

    //to insert person in DB with biometrics
    void createPerson(string name, string lastName, string id, int age, string gender, Mat mymat)
    {
        if (validateData.validate_all(name, lastName, id, gender))
        {
            document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender;
            vector<float> biometrics = matToVector(mymat);
            auto array = document << "biometricData " << bsoncxx::builder::stream::open_array;

            for (int i = 0; i < biometrics.size(); i++)
            {
                array << biometrics[i];
            }
            array << bsoncxx::builder::stream::close_array;

            collection.insert_one(document.view());
            increment(mymat);
        }
    }

    //to insert person in DB with photo and biometrics
    void createPerson(string name, string lastName, string id, int age, string gender, string imageURL, Mat mymat)
    {
        if (validateData.validate_all(name, lastName, id, gender))
        {
            document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender << "imageUrl" << imageURL;

            vector<float> biometrics = matToVector(mymat);
            auto array = document << "biometricData " << bsoncxx::builder::stream::open_array;

            for (int i = 0; i < biometrics.size(); i++)
            {
                array << biometrics[i];
            }
            array << bsoncxx::builder::stream::close_array;

            collection.insert_one(document.view());
            increment(mymat);
        }
    }

    void deletePersonById(string id)
    {
        
        Mat deletedMat = getMatById(id);
        cout << "the deleted Mat is: " << deletedMat << endl;
        if(deletedMat.rows != 0){
            makeRange(deletedMat);
            bsoncxx::builder::stream::document filter;
            filter << "studentId" << id;
            collection.delete_one(filter.view());
            
        }
        else{
            cout << "no existe el usuario y no borre nada" << endl;
        }
        
    }

    void saveImage(Mat image, string fileName)
    {
        imwrite("./../img/" + fileName + ".png", image);
    }

    //write image url into existing user
    void insertImage(string id, string fileName)
    {
        bsoncxx::builder::stream::document filter;

        filter << "studentId" << id;

        bsoncxx::builder::stream::document update;

        string imageURL = ("./../img/" + fileName);

        update << "$set" << bsoncxx::builder::stream::open_document << "imageUrl" << imageURL << bsoncxx::builder::stream::close_document;

        collection.update_one(filter.view(), update.view());
    }

    //insert matrix with biometric data into existing user
    void insertBiometric(string id, Mat mymat)
    {
        bsoncxx::builder::stream::document filter;

        filter << "studentId" << id;

        bsoncxx::builder::stream::document update;

        update << "$set" << bsoncxx::builder::stream::open_document;
        vector<float> biometrics = matToVector(mymat);
        auto array = update << "biometricData " << bsoncxx::builder::stream::open_array;

        for (int i = 0; i < biometrics.size(); i++)
        {
            array << biometrics[i];
        }
        array << bsoncxx::builder::stream::close_array;

        update << bsoncxx::builder::stream::close_document;

        collection.update_one(filter.view(), update.view());
    }

    vector<float> matToVector(Mat mymat)
    {
        vector<float> normalVector;
        normalVector.assign((float *)mymat.datastart, (float *)mymat.dataend);
        return normalVector;
    }

    Mat vectorToMat(long rows, long col, vector<float> vtest)
    {
        Mat mymat = Mat(rows, col, CV_32FC1); // Mat(row, columns, type);
        memcpy(mymat.data, vtest.data(), vtest.size() * sizeof(float));
        return mymat;
    }

    //Print all documents in DB
    void printDB()
    {
        auto cursor = collection.find({});

        cout << endl
             << "- -THE DATABASE IS: " << endl
             << endl;
        for (auto &&doc : cursor)
        {
            cout << bsoncxx::to_json(doc) << endl
                 << endl;
        }
    }




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
