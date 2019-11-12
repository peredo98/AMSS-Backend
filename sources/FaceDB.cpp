#include "./../headers/FaceDB.h"
// #include <bits/stdc++.h>
// #include <boost/algorithm/string.hpp>

using namespace std;
using namespace cv;
using namespace rapidjson;

FaceDB::FaceDB()
{
    cout << "FaceDB class created..." << endl;
    validateData = new ValidateData();
    flannSearch = new IndexSearch();
    totalPeople = getTotal();
    makeDataSet();
    updateIndex();
}

void FaceDB::updateIndex()
{
    flannSearch->updateIndex(dataMatset);
}

Mat FaceDB::searchPerson(cv::Mat_<float> query, int numKnn)
{
    vector<Mat> in_dis = flannSearch->searchPerson(query, numKnn);

    Mat indices = in_dis[0];
    Mat dist = in_dis[1];
    Mat nearestNeighbors;

    for (int i = 0; i < numKnn; i++)
    {
        Mat neigh = dataMatset.row(indices.at<int>(0, i));
        cout << neigh << endl;
        nearestNeighbors.push_back(neigh);
    }
    return nearestNeighbors;
}

void FaceDB::makeDataSet()
{

    Mat_<double> mymat(totalPeople, 128);

    int i = 0;
    auto cursor = collection.find({});
    for (auto &&doc : cursor)
    {
        bsoncxx::document::element bio_element{doc["biometricData "]};
        if (bio_element)
        {
            vector<float> tempVector;
            auto arr = bio_element.get_array();
            for (int j = 0; j < arr.value.length(); j++)
            {
                try
                {
                    float tempVal = (float)arr.value[j].get_double();
                    tempVector.push_back(tempVal);
                    mymat(i, j) = tempVal;
                }
                catch (exception e)
                {
                    break;
                }
            }
            i++;
        }
    }

    dataMatset = mymat;
    cout << "The Mat is: " << endl
         << dataMatset << endl;
}

long FaceDB::getTotal()
{
    auto cursor = collection.find({});
    long total = 0;
    for (auto &&doc : cursor)
    {
        total++;
    }
    return total;
}

void FaceDB::increment(Mat newMat)
{
    totalPeople++;
    dataMatset.push_back(newMat);
    // cout << "The new DataMatSet is: " << endl
    //      << dataMatset << endl;
    updateIndex();
}

void FaceDB::makeRange(Mat indexMat)
{
    int index = 0;

    for (int i = 0; i < dataMatset.rows; i++)
    {
        cout << "an element: " << (i + 1) << endl;
        cv::Mat diff = dataMatset.row(i) != indexMat;
        if (cv::countNonZero(diff) == 0)
        {
            index = i;
            break;
        }
    }

    totalPeople--;

    Mat newRangeMat;

    if (index == 0)
    {
        cv::Range range(1, dataMatset.rows);
        Mat_<double> tempMat(dataMatset, range);
        newRangeMat.push_back(tempMat);
    }
    else if (index == dataMatset.rows - 1)
    {
        cv::Range range(0, dataMatset.rows - 1);
        Mat_<double> tempMat(dataMatset, range);
        newRangeMat.push_back(tempMat);
    }
    else
    {
        cv::Range range(0, index);
        cv::Range range2(index + 1, dataMatset.rows);
        Mat_<double> tempMat(dataMatset, range);
        Mat_<double> tempMat2(dataMatset, range2);
        newRangeMat.push_back(tempMat);
        newRangeMat.push_back(tempMat2);
    }

    dataMatset = newRangeMat;
    // cout
    //     << "The new DataMatSet is: " << endl
    //     << dataMatset << endl;

    updateIndex();
}

Mat FaceDB::getMatById(string id)
{
    bsoncxx::builder::stream::document filter;
    filter << "studentId" << id;
    auto cursor = collection.find({filter.view()});
    vector<float> tempVector;
    Mat myMat;
    for (auto &&doc : cursor)
    {
        bsoncxx::document::element bio_element{doc["biometricData "]};
        if (bio_element)
        {
            auto arr = bio_element.get_array();

            for (int i = 0; i < arr.value.length(); i++)
            {
                try
                {
                    float tempVal = (float)arr.value[i].get_double();
                    tempVector.push_back(tempVal);
                }
                catch (exception e)
                {
                    break;
                }
            }
            myMat = vectorToMat(1, tempVector.size(), tempVector);
        }
    }
    return myMat;
}

