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

    brew install mongodb

    brew tap mongodb/brew

    brew install mongodb-community

    brew install mongo-cxx-driver

    brew services start mongodb-community

<br>

- **Windows**

prerequisites:

- Visual Studio Community 2019 - Visual Studio English Language Pack 2019

First, you need to install vckpg 2019.10

    https://github.com/microsoft/vcpkg/archive/2019.10.zip

Then, you must extract the zip and open the extracted directory on the command prompt and enter the following commands:

    .\bootstrap-vcpkg.bat
    .\vcpkg.exe install mongo-cxx-driver
    .\vcpkg.exe install opencv
    .\vcpkg.exe integrate install

# Start

In the main class its is needed to import only the class `FaceDB.cpp` and instantiate it in the following way.

```
#include "FaceDB.cpp"
FaceDB *db = new FaceDB();
```

Also, it needed to download all the .cpp in the `sources` folder and the .h files in the `headers`folder and leave the in the same directory to the projects work as it should.

### Fill the database

To fill your local database you need to do the following steps:

1. Download the Vectors.txt from <https://drive.google.com/file/d/1PvNtaSKuFYAo1ZC5dKNNMdLr9eAO0UcT/view> and put it in the `testFolder` folder.

2. Compile and run the `fullDB.cpp` file inside the same folder than above. It will take a minute, don't worry.

Now, you should have stored 100,000 people with name, lastname, age, id, gender, a descriptor vector and its image.

This must to be done **ONLY ONCE**, so you can forget about this once you're done.

# Compilation

To test the proyect, first compile it and then run it. Depending of the OS you have, the process will be different.

The `main.cpp` file is the main file.

- **MAC OS**

  Open your terminal in the `sources` foulder and run the following command to run.

  > g++ --std=c++11 main.cpp -o main \$(pkg-config --cflags --libs libmongocxx opencv4)

  In the same root run the following command to test the project.

  > ./main

