#include <iostream>

#include<string> 

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "./../headers/FaceDB.h"

#include "./../include/rapidjson/document.h"

using namespace std; 

using namespace rapidjson;

int main(int, char**) {
    
    FaceDB db;
    // Crate Person createPerson(name, lastName, studentId, age, gender) eg:
    //db.createPerson("Ruben", "Salazar", "A01234567", 21, "Male");

    /*
    //Get Person's name by StudentId getPersonById(studentId) eg:
    string json =  db.getPersonById("A01234567");
    printf("%s\n", json.c_str());

    //Retrieve name from retrived Person
    Document d;
    d.Parse(json.c_str());
    Value& val = d["name"];
    printf("%s\n", val.GetString());
    */

    //Read image
    Mat image;
    image = imread( "./../img/sample.jpeg", 1 );

    //Save image (the image will be saved with .png extension)
    db.saveImage(image, "A01234567");

    //Update imageURL by studentId insetImage(studentId, fileName) | filename must include the file extension
    db.insertImage("A01234567", "A01234567.png");

    //PrintDB
    db.printDB();
}