// Carros.h
// Creaod por Oscar Alexander Vilchis SOto A01713207
// Ultima modificación 26/09/2025
// Se crea la clase Carros.h en donde se realizan operaciones de busqueda y ordenamiento mediante el metodo de Merge Sort (26/09/2025)
//  Se modifica la clase carros.h para sustituir ek  uso de vector<Carro> por una lista doblemente ligada implementada manualmente
//(estructuras Nodo y punteros head/tail)
// De igual manera Se adaptaron las funciones de ordenamiento y se añadieron nuevas funciones de filtrado (24/10/2025)
#ifndef CARROS_H
#define CARROS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

// Estructura Carro  representa los datos básicos de cada vehículo
struct Carro {
    std::string marca, modelo, tipo, motor;
    int anio = 0;
};


// Lista doblemente ligada
// Contiene un objeto Carro y apuntadores al nodo anterior y siguiente
struct Nodo {
    Carro data;
    Nodo* next;
    Nodo* prev;
    explicit Nodo(const Carro& c) : data(c), next(nullptr), prev(nullptr) {}
};

class Carros {
    Nodo* head = nullptr;
    Nodo* tail = nullptr;
    size_t n = 0;

    static std::string trim(const std::string& s){// función que sirve para quitar espacios al inicio y al final
        const char* ws = " \t\r\n"; // función que permite encontrar el primr caracter
        size_t i = s.find_first_not_of(ws);
        if (i == std::string::npos) return "";
        size_t j = s.find_last_not_of(ws);
        return s.substr(i, j - i + 1);
    }

    Nodo* nodoEnPos(size_t idx) const {
        if (idx < 1 || idx > n) return nullptr;
        // elige lado más cercano
        if (idx <= n/2) {
            Nodo* cur = head;
            for (size_t i=1; i<idx; ++i) cur = cur->next;
            return cur;
        } else {
            Nodo* cur = tail;
            for (size_t i=n; i>idx; --i) cur = cur->prev;
            return cur;
        }
    }

    // Merge Sort sobre lista
    template<class Comp>
    static void splitMitad(Nodo* src, Nodo*& a, Nodo*& b){
        Nodo* slow = src;
        Nodo* fast = src->next;
        while (fast){
            fast = fast->next;
            if (fast){
                slow = slow->next;
                fast = fast->next;
            }
        }
        a = src;
        b = slow->next;
        slow->next = nullptr;
        if (b) b->prev = nullptr;
        if (a) a->prev = nullptr;
    }

    template<class Comp>
    static Nodo* mergeOrdenado(Nodo* a, Nodo* b, Comp comp){
        if (!a) return b;
        if (!b) return a;
        // comp(x,y) == true si x debe ir antes que y
        if (comp(a->data, b->data)){
            a->next = mergeOrdenado<Comp>(a->next, b, comp);
            if (a->next) a->next->prev = a;
            a->prev = nullptr;
            return a;
        } else {
            b->next = mergeOrdenado<Comp>(a, b->next, comp);
            if (b->next) b->next->prev = b;
            b->prev = nullptr;
            return b;
        }
    }
    // Llamada recursiva del Merge Sort sobre listas
    template<class Comp>
    static void mergeSortRec(Nodo*& headRef, Comp comp){
        if (!headRef || !headRef->next) return;
        Nodo *a=nullptr, *b=nullptr;
        splitMitad<Comp>(headRef, a, b);
        mergeSortRec<Comp>(a, comp);
        mergeSortRec<Comp>(b, comp);
        headRef = mergeOrdenado<Comp>(a, b, comp);
    }

    void recomputarTail(){
        tail = head;
        if (!tail) return;
        while (tail->next) tail = tail->next;
    }

public:
    // Constructor y destructor para  inicializar y liberar memoria

    Carros() = default;
    ~Carros(){
        Nodo* cur = head;
        while (cur){
            Nodo* nx = cur->next;
            delete cur;
            cur = nx;
        }
    }

    size_t size() const { return n; }
    bool empty() const { return n == 0; }

