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
    //db.createPerson("Ernesto", "Rámirez", "A01019589", 23, "Male");
    string str =  db.getPersonById("A01019589");
    printf("%s", str.c_str());
    //db.printDB();
}