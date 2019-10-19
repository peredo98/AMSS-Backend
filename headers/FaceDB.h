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
// #include <nlohmann/json.hpp>
// using namespace nlohmann;

// #include <jsoncpp/json/json.h>
// #include <jsoncpp/json/reader.h>
// #include <jsoncpp/json/writer.h>
// #include <jsoncpp/json/value.h>

#include "./../include/rapidjson/document.h"
// #include "./../sources/test.cpp"

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
    mongocxx::collection collection = conn["testdb"]["testcollection"];
    vector<float> dataset;
    cv::Mat_<float> dataMatset;
    long totalPeople;

public:

    FaceDB()
    {
        cout << "FaceDB class created..." << endl << endl;
        makeDataSet();
        totalPeople = getTotal();
    }

    cv::Mat_<float> getDataSet(){
        return dataMatset;
    }

    void makeDataSet(){
        // update dataset <float>
        // dataset = {};
    }

    void getBiometricData(){
        auto cursor = collection.find({});

        for (auto &&doc : cursor)
        {
            bsoncxx::document::element bio_element{doc["biometricData "]};
            if (bio_element){
                auto arr = bio_element.get_array();
                cout << bsoncxx::to_json(arr.value) << endl << endl;
            }
        }
    }


    //It is called every time you add or delete a person in the db
    void updateDataSet(bool upOrdel){ //true = createPerson() ;  false = deletePerson();
        if(upOrdel){
            totalPeople++;
        }else{
            totalPeople--;
        }
        makeDataSet();
        dataMatset = vectorToMat(totalPeople, dataset.size() ,dataset);
        
    }

    //to insert person in DB without photo
    void createPerson(string name, string lastName, string id, int age, string gender)
    {
        if(validateData.validate_all(name, lastName, id, gender)){
            document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender;
            collection.insert_one(document.view());
            updateDataSet(true);
        }
            
    }

    //to insert person in DB with photo
    void createPerson(string name, string lastName, string id, int age, string gender, string imageURL)
    {
        if(validateData.validate_all(name, lastName, id, gender)){
            document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender << "imageUrl" << imageURL;
            collection.insert_one(document.view());
            updateDataSet(true);
        }
    }

    //to insert person in DB with biometrics
    void createPerson(string name, string lastName, string id, int age, string gender, Mat mymat)
    {
        if(validateData.validate_all(name, lastName, id, gender)){
            document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender;
            vector<float> biometrics = matToVector(mymat);
            auto array = document << "biometricData " << bsoncxx::builder::stream::open_array;

            for (int i = 0; i < biometrics.size(); i++)
            {
                array << biometrics[i];
            }
            array << bsoncxx::builder::stream::close_array;

            collection.insert_one(document.view());
            updateDataSet(true);
        }
    }

    //to insert person in DB with photo and biometrics
    void createPerson(string name, string lastName, string id, int age, string gender, string imageURL, Mat mymat)
    {
        if(validateData.validate_all(name, lastName, id, gender)){
            document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender << "imageUrl" << imageURL;

            vector<float> biometrics = matToVector(mymat);
            auto array = document << "biometricData " << bsoncxx::builder::stream::open_array;

            for (int i = 0; i < biometrics.size(); i++)
            {
                array << biometrics[i];
            }
            array << bsoncxx::builder::stream::close_array;

            collection.insert_one(document.view());
            updateDataSet(true);
        }
    }

    void deletePersonById(string id){
        bsoncxx::builder::stream::document filter;

        filter << "studentId" << id;
        collection.delete_one(filter.view());
        updateDataSet(false);
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



    string getPersonByBiometricData(vector<float> myvector){

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
            return bsoncxx::to_json(*maybe_result);
        }
        return "Not person found";
    }

    string getPersonByBiometricData(Mat matSearch){

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
            return bsoncxx::to_json(*maybe_result);
        }
        return "Not person found";
    }


    // to retrieve person from DB
    string getPersonById(string id)
    {
        bsoncxx::builder::stream::document filter;

        filter << "studentId" << id;

        bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            collection.find_one(filter.view());
        if (maybe_result)
        {
            return bsoncxx::to_json(*maybe_result);
        }
        return "Not person found";
    }


    vector<float> matToVector(Mat mymat){
        vector<float> normalVector; 
        normalVector.assign((float*)mymat.datastart, (float*)mymat.dataend);
        return normalVector;

        // This is just to confirm 

        // int cnt=0;
        // int r = 1; 
        // int c = normalVector.size();
        // for(int i=0; i< c; ++i)
        // {
        //     for(int j=0; j< r; ++j) {
        //         printf("%lf ", normalVector[cnt++]);
        //         printf("\n");
        //     }
            
        // }
    }

    Mat vectorToMat(long rows, long col, vector<float> vtest){
        Mat mymat = Mat(rows, col, CV_32FC1); // Mat(row, columns, type);
        memcpy(mymat.data, vtest.data(), vtest.size()*sizeof(float));
        return mymat;

        //ANOTHER WAY
        // double vtest2[5] = {-0.116467, 0.0991249, 0.0624924, 0.00583552, -0.0165893};
        // Mat mymat = Mat(5, 5, CV_64FC1, vtest2).clone();
    }

    


    vector<string> returnData(){
        auto cursor = collection.find({});
         
        cout << "matriz 2" << endl << endl;
        vector<string> matrix;
        for (auto &&doc : cursor)
        {
            string json = bsoncxx::to_json(doc) ;
            matrix.push_back(json);
        }
        return matrix;
    }

    
    long getTotal(){
        auto cursor = collection.find({});
        long total = 0;
        for (auto &&doc : cursor)
        {
            total ++;
        }
        return total;
    }
    //Print all documents in DB
    void printDB()
    {
        auto cursor = collection.find({});

        cout << endl << "- -THE DATABASE IS: " << endl << endl;
        for (auto &&doc : cursor)
        {
            cout << bsoncxx::to_json(doc) << endl << endl;
        }

    }

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

    vector<Mat> searchPersonKnn(cv::Mat_<float> query, int numKnn)
    {
        cout << "Time to search..." << endl << endl;

        vector<Mat> result;

        auto cursor = collection.find({});

        for (auto &&doc : cursor)
        {
            vector<float> tempVector;
            bsoncxx::document::element bio_element{doc["biometricData "]};
            if (bio_element){
                auto arr = bio_element.get_array();
                cout << bsoncxx::to_json(arr.value) << endl << endl;
                for(int i = 0; i<arr.value.length(); i++){
                    tempVector.push_back((float) arr.value[i].get_double());
                }
                if (result.size() < numKnn){
                    Mat tempMat = vectorToMat(1, tempVector.size(), tempVector);
                    result.push_back(tempMat);
                }
                else{
                    int farestVector = 0;
                    for(int i = 1; i<result.size(); i++){
                        if(distance(matToVector(query), matToVector(result[farestVector])) < distance(matToVector(query),matToVector(result[i]))){
                            farestVector = i;
                        } 
                    }
                    if(distance(matToVector(query), matToVector(result[farestVector])) > distance(matToVector(query), tempVector)){
                        Mat tempMat = vectorToMat(1, tempVector.size(), tempVector);
                        result[farestVector] = tempMat;
                    }
                }
                
            }
            
        }
        return result;
    }

   
};
