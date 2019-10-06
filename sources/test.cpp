#include <iostream>

#include <string>
#include<string.h> 

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "./../headers/FaceDB.h"
#include "./../headers/IndexSearch.cpp"
#include "./../include/rapidjson/document.h"

// #include <jsoncpp/json/json.h>
#include <regex> 

using namespace std;

using namespace rapidjson;

FaceDB db;
Document d;
// IndexSearch flannSearch;


void createMatrix(){
    vector<string> dataDB = db.returnData();
    for (int i=0; i<dataDB.size(); i++){
        string json = dataDB[i];
        // cout << json << endl;
        regex r("[.*]");  
        smatch m;
        regex_search(json, m, r);
        // for each loop 
        for (auto x : m) {
            cout << "hola" << endl;
            cout << x << " "; 
        }
        
    }       
}

int main(int, char **)
{


    createMatrix();
    /* CREATE A PERSON WITH BIOMETRIC DATA  */

    // vector<float> vtest = {-0.0569064, 0.155576, 0.0567186, -0.148239, -0.162697};
    // vector<float> vtest = {-0.032206, 0.168639, 0.0554004, -0.131378, -0.161355};
    // vector<float> vtest = {-0.0525553, 0.185332, 0.0755945, -0.113336, -0.187507};
    // vector<float> vtest = {-0.0483017, 0.167963, 0.0510118, -0.0883058, -0.193016};
    // vector<float> vtest = {-0.0715808, 0.234204, 0.066136, -0.0514578, -0.217422};
    
    // Mat mymat = Mat(1, vtest.size(), CV_32FC1); // Mat(row, columns, type);
    // memcpy(mymat.data, vtest.data(), vtest.size() * sizeof(float));
    // db.createPerson("Camila", "Rovirosa", "A01024192", 21, "Female", mymat);




    // /* DELETE A PERSON BASED ON ITS ID */
    // db.deletePersonById("A01234567");



    // /* Get Person's name by StudentId */
    // string json =  db.getPersonById("A01024192");
    // d.Parse(json.c_str());
    // Value& val = d["name"];
    // printf("%s\n", val.GetString());

    
    // /* GET PERSON BASED ON VECTOR FORMAT*/
    // vector<float> vSearch = {-0.077756, 0.192846, 0.0550688, -0.168125, -0.182494};
    // string json = db.getPersonByBiometricData(vSearch);
    // d.Parse(json.c_str());
    // Value& val = d["name"];
    // printf("%s\n", val.GetString());
    

    // /* GET A PERSON BASED ON MAT FORMAT*/
    // vSearch = {-0.0576136, 0.171748, 0.0571629, -0.152391, -0.166514};
    // Mat matSearch = Mat(1, vSearch.size(), CV_32FC1); // Mat(row, columns, type);
    // memcpy(matSearch.data, vSearch.data(), vSearch.size() * sizeof(float));
    // string jsonM = db.getPersonByBiometricData(matSearch);
    // d.Parse(jsonM.c_str());
    // Value& valM = d["name"];
    // printf("%s\n", valM.GetString());


    // vector<float> vSearch = {-0.077756, 0.192846, 0.0550688, -0.168125, -0.182494};
    // Mat mymat = Mat(1, vtest.size(), CV_32FC1); // Mat(row, columns, type);
    // memcpy(mymat.data, vtest.data(), vtest.size() * sizeof(float));
    // flannSearch.searchPerson(mymat, mymat, 5);


    //PRINTDB
    db.printDB();
}