    // Cargar CSV (ruta relativa)
    bool cargarCSV(const std::string& rutaRelativa){
        std::ifstream in(rutaRelativa);
        if (!in.is_open()){
            std::cout << "No se pudo abrir el archivo: " << rutaRelativa << "\n";
            return false;
        }
        std::string linea;
        // lee encabezado (si existe)
        std::getline(in, linea);
        size_t cargados = 0;
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
            agregar(c);
            ++cargados;
        }
        std::cout << "Registros cargados: " << cargados << "\n";
        return true;
    }
    // Agrega nuevo carro  al final (O(1))
    void agregar(const Carro& c){
        Nodo* nuevo = new Nodo(c);
        if (!head){
            head = tail = nuevo;
        } else {
            tail->next = nuevo;
            nuevo->prev = tail;
            tail = nuevo;
        }
        ++n;
    }

    // Mostrar lista de inventario completo
    void mostrar() const {
        if (empty()){
            std::cout << "(Inventario vacio)\n";
            return;
        }
        size_t i=1;
        for (Nodo* cur=head; cur; cur=cur->next){
            std::cout << i++ << ") " << cur->data.marca << " " << cur->data.modelo
                      << " | " << cur->data.tipo
                      << " | " << cur->data.anio
                      << " | " << cur->data.motor << "\n";
        }
    }

    // Ordenar por marca (A-Z) que utiliza Merge Sort con complejidad O(n log n)

    void ordenarPorMarcaAZ(){
        mergeSortRec(head, [](const Carro& a, const Carro& b){
            if (a.marca != b.marca) return a.marca < b.marca;
            return a.modelo < b.modelo;
        });
        recomputarTail();
        std::cout << "Ordenado por marca (A-Z).\n";
    }

    // Ordenar por año (ascendente) también con complejidad O(n log n)
    void ordenarPorAnioAsc(){
        mergeSortRec(head, [](const Carro& a, const Carro& b){
            return a.anio < b.anio;
        });
        recomputarTail();
        std::cout << "Ordenado por año (ascendente).\n";
    }


    void seleccionarYConfirmarAnio(){
        if (empty()){
            std::cout << "Inventario vacio.\n"; return;
        }
        std::cout << "Selecciona un numero (1.." << n << "): ";
        size_t idx;
        if (!(std::cin >> idx) || idx<1 || idx>n){
            std::cout << "Indice invalido.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        Nodo* nd = nodoEnPos(idx);
        std::cout << "Elegiste: " << nd->data.marca << " " << nd->data.modelo
                  << " (" << nd->data.anio << ")\n";
        std::cout << "¿Ese es el año de tu vehiculo? (s/n): ";
        char r; std::cin >> r;
        if (r=='n' || r=='N'){
            std::cout << "Ingresa el año real: ";
            int a;
            if (std::cin >> a){
                nd->data.anio = a;
                std::cout << "Actualizado: " << nd->data.marca << " " << nd->data.modelo
                          << " (" << nd->data.anio << ")\n";
            } else {
                std::cout << "Entrada invalida.\n";
                std::cin.clear();
            }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

       void agregarManual(){
        Carro c; std::cin.ignore();
        std::cout << "Marca: ";   std::getline(std::cin, c.marca);
        std::cout << "Modelo: ";  std::getline(std::cin, c.modelo);
        std::cout << "Tipo: ";    std::getline(std::cin, c.tipo);
        std::cout << "Anio: ";    std::cin >> c.anio; std::cin.ignore();
        std::cout << "Motor: ";   std::getline(std::cin, c.motor);
        agregar(c);
        std::cout << "Agregado.\n";
    }

    // Filtro por marca que recorre toda la lista e imprime coincidencias exactas
    void filtrarPorMarca(const std::string& marca) const {
        bool found=false; size_t i=1;
        for (Nodo* cur=head; cur; cur=cur->next, ++i){
            if (cur->data.marca == marca){
                if (!found) std::cout << "Resultados para marca '"<<marca<<"':\n";
                std::cout << i << ") " << cur->data.marca << " " << cur->data.modelo
                          << " | " << cur->data.tipo
                          << " | " << cur->data.anio
                          << " | " << cur->data.motor << "\n";
                found=true;
            }
        }
        if (!found) std::cout << "No se encontraron autos de la marca: " << marca << "\n";
    }

    // Filtro por año que busca autos cuyo año coincida exactamente con el ingresado

    void filtrarPorAnio(int anio) const {
        bool found=false; size_t i=1;
        for (Nodo* cur=head; cur; cur=cur->next, ++i){
            if (cur->data.anio == anio){
                if (!found) std::cout << "Resultados para año "<<anio<<":\n";
                std::cout << i << ") " << cur->data.marca << " " << cur->data.modelo
                          << " | " << cur->data.tipo
                          << " | " << cur->data.anio
                          << " | " << cur->data.motor << "\n";
                found=true;
            }
        }
        if (!found) std::cout << "No se encontraron autos del anio: " << anio << "\n";
    }
};

#endif // CARROS_H
