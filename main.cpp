// Main.cpp
// Creaod por Oscar Alexander Vilchis SOto A01713207
// Ultima modificación 26/10/2025
// Se crea el main y el menú con 7 opciones disponibles al usuario, desde ver la lista de vehiculos registrados hasta agregar otro vehiculo 26/09/2025
//  Se modifica el main del código para asegurar que el inventario.csv se pueda abrir mediante una ruta relativa y pueda ser accedida desde otros dispositivos
//  de igual manera se añade al menu 2 nuevas funciones (filtrar por año y por marca
#include <iostream>
#include <limits>
#include "Carros.h"
#include <filesystem>

int main(){
    Carros carros;

    carros.cargarCSV("inventario.csv");
    int op = 0;
    do{
        // MENÚ PRINCIPAL: muestra las acciones disponibles hasta el momento al usuario
        std::cout << "\nGESTOR DE GARAGE\n"
                  << "1) Mostrar inventario\n"// Imprime todos los autos
                  << "2) Ordenar por marca (A-Z)\n" // Usa Merge Sort por marca
                  << "3) Ordenar por año (ascendente)\n" // Usa Merge Sort por año
                  << "4) Seleccionar año\n" // Permite ajustar el año a un registro elegido
                  << "5) Agregar carro manualmente\n" // Inserta un nuevo registro capturando datos
                  << "6) Filtrar por año\n" // Filtra los datos por base a un criterio de año que el usuario ingreesa (busqueda lineal)
                  << "7) Filtrar por marca\n" // Filtra los datos por base a un criterio de marca que el usuario ingreesa (busqueda lineal)
                  << "8) Salir\n> " // Opción para terminar el programa
                  << std::flush;

        if (!(std::cin >> op)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (op==1){
            carros.mostrar();
        } else if (op==2){
            carros.ordenarPorMarcaAZ();
            carros.mostrar();
        } else if (op==3){
            carros.ordenarPorAnioAsc();
            carros.mostrar();
        } else if (op==4){
            carros.seleccionarYConfirmarAnio();
        } else if (op==5){
            carros.agregarManual();
        } else if (op==6){
            int y; std::cout << "Año a filtrar: "; std::cin >> y;
            carros.filtrarPorAnio(y);
        } else if (op==7){
            std::string m; std::cout << "Marca a filtrar: ";
            std::cin.ignore();
            std::getline(std::cin, m);
            carros.filtrarPorMarca(m);
        }
    }while(op!=8);

    return 0;
}