* **Windows**

  Open Visual Studio 2019 and make a new solution with existing code.

  On your solution explorer view right click on your solution and select properties:

  ![alt text](<https://github.com/peredo98/AMSS-Backend/blob/master/img/Captura%20de%20Pantalla%202019-11-11%20a%20la(s)%2018.29.52.png>)

  Go to Configuration properties, in Linker, and in System select the Console(/SUBSYSTEM:CONSOLE) as subsystem, and click on the apply button:

  ![alt text](<https://github.com/peredo98/AMSS-Backend/blob/master/img/Captura%20de%20Pantalla%202019-11-11%20a%20la(s)%2018.32.20.png>)

  In the debug tab click on Start without debbuging and the project should run:

  ![alt text](<https://github.com/peredo98/AMSS-Backend/blob/master/img/Captura%20de%20Pantalla%202019-11-11%20a%20la(s)%2018.32.51.png>)

# Methods

> Create a person in the data base

- There are multiple ways to insert someone into the data base. However, the most recomendable are the following ones. It is neccessary to have the name, parternal lastname, id, age, gender and the decription vector.

  ```
  string n = "-0.0655079 0.0690271 0.0021162 -0.0257782 -0.0986043 0.111701 0.0208896 -0.0399436 0.110203 -0.0340782 0.26934 -0.0160517 -0.295691 -0.0752613 0.031978 0.0983907 -0.117126 -0.136332 -0.120889 0.0175581 -0.0692704 0.0023763 0.0305309 0.0260692 -0.147197 -0.379964 -0.0622384 -0.0865151 0.0217936 -0.130979 -0.0441539 0.098084 -0.169122 -0.077425 0.0604469 0.0480285 -0.096275 -0.0401113 0.234278 0.0751676 -0.19235 0.0423303 0.0325505 0.331564 0.140167 0.00262341 0.0690553 -0.0634018 0.0349632 -0.297434 0.110803 0.177569 0.143938 0.088171 -0.0031783 -0.13914 -0.00284011 0.135178 -0.204379 0.147438 0.0747636 -0.107236 -0.0248385 -0.059577 0.15486 0.107293 -0.089704 -0.180458 0.151387 -0.119339 -0.0765511 0.0796549 -0.125105 -0.259026 -0.282548 0.0901779 0.37832 0.201828 -0.172716 0.0149473 -0.11909 -0.0544199 0.00282964 0.0802033 -0.0430424 -0.0503241 -0.0401632 0.0529515 0.231029 -0.0132195 -0.068395 0.194758 0.0335194 -0.0230613 0.0768645 0.0484102 -0.0222673 -0.0155564 -0.145723 0.0133732 -0.0550851 -0.177206 0.0268946 0.0762096 -0.241841 0.211683 0.0221193 -0.0696319 0.0447158 0.0197885 -0.0731614 -0.0160547 0.177402 -0.366922 0.244778 0.24591 0.141014 0.156699 0.0798074 0.0541609 0.0404421 -0.0162672 -0.146647 -0.118927 0.0306446 0.0156863 0.0237265 0.0585895";

  Mat mymat = db->stringToMat(n);

  db->createPerson("Ruben", "Salazar", "A01338798", 20, "Male", mymat);
  ```

> Delete a person related to an ID

```
db->deletePersonById("A01234567");
```

> Get a person's name related to its description vector on Mat formatvector<float> format

- Returns the corresponding name in string format to the given vector. It returns 0 if there's record of the person or 1 if it doesn't. The string is passed by reference.

  ```
  string name;

  string matStr = "-0.0616511 0.0475776 0.0362354 -0.00242895 -0.112268 0.0606102 0.00753146 -0.0637529 0.106891 -0.0187525 0.234492 -0.0159751 -0.307106 -0.043978 -0.0115506 0.111364 -0.0745489 -0.158511 -0.101033 0.00115909 -0.0506868 -0.00411913 0.0347568 0.0161157 -0.114755 -0.343202 -0.0764834 -0.0734758 -0.0221774 -0.107824 -0.0256894 0.0826778 -0.178726 -0.0932796 0.0919714 0.059551 -0.110057 -0.0537951 0.236683 0.0418406 -0.149338 0.0509383 0.0202544 0.31261 0.105552 0.00383814 0.0733314 -0.0827081 0.0150385 -0.306268 0.116218 0.178675 0.132616 0.102245 0.0139852 -0.156941 0.0219384 0.172704 -0.197279 0.172844 0.0878312 -0.0951407 -0.0269293 -0.0737721 0.184078 0.114524 -0.106078 -0.156875 0.152411 -0.0966852 -0.0578988 0.0594064 -0.128421 -0.253084 -0.259731 0.0860366 0.365467 0.172306 -0.193488 -0.0112439 -0.118117 0.0102733 -0.0197583 0.0182373 -0.0595545 -0.0467462 -0.0528645 0.0386661 0.222398 -0.00462176 -0.0749823 0.207324 0.02384 -0.0242014 0.0872049 0.0496973 0.0073562 -0.0334233 -0.157541 0.0342626 -0.0506163 -0.199644 0.0226653 0.0700061 -0.228765 0.162332 -0.00795656 -0.054744 0.0033665 0.0153879 -0.119359 0.00656874 0.196424 -0.368868 0.289858 0.238483 0.129638 0.144729 0.0572777 0.0434036 0.0245095 -0.0430119 -0.127455 -0.115466 0.0321838 0.0248377 0.0170342 0.0841654";

  Mat matSearch = db->stringToMat(matStr);

  int result = db->getNameByBiometricData(matSearch, name);

  cout << "The result is: " << result << " and the name is: " << name << endl;
  ```

> Get the biometric data of a person based on its ID

- Return the corresponding Mat to the given ID. It returns a Mat of 0 rows if there is no record of that ID or the ID has no a descriptor vector.

  ```
  Mat mymat;

  int result = db->getMatById("A01159981", mymat);

  cout << "The result is: " << result << " and the Mat is: " << endl << mymat << endl;
  ```

> Get the person's name based on its ID

- Returns the corresponding name to the given ID. It return the name "NULL" if there is no record of that ID.

  ```
  string name;

  int result = db->getNameById("A01159981", name);
  cout << "The result is: " << result << " and the name is: " << name << endl;
  ```

> Get the ID of a person based on its Biometric data

```

string vectStr = "-0.0616511 0.0475776 0.0362354 -0.00242895 -0.112268 0.0606102 0.00753146 -0.0637529 0.106891 -0.0187525 0.234492 -0.0159751 -0.307106 -0.043978 -0.0115506 0.111364 -0.0745489 -0.158511 -0.101033 0.00115909 -0.0506868 -0.00411913 0.0347568 0.0161157 -0.114755 -0.343202 -0.0764834 -0.0734758 -0.0221774 -0.107824 -0.0256894 0.0826778 -0.178726 -0.0932796 0.0919714 0.059551 -0.110057 -0.0537951 0.236683 0.0418406 -0.149338 0.0509383 0.0202544 0.31261 0.105552 0.00383814 0.0733314 -0.0827081 0.0150385 -0.306268 0.116218 0.178675 0.132616 0.102245 0.0139852 -0.156941 0.0219384 0.172704 -0.197279 0.172844 0.0878312 -0.0951407 -0.0269293 -0.0737721 0.184078 0.114524 -0.106078 -0.156875 0.152411 -0.0966852 -0.0578988 0.0594064 -0.128421 -0.253084 -0.259731 0.0860366 0.365467 0.172306 -0.193488 -0.0112439 -0.118117 0.0102733 -0.0197583 0.0182373 -0.0595545 -0.0467462 -0.0528645 0.0386661 0.222398 -0.00462176 -0.0749823 0.207324 0.02384 -0.0242014 0.0872049 0.0496973 0.0073562 -0.0334233 -0.157541 0.0342626 -0.0506163 -0.199644 0.0226653 0.0700061 -0.228765 0.162332 -0.00795656 -0.054744 0.0033665 0.0153879 -0.119359 0.00656874 0.196424 -0.368868 0.289858 0.238483 0.129638 0.144729 0.0572777 0.0434036 0.0245095 -0.0430119 -0.127455 -0.115466 0.0321838 0.0248377 0.0170342 0.0841654";

Mat theMat = db->stringToMat(vectStr);

string theID;

int result = getIdByBioData(theMat, theID);

cout << "The ID is: " <<  theId << endl;

```

> Get the description vector of the people most alike to someone

- Prints and return a matrix of Mat's of n rows. That matrix has the descriptor of the n people most alike to the given descriptor .In this example n = numKnn = 4.

  ```
  string vectStr = "-0.0616511 0.0475776 0.0362354 -0.00242895 -0.112268 0.0606102 0.00753146 -0.0637529 0.106891 -0.0187525 0.234492 -0.0159751 -0.307106 -0.043978 -0.0115506 0.111364 -0.0745489 -0.158511 -0.101033 0.00115909 -0.0506868 -0.00411913 0.0347568 0.0161157 -0.114755 -0.343202 -0.0764834 -0.0734758 -0.0221774 -0.107824 -0.0256894 0.0826778 -0.178726 -0.0932796 0.0919714 0.059551 -0.110057 -0.0537951 0.236683 0.0418406 -0.149338 0.0509383 0.0202544 0.31261 0.105552 0.00383814 0.0733314 -0.0827081 0.0150385 -0.306268 0.116218 0.178675 0.132616 0.102245 0.0139852 -0.156941 0.0219384 0.172704 -0.197279 0.172844 0.0878312 -0.0951407 -0.0269293 -0.0737721 0.184078 0.114524 -0.106078 -0.156875 0.152411 -0.0966852 -0.0578988 0.0594064 -0.128421 -0.253084 -0.259731 0.0860366 0.365467 0.172306 -0.193488 -0.0112439 -0.118117 0.0102733 -0.0197583 0.0182373 -0.0595545 -0.0467462 -0.0528645 0.0386661 0.222398 -0.00462176 -0.0749823 0.207324 0.02384 -0.0242014 0.0872049 0.0496973 0.0073562 -0.0334233 -0.157541 0.0342626 -0.0506163 -0.199644 0.0226653 0.0700061 -0.228765 0.162332 -0.00795656 -0.054744 0.0033665 0.0153879 -0.119359 0.00656874 0.196424 -0.368868 0.289858 0.238483 0.129638 0.144729 0.0572777 0.0434036 0.0245095 -0.0430119 -0.127455 -0.115466 0.0321838 0.0248377 0.0170342 0.0841654";

  Mat matSearch = db->stringToMat(vectStr);

  vector<Mat> topMatches;

  vector<string> topNames;

  vector<string> topMatchesId;

  int numKnn = 4;

  result = db->searchPerson(matSearch, numKnn, topMatches, topNames,topMatchesId);

  //Print the people
  for (int i = 0; i < numKnn; i++)
  {
    cout << "Person #" << (i + 1) << endl;
    cout << "Mat: " << endl  << topMatches[i] << endl;
    cout << "ID: " << topMatchesId[i] << endl;
    cout << "Name: " << topNames[i] << endl << endl;
  }
  ```

> Print the data base

- Prints the whole data base with all the atributes. It's only recommendable if the data base is short.

  ```
  db->printDB();
  ```
