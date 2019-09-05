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
    db.createPerson("Ernesto", "Rámirez", "A01019589", 23, "Male");

    //Get Person by StudentId getPersonById(studentId) eg:
    string str =  db.getPersonById("A01019589");
    printf("%s", str.c_str());

    //PrintDB
    //db.printDB();
}