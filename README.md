# TEAM 4 - DATABASE

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

# Tests

To test the proyect, first compile it and then run it. Depending of the OS you have, the process will be different.

- **MAC OS**

  Open your terminal in the `sources` foulder and run the following command to run.

  > g++ --std=c++11 test.cpp -o test \$(pkg-config --cflags --libs libmongocxx opencv4)

  In the same root run the following command to test the project.

  > ./test

* **Windows**
