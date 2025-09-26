// Main.cpp
// Creaod por Oscar Alexander Vilchis SOto A01713207
// Ultima modificación 26/09/2025
// Se crea el main y el menú con 7 opciones disponibles al usuario, desde ver la lista de vehiculos registrados hasta agregar otro vehiculo 

#include "Carros.h"

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(&std::cout);

    Carros carros;

    carros.cargarCSV("C:/Users/alex_/OneDrive/Escritorio/inventario.txt");

    std::cout << "Registros cargados: " << carros.size() << "\n";

    int op = 0;
    do{
        // MENÚ PRINCIPAL: muestra las acciones disponibles hasta el momento al usuario
        std::cout << "\nGESTOR DE GARAGE\n"
                  << "1) Mostrar inventario\n"                  // Imprime todos los autos
                  << "2) Ordenar por marca (A-Z)\n"             // Usa Merge Sort por marca
                  << "3) Ordenar por an~o (ascendente)\n"       // Usa Merge Sort por año
                  << "4) Seleccionar an~o\n"        // Permite ajustar el año a un registro elegido
                  << "5) Agregar carro manualmente\n"           // Inserta un nuevo registro capturando datos
                  << "6) Buscar por marca\n"                    // Búsqueda lineal de coincidencias exactas por marca
                  << "7) Salir\n ";                            // Opción para terminar el programa


        if (!(std::cin >> op)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // OPCIÓN 1: Mostrar inventario completo
        if (op == 1){
            carros.mostrar();
        }
        // OPCIÓN 2: Ordenar por marca (A-Z) y mostrar resultado
        else if (op == 2){
            carros.ordenarPorMarcaAZ();
            carros.mostrar();
        }
        // OPCIÓN 3: Ordenar por año (ascendente) y mostrar resultado
        else if (op == 3){
            carros.ordenarPorAnioAsc();
            carros.mostrar();
        }
        // OPCIÓN 4 Selecciona un número desde el 1 hasta N (numero de vehiculos registrados) y confirmar/cambiar el año del vehículo
        else if (op == 4){
            carros.seleccionarYConfirmarAnio();
        }
        // OPCIÓN 5: Agregar un carro capturando datos desde la consola
        else if (op == 5){
            Carro c;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Marca: ";   std::getline(std::cin, c.marca);
            std::cout << "Modelo: ";  std::getline(std::cin, c.modelo);
            std::cout << "Tipo: ";    std::getline(std::cin, c.tipo);

            std::cout << "An~o: ";    std::cin >> c.anio;
            std::cin.ignore();

            std::cout << "Motor: ";   std::getline(std::cin, c.motor);

            carros.agregar(c);
            std::cout << "Agregado.\n";
        }
        // OPCIÓN 6: Buscar por marca
        else if (op == 6){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::string marca; // Marca a buscar
            std::cout << "Ingresa la marca a buscar: ";
            std::getline(std::cin, marca);
            carros.buscarPorMarca(marca);
        }
        else if (op != 7){
            std::cout << "Opcion invalida.\n";
        }

    } while (op != 7);

    std::cout << "Gracias por usar el gestor de garage  :D\n";
    return 0;
}
