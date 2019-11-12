#include <iostream>

#include <string>
#include <string.h>

#include <regex>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "FaceDB.cpp"

using namespace std;

FaceDB *db = new FaceDB();

int main(int, char **)
{
    cout << endl
         << " ** version 18 **" << endl;

    /* CREATE A PERSON WITH BIOMETRIC DATA  */
    // vector<float> vtest = {-0.076754, 0.0851077, 0.00011571, -0.072535, -0.114122};
    // Mat mymat = db->vectorToMat(1, vtest.size(), vtest);
    // db->createPerson2("ruben", "slazar", "A01338798", 25, "Male", {-0.03334, 0.0851077, 0.00011571, -0.072535, -0.114122});

    // /* DELETE A PERSON BASED ON ITS ID */
    // cout << "delete a person" << endl;
    // db->deletePersonById("A01338798");

    // /* GET PERSON'S NAME BY STUDENT ID */
    // string name =  db->getNameById("A01024192");
    // if(name != "NULL"){
    //     cout << "The person's name is: " << name << endl;
    // }

    // /* GET PERSON'S NAME BASED ON VECTOR FORMAT*/
    // vector<float> vSearch = {-0.077756, 0.192836, 0.0550688, -0.168125, -0.182494};
    // string name = db->getNameByBiometricData(vSearch);
    // if(name != "NULL"){
    //     cout << "The person's name is: " << name << endl;
    // }

    // /* GET A PERSON'S NAME BASED ON MAT FORMAT*/
    // vector<float> vSearch = {-0.0576136, 0.171748, 0.0571629, -0.152391, -0.166514};
    // Mat matSearch = db->vectorToMat(1, vSearch.size() ,vSearch);
    // string name = db->getNameByBiometricData(matSearch);
    // if(name != "NULL"){
    //     cout << "The person's name is: " << name << endl;
    // }

    // /* GET THE BIOMETRIC DATA BASED ON ITS ID */
    // Mat mymat = db->getMatById("A01025599");
    // if(mymat.rows != 0){
    //     cout << "The mat of the person you look for is: " << mymat << endl;
    // }

    /* SEARCH IN DB -- A PERSON PASSES  */
    // vector<float> vSearch = {-0.076754, 0.0851077, 0.00011571, -0.072535, -0.114122};
    // Mat matSearch = db->vectorToMat(1, vSearch.size(), vSearch);
    // Mat nearestNeighbors = db->searchPerson(matSearch, 4);

    //PRINTDB
    db->printDB();

    //ALTERNATIVE KNNSEARCH
    /*
    vector<Mat> result = db->searchPersonKnn(matSearch, 4);
    for (int i = 0; i < result.size(); i++)
    {
        vector<float> tempVector = db->matToVector(result[i]);
        for (int j = 0; j < tempVector.size(); j++)
        {
            printf("%f ", tempVector[j]);
        }
        printf("\n");
    }
    */
}