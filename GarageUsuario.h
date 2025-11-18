// GarageUsuario.h
// Creado por Oscar Alexander Vilchis Soto A01713207
// Última modificación: 10/11/2025
// Este archivo implementa la estructura de datos "GarageUsuario", una lista doblemente ligada con máximo de 5 vehículos del usuario
// Además implementa lectura y escritura en archivo CSV para guardar el garage del usuario

#ifndef GARAGE_USUARIO_H
#define GARAGE_USUARIO_H

#include <iostream>
#include <fstream>
#include <string>
#include "Carros.h"

struct VehiculoUsuario {
    Carro base; // datos generales (marca, modelo, tipo, año, motor)

    bool requiereVerificacion = true;
    int mesesDesdeVerificacion = -1; // -1 si no aplica
    int mesesDesdeServicio = 0;
    int kmUltimoServicio = 0;
};

// Nodo para lista doblemente ligada
struct NodoUsuario {
    VehiculoUsuario data;
    NodoUsuario* next;
    NodoUsuario* prev;

    explicit NodoUsuario(const VehiculoUsuario& v)
        : data(v), next(nullptr), prev(nullptr) {}
};

class GarageUsuario {
private:
    NodoUsuario* head = nullptr;
    NodoUsuario* tail = nullptr;
    size_t n = 0;
    const size_t MAX_AUTOS = 5;

public:
    GarageUsuario() = default;

    // Destructor
    ~GarageUsuario() {
        NodoUsuario* cur = head;
        while (cur) {
            NodoUsuario* nx = cur->next;
            delete cur;
            cur = nx;
        }
    }

    size_t size() const { return n; }
    bool lleno() const { return n >= MAX_AUTOS; }

    // Agregar vehículo al garage
    bool agregar(const VehiculoUsuario& v) {
        if (lleno()) {
            std::cout << "El garage ya tiene 5 vehículos registrados.\n";
            return false;
        }

        NodoUsuario* nuevo = new NodoUsuario(v);

        if (!head) {
            head = tail = nuevo;
        } else {
            tail->next = nuevo;
            nuevo->prev = tail;
            tail = nuevo;
        }

        n++;
        std::cout << "Vehículo agregado al garage del usuario.\n";
        return true;
    }

    // Mostrar garage del usuario
    void mostrar() const {
        if (!head) {
            std::cout << "(Garage del usuario vacío)\n";
            return;
        }

        int i = 1;
        for (NodoUsuario* cur = head; cur; cur = cur->next) {
            std::cout << i++ << ") "
                      << cur->data.base.marca << " "
                      << cur->data.base.modelo
                      << " | Año: " << cur->data.base.anio
                      << " | Servicio hace: " << cur->data.mesesDesdeServicio << " meses"
                      << " | Km al servicio: " << cur->data.kmUltimoServicio;

            if (!cur->data.requiereVerificacion)
                std::cout << " | Sin verificación (EV/Híbrido)\n";
            else
                std::cout << " | Verificación hace: "
                          << cur->data.mesesDesdeVerificacion << " meses\n";
        }
    }

    // Guardar garage en archivo CSV
    bool guardarCSV(const std::string& ruta) const {
        std::ofstream out(ruta);
        if (!out.is_open()) {
            std::cout << "No se pudo abrir el archivo: " << ruta << "\n";
            return false;
        }

        out << "marca,modelo,tipo,anio,motor,requiereVerificacion,mesesDesdeVerificacion,mesesDesdeServicio,kmUltimoServicio\n";

        for (NodoUsuario* cur = head; cur; cur = cur->next) {
            out << cur->data.base.marca << ","
                << cur->data.base.modelo << ","
                << cur->data.base.tipo << ","
                << cur->data.base.anio << ","
                << cur->data.base.motor << ","
                << (cur->data.requiereVerificacion ? 1 : 0) << ","
                << cur->data.mesesDesdeVerificacion << ","
                << cur->data.mesesDesdeServicio << ","
                << cur->data.kmUltimoServicio << "\n";
        }

        std::cout << "Garage guardado correctamente en archivo.\n";
        return true;
    }
};

#endif // GARAGE_USUARIO_H
