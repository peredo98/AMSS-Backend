#include "./../headers/FaceDB.h"
// #include <bits/stdc++.h>
// #include <boost/algorithm/string.hpp>

using namespace std;
using namespace cv;
using namespace rapidjson;
using bsoncxx::builder::stream::finalize;

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

int FaceDB::searchPerson(cv::Mat_<float> query, int numKnn, vector<Mat> &topMatches, vector<string> &topNames, vector<string> &topMatchesId)
{
    vector<Mat> in_dis = flannSearch->searchPerson(query, numKnn);

    Mat indices = in_dis[0];
    Mat dist = in_dis[1];

    for (int i = 0; i < numKnn; i++)
    {
        Mat theMat = dataMatset.row(indices.at<int>(0, i));

        string theName;
        getNameByBiometricData(theMat, theName);

        string theID;
        getIdByBioData(theMat, theID);

        topMatches.push_back(theMat);
        topNames.push_back(theName);
        topMatchesId.push_back(theID);
    }
    return 0;
    // return nearestNeighbors;
}

void FaceDB::makeDataSet()
{

    // Mat_<double> mymat(totalPeople, 128);

    // int i = 0;
    // auto cursor = collection.find({});
    // for (auto &&doc : cursor)
    // {
    //     bsoncxx::document::element bio_element{doc["biometricData "]};
    //     if (bio_element)
    //     {
    //         vector<float> tempVector;
    //         auto arr = bio_element.get_array();
    //         for (int j = 0; j < arr.value.length(); j++)
    //         {
    //             try
    //             {
    //                 float tempVal = (float)arr.value[j].get_double();
    //                 tempVector.push_back(tempVal);
    //                 mymat(i, j) = tempVal;
    //             }
    //             catch (exception e)
    //             {
    //                 break;
    //             }
    //         }
    //         i++;
    //     }
    // }

    // Mat_<double> mymat(totalPeople, 128);

    int i = 0;
    auto cursor = collection.find({});
    for (auto &&doc : cursor)
    {

        // bsoncxx::document::element bio_element{doc["biometricData "]};
        string json = bsoncxx::to_json(doc);
        // cout << "entro aqui" << endl
        //      << json << endl;

        d.Parse(json.c_str());
        Value &val = d["biometricData"];
        string matStr = val.GetString();
        // std::cout << matStr << endl;

        Mat auxMat = stringToMat(matStr);
        dataMatset.push_back(auxMat);

        i++;

        // if (bio_element)
        // {

        //     string json = bsoncxx::to_json(doc);
        //     cout << "entro aqui" << endl
        //          << json << endl;
        //     // d.Parse(bsoncxx::to_json(&bio_element).c_str());
        //     // vector<float> tempVector;
        //     // auto arr = bio_element.get_array();
        //     // for (int j = 0; j < arr.value.length(); j++)
        //     // {
        //     //     try
        //     //     {
        //     //         float tempVal = (float)arr.value[j].get_double();
        //     //         tempVector.push_back(tempVal);
        //     //         mymat(i, j) = tempVal;
        //     //     }
        //     //     catch (exception e)
        //     //     {
        //     //         break;
        //     //     }
        //     // }
        //     // i++;
        // }
    }

    // dataMatset = mymat;
    // cout << "The Mat is: " << endl
    //      << dataMatset << endl;
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

    updateIndex();
}

int FaceDB::getMatById(string id, Mat &mymat)
{
    bsoncxx::builder::stream::document filter;

    filter << "studentId" << id;
    // Mat mymat;
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
        collection.find_one(filter.view());
    if (maybe_result)
    {
        d.Parse(bsoncxx::to_json(*maybe_result).c_str());
        Value &val = d["biometricData"];
        string matStr = val.GetString();
        mymat = stringToMat(matStr);
        return 0; // MAT FOUND
    }
    return 1; //MAT NOT FOUND

    // bsoncxx::builder::stream::document filter;
    // filter << "studentId" << id;
    // auto cursor = collection.find({filter.view()});
    // vector<float> tempVector;
    // Mat myMat;
    // for (auto &&doc : cursor)
    // {
    //     bsoncxx::document::element bio_element{doc["biometricData "]};
    //     if (bio_element)
    //     {
    //         auto arr = bio_element.get_array();

    //         for (int i = 0; i < arr.value.length(); i++)
    //         {
    //             try
    //             {
    //                 float tempVal = (float)arr.value[i].get_double();
    //                 tempVector.push_back(tempVal);
    //             }
    //             catch (exception e)
    //             {
    //                 break;
    //             }
    //         }
    //         myMat = vectorToMat(1, tempVector.size(), tempVector);
    //     }
    // }
    // return myMat;
}

int FaceDB::getNameByBiometricData(vector<float> myvector, string &name) // This is not useful
{

    Mat mymat = vectorToMat(1, myvector.size(), myvector);
    string matStr = matToString(mymat);

    bsoncxx::builder::stream::document filter;

    // auto array = filter << "biometricData " << bsoncxx::builder::stream::open_array;
    // for (int i = 0; i < myvector.size(); i++)
    // {
    //     array << myvector[i];
    // }
    // array << bsoncxx::builder::stream::close_array;

    auto array = filter << "biometricData" << matStr;
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
        collection.find_one(filter.view());
    if (maybe_result)
    {

        d.Parse(bsoncxx::to_json(*maybe_result).c_str());
        Value &val = d["name"];
        name = val.GetString();
        return 0;
    }
    return 1;
}

