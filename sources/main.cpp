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
    // db->createPerson("ruben", "slazar", "A01338798", 25, "Male", mymat);

    // /* DELETE A PERSON BASED ON ITS ID */
    // cout << "delete a person" << endl;
    // db->deletePersonById("A01330000"); //NO EXISTE

    // /* DELETE ALL */  IN PROGRESS
    // db->deleteAll();

    // /* GET PERSON'S NAME BY STUDENT ID */
    // string name = db->getNameById("A01953564"); //Natalia
    // if (name != "NULL")
    // {
    //     cout << "The person's name is: " << name << endl;
    // }
    // else
    // {
    //     cout << "Null" << endl;
    // }

    /* GET A PERSON'S NAME BASED ON MAT FORMAT*/
    // string matStr = "-0.0686191 0.102089 -0.00105337 -0.0144187 -0.113577 0.11341 -0.00906423 -0.0431836 0.117796 -0.0361874 0.2743 -0.0159567 -0.304417 -0.0618783 0.0312915 0.0929223 -0.106628 -0.125286 -0.0993145 0.0348979 -0.0563836 0.00096218 0.0368185 0.0305798 -0.143035 -0.365484 -0.0746458 -0.057839 0.0131048 -0.103785 -0.0564006 0.0926407 -0.141517 -0.0807013 0.0649695 0.0435849 -0.104015 -0.0415971 0.252735 0.0421941 -0.172736 0.0481856 0.018572 0.314911 0.140714 -0.0160041 0.0827845 -0.0748115 0.0241836 -0.284979 0.109694 0.196652 0.149352 0.0793323 -0.0042334 -0.135595 -0.0263065 0.150851 -0.181326 0.140949 0.0696108 -0.101495 -0.0218032 -0.0794853 0.147624 0.111091 -0.0873384 -0.203681 0.165975 -0.107077 -0.0794623 0.0857135 -0.132143 -0.265836 -0.268982 0.095123 0.358186 0.176736 -0.17145 0.0196853 -0.105849 -0.0732479 -0.0305209 0.048035 -0.0501492 -0.0846746 -0.0453903 0.0513115 0.259576 -0.027062 -0.0654939 0.194835 0.0525291 -0.0260576 0.0944489 0.0588643 0.00694044 -0.00896938 -0.149756 0.0563699 -0.0511785 -0.224327 0.011867 0.069841 -0.244067 0.198618 0.020369 -0.0680785 0.0363366 0.0194272 -0.123889 -0.00884694 0.218093 -0.362971 0.254226 0.222162 0.159384 0.156957 0.0816286 0.0715054 0.0502839 -0.0143791 -0.129323 -0.133592 0.030814 0.00817115 0.0134029 0.082819";
    // Mat matSearch = db->stringToMat(matStr);
    // string name = db->getNameByBiometricData(matSearch); //Alice
    // if (name != "NULL")
    // {
    //     cout << "The person's name is: " << name << endl;
    // }
    // else
    // {
    //     cout << "NUll" << endl;
    // }

    // /* GET THE BIOMETRIC DATA BASED ON ITS ID */
    // Mat mymat = db->getMatById("A01668163");
    // if (mymat.rows != 0)
    // {
    //     cout << "The mat of the person you look for is: " << mymat << endl;
    // }
    // else
    // {
    //     cout << "there is no record of the person you are looking for " << endl;
    // }

    /* SEARCH IN DB -- A PERSON PASSES  */
    auto start = std::chrono::system_clock::now();
    string vectStr = "-0.0739119 0.0508914 0.0434102 -0.0689023 -0.0424293 -0.0523956 0.0244958 -0.132437 0.191549 -0.0139284 0.221676 0.00304676 -0.220627 -0.065953 -0.0331979 0.0915333 -0.188661 -0.0562228 -0.100452 -0.0881964 -0.0398805 0.0254575 0.117802 -0.00514188 -0.101839 -0.247875 -0.0554136 -0.154361 0.115293 -0.138076 0.0127339 0.0497169 -0.287599 -0.141182 0.0284877 0.026435 -0.0673098 -0.0934699 0.304127 0.0249987 -0.125856 0.0486641 0.0994711 0.193468 0.210673 -0.0857041 0.0251015 -0.0883125 0.191424 -0.244326 0.0981953 0.0772285 0.222085 0.0492346 0.111709 -0.167778 -0.0075764 0.125631 -0.178099 0.148825 0.119205 -0.030087 -0.0170973 0.0155997 0.149062 0.0969186 -0.0728601 -0.178364 0.126701 -0.103289 -0.0243443 0.124617 -0.0825522 -0.103665 -0.310835 0.0417986 0.311187 0.0596648 -0.150578 0.00502425 -0.146475 -0.085487 -0.0610616 0.0438711 -0.0919782 -0.0231383 -0.0430655 0.0193191 0.197668 0.0153208 -0.0877158 0.168577 -0.0401181 0.0153725 -0.00951233 0.0100146 -0.182551 -0.066621 -0.128911 -0.0308653 -0.0299905 -0.0913147 0.00133691 0.156026 -0.214335 0.111146 -0.0695805 -0.0943595 -0.0363303 -0.0206769 -0.0509179 0.0518197 0.10836 -0.264059 0.300562 0.107418 0.0133784 0.075063 0.0393664 -0.00587485 0.0234381 0.0998835 -0.0913251 -0.116732 0.0055925 -0.0136491 0.0833201 0.025134";
    Mat matSearch = db->stringToMat(vectStr);
    Mat nearestNeighbors = db->searchPerson(matSearch, 4);
    cout << "The four nearest are: " << endl
         << nearestNeighbors << endl;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}