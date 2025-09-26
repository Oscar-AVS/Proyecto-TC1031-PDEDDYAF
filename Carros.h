// Carros.h
// Creaod por Oscar Alexander Vilchis SOto A01713207
// Ultima modificación 26/09/2025
// Se crea la clase Carros.h en donde se realizan operaciones de busqueda y ordenamiento mediante el método de Merge Sort 
#ifndef CARROS_H
#define CARROS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

// Estructura que define cómo están acomodados los datos en el archivo de texto inventario.txt
struct Carro {
    std::string marca, modelo, tipo, motor;
    int anio = 0;
};

// Clase carros.h gestiona una colección de Carro y realiza operaciones sobre ella
class Carros {
    std::vector<Carro> v;

    static std::string trim(const std::string& s){ // función que sirve para quitar espacios al inicio y al final
        size_t i = s.find_first_not_of(" \t\r\n"); // función que permite encontrar el primr caracter
        if (i == std::string::npos) return "";
        size_t j = s.find_last_not_of(" \t\r\n");
        return s.substr(i, j - i + 1);
    }

    // Se implementa un algoritmo de busqueda de tipo Merge Sort, ordena el vector "a" comparandolo
    template<class T, class Comp>
    void mergeSort(std::vector<T>& a, Comp comp){
        if (a.size() < 2) return;
        std::vector<T> tmp(a.size());
        sortRec(a, tmp, 0, (int)a.size()-1, comp);
    }
// parte recursiva de la busqueda merge sort, se separan los elementos para después ordenar
// primero el izquierdo y luego el derecho y al finalizar se comparan los elementos de cada mitad
    template<class T, class Comp>
    void sortRec(std::vector<T>& a, std::vector<T>& tmp, int l, int r, Comp comp){
        if (l >= r) return;
        int m = (l + r) / 2;
        sortRec(a, tmp, l, m, comp);
        sortRec(a, tmp, m+1, r, comp);
        int i=l, j=m+1, k=l;
        while (i<=m && j<=r) tmp[k++] = comp(a[i],a[j]) ? a[i++] : a[j++];
        while (i<=m) tmp[k++] = a[i++];
        while (j<=r) tmp[k++] = a[j++];
        for (int t=l; t<=r; ++t) a[t] = tmp[t];
    }

public:
//Metodo para cargar los elementos CSV (valores separados por comas)  abre el archivo en modo lectura y verifica si es legible
    bool cargarCSV(const std::string& ruta){
        std::ifstream in(ruta);
        if (!in.is_open()){
            std::cout << "No es posible leer : " << ruta << "\n";
            return false;
        }
        std::string linea;
        if (!std::getline(in, linea)) return true; // archivo vacío (o solo encabezado)
        while (std::getline(in, linea)){
            if (linea.empty()) continue;
            std::stringstream ss(linea);
            std::string marca, modelo, tipo, anioS, motor;
            std::getline(ss, marca, ',');
            std::getline(ss, modelo, ',');
            std::getline(ss, tipo, ',');
            std::getline(ss, anioS, ',');
            std::getline(ss, motor, ',');
            Carro c;
            c.marca  = trim(marca);
            c.modelo = trim(modelo);
            c.tipo   = trim(tipo);
            c.motor  = trim(motor);
            c.anio   = anioS.empty()?0:std::stoi(trim(anioS));
            v.push_back(c);
        }
        return true;
    }

    void agregar(const Carro& c){ v.push_back(c); }
    size_t size() const { return v.size(); }

    void ordenarPorMarcaAZ(){
        mergeSort(v, [](const Carro& a, const Carro& b){
            if (a.marca != b.marca) return a.marca < b.marca;
            return a.modelo < b.modelo;
        });
        std::cout << "Ordenado por marca (A-Z).\n";
    }

    void ordenarPorAnioAsc(){
        mergeSort(v, [](const Carro& a, const Carro& b){
            return a.anio < b.anio;
        });
        std::cout << "Ordenado por a~no\n";
    }

    void mostrar() const {
        if (v.empty()){
            std::cout << "(Inventario vacio)\n";
            return;
        }
        int i=1;
        for (const auto& c : v){
            std::cout << i++ << ". " << c.marca << " " << c.modelo
                      << " | " << c.tipo << " | " << c.anio
                      << " | " << c.motor << "\n";
        }
    }

    void seleccionarYConfirmarAnio() {
        if (v.empty()){
            std::cout << "Inventario vacio.\n";
            return;
        }
        size_t idx;
        std::cout << "Selecciona un numero (1.." << v.size() << "): ";
        if (!(std::cin >> idx) || idx<1 || idx>v.size()){
            std::cout << "Indice invalido.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        Carro &c = v[idx-1];
        std::cout << "Acabas d elegir : " << c.marca << " " << c.modelo
                  << " (" << c.anio << ")\n";
        std::cout << "¿Ese es el an~o de tu vehiculo? (si/no): ";
        char r; std::cin >> r;
        if (r=='n' || r=='N'){
            std::cout << "Ingresa el an~o de tu vehiculo: ";
            int a;
            if (std::cin >> a){
                c.anio = a;
                std::cout << "Actualizado: " << c.marca << " " << c.modelo
                          << " (" << c.anio << ")\n";
            } else {
                std::cout << "error .\n";
                std::cin.clear();
            }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

// FUnción que permite buscar al usuario vehículos por marca 
void buscarPorMarca(const std::string& marcaBuscada) const {
        bool encontrado = false;
        for (const auto& c : v){
            if (c.marca == marcaBuscada){
                std::cout << c.marca << " " << c.modelo
                          << " | " << c.tipo
                          << " | " << c.anio
                          << " | " << c.motor << "\n";
                encontrado = true;
            }
        }
        if (!encontrado){
            std::cout << "No se encontraron autos de marca: " << marcaBuscada << "\n";
        }
    }
};

#endif // CARROS_H
