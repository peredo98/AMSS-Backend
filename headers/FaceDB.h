#include <iostream>

#include<string> 

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std; 
using namespace cv;

class FaceDB{

    public:

        //init mongo
        mongocxx::instance inst{};
        mongocxx::client conn{mongocxx::uri{}};
        bsoncxx::builder::stream::document document{}; 

        FaceDB(){

        }

        //to insert person in DB without photo
        void createPerson(string name, string lastName, string id, int age, string gender){

            auto collection = conn["testdb"]["testcollection"];
            
            document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age  << "gender" << gender;
            collection.insert_one(document.view());
        }

        //to insert person in DB with photo
        void createPerson(string name, string lastName, string id, int age, string gender, string imageURL){

            auto collection = conn["testdb"]["testcollection"];
            
            document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age  << "gender" << gender << "imageUrl" << imageURL;
            collection.insert_one(document.view());
        }

         //to insert person in DB with photo and biometrics
        void createPerson(string name, string lastName, string id, int age, string gender, vector<vector<int>> biometrics){

            auto collection = conn["testdb"]["testcollection"];
            
            document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age  << "gender" << gender;
            

            auto array = document << "biometricData "<<  bsoncxx::builder::stream::open_array;

            for (int i =0;i < biometrics.size(); i++) {

                biometrics[i].size();
                
                array << bsoncxx::builder::stream::open_array;
                
                for (int j =0;j < biometrics[i].size(); j++) {
                   array << biometrics[i][j];
                }

                array << bsoncxx::builder::stream::close_array;
            }
            array << bsoncxx::builder::stream::close_array;

            collection.insert_one(document.view());
        }

        //to insert person in DB with photo and biometrics
        void createPerson(string name, string lastName, string id, int age, string gender, string imageURL, vector<vector<int>> biometrics){

            auto collection = conn["testdb"]["testcollection"];
            
            document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age  << "gender" << gender << "imageUrl" << imageURL;
            

            auto array = document << "biometricData "<<  bsoncxx::builder::stream::open_array;

            for (int i =0;i < biometrics.size(); i++) {

                biometrics[i].size();
                
                array << bsoncxx::builder::stream::open_array;
                
                for (int j =0;j < biometrics[i].size(); j++) {
                   array << biometrics[i][j];
                }

                array << bsoncxx::builder::stream::close_array;
            }
            array << bsoncxx::builder::stream::close_array;

            collection.insert_one(document.view());
        }
        
        void saveImage(Mat image, string fileName){
            imwrite("./../img/" + fileName + ".png", image);
        }

        //write image url into existing user
        void insertImage(string id ,string fileName){
            auto collection = conn["testdb"]["testcollection"];

            bsoncxx::builder::stream::document filter;

            filter << "studentId" << id;

            bsoncxx::builder::stream::document update;

            string imageURL = ("./../img/" + fileName);

            update << "$set" << bsoncxx::builder::stream::open_document << "imageUrl" << imageURL << bsoncxx::builder::stream::close_document;

            collection.update_one(filter.view(), update.view());
        }
        
         //insert matrix with viometric data into existing user
        void insertBiometric(string id, vector<vector<int>> biometrics){
            auto collection = conn["testdb"]["testcollection"];

            bsoncxx::builder::stream::document filter;

            filter << "studentId" << id;

            bsoncxx::builder::stream::document update;
     
            update << "$set" << bsoncxx::builder::stream::open_document;

            auto array = update << "biometricData "<<  bsoncxx::builder::stream::open_array;

            for (int i =0;i < biometrics.size(); i++) {

                biometrics[i].size();
                
                array << bsoncxx::builder::stream::open_array;
                
                for (int j =0;j < biometrics[i].size(); j++) {
                   array << biometrics[i][j];
                }

                array << bsoncxx::builder::stream::close_array;
            }
            array << bsoncxx::builder::stream::close_array;

            update << bsoncxx::builder::stream::close_document;

            collection.update_one(filter.view(), update.view());
        }
        
        // to retrieve person from DB
        string getPersonById(string id){
            auto collection = conn["testdb"]["testcollection"];

            bsoncxx::builder::stream::document filter;

            filter << "studentId" << id;

            bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            collection.find_one(filter.view());
            if(maybe_result) {

                //std::cout << bsoncxx::to_json(*maybe_result) << "\n";

                return bsoncxx::to_json(*maybe_result);
            }
            return "";
        }


        //Print all documents in DB
        void printDB(){
            auto collection = conn["testdb"]["testcollection"];
            auto cursor = collection.find({});

            
            for (auto&& doc : cursor) {
                std::cout << bsoncxx::to_json(doc) << std::endl;
            }
        }
        
};
