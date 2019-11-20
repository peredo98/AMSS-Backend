#include <iostream>
#include <algorithm>

#include <string>
#include <string.h>
#include <stdlib.h>

#include <chrono>
#include <thread>
#include <unistd.h>
#include <regex>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "./../sources/FaceDB.cpp"

using namespace std;

FaceDB *db = new FaceDB();

//-- This function loads features stored in a text file
//-- Every feature takes 1 line, and its values separated by a space
Mat LoadVectorFromTextFile(string filename)
{
    std::ifstream file(filename);

    std::string line;

    Mat features;

    // Read one line at a time into the variable line:
    while (std::getline(file, line))
    {
        std::vector<float> lineData;
        std::stringstream lineStream(line);

        float value;
        // Read a float at a time from the line
        while (lineStream >> value)
        {
            // Add the float from a line to a 1D array (vector)
            lineData.push_back(value);
        }

        Mat aux(1, (int)lineData.size(), CV_32FC1, lineData.data());
        features.push_back(aux);
    }

    return features;
}

//-- This function loads text stored in a text file
//-- Every text takes 1 line
std::vector<std::string> LoadTextFromTextFile(string filename)
{
    std::ifstream file(filename);

    std::string line;

    std::vector<std::string> features;

    // Read one line at a time into the variable line:
    while (std::getline(file, line))
    {
        features.push_back(line);
    }

    return features;
}

std::vector<int> LoadAgeFromTextFile(string filename)
{
    std::ifstream file(filename);

    std::string line;

    std::vector<int> features;

    // Read one line at a time into the variable line:
    while (std::getline(file, line))
    {
        int i = std::stoi(line);
        features.push_back(i);
    }

    return features;
}

std::vector<std::string> LoadIDFromTextFile(string filename)
{
    std::ifstream file(filename);

    std::string line;

    std::vector<std::string> features;

    // Read one line at a time into the variable line:
    while (std::getline(file, line))
    {
        string id = line.substr(0, 9);
        features.push_back(id);
    }

    return features;
}

int main()
{
    cout << endl
         << " ** version FULL THE DATABASE **" << endl;

    Mat vectors = LoadVectorFromTextFile("Vectores.txt");
    vector<int> edades = LoadAgeFromTextFile("edades.txt");
    vector<string> nombres = LoadTextFromTextFile("Nombres.txt");
    vector<string> apellidos = LoadTextFromTextFile("Apellidos.txt");
    vector<string> generos = LoadTextFromTextFile("Genero.txt");
    vector<string> id = LoadIDFromTextFile("Matriculas.txt");

    cout << "the size mat is " << vectors.rows << endl;
    cout << "the size age is " << edades.size() << endl;
    cout << "the size name is " << nombres.size() << endl;
    cout << "the size lastname is " << apellidos.size() << endl;
    cout << "the size gender is " << generos.size() << endl;
    cout << "the size id is " << id.size() << endl;

    db->insertMany(nombres, apellidos, id, edades, generos, vectors);
    cout << "YEAH! YOUR DB IS NOW FILLED WITH 100,000 GOOD LUCK..." << endl;
}
