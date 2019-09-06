#include <iostream>

#include<string> 

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "./../headers/FaceDB.h"

#include "./../include/rapidjson/document.h"

using namespace std; 

using namespace rapidjson;

int main(int, char**) {
    
    FaceDB db;
    // Crate Person createPerson(name, lastName, studentId, age, gender) eg:
    //db.createPerson("Ruben", "Salazar", "A01234567", 21, "Male");

    //Get Person's name by StudentId getPersonById(studentId) eg:
    string json =  db.getPersonById("A01234567");
    //printf("%s\n", json.c_str());
    Document d;
    d.Parse(json.c_str());
    Value& val = d["name"];
    printf("%s\n", val.GetString());

    //Update imageURL by studentId insetImage(studentId, imageURL)
    //db.insertImage("A01234567", "/img/A01234567.png");

    //PrintDB
    //db.printDB();
}