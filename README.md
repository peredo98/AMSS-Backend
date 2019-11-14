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
  vector<float> vtest =  {0.0686191, 0.102089, -0.00105337, -0.0144187, -0.113577, 0.11341, -0.00906423, -0.0431836, 0.117796, -0.0361874, 0.2743, -0.0159567, -0.304417, -0.0618783, 0.0312915, 0.0929223, -0.106628, -0.125286, -0.0993145, 0.0348979, -0.0563836, 0.00096218, 0.0368185, 0.0305798, -0.143035, -0.365484, -0.0746458, -0.057839, 0.0131048, -0.103785, -0.0564006, 0.0926407, -0.141517, -0.0807013, 0.0649695, 0.0435849, -0.104015, -0.0415971, 0.252735, 0.0421941, -0.172736, 0.0481856, 0.018572, 0.314911, 0.140714, -0.0160041, 0.0827845, -0.0748115, 0.0241836, -0.284979, 0.109694, 0.196652, 0.149352, 0.0793323, -0.0042334, -0.135595, -0.0263065, 0.150851, -0.181326, 0.140949, 0.0696108, -0.101495, -0.0218032, -0.0794853, 0.147624, 0.111091, -0.0873384, -0.203681, 0.165975, -0.107077, -0.0794623, 0.0857135, -0.132143, -0.265836, -0.268982, 0.095123, 0.358186, 0.176736, -0.17145, 0.0196853, -0.105849, -0.0732479, -0.0305209, 0.048035, -0.0501492, -0.0846746, -0.0453903, 0.0513115, 0.259576, -0.027062, -0.0654939, 0.194835, 0.0525291, -0.0260576, 0.0944489, 0.0588643, 0.00694044, -0.00896938, -0.149756, 0.0563699, -0.0511785, -0.224327, 0.011867, 0.069841, -0.244067, 0.198618, 0.020369, -0.0680785, 0.0363366, 0.0194272, -0.123889, -0.00884694, 0.218093, -0.362971, 0.254226, 0.222162, 0.159384, 0.156957, 0.0816286, 0.0715054, 0.0502839, -0.0143791, -0.129323, -0.133592, 0.030814, 0.00817115, 0.0134029, 0.082819};
  Mat mymat = db->vectorToMat(1, vtest.size(), vtest);
  db->createPerson("Nancy", "Medina", "A01330291", 20, "Female", mymat);
  ```

  ```
  string matStr =  "0.0686191, 0.102089, -0.00105337, -0.0144187, -0.113577, 0.11341, -0.00906423, -0.0431836, 0.117796, -0.0361874, 0.2743, -0.0159567, -0.304417, -0.0618783, 0.0312915, 0.0929223, -0.106628, -0.125286, -0.0993145, 0.0348979, -0.0563836, 0.00096218, 0.0368185, 0.0305798, -0.143035, -0.365484, -0.0746458, -0.057839, 0.0131048, -0.103785, -0.0564006, 0.0926407, -0.141517, -0.0807013, 0.0649695, 0.0435849, -0.104015, -0.0415971, 0.252735, 0.0421941, -0.172736, 0.0481856, 0.018572, 0.314911, 0.140714, -0.0160041, 0.0827845, -0.0748115, 0.0241836, -0.284979, 0.109694, 0.196652, 0.149352, 0.0793323, -0.0042334, -0.135595, -0.0263065, 0.150851, -0.181326, 0.140949, 0.0696108, -0.101495, -0.0218032, -0.0794853, 0.147624, 0.111091, -0.0873384, -0.203681, 0.165975, -0.107077, -0.0794623, 0.0857135, -0.132143, -0.265836, -0.268982, 0.095123, 0.358186, 0.176736, -0.17145, 0.0196853, -0.105849, -0.0732479, -0.0305209, 0.048035, -0.0501492, -0.0846746, -0.0453903, 0.0513115, 0.259576, -0.027062, -0.0654939, 0.194835, 0.0525291, -0.0260576, 0.0944489, 0.0588643, 0.00694044, -0.00896938, -0.149756, 0.0563699, -0.0511785, -0.224327, 0.011867, 0.069841, -0.244067, 0.198618, 0.020369, -0.0680785, 0.0363366, 0.0194272, -0.123889, -0.00884694, 0.218093, -0.362971, 0.254226, 0.222162, 0.159384, 0.156957, 0.0816286, 0.0715054, 0.0502839, -0.0143791, -0.129323, -0.133592, 0.030814, 0.00817115, 0.0134029, 0.082819";
  Mat mymat = db->stringToMat(matStr);
  db->createPerson("Nancy", "Medina", "A01330291", 20, "Female", mymat);
  ```

> Delete a person related to an ID

```
db->deletePersonById("A01234567");
```

> Get a person's name related to its description vector on vector<float> format

- Returns the corresponding name in string format to the given vector. It return the string "NULL" if there is no record of the given vector

  ```
  vector<float> vSearch = {-0.077756, 0.192846, 0.0550688, -0.168125, -0.182494};
  string name = db->getPersonByBiometricData(vSearch);
  if(name != "NULL"){
      cout << "The person's name is: " << name << endl;
  }
  ```

> Get a person's name related to its description vector on Mat format

- Returns the corresponding name in string format to the given Mat. It return the string "NULL" if there is no record of the given Mat

  ```
  vector<float> vSearch = {-0.0576136, 0.171748, 0.0571629, -0.152391, -0.166514};
  Mat matSearch = db->vectorToMat(1, vSearch.size() ,vSearch);
  string name = db->getPersonByBiometricData(matSearch);
  if(name != "NULL"){
      cout << "The person's name is: " << name << endl;
  }
  ```

> Get the biometric data of a person based on its ID

- Return the corresponding Mat to the given ID. It returns a Mat of 0 rows if there is no record of that ID or the ID has no a descriptor vector.

  ```
  Mat mymat = db->getMatById("A01025599");
  if(mymat.rows != 0){
      cout << "The mat of the person you look for is: " << mymat << endl;
  }
  ```

> Get the person's name based on its ID

- Returns the corresponding name to the given ID. It return the name "NULL" if there is no record of that ID.

  ```
  string name = db->getNameById("A01024192");
  if(name != "NULL"){
      cout << "The person's name is: " << name << endl;
  }
  ```

> Get the description vector of the four persons most alike to someone

- Prints and return a matrix of Mat's of n rows. That matrix has the descriptor of the n people most alike to the given descriptor .In this example n=4.
  ```
  vector<float> vSearch = {-0.076754, 0.0851077, 0.00011571, -0.072535, -0.114122};
  Mat matSearch = db->vectorToMat(1, vSearch.size(), vSearch);
  Mat nearestNeighbors = db->searchPerson(matSearch, 4);
  ```

> Print the data base

- Prints the whole data base with all the atributes. It's only recommendable if the data base is short.

  ```
  db->printDB();
  ```
