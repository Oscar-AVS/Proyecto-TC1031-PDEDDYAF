# Proyecto TC1031 – Programación de Estructuras de Datos y Algoritmos Fundamentales
#  Proyecto Gestor de Garage  

Repositorio  para los  avances y proyecto integrador de la materia programación de estructuras de datos y algoritmos fundamentales.


## Descripción del proyecto

Este proyecto " Gestor de garage" es un sistema que busca ayudar de manera sencilla a los usuarios a organizar y consultar información clave sobre sus vehículos de una manera más práctica y eficiente sin ser demasiado elaborado de usar. La idea surge de una necesidad común que yo pud eidentificar, ya que usualemnte el llevar control de aspectos básicos como verificaciones, pagos de tenencia, mantenimientos y kilometraje se vuelve una tarea que aunque es "sencilla" se peude volver tediosa. Muchas personas olvidan estas fechas importantes o las manejan de manera dispersa, lo que genera complicaciones, retardos e incluso gastos mayores e  inesperados. Este gestor busca centralizar todo en un solo lugar.



## Descripción del avance1 

En este primer avance, se  implementa un sistema básico que permita almacenar y organizar la información de los vehículos de manera ordenada. En esta etapa inicial, el programa se centra en trabajar con datos fundamentales de cada auto, como marca, modelo, tipo, año y motor, cargados desde un archivo de texto o ingresados manualmente por el usuario.

La funcionalidad principal es la organización de los datos mediante algoritmos de ordenamiento, específicamente Merge Sort, que garantiza eficiencia con una complejidad de O(n log n). El usuario podrá visualizar la lista de autos ordenada de diferentes formas, como por marca-modelo (alfabético) o por año (ascendente), lo que facilita la consulta. 

El programa actualmente  permite:
- Mostrar en pantalla el inventario de vehículos.
- Ordenar los datos de los carros por **marca (A-Z)** o por **año (ascendente)** utilizando el algoritmo Merge Sort.
- Seleccionar un carro por número y confirmar o modificar el año registrado.
- Agregar manualmente un carro nuevo al inventario desde la consola.
- Buscar autos por marca mediante una búsqueda lineal.


## Descripción avance 2

En este segundo avance se realizaron distintos cambios significativos, ya que el sistema fue actualizado para hacer uso de una estructura de datos más eficiente, de esta manera se sustituyó el uso de vector<Carro> por una lista doblemente ligada implementada manualmente, la cual permite manejar de manera dinámica la información y recorrerla en ambos sentidos (inicio y fin).

De igual manera se adaptaron distintas funciones de ordenamiento, siguiendo la base de Merge sort para trabajar con nodos, aún así mantuvimos una complejidad de O(n log n). Además se añaden dos nuevas funciones de filtrado que permiten al usuario consultar los vehículos según un criterio de marca o año.

Por últimno se cambió el formato de inventario.txt por un inventario.csv para que sea más fácil de leer.

## Cómo usar el programa 

Es necesario primero guardar el archivo "inventario.csv" en la misma carpeta que los demás archivos 

En CLion, si se ejecuta desde la carpeta cmake-build-debug, puede usarse la ruta relativa "../inventario.csv".

Compilar y ejecutar el programa.

El menú mostrará las siguientes opciones:

1) Mostrar inventario
2) Ordenar por marca (A-Z)
3) Ordenar por año (ascendente)
4) Seleccionar año
5) Agregar carro manualmente
6) Filtrar por año
7) Filtrar por marca
8) Salir

De esta manera, el usuario puede visualizar, filtrar, ordenar o agregar nuevos registros.


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

En cuanto al análisis de complejidad del programa, la lista doblemente ligada presenta un acceso por valor de O(n), ya que para localizar un elemento es necesario recorrer los nodos uno por uno. La inserción tiene una complejidad de O(1), pues cada nuevo vehículo se agrega directamente al final de la lista utilizando el apuntador tail. La eliminación de un elemento requiere una búsqueda previa, lo que implica una complejidad de O(n), mientras que las operaciones de recorrido y visualización del inventario mantienen también una complejidad lineal O(n). En cuanto al ordenamiento mediante el algoritmo Merge Sort, este conserva una complejidad temporal de O(n log n) en el mejor, promedio y peor caso.  Finalmente, las funciones de filtrado por marca o año tienen una complejidad O(n), ya que realizan una búsqueda lineal a lo largo de toda la lista para encontrar coincidencias con el criterio ingresado por el usuario.

### SICT0303B: Implementa acciones científicas

El programa permite consultar y filtrar los vehículos mediante distintas funciones, entre las cuales encontramos las que se agregaron en este segundo avance:

filtrarPorMarca() muestra todos los autos cuya marca coincide con el criterio ingresado.

filtrarPorAnio() muestra los autos del año especificado por el usuario.
Ambas operaciones recorren la lista doblemente ligada para identificar coincidencias.

De igual manera, se implementa mecanismos de lectura de archivos correctos  ya que el archivo inventario.csv se carga al iniciar el programa usando una ruta relativa, garantizando su funcionamiento en cualquier entorno sin necesidad de rutas absolutas.