string FaceDB::getNameByBiometricData(vector<float> myvector)
{

    bsoncxx::builder::stream::document filter;

    auto array = filter << "biometricData " << bsoncxx::builder::stream::open_array;
    for (int i = 0; i < myvector.size(); i++)
    {
        array << myvector[i];
    }
    array << bsoncxx::builder::stream::close_array;

    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
        collection.find_one(filter.view());
    if (maybe_result)
    {

        d.Parse(bsoncxx::to_json(*maybe_result).c_str());
        Value &val = d["name"];
        string name = val.GetString();
        return name;
    }
    return "NULL";
}

string FaceDB::getNameByBiometricData(Mat matSearch)
{

    bsoncxx::builder::stream::document filter;
    vector<float> myvector = matToVector(matSearch);
    auto array = filter << "biometricData " << bsoncxx::builder::stream::open_array;
    for (int i = 0; i < myvector.size(); i++)
    {
        array << myvector[i];
    }
    array << bsoncxx::builder::stream::close_array;

    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
        collection.find_one(filter.view());
    if (maybe_result)
    {
        d.Parse(bsoncxx::to_json(*maybe_result).c_str());
        Value &val = d["name"];
        string name = val.GetString();
        return name;
    }
    return "NULL";
}

// to retrieve person from DB
string FaceDB::getNameById(string id)
{
    bsoncxx::builder::stream::document filter;

    filter << "studentId" << id;

    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
        collection.find_one(filter.view());
    if (maybe_result)
    {
        d.Parse(bsoncxx::to_json(*maybe_result).c_str());
        Value &val = d["name"];
        return val.GetString();
    }
    return "NULL";
}

//to insert person in DB without photo
void FaceDB::createPerson(string name, string lastName, string id, int age, string gender)
{
    if (validateData->validate_all(name, lastName, id, gender))
    {
        document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender;
        collection.insert_one(document.view());
        Mat null;
        increment(null);
    }
}

//to insert person in DB with photo
void FaceDB::createPerson(string name, string lastName, string id, int age, string gender, string imageURL)
{
    if (validateData->validate_all(name, lastName, id, gender))
    {
        document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender << "imageUrl" << imageURL;
        collection.insert_one(document.view());
        Mat null;
        increment(null);
    }
}

//to insert person in DB with biometrics
void FaceDB::createPerson(string name, string lastName, string id, int age, string gender, Mat mymat)
{
    if (validateData->validate_all(name, lastName, id, gender))
    {
        document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender;
        vector<float> biometrics = matToVector(mymat);
        auto array = document << "biometricData " << bsoncxx::builder::stream::open_array;

        for (int i = 0; i < biometrics.size(); i++)
        {
            array << biometrics[i];
        }
        array << bsoncxx::builder::stream::close_array;

        collection.insert_one(document.view());
        increment(mymat);
    }
}

//to insert person in DB with biometrics
void FaceDB::createPerson2(string name, string lastName, string id, int age, string gender, Mat auxMat)
{
    if (validateData->validate_all(name, lastName, id, gender))
    {

        string matStr = matToString(auxMat);
        // cout << "The mat string is: " << endl
        //      << matStr << endl;

        document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender << "biometricData" << matStr;
        collection.insert_one(document.view());

        increment(auxMat);
    }
}

//to insert person in DB with photo and biometrics
void FaceDB::createPerson(string name, string lastName, string id, int age, string gender, string imageURL, Mat mymat)
{
    if (validateData->validate_all(name, lastName, id, gender))
    {
        document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender << "imageUrl" << imageURL;

        vector<float> biometrics = matToVector(mymat);
        auto array = document << "biometricData " << bsoncxx::builder::stream::open_array;

        for (int i = 0; i < biometrics.size(); i++)
        {
            array << biometrics[i];
        }
        array << bsoncxx::builder::stream::close_array;

        collection.insert_one(document.view());
        increment(mymat);
    }
}

void FaceDB::deletePersonById(string id)
{

    Mat deletedMat = getMatById(id);
    cout << "the deleted Mat is: " << deletedMat << endl;
    if (deletedMat.rows != 0)
    {
        makeRange(deletedMat);
        bsoncxx::builder::stream::document filter;
        filter << "studentId" << id;
        collection.delete_one(filter.view());
    }
    else
    {
        cout << "no existe el usuario y no borre nada" << endl;
    }
}

void FaceDB::saveImage(Mat image, string fileName)
{
    imwrite("./../img/" + fileName + ".png", image);
}

//write image url into existing user
void FaceDB::insertImage(string id, string fileName)
{
    bsoncxx::builder::stream::document filter;

    filter << "studentId" << id;

    bsoncxx::builder::stream::document update;

    string imageURL = ("./../img/" + fileName);

    update << "$set" << bsoncxx::builder::stream::open_document << "imageUrl" << imageURL << bsoncxx::builder::stream::close_document;

    collection.update_one(filter.view(), update.view());
}

