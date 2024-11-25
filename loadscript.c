#include "loadscript.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Implementación de load_script
void load_script(const char* filename, bool show_script) {
    FILE* f = NULL;
    char* script = NULL;
    size_t file_size;

    f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "Error al abrir el archivo \"%s\": %s\n", filename, strerror(errno));
        return;
    }

    fseek(f, 0, SEEK_END);
    file_size = ftell(f);
    rewind(f);

    script = (char*)malloc(file_size + 1);
    if (!script) {
        fprintf(stderr, "Error al reservar memoria para el archivo\n");
        fclose(f);
        return;
    }

    fread(script, 1, file_size, f);
    script[file_size] = '\0';

    if (ferror(f)) {
        fprintf(stderr, "Error al leer el archivo \"%s\": %s\n", filename, strerror(errno));
        free(script);
        fclose(f);
        return;
    }

    fclose(f);

    if (show_script) {
        printf("\033[34m\033[47m%s\033[0m\n", script); // Color de texto
    }

    free(script);
}

// Implementación de load_script_interactive
void load_script_interactive() {
    char filename[500];

    printf("Ingrese el nombre del archivo: ");
    if (scanf("%499s", filename) != 1) {
        fprintf(stderr, "Error al leer el nombre del archivo.\n");
        return;
    }

    load_script(filename, true);
}
