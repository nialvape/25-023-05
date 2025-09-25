#include iostream 
#include fstream
#include "rwstring.hpp"
#include "listas.hpp"
using namespace std;

const int dimprod = 10;
const int dimsku = 10;
const int dimdesc = 20;
const int dimcostF = 4;
const int dimclie = 15;
const int dimtipoP = 3; 
const int dimCost= 4;
const int dimpresup= 4;

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

ifstream& operator>>(ifstream &fs, Product &p) {
    p.sku  = readstring(fs, dimsku);
    p.desc = readstring(fs, dimdesc);
    fs.read(reinterpret_cast<char *>(&p.costoF), sizeof(dimcostF));
    return fs;
}

ifstream& operator>>(ifstream &fs, Repa &r) {
    r.cliente = readstring(fs, dimclie);
    fs.read(reinterpret_cast<char *>(&r.tipoP), sizeof(dimtipoP));
    r.sku = readstring(fs, dimsku);
    fs.read(reinterpret_cast<char *>(&r.Cost), sizeof(dimCost));
    fs.read(reinterpret_cast<char *>(&r.presup), sizeof(dimpresup));
    return fs;
}

int main(){
 int dim rep=0;
 Product prod [dimprod];
 Repa rep [dim];

 //Ejercicio 2
 ifstream archiprod; 
 archiprod.open("productos.bin", ios::binary);   
     for (int i = 0; i < 10; i++) {
        archiprod >> prod [i];         // usa el operador >> que creaste
    }
 archiprod.close();

 ifstream archirep; 
 archirep.open("reparaciones.bin", ios::binary);

    if(archirep>>) {
        dim++;
    }



 archirep.close();

}
