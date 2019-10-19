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
IndexSearch flannSearch(db.getDataSet());

//VERSION 2.1 -ITERACIÓN 2
int main(int, char **)
{

    /* CREATE A PERSON WITH BIOMETRIC DATA  */
    // vector<float> vtest = {-0.0554103, 0.234784, 0.0174269, -0.0774777, -0.147699};
    // Mat mymat = db.vectorToMat(1, vtest.size(), vtest);
    // db.createPerson("Nancy", "Medina", "A01330291", 20, "Female", mymat);
    // flannSearch.updateIndex(db.getDataSet()); //Just after when a person is created or deleted.

    // /* DELETE A PERSON BASED ON ITS ID */
    // db.deletePersonById("A01234567");
    // flannSearch.updateIndex(db.getDataSet());

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
    // Mat matSearch = db.vectorToMat(1, vSearch.size() ,vSearch);
    // string jsonM = db.getPersonByBiometricData(matSearch);
    // d.Parse(jsonM.c_str());
    // Value& valM = d["name"];
    // printf("%s\n", valM.GetString());

    /* MAKE FILTER IN DB -- A PERSON PASSES  */
    vector<float> vSearch = {-0.077756, 0.192846, 0.0550688, -0.168125, -0.182494};
    Mat matSearch = db.vectorToMat(1, vSearch.size(), vSearch);
    //flannSearch.searchPerson(matSearch, 5);

    //print Biometric Data of all set
    // db.getBiometricData();

    //PRINTDB
    db.printDB();
    vector<Mat> result = db.searchPersonKnn(matSearch, 4);
    for (int i = 0; i < result.size(); i++)
    {
        vector<float> tempVector = db.matToVector(result[i]);
        for (int j = 0; j < tempVector.size(); j++)
        {
            printf("%f ", tempVector[j]);
        }
        printf("\n");
    }
}