//insert matrix with biometric data into existing user
void FaceDB::insertBiometric(string id, Mat mymat)
{
    bsoncxx::builder::stream::document filter;

    filter << "studentId" << id;

    bsoncxx::builder::stream::document update;

    update << "$set" << bsoncxx::builder::stream::open_document;
    vector<float> biometrics = matToVector(mymat);
    auto array = update << "biometricData " << bsoncxx::builder::stream::open_array;

    for (int i = 0; i < biometrics.size(); i++)
    {
        array << biometrics[i];
    }
    array << bsoncxx::builder::stream::close_array;

    update << bsoncxx::builder::stream::close_document;

    collection.update_one(filter.view(), update.view());
}

vector<float> FaceDB::matToVector(Mat mymat)
{
    vector<float> normalVector;
    normalVector.assign((float *)mymat.datastart, (float *)mymat.dataend);
    return normalVector;
}

Mat FaceDB::vectorToMat(long rows, long col, vector<float> vtest)
{
    Mat mymat = Mat(rows, col, CV_32FC1); // Mat(row, columns, type);
    memcpy(mymat.data, vtest.data(), vtest.size() * sizeof(float));
    return mymat;
}

string FaceDB::matToString(Mat mymat)
{
    cout << "i create the mat: " << mymat.cols << endl;
    string auxStr = "";

    for (int i = 0; i < mymat.cols; i++)
    {
        // cout << "i: " << i << ": " << mymat(0, i) << endl;
        // cout << "i: " << i << ": " << mymat.at<float>(0, i) << endl;
        float element = mymat.at<float>(0, i);
        auxStr = auxStr + to_string(element) + " ";
    }
    cout << "i stope here" << endl;

    return auxStr;
}

const vector<float> explode(const string &s, const char &c)
{
    string buff{""};
    vector<float> v;

    for (auto n : s)
    {
        if (n != c)
            buff += n;
        else if (n == c && buff != "")
        {
            v.push_back(stof(buff));
            buff = "";
        }
    }
    if (buff != "")
        v.push_back(stof(buff));

    return v;
}

Mat FaceDB::stringToMat(string matStr)
{
    char *pch;
    printf("Splitting string \"%s\" into tokens:\n", matStr);
    pch = strtok(matStr, " ,.-");
    while (pch != NULL)
    {
        printf("%s\n", pch);
        pch = strtok(NULL, " ,.-");
    }
}

//Print all documents in DB
void FaceDB::printDB()
{
    auto cursor = collection.find({});

    cout << endl
         << "- -THE DATABASE IS: " << endl
         << endl;
    for (auto &&doc : cursor)
    {
        cout << bsoncxx::to_json(doc) << endl
             << endl;
    }
}

/* ALTERNATIVE KNNSEARCH 
double distance(vector<float> p, vector<float> q)
{
    double d = 0;
    if (p.size() == q.size())
    {
        for (int i = 0; i < p.size(); i++)
        {
            d += (p[i] - q[i]) * (p[i] - q[i]);
        }
        d = sqrt(d);
        return d;
    }
    else
    {
        return 0x1.fffffffffffffp+1023;
    }
}

vector<Mat> searchPersonKnn(cv::Mat_<float> query, int numKnn)
{
    cout << "Time to search..." << endl
            << endl;

    vector<Mat> result;

    auto cursor = collection.find({});

    for (auto &&doc : cursor)
    {

        bsoncxx::document::element bio_element{doc["biometricData "]};
        if (bio_element)
        {
            auto arr = bio_element.get_array();
            vector<float> tempVector;
            for (int i = 0; i < arr.value.length(); i++)
            {
                try
                {
                    float tempVal = (float)arr.value[i].get_double();

                    tempVector.push_back(tempVal);
                }
                catch (exception e)
                {
                    break;
                }
            }

            cout << bsoncxx::to_json(arr.value) << distance(matToVector(query), tempVector) << endl
                    << endl;

            if (result.size() < numKnn)
            {
                Mat tempMat = vectorToMat(1, tempVector.size(), tempVector);
                result.push_back(tempMat);
            }
            else
            {
                int farestVector = 0;
                for (int i = 1; i < result.size(); i++)
                {
                    if (distance(matToVector(query), matToVector(result[farestVector])) < distance(matToVector(query), matToVector(result[i])))
                    {
                        farestVector = i;
                    }
                }
                if (distance(matToVector(query), matToVector(result[farestVector])) > distance(matToVector(query), tempVector))
                {
                    Mat tempMat = vectorToMat(1, tempVector.size(), tempVector);
                    result[farestVector] = tempMat;
                }
            }
        }
    }
    return result;
} 
*/
