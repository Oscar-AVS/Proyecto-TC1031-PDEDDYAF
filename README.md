# Proyecto TC1031 – Programación de Estructuras de Datos y Algoritmos Fundamentales
## Proyecto Gestor de Garage  

### Descripción del proyecto

Este proyecto " Gestor de garage" es un sistema que busca ayudar de manera sencilla a los usuarios a organizar y consultar información clave sobre sus vehículos de una manera más práctica y eficiente sin ser demasiado elaborado de usar. La idea surge de una necesidad común que yo pude identificar, ya que usualmente el llevar control de aspectos básicos como verificaciones, pagos de tenencia, mantenimientos y kilometraje se vuelve una tarea que aunque es "sencilla" se puede volver tediosa. Muchas personas olvidan estas fechas importantes o las manejan de manera dispersa, lo que genera complicaciones, retardos e incluso gastos mayores e  inesperados. Este gestor busca centralizar todo en un solo lugar.



## Descripción del avance 1 

En este primer avance, se  implementa un sistema básico que permite almacenar y organizar la información de los vehículos de manera ordenada. En esta etapa inicial, el programa se centra en trabajar con datos fundamentales de cada auto, como marca, modelo, tipo, año y motor, cargados desde un archivo de texto o ingresados manualmente por el usuario.

La funcionalidad principal es la organización de los datos mediante algoritmos de ordenamiento, específicamente Mergesort, que garantiza eficiencia con una complejidad de O(n log n). El usuario podrá visualizar la lista de autos ordenada de diferentes formas, como por marca-modelo (alfabético) o por año (ascendente), lo que facilita la consulta. 

El programa actualmente  permite:
- Mostrar en pantalla el inventario de vehículos.
- Ordenar los datos de los carros por **marca (A-Z)** o por **año (ascendente)** utilizando el algoritmo Merge Sort.
- Seleccionar un carro por número y confirmar o modificar el año registrado.
- Agregar manualmente un carro nuevo al inventario desde la consola.
- Buscar autos por marca mediante una búsqueda lineal.


## Descripción avance 2

En este segundo avance se realizaron distintos cambios significativos, ya que el sistema fue actualizado para hacer uso de una estructura de datos más eficiente, de esta manera se sustituyó el uso de vector<Carro> por una lista doblemente ligada implementada manualmente, la cual permite manejar de manera dinámica la información y recorrerla en ambos sentidos (inicio y fin).

De igual manera se adaptaron distintas funciones de ordenamiento, siguiendo la base de Merge sort para trabajar con nodos, aún así mantuvimos una complejidad de O(n log n). Además se añaden dos nuevas funciones de filtrado que permiten al usuario consultar los vehículos según un criterio de marca o año.

Por último se cambió el formato de inventario.txt por un inventario.csv para que sea más fácil de leer.


## Descripción del avance 3 
En este último avance se realizaron distintos cambios significativos, para empezar se creó un nuevo header llamado GarageUsuario.h en donde se permite agregar hasta 5 vehículos al garage de cada usuario.  Dentro de estas nuevas funciones se incluye una nueva  estructura VehiculoUsuario con datos base, información real del vehículo que selecciona el usuario (verificación, servicio, kilometraje) y una nueva lista doblemente ligada para el garage personal así cómo una función para guardar el garage en garage_usuario.csv.

De igual manera se implementan nuevas opciones de menú:
Mostrar garage del usuario
Guardar garage en archivo

De esta manera, ahora el usuario cuando  agrega un carro manualmente, puede:

Registrarlo en su garage personal

Capturar datos reales como verificación y servicios

Guardarlo 


## Cómo usar el programa 

Es necesario primero guardar el archivo "inventario.csv" en la misma carpeta que los demás archivos 

En CLion, si se ejecuta desde la carpeta cmake-build-debug, puede usarse la ruta relativa "../inventario.csv".

Compilar y ejecutar el programa.

El menú mostrará las siguientes opciones:

1) Mostrar inventario
2) Ordenar por marca (A-Z)       
3) Ordenar por año (ascendente)     
4) Seleccionar año
5) Agregar vehiculo del inventario a mi garage
6) Agregar carro manualmente        
7) Filtrar por año                 
8) Filtrar por marca     
9) Mostrar vehiculos de mi garage   
10) Guardar mi garage en archivo
11) Salir


De esta manera, el usuario puede visualizar, filtrar, ordenar o agregar nuevos registros e incluso guardarlos en garage_usuario.csv

## Cumplimiento de sub-competencias

### SICT0302B: Toma decisiones

Se eligió una lista doblemente ligada para almacenar los datos de los vehículos.
Esta estructura permite recorrer los elementos en ambos sentidos y realizar inserciones eficientes en O(1) sin necesidad de mover elementos, a diferencia de los vectores.

Cada nodo contiene un objeto Carro con sus atributos: marca, modelo, tipo, año y motor, y los punteros next y prev que facilitan el recorrido en ambas direcciones.
El uso de esta estructura resulta ideal para un inventario dinámico donde el usuario puede agregar nuevos autos o consultar los existentes sin requerir índices.

Se utiliza el algoritmo Merge Sort para ordenar la lista de carros por marca o por año.
Merge Sort fue elegido porque:

Mantiene una complejidad O(n log n) en todos los casos.

Es un algoritmo estable, conserva el orden relativo de elementos iguales (útil si varios autos tienen el mismo año o marca). 

### SICT0301B: Evalúa los componentes

