#include <iostream>

#include <string>
#include <string.h>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "./../headers/FaceDB.h"
#include "./../headers/IndexSearch.h"
#include "./../include/rapidjson/document.h"

// #include <jsoncpp/json/json.h>
#include <regex>

using namespace std;

using namespace rapidjson;

FaceDB db;
Document d;
IndexSearch flannSearch;

void createMatrix()
{
    vector<string> dataDB = db.returnData();
    for (int i = 0; i < dataDB.size(); i++)
    {
        string json = dataDB[i];
        // cout << json << endl;
        regex r("[.*]");
        smatch m;
        regex_search(json, m, r);
        // for each loop
        for (auto x : m)
        {
            cout << "hola2" << endl;
            cout << x << " " <<endl;
        }
    }
}

//VERSION 2.1 -ITERACIÓN 2
int main(int, char **)
{
    
    /* CREATE A PERSON WITH BIOMETRIC DATA  */
    //ESTE VECTOR YA NO SIRVE
    // vector<float> vtest = {-0.0715808, 0.234204, 0.066136, -0.0514578, -0.217422};
    // Mat mymat = db.vectorToMat(1, vtest);
    // db.createPerson("Alan", "Zavala", "A01338448", 20, "Male", mymat);
    // flannSearch.updateIndex(db.getDataSet());
    flannSearch.updateIndex();

    // /* DELETE A PERSON BASED ON ITS ID */
    // db.deletePersonById("A01234567");

    // /* GET PERSON'S NAME BY STUDENT ID */
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
    // vector<float> vSearch = {-0.0576136, 0.171748, 0.0571629, -0.152391, -0.166514};
    // Mat matSearch = db.vectorToMat(1, vSearch);
    // string jsonM = db.getPersonByBiometricData(matSearch);
    // d.Parse(jsonM.c_str());
    // Value& valM = d["name"];
    // printf("%s\n", valM.GetString());


    /* MAKE FILTER IN DB -- A PERSON PASSES  */
    vector<float> vSearch = {-0.077756, 0.192846, 0.0550688, -0.168125, -0.182494};
    Mat matSearch = db.vectorToMat(1, vSearch);
    flannSearch.searchPerson(db.getDataSet(), matSearch, 5);

    //PRINTDB
    db.printDB();
}