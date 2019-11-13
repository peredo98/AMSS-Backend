#include <iostream>

#include <string>
#include <string.h>
#include <iostream>
#include <chrono>
#include <ctime>
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
         << " ** version 21 **" << endl;

    /* CREATE A PERSON WITH BIOMETRIC DATA  */
    // vector<float> vtest = {-0.076754, 0.0851077, 0.00011571, -0.072535, -0.114122};
    // Mat mymat = db->vectorToMat(1, vtest.size(), vtest);
    // db->createPerson2("ruben", "slazar", "A01338798", 25, "Male", {-0.03334, 0.0851077, 0.00011571, -0.072535, -0.114122});

    // /* DELETE A PERSON BASED ON ITS ID */
    // cout << "delete a person" << endl;
    // db->deletePersonById("A01262131");
    // db->deletePersonById("A01794060");
    // db->deletePersonById("A01178944");

    // db->deletePersonById("A01306351");
    // db->deletePersonById("A01186654");
    // db->deletePersonById("A01802256");
    // db->deletePersonById("A01465330");
    // db->deletePersonById("A01393169");

    // /* DELETE ALL */
    // db->deleteAll();

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
    // auto start = std::chrono::system_clock::now();
    // string vectStr = "-0.0739119 0.0508914 0.0434102 -0.0689023 -0.0424293 -0.0523956 0.0244958 -0.132437 0.191549 -0.0139284 0.221676 0.00304676 -0.220627 -0.065953 -0.0331979 0.0915333 -0.188661 -0.0562228 -0.100452 -0.0881964 -0.0398805 0.0254575 0.117802 -0.00514188 -0.101839 -0.247875 -0.0554136 -0.154361 0.115293 -0.138076 0.0127339 0.0497169 -0.287599 -0.141182 0.0284877 0.026435 -0.0673098 -0.0934699 0.304127 0.0249987 -0.125856 0.0486641 0.0994711 0.193468 0.210673 -0.0857041 0.0251015 -0.0883125 0.191424 -0.244326 0.0981953 0.0772285 0.222085 0.0492346 0.111709 -0.167778 -0.0075764 0.125631 -0.178099 0.148825 0.119205 -0.030087 -0.0170973 0.0155997 0.149062 0.0969186 -0.0728601 -0.178364 0.126701 -0.103289 -0.0243443 0.124617 -0.0825522 -0.103665 -0.310835 0.0417986 0.311187 0.0596648 -0.150578 0.00502425 -0.146475 -0.085487 -0.0610616 0.0438711 -0.0919782 -0.0231383 -0.0430655 0.0193191 0.197668 0.0153208 -0.0877158 0.168577 -0.0401181 0.0153725 -0.00951233 0.0100146 -0.182551 -0.066621 -0.128911 -0.0308653 -0.0299905 -0.0913147 0.00133691 0.156026 -0.214335 0.111146 -0.0695805 -0.0943595 -0.0363303 -0.0206769 -0.0509179 0.0518197 0.10836 -0.264059 0.300562 0.107418 0.0133784 0.075063 0.0393664 -0.00587485 0.0234381 0.0998835 -0.0913251 -0.116732 0.0055925 -0.0136491 0.0833201 0.025134";
    // Mat matSearch = db->stringToMat(vectStr);
    // Mat nearestNeighbors = db->searchPerson(matSearch, 4);
    // cout << "The four nearest are: " << endl
    //      << nearestNeighbors << endl;
    // auto end = std::chrono::system_clock::now();
    // std::chrono::duration<double> elapsed_seconds = end - start;
    // std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    // std::cout << "finished computation at " << std::ctime(&end_time)
    //           << "elapsed time: " << elapsed_seconds.count() << "s\n";

    //PRINTDB
    // db->printDB();

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