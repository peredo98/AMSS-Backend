#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;
#include <string.h>
#include <bits/stdc++.h>
#include <ctype.h>

int validar_matricula(char[100]);
int validar_apellido(char[100]);
int validar_sexo(char[100]);
int validar_edad(char[100]);
int validar_nombre(char[100]);

main()
{
    int sw = 0;
    char edad[100], nombre[100], matricula[100], apellido[100], sexo[100];

    fflush(stdin);
    printf("Ingrese Nombre: ");
    gets(nombre);
    sw = validar_nombre(nombre);
    if (sw == 0)
    {
        printf("Nombre Valido\n");
    }
    else
    {
        printf("Nombre Invalido\n");
    }
    printf("\n");
    fflush(stdin);
    printf("Ingrese la edad: ");
    gets(edad);
    sw = validar_edad(edad);
    if (sw == 0)
    {
        printf("edad Valido");
    }
    else
    {
        printf("edad invalido");
    }
    printf("\n");

    fflush(stdin);
    printf("Ingrese Apellido: ");
    gets(apellido);
    sw = validar_apellido(apellido);
    if (sw == 0)
    {
        printf("apellido Valido\n");
    }
    else
    {
        printf("apellido Invalido\n");
    }
    printf("\n");

    fflush(stdin);
    printf("Ingrese su matricula exluyendo la A: ");
    gets(matricula);
    sw = validar_matricula(matricula);
    if (sw == 0)
    {
        printf("matricula Valido");
    }
    else
    {
        printf("matricula invalido");
    }
    printf("\n");

    fflush(stdin);
    printf("El sexo, Male para hombre y Female para mujer: ");
    gets(sexo);
    sw = validar_sexo(sexo);
    if (sw == 0)
    {
        printf("sexo Valido\n");
    }
    else
    {
        printf("sexo Invalido\n");
    }
    printf("\n");

} //main

int validar_edad(char edad[100])
{
    int i = 0, sw = 0, j;
    j = strlen(edad);
    while (i < j && sw == 0)
    {
        if (isdigit(edad[i]) != 0)
        {
            i++;
        }
        else
        {
            sw = 1;
        }
    }
    return sw;
}
int validar_matricula(char matricula[100])
{
    int i = 0, sw = 0, j;
    j = strlen(matricula);
    while (i < j && sw == 0)
    {
        if (isdigit(matricula[i]) != 0)
        {
            i++;
        }
        else
        {
            sw = 1;
        }
    }
    return sw;
}
int validar_nombre(char nombre[100])
{
    int i = 0, sw = 0, j;
    j = strlen(nombre);
    while (i < j && sw == 0)
    {
        if (isalpha(nombre[i]) != 0)
        {
            i++;
        }
        else
        {
            sw = 1;
        }
    }
    return sw;
}
int validar_sexo(char sexo[100])
{
    int i = 0, sw = 0, j;
    j = strlen(sexo);
    while (i < j && sw == 0)
    {
        if (isalpha(sexo[i]) != 0)
        {
            i++;
        }
        else
        {
            sw = 1;
        }
    }
    return sw;
}

int validar_apellido(char apellido[100])
{
    int i = 0, sw = 0, j;
    j = strlen(apellido);
    while (i < j && sw == 0)
    {
        if (isalpha(apellido[i]) != 0)
        {
            i++;
        }
        else
        {
            sw = 1;
        }
    }
    return sw;
}

// Crate Person createPerson(name, lastName, studentId, age, gender) eg:
//db.createPerson("Ruben", "Salazar", "A01234567", 21, "Male");

// Create Person with imageURL createPerson(name, lastName, studentId, age, gender, imageURL) eg:
//db.createPerson("Ruben", "Salazar", "A01234567", 21, "Male", "A01234567.png");

// Create Person with biometrics createPerson(name, lastName, studentId, age, gender, biometricData) eg:
//vector<vector<int>> biometrics{ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } }; ;
//db.createPerson("Ruben", "Salazar", "A01234567", 21, "Male", biometrics);

// Create Person with imageURL and BiometricData createPerson(name, lastName, studentId, age, gender, imageURL, biometricData) eg:
//vector<vector<int>> biometrics{ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } }; ;
//db.createPerson("Ruben", "Salazar", "A01234567", 21, "Male", "A01234567.png", biometrics);

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
/*
    Mat image;
    image = imread( "./../img/sample.jpeg", 1 );
    */

//Save image (the image will be saved with .png extension)
