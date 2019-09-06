#include <iostream>

#include<string> 

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "./../headers/FaceDB.h"

using namespace std; 
int main(int, char**) {
    
    FaceDB db;
    // Crate Person createPerson(name, lastName, studentId, age, gender) eg:
    //db.createPerson("Ruben", "Salazar", "A01234567", 21, "Male");

    //Get Person by StudentId getPersonById(studentId) eg:
    string str =  db.getPersonById("A01234567");
    printf("%s", str.c_str());

    //PrintDB
    //db.printDB();
}