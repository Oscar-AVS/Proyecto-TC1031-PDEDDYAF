// Main.cpp
// Creaod por Oscar Alexander Vilchis SOto A01713207
// Ultima modificación 26/10/2025
// Se crea el main y el menú con 7 opciones disponibles al usuario, desde ver la lista de vehiculos registrados hasta agregar otro vehiculo 26/09/2025
//  Se modifica el main del código para asegurar que el inventario.csv se pueda abrir mediante una ruta relativa y pueda ser accedida desde otros dispositivos
//  de igual manera se añade al menu 2 nuevas funciones (filtrar por año y por marca) 
//  Para el tercer avance se integra un nuevo módulo GarageUsuario que permite registrar hasta 5 vehículos personales del usuario
//  y guardarlos en un archivo CSV (garage_usuario.csv)

#include <iostream>
#include <limits>
#include <cctype>       
#include "Carros.h"
#include "GarageUsuario.h"

// Función que  a partir de un Carro del inventario pregunta al usuario datos extra de su vehículo real (verificación y servicio)
// y construye un VehiculoUsuario que se podrá guardar en el garage de cada usuario
VehiculoUsuario capturarVehiculoUsuario(const Carro& base){
    VehiculoUsuario v;
    v.base = base;

    // Inferimos si requiere verificación según el tipo de motor, si contiene "EV" o "Hybrid" asumimos que NO requiere verificación.
    std::string motorLower = base.motor;
    for (char& c : motorLower){
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }

    bool requiereVerifPorDefecto = true;
    if (motorLower.find("ev") != std::string::npos ||
        motorLower.find("hybrid") != std::string::npos){
        requiereVerifPorDefecto = false;
    }

    std::cout << "\nConfigurando tu vehiculo personal: "
              << base.marca << " " << base.modelo
              << " (" << base.anio << ")\n";

    std::cout << "¿Tu auto requiere verificacion? (s/n): ";
    char rv;
    std::cin >> rv;

    if (rv == 's' || rv == 'S'){
        v.requiereVerificacion = true;
    } else if (rv == 'n' || rv == 'N'){
        v.requiereVerificacion = false;
    } else {
        v.requiereVerificacion = requiereVerifPorDefecto;
    }

    if (v.requiereVerificacion){
        std::cout << "¿Hace cuantos meses fue tu ultima verificacion?: ";
        std::cin >> v.mesesDesdeVerificacion;
    } else {
        // Usamos -1  para indicar que no aplica verificación
        v.mesesDesdeVerificacion = -1;
    }

    std::cout << "¿Hace cuantos meses fue tu ultimo servicio?: ";
    std::cin >> v.mesesDesdeServicio;

    std::cout << "¿Cuantos km tenia tu auto en ese ultimo servicio?: ";
    std::cin >> v.kmUltimoServicio;

    return v;
}

int main(){
    Carros carros;             // Estructura principal con el inventario general de autos
    GarageUsuario garage;      // Estructura para el garage personal del usuario

    // Carga inicial del inventario desde un archivo CSV con ruta relativa
    carros.cargarCSV("inventario.csv");

    int op = 0;
    do{
        // MENÚ PRINCIPAL: muestra las acciones disponibles hasta el momento al usuario
        std::cout << "\nGESTOR DE GARAGE\n"
                  << "1) Mostrar inventario\n"          // Imprime todos los autos del inventario general
                  << "2) Ordenar por marca (A-Z)\n"     // Usa Merge Sort por marca sobre la lista doblemente ligada
                  << "3) Ordenar por año (ascendente)\n"// Usa Merge Sort por año sobre la lista doblemente ligada
                  << "4) Seleccionar año\n"             // Permite ajustar el año a un registro elegido del inventario
                  << "5) Agregar carro manualmente\n"   // Inserta un nuevo registro capturando datos para el inventario
                  << "6) Filtrar por año\n"             // Filtra los datos del inventario según un año (búsqueda lineal)
                  << "7) Filtrar por marca\n"           // Filtra los datos del inventario según una marca (búsqueda lineal)
                  << "8) Mostrar vehiculos de mi garage\n" // Muestra los autos registrados en el garage personal
                  << "9) Guardar mi garage en archivo\n"   // Guarda el garage del usuario en garage_usuario.csv
                  << "10) Salir\n> "                   // Opción para terminar el programa
                  << std::flush;

        if (!(std::cin >> op)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (op==1){
            // Muestra todo el inventario de autos
            carros.mostrar();

        } else if (op==2){
            // Ordena el inventario por marca y luego lo muestra
            carros.ordenarPorMarcaAZ();
            carros.mostrar();

        } else if (op==3){
            // Ordena el inventario por año de manera ascendente y luego lo muestra
            carros.ordenarPorAnioAsc();
            carros.mostrar();

        } else if (op==4){
        
            carros.seleccionarYConfirmarAnio();

        } else if (op==5){
            // Captura manualmente un nuevo carro y lo agrega al inventario general
            Carro c;
            std::cin.ignore();  
            std::cout << "Marca: ";
            std::getline(std::cin, c.marca);
            std::cout << "Modelo: ";
            std::getline(std::cin, c.modelo);
            std::cout << "Tipo: ";
            std::getline(std::cin, c.tipo);
            std::cout << "Anio: ";
            std::cin >> c.anio;
            std::cin.ignore();
            std::cout << "Motor: ";
            std::getline(std::cin, c.motor);

            carros.agregar(c); // Se inserta al final de la lista doblemente ligada del inventario
            std::cout << "Carro agregado al inventario.\n";

            // Pregunta adicional para saber si el usuario desea  este mismo carro en el garage personal 
            char r;
            std::cout << "¿Quieres agregar este vehiculo a tu garage personal? (s/n): ";
            std::cin >> r;

            if (r=='s' || r=='S'){
                if (garage.lleno()){
                    std::cout << "No se puede agregar, tu garage ya esta lleno (maximo 5 vehiculos).\n";
                } else {
                    VehiculoUsuario v = capturarVehiculoUsuario(c);
                    garage.agregar(v);
                }
            }

        } else if (op==6){
            // Filtra el inventario por un año específico
            int y;
            std::cout << "Año a filtrar: ";
            std::cin >> y;
            carros.filtrarPorAnio(y);

        } else if (op==7){
            // Filtra el inventario por marca específica
            std::string m;
            std::cout << "Marca a filtrar: ";
            std::cin.ignore();
            std::getline(std::cin, m);
            carros.filtrarPorMarca(m);

        } else if (op==8){
            // Muestra todos los vehículos registrados en el garage personal del usuario
            garage.mostrar();

        } else if (op==9){
            // Guarda el garage personal en un archivo CSV
            garage.guardarCSV("garage_usuario.csv");
        }

    }while(op!=10); 

    return 0;
}
