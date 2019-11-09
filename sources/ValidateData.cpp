#include "./../headers/ValidateData.h"

using namespace std;

ValidateData::ValidateData(){}

bool ValidateData::validate_all(string name, string lastname, string id, string gender)
{
    try
    {
        cout << "Name: " << endl;
        validar_nombre(name);

        cout << "Lastname: " << endl;
        validar_nombre(lastname);

        cout << "ID: " << endl;
        validar_matricula(id);

        cout << "Gender: " << endl;
        validar_sexo(gender);
    }
    catch (const char *msg)
    {
        cout << msg << endl;
        return false;
    }
    catch (const std::string &my_msg)
    {
        cout << my_msg << endl;
        return false;
    }
    return true;
}

//Validates that the id has the correct format A0-
bool ValidateData::validar_matricula(string matricula)
{
    int j = matricula.length();
    if (j == 9) //Validate that the id has exactly 9 characters including the A0
    {
        for (int i = 0; i < j; i++)
        {
            if (i == 0) //Check if the first position is an 'A'.
            {
                int validA = isalpha(matricula.at(0));
                if (validA != 0)
                {
                    char a = matricula.at(0);
                    if (a != 'A' && a != 'a')
                    {
                        throw "The id starts with a different letter than 'A' or 'a'.";
                    }
                }
                else
                {
                    throw "The id does not start with an alphabetic character.";
                }
            }
            else //Check if the following data is all digit.
            {
                if (isdigit(matricula.at(i)) == 0)
                {
                    string error = "The id at the position " + std::to_string(i + 1) + " is not a digit.";
                    throw error;
                }
            }
        }
        cout << " --Correct" << endl
             << endl;
        return true;
    }
    throw "The ID does not have the correct length of 8 characters.";
}

//Validate both the name and lastname of a person
int ValidateData::validar_nombre(string nombre)
{
    int j = nombre.length();
    for (int i = 0; i < j; i++)
    {
        if (isalpha(nombre.at(i)) == 0)
        {
            string error = "The " + std::to_string(i + 1) + " position is not an alphabetich character.";
            throw error;
        }
    }
    cout << " --Correct" << endl
         << endl;
    return true;
}

//Validates that the sex is either male or female
bool ValidateData::validar_sexo(string sexo)
{
    transform(sexo.begin(), sexo.end(), sexo.begin(), ::tolower);
    if (sexo != "male" && sexo != "female")
    {
        throw "The gender is not correct.";
    }
    cout << " --Correct" << endl
         << endl;
    return true;
}