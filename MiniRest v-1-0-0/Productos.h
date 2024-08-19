#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

typedef struct {

    char id[30];
    char nombre[30];
    float precio;
    int stock;
    int estadoActividad; //1-Activo, 0-Inactivo

} Producto;

///ALTA
Producto agregarProductoDeAuno(char archivo[]);
void crearProductos(char archivo[]);

///BAJA
void darDeBaja(char archivo[]);

///MODIFICACION
Producto modificarProducto2(char archivo[],Producto p, char *flag);
void modificarProducto(char archivo[]);
void ingresarNuevoNombreProducto(char archivo[],char nombreProducto[]);
void ingresarNuevoIDProducto(char archivo[],char idProducto[]);
void ingresarPrecioNuevoProducto(float *precio);
void ingresarNuevoStockProducto(int *stock);
void modificarStockAutomatico(char archivo[], int pos, int valor);

///CONSULTA Y LISTADO
void verTodoProductos(char archivo[]);
void mostrarProducto(Producto p);
void mostrarProductoReducido(Producto p);
void ingresarIDProducto(char id[]);
void pasajeProductosArreglo(char archivo[], Producto arregloProductos[], int validos, int dim);
void filtrarProductosActividad(char archivo[], char dato);
void ordenarProductosID(Producto arregloProductos[], int validos);
void insertarProductoID(Producto arregloProducto[], Producto insertada, int validos);
void filtrarProductosID(char archivo[], char orden);
void insertarProductoNombre(Producto arreglo[], Producto insertada, int validos);
void ordenarProductosMenorAmayorNombre(Producto arreglo[], int validos);
void filtrarProductosNombre(char archivo[]);
void filtrarProductosPrecio(char archivo[]);
void ordenarProductosPrecio(Producto arregloProductos[], int validos);
void insertarProductoPrecio(Producto arregloProducto[], Producto insertada, int validos);
void insertarProductoStock(Producto arregloProducto[], Producto insertada, int validos);
void ordenarProductosStock(Producto arregloProductos[], int validos);
void filtrarProductosStock(char archivo[]);
void IDingresadoAbuscar(char id[]);
int buscarProductoPorNombre(char archivo[], char nombre[]);
void buscarYmostrarProductoNombre(char archivo[]);
void nombreIngresadoAbuscar(char nombre[]);
int buscarProductoPorID(char archivo[], char id[]);
void buscarYmostrarProductoID(char archivo[]);
Producto buscarYretornarProductoPorPosicion(char archivo[], int pos);


#endif // PRODUCTOS_H_INCLUDED