int FaceDB::getNameByBiometricData(Mat matSearch, string &name)
{

    bsoncxx::builder::stream::document filter;
    // vector<float> myvector = matToVector(matSearch);
    // auto array = filter << "biometricData " << bsoncxx::builder::stream::open_array;
    // for (int i = 0; i < myvector.size(); i++)
    // {
    //     array << myvector[i];
    // }
    // array << bsoncxx::builder::stream::close_array;
    string matStr = matToString(matSearch);
    auto array = filter << "biometricData" << matStr;
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
        collection.find_one(filter.view());
    if (maybe_result)
    {
        d.Parse(bsoncxx::to_json(*maybe_result).c_str());
        Value &val = d["name"];
        name = val.GetString();
        return 0;
    }
    return 1;
}

int FaceDB::getIdByBioData(cv::Mat mymat, string &id)
{
    bsoncxx::builder::stream::document filter;
    string matStr = matToString(mymat);
    auto array = filter << "biometricData" << matStr;
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
        collection.find_one(filter.view());
    if (maybe_result)
    {
        d.Parse(bsoncxx::to_json(*maybe_result).c_str());
        Value &val = d["studentId"];
        id = val.GetString();
        return 0;
    }
    return 1;
}

// to retrieve person from DB
int FaceDB::getNameById(string id, string &name)
{
    bsoncxx::builder::stream::document filter;

    filter << "studentId" << id;

    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
        collection.find_one(filter.view());
    if (maybe_result)
    {
        d.Parse(bsoncxx::to_json(*maybe_result).c_str());
        Value &val = d["name"];
        // name = "HOla mundo";
        name = val.GetString();

        // return val.GetString();
        return 0;
    }
    name = "NULL";

    return 1;
}

// get the img of a person
int FaceDB::getImgById(string id, Mat &img)
{
    bsoncxx::builder::stream::document filter;

    filter << "studentId" << id;

    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
        collection.find_one(filter.view());

    if (maybe_result)
    {
        d.Parse(bsoncxx::to_json(*maybe_result).c_str());

        Value &val = d["imageUrl"];

        string path = val.GetString();

        img = cv::imread(path);

        return 0;
    }
    return 1;
}

//to insert person in DB without photo
void FaceDB::createPerson(string name, string lastName, string id, int age, string gender) //This is not useful
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
void FaceDB::createPerson(string name, string lastName, string id, int age, string gender, string imageURL) //This is not useful
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
        string biometrics = matToString(mymat);
        document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender << "biometricData" << biometrics;
        collection.insert_one(document.view());
        increment(mymat);
    }
}

//to insert person in DB with photo and biometrics
void FaceDB::createPerson(string name, string lastName, string id, int age, string gender, string imageURL, Mat mymat)
{
    if (validateData->validate_all(name, lastName, id, gender))
    {
        string biometrics = matToString(mymat);
        document << "name" << name << "lastName" << lastName << "studentId" << id << "age" << age << "gender" << gender << "imageUrl" << imageURL << "biometricData" << biometrics;
        collection.insert_one(document.view());
        increment(mymat);
    }
}

void FaceDB::insertMany(vector<string> name, vector<string> lastName, vector<string> id, vector<int> age, vector<string> gender, Mat auxMat)
{
    std::vector<bsoncxx::document::value> documents;

    for (int i = 0; i < 100000; i++)
    {
        string matStr = "";
        matStr = matToString(auxMat.row(i));
        string imageURL = "./../img/" + id[i] + ".png";
        documents.push_back(
            bsoncxx::builder::stream::document{} << "name" << name[i] << "lastName" << lastName[i] << "studentId" << id[i] << "age" << age[i] << "gender" << gender[i] << "imageUrl" << imageURL << "biometricData" << matStr << finalize);
    }

    collection.insert_many(documents);
}

void FaceDB::deletePersonById(string id)
{

    Mat deletedMat;
    int result = getMatById(id, deletedMat);

    cout << "the deleted Mat is: " << deletedMat << endl;

    if (result == 0)
    {
        makeRange(deletedMat);
        bsoncxx::builder::stream::document filter;
        filter << "studentId" << id;
        collection.delete_one(filter.view());
        cout << "BORRADO EXITOSO" << endl;
    }
    else
    {
        cout << "no existe el usuario y no borre nada" << endl;
    }
}

void FaceDB::deleteAll()
{
    collection.drop();
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
    // cout << "i create the mat: " << mymat.cols << endl;
    string auxStr = "";

    for (int i = 0; i < mymat.cols; i++)
    {
        // cout << "i: " << i << ": " << mymat(0, i) << endl;
        // cout << "i: " << i << ": " << mymat.at<float>(0, i) << endl;

        float element = mymat.at<float>(0, i);
        std::ostringstream os;
        os << element;
        auxStr = auxStr + os.str() + " ";
    }
    return auxStr;
}

Mat FaceDB::stringToMat(string s)
{
    std::string delimiter = " ";
    vector<float> auxVec;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        // cout << "the token is: ";
        // std::cout << token << std::endl;
        auxVec.push_back(std::stof(token));
        s.erase(0, pos + delimiter.length());
    }
    // std::cout << "The length of the vector is" << auxVec.size() << std::endl;
    Mat mymat = vectorToMat(1, auxVec.size(), auxVec);
    return mymat;
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
