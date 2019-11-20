#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include <cstring>
#include <cstdio>
#include <cctype>

class ValidateData
{
public:
    ValidateData();

    bool validate_all(std::string name, std::string lastname, std::string id, std::string gender);

    //Validates that the id has the correct format A0-
    bool validar_matricula(std::string matricula);

    //Validate both the name and lastname of a person
    int validar_nombre(std::string nombre);

    //Validates that the sex is either male or female
    bool validar_sexo(std::string sexo);
};