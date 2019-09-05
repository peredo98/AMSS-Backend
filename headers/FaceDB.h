#include <iostream>

#include<string> 

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

using namespace std; 
class FaceDB{

    public:
        mongocxx::instance inst{};
        mongocxx::client conn{mongocxx::uri{}};

        bsoncxx::builder::stream::document document{}; 

        FaceDB(){

        }

        void createPerson(string name, string lastName, string id, int age, string gender){

            auto collection = conn["testdb"]["testcollection"];
            
            document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age  << "gender" << gender;
            collection.insert_one(document.view());
        }

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

        void printDB(){
            auto collection = conn["testdb"]["testcollection"];
            auto cursor = collection.find({});

            
            for (auto&& doc : cursor) {
                std::cout << bsoncxx::to_json(doc) << std::endl;
            }
        }
        
};