En cuanto al análisis de complejidad del programa, la estructura principal utilizada es una lista doblemente ligada, cuya eficiencia depende de la operación que se realice. El acceso por valor tiene una complejidad O(1)  en el mejor caso que es cuando el elemento se encuntra inmediatamente en head o en tail, y O (n) tanto en el caso promedio como el peor caso ya que para localizar un elemento es necesario recorrer los nodos secuencialmente desde uno de los extremos. 

La inserción de nuevos vehículos al final de la lista mantiene una complejidad O(1) en el mejor, promedio y peor caso, porque se utiliza el apuntador tail, lo que evita recorrer la estructura. La eliminación de algún elemento presenta una complejidad de O(1) en el mejor caso (cuando el nodo a eliminar es head o tail) y O(n) en el caso promedio y peor, ya que primero requiere localizar el nodo mediante un recorrido lineal.

Las operaciones de recorrido, impresión y visualización del inventario son siempre O(n), pues deben visitar todos los nodos sin importar el caso. 

 El ordenamiento mediante el algoritmo Merge Sort conserva una complejidad temporal uniforme de O(n log n) en el mejor, promedio y peor caso. Esto se debe a su naturaleza recursiva de dividir la lista en mitades y fusionarlas ordenadamente, sin depender del orden inicial de los datos.

Las funciones de filtrado por marca y por año tienen una complejidad de O(n) en todos los casos, ya que requieren recorrer cada elemento de la lista para comprobar si coincide con el criterio ingresado por el usuario.

Finalmente, para el avance 3 se añadió la estructura GarageUsuario, también basada en una lista doblemente ligada. Dado que su tamaño máximo es de 5 elementos, todas las operaciones tienen complejidad O(1), aunque teóricamente equivalen a O(m), donde m ≤ 5. En conjunto, la operación más costosa del programa sigue siendo el ordenamiento del inventario mediante Merge Sort, por lo que la complejidad del sistema completo es O(n log n).



### SICT0303B: Implementa acciones científicas

El programa permite consultar y filtrar los vehículos mediante distintas funciones, entre las cuales encontramos las que se agregaron en este segundo avance:

filtrarPorMarca() muestra todos los autos cuya marca coincide con el criterio ingresado.

filtrarPorAnio() muestra los autos del año especificado por el usuario.
Ambas operaciones recorren la lista doblemente ligada para identificar coincidencias.

De igual manera, se implementa mecanismos de lectura de archivos correctos  ya que el archivo inventario.csv se carga al iniciar el programa usando una ruta relativa, garantizando su funcionamiento en cualquier entorno sin necesidad de rutas absolutas.

Además  el programa implementa  mecanismos de escritura de archivos para guardar la información de las estructuras de datos, el ejemplo está en el  `GarageUsuario` que  incluye la función `guardarCSV("garage_usuario.csv")`, que recorre la lista doblemente ligada de vehículos que ingresa el usuario y genera un archivo CSV concada vehículo (marca, modelo, tipo, año, motor y datos de verificación y servicio). Esta función se puede usar  desde el menú principal en la opción "Guardar mi garage " lo que permite que el usuario guarde sus datos a medida que va usando el programa.



# Evidencia 2: Videos 

Problema 1: Relative Sort Array 1122 
https://youtu.be/IxPLgakt2Ds 

Código utilizado: 

    #include <iostream>
    #include <vector>
    using namespace std;
    
    class Solution {
    public:
        vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
            // arreglo de frecuencias para valores de 0 a 1000
            const int MAX_VAL = 1000;
            int freq[MAX_VAL + 1] = {0};

        // contar cuántas veces aparece cada número en arr1
        for (int x : arr1) {
            freq[x]++;
        }

        vector<int> res;

        // se  agregan los elementos que aparecen en arr2
        for (int x : arr2) {
            while (freq[x] > 0) {
                res.push_back(x);
                freq[x]--;
            }
        }

        // se agregan los eleemnetos que no están en arr 2 en orden ascendente
        for (int v = 0; v <= MAX_VAL; v++) {
            while (freq[v] > 0) {
                res.push_back(v);
                freq[v]--;
            }
        }

        return res;
    }
    };

Problema 2: Daily Temperatures 739
https://youtu.be/Nra8hkZM6CA

Código utilizado: 

    #include <vector>
    #include <stack>
    using namespace std;
    
    class Solution {
    public:
        vector<int> dailyTemperatures(vector<int>& temperatures) {
            int n = temperatures.size();
            vector<int> answer(n, 0);  // por defecto todos en 0
            stack<int> st;             

        for (int i = 0; i < n; i++) {
            // Mientras el día actual sea más caliente que el día en la cima del stack 
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int idx = st.top();    // día anterior pendiente
                st.pop();
                answer[idx] = i - idx; // cuántos días esperó
            }
            // El día actual queda pendiente
            st.push(i);
        }

        return answer;
    }
    };

Problema 3: Path Sum 112 
https://youtu.be/1zTga_1MlBU 

Código utillizado: 

    /**
     * Definition for a binary tree node.
     * struct TreeNode {
     *     int val;
     *     TreeNode *left;
     *     TreeNode *right;
     *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
     * };
     */
    
    class Solution {
    public:
        bool hasPathSum(TreeNode* root, int targetSum) {
            // Caso 1 si el árbol vacío entonces  no hay ruta
            if (root == nullptr) {
                return false;
            }

        // Caso 2 si estamos en una hoja
        if (root->left == nullptr && root->right == nullptr) {
             return (root->val == targetSum);
        }

        // Caso 3 si estamos en nodo interno entonces restamos el valor actual
        int newTarget = targetSum - root->val;

        // Buscamos en subárbol izquierdo o derecho
        return hasPathSum(root->left, newTarget) ||
               hasPathSum(root->right, newTarget);
    }
    };


