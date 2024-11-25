#ifndef LOADSCRIPT_H
#define LOADSCRIPT_H

#include <stdbool.h> // Para usar el tipo `bool`

// Declaraciones de las funciones
void load_script(const char* filename, bool show_script); // Carga el archivo dado
void load_script_interactive(); // Solicita el archivo al usuario

#endif // LOADSCRIPT_H
