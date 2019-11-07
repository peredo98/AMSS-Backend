# TEAM 4 - DATABASE

## Proyect description

Create a database which receive the vector description of the person who has just enter. After that, get their personal and biographic in# TEAM 4 - DATABASE

## Proyect description

Create a database which receive the vector description of the person who has just enter. After that, get their personal and biographic information to notify if the person is already in the system.

## Functional requirements

- The system will be able to save biometric, personal information (name, id, age, gender, lastname) and a user's photo.
- The system returns the personal information of the person that has the greatest similarity to the person who has just entered.
- The search of the database must be index.
- The system can add, edit or delete profiles.
- The database must have a backup system.

## Non-functional requirements

- The system only accepts biometric, biographic data and a photo.
- The percentage of error in returning the right person must be less than or equal to 10% (1 of 10 person who enter may fail).
- The response time of the search system must be equal to or less than one second.
- The database must have the ability to save 100,000 profiles.
- The database works in both MongoDB and OpenCV.
- The system must restrict only one profile per person. Therefore, you should not accept repeated.
- The system must have properly structured user manuals.
- The system must be multi platform (Windows, Mac OS , Linux ).

# Installation

For this proyect it's neccesaary to have `MongoDB` which allow you to store the data and `Mongocxx` which is the driver of MongoDB for C++ (For further information about Mongocxx click [here](http://mongocxx.org/mongocxx-v3/tutorial/)).

For `Mac OS` and `Windows` is different the installation and dependending of the system you have follow the corresponding process:

- **Mac OS**

First, you need to have Homebrew installed to have the correct dependencies for this proyect.

> Homebrew not installed

Open your terminal and run the following commands to install Hombrew.

    ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    brew update

Also add Homebrew to PATH

    echo "# Homebrew" >> ~/.bash_profile
    echo "export PATH=/usr/local/bin:\$PATH" >> ~/.bash_profile

Then, you should have Homebrew installed and you're ready to install de dependecies.

> Homebrew installed

Open your terminal and run the following commands to install de dependencies.

    brew install python3
    brew install cmake
    brew install qt5
    QT5PATH=/usr/local/Cellar/qt/5.11.2_1

    brew install mongodb

    brew tap mongodb/brew

    brew install mongodb

    brew install mongodb-community

    brew install mongo-cxx-driver

    brew services start mongodb-community

    brew install pkg-config

    brew tap nlohmann/json

    brew install nlohmann-json

    brew tap cuber/homebrew-jsoncpp

    brew install jsoncpp

<br>

- **Windows**

# Compilation

To test the proyect, first compile it and then run it. Depending of the OS you have, the process will be different.

The `test.cpp` file is the main file.

- **MAC OS**

  Open your terminal in the `sources` foulder and run the following command to run.

  > g++ --std=c++11 test.cpp -o test \$(pkg-config --cflags --libs libmongocxx opencv4)

  In the same root run the following command to test the project.

  > ./test

* **Windows**

# Test

- Create a person in the data base

  There are multiple ways to insert someone into the data base. However, the most recomendable one is the following. It is neccessary to have the name, parternal lastname, id, age, gender and the decription vector.

  > vector<float> vtest = {-0.0554103, 0.234784, 0.0174269, -0.0774777, -0.147699};
  >
  > Mat mymat = db.vectorToMat(1, vtest.size(), vtest);
  >
  > db.createPerson("Nancy", "Medina", "A01330291", 20, "Female", mymat);

- Delete a person related to an ID

  > db.deletePersonById("A01234567");

- Get a person related to its description vector on vector<float> format

  > vector<float> vSearch = {-0.077756, 0.192846, 0.0550688, -0.168125, -0.182494};
  >
  > string json = db.getPersonByBiometricData(vSearch);
  >
  > d.Parse(json.c_str());
  >
  > Value& val = d["name"];
  >
  > printf("%s\n", val.GetString());

- Get a person related to its description vector on Mat format

  > vector<float> vSearch = {-0.0576136, 0.171748, 0.0571629, -0.152391, -0.166514};
  >
  > Mat matSearch = db.vectorToMat(1, vSearch.size() ,vSearch);
  >
  > string jsonM = db.getPersonByBiometricData(matSearch);
  >
  > d.Parse(jsonM.c_str());
  >
  > Value& valM = d["name"];
  >
  > printf("%s\n", valM.GetString());

- Get the description vector of the four persons most alike to someone

  > vector<float> vSearch = {-0.077756, 0.192846, 0.0550688, -0.168125, -0.182494}; //Vector of the person you are looking for.
  >
  > Mat matSearch = db.vectorToMat(1, vSearch.size(), vSearch);
  >
  > vector<Mat> result = db.searchPersonKnn(matSearch, 4);
  >
  > for (int i = 0; i < result.size(); i++){
  >
  > vector<float> tempVector = db.matToVector(result[i]);
  >
  > for (int j = 0; j < tempVector.size(); j++){
  >
  > printf("%f ", tempVector[j]);
  > }
  >
  > printf("\n");
  >
  > }

- Print the data base

  > db.printDB();
  > formation to notify if the person is already in the system.
