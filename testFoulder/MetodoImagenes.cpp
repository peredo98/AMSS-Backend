# include <stdlib.h>
# include <string.h>
# include <fstream>
using namespace std;
/*
No se en donde va el 
Mat image; lo pongo dentro del while?
*/
int main(){
   const string Matriculas= "Matriculas.txt";// mandar traer el archivo
   char matricula[10];// char de cada matricula
   int i=0;//el contador hasta 100k para los sample de la imagen
   char ruta[30];// char de la ruta
   ifstream fichero;
   fichero.open(Matriculas.c_str());
   if (!fichero.fail()){
   while (!fichero.eof()){
       //tengo un pedo en como crear el char de la ruta
       image=imread()// aquí debería de crear esta línea image = imread("./../img/sample.jpeg", 1);

       db.saveImage(image, matricula);// esto es igual a esto db.saveImage(image, "A01024592");
       fichero.getline(matricula, 10, '\n');
   }
   fichero.close();
   }
}


