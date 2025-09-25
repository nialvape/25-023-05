#include iostream 
#include fstream
#include "rwstring.hpp"
#include "listas.hpp"
using namespace std;

struct Product {
    string sku;
    string desc;
    float costoF = 0;};

struct Repa {
    string cliente;
    int tipoP; // puede ser 0,1,2
    string sku;
    float Cost = 0;
    float presup = 0;};

int main(){

 //Ejercicio 2
 ifstream archiprod; 
 archiprod.open("productos.bin", ios::binary);

    
 archiprod.close();

 ifstream archirep; 
 archirep.open("reparaciones.bin", ios::binary);



 archirep.close();

}
