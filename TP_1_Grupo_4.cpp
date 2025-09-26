#include <iostream>
#include <fstream>
#include "rwstring.hpp"
using namespace std;

const int dimprod = 10;
const int dimsku = 10;
const int dimdesc = 20;
const int dimcostF = 4;
const int dimclie = 15;
const int dimtipoP = 3; 
const int dimCost= 4;
const int dimpresup= 4;
const int dimtp=3;

const string FIN= "EOF";

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

ifstream & operator>>(ifstream  &fs, Product &p) {
    p.sku  = readstring(fs, dimsku);
    p.desc = readstring(fs, dimdesc);
    fs.read(reinterpret_cast<char *>(&p.costoF), sizeof(float));
    return fs;
}

ifstream & operator>>(ifstream  &fs, Repa &r) {
    r.cliente = readstring(fs, dimclie);
    fs.read(reinterpret_cast<char *>(&r.tipoP), sizeof(int));
    r.sku = readstring(fs, dimsku);
    fs.read(reinterpret_cast<char *>(&r.Cost), sizeof(float));
    fs.read(reinterpret_cast<char *>(&r.presup), sizeof(float));
    return fs;
}

bool criterio(const Repa &a, const Repa &b) {
    if (a.cliente != b.cliente) {
        return a.cliente < b.cliente; 
    }
    if (a.tipoP != b.tipoP) {
        return a.tipoP < b.tipoP;  
    }
    return a.sku < b.sku;  
}

template <typename T>
void ordenar(T rep[], int dimrep, bool (*criterio)(const T&, const T&)) {
    bool desordenado = true;
    for (int i = 1; i < dimrep && desordenado; i++) {
        desordenado = false;
        for (int j = 0; j < dimrep - i; j++) {
            if (criterio(rep[j + 1], rep[j])) {
                T aux = rep[j];
                rep[j] = rep[j + 1];
                rep[j + 1] = aux;
                desordenado = true;}
        } } }

int buscar_linea_ord(string clave, Repa rep[], int dimrep){
    int i;
    for (i=0; i<dimrep && rep[i].cliente != clave; i++);
    return(i<dimrep && rep[i].cliente == clave)?i:-1;
}

int buscar_linea_ord2(string aux, Product prod []){
    int i;
    for (i=0; i<dimprod && prod[i].sku != aux; i++);
    return(i<dimprod && prod[i].sku == aux)?i:-1;
}

ostream& operator <<(ostream& os, const Repa& a) {
    string tp [dimtp] {"Electronico", "Mecanico", "Mecatronico"};
    os << "Cliente: "<<a.cliente<<", Tipo de product:"<< tp[a.tipoP]
       <<", SKU: "<< a.sku<<", costo:"<<a.Cost<<", Presupuesto:"<<a.presup;
    return os;
}
ostream& operator <<(ostream& os, const Product& a) {
    os <<"Descripción:"<< a.desc
       <<", Costo Final: "<< a.costoF;
    return os;
}

void Cliente (Repa rep[], int dimrep, Product prod []){ 
    string clave;
    cout << "Ingresar el nombre del Cliente: ";
    cin >> clave;
    if(clave == FIN)
        return;

    int iclien = buscar_linea_ord (clave, rep, dimrep);
    if (iclien==-1){
        cout<<"Cliente no encontrado"<<endl;
        return Cliente (rep, dimrep, prod);;
    } //ejercicio 5
    
    float CostoFijo =0, CostoDirecto=0, Presupuesto=0; 
    while(rep[iclien].cliente==clave){ 
        //Ejercicio 3
        cout<<rep[iclien];
        string aux= rep[iclien].sku;
        int isku= buscar_linea_ord2(aux, prod);
        cout<<prod[isku];

        //Ejercicio 4
        CostoFijo+= prod[isku].costoF;
        CostoDirecto+= rep[iclien].Cost;
        Presupuesto+= rep[iclien].presup;

        iclien++;
    }
    cout<<"La ganancia total de una reparación es de "<<Presupuesto - CostoFijo + CostoDirecto <<"$"<<endl;
     return Cliente (rep, dimrep, prod);}


int main(){
 int dimrep=16;
 Product prod [dimprod];
 Repa rep [dimrep];


 //Ejercicio 2
 ifstream archiprod; 
 archiprod.open("productos.bin", ios::binary);   
     for (int i = 0; i < dimprod; i++) {
        archiprod >> prod [i];   
    }
 archiprod.close();

 ifstream archirep; 
 archirep.open("reparaciones.bin", ios::binary);
    for (int i = 0; i < dimrep; i++) {
        archirep >> rep [i];
    }
 archirep.close();

 ordenar(rep, dimrep,*criterio);
Cliente (rep, dimrep, prod);

 return 0;
}
