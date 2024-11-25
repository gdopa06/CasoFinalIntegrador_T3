# Caso Final Integrador Tema 3

URL: https://github.com/gdopa06/CasoFinalIntegrador_T3.git

<details>
  <summary>ENUNCIADO DE LOS EJERCICIOS: </summary>
  <p style="font-size: 12px; line-height: 1.4;">
    <details>
      <summary>1. Carga de scripts en tiny-lisp</summary>
      <p style="font-size: 12px; line-height: 1.4;">
        El módulo Labmain.cpp define la función <code>load_script()</code>, que se utiliza para cargar un script en la memoria y aplicarle la coloración sintáctica. Esta función se basa en la librería estándar de C.
        Implementa las funciones <code>load_script()</code> y <code>load_script(filename, true)</code> en CLion, de tal manera que puedas abrir y leer archivos de texto. El primer método toma el nombre de un archivo como entrada del usuario, mientras que el segundo muestra el contenido del archivo. Ambos métodos deben cargar el script en la consola.
        <code>void load_script(const char* filename, bool show_script = false);</code><br>
        <code>void load_script();</code>
      </p>
    </details>
    <details>
      <summary>2. Asegurando la robustez del código</summary>
      <p style="font-size: 12px; line-height: 1.4;">
        Asegúrate de que tu código pueda manejar diferentes tipos de errores de entrada. Esto incluye, pero no se limita a:
        <ul>
          <li>El usuario proporciona un nombre de archivo que no existe.</li>
          <li>El archivo proporcionado no se puede abrir por alguna razón.</li>
          <li>Se produce un error de lectura durante la lectura del archivo.</li>
        </ul>
        Para manejar estos y otros errores potenciales, es posible que desees agregar comprobaciones de errores adicionales y manejar los fallos de manera más sofisticada.
      </p>
    </details>
    <details>
      <summary>Notas</summary>
      <p style="font-size: 12px; line-height: 1.4;">
        Este ejercicio no requiere el uso de funciones seguras específicas de Microsoft (las funciones con sufijo <code>_s</code>). En cambio, deberías usar las funciones estándar de C/C++ disponibles en todas las plataformas y compiladores, como <code>fopen</code>, <code>printf</code> y <code>scanf</code>.
      </p>
    </details>
    <details>
      <summary>Rúbrica</summary>
      <p style="font-size: 12px; line-height: 1.4;">
        <strong>Carga de scripts (50 puntos)</strong>
        <ul>
          <li>Se proporciona una implementación correcta de <code>load_script(const char* filename, bool show_script = false)</code> que carga correctamente el archivo dado y muestra su contenido si <code>show_script</code> es verdadero. (25 puntos)</li>
          <li>Se proporciona una implementación correcta de <code>load_script()</code> que solicita al usuario un nombre de archivo, llama a la función <code>load_script(const char* filename, bool show_script = false)</code> y maneja cualquier error de manera apropiada. (25 puntos)</li>
        </ul>
        <strong>Manejo de errores (50 puntos)</strong>
        <ul>
          <li>El código tiene un manejo de errores sólido y completo para el caso de que el nombre del archivo proporcionado no exista. (15 puntos)</li>
          <li>El código tiene un manejo de errores sólido y completo para el caso de que el archivo proporcionado no se pueda abrir por alguna razón. (15 puntos)</li>
          <li>El código tiene un manejo de errores sólido y completo para el caso de que se produzca un error de lectura durante la lectura del archivo. (20 puntos)</li>
        </ul>
        <strong>Total: 100 puntos</strong>
      </p>
    </details>
  
  </p>
</details>


## Propuesta de solución
En CLion, las funciones seguras de la biblioteca estándar de C (*_s funciones) generalmente no están disponibles porque estas son específicas de Microsoft y no son estándar de C/C++. Por lo tanto, en lugar de utilizar funciones como fopen_s, printf_s y scanf_s, puedes usar sus equivalentes no seguros, que son fopen, printf y scanf.

A continuación se muestra cómo se podría reescribir el código para CLion:
```
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox; // suponemos que ya está inicializado

void load_script(const char* filename, bool show_script = false)
{
    string script;
    FILE* f = nullptr;
    try
    {
        f = fopen(filename, "rb");
        if (!f)
        {
            cerr << "error de apertura de " << filename << endl;
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0)
        {
            buf[c] = 0;
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }
        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (...)
    {
        cerr << "error durante la lectura del archivo" << endl;
        if(f)
            fclose(f);
    }
}

void load_script()
{
    char filename[500];
    printf("Archivo: ");
    scanf("%499s", filename);
    load_script(filename, true);
}
```
Este código debería compilar y funcionar en CLion sin necesidad de agregar la directiva _CRT_SECURE_NO_WARNINGS, ya que no se están utilizando las versiones seguras específicas de Microsoft de las funciones de la biblioteca estándar de C.

Por último, ten en cuenta que este código no realiza una comprobación completa de errores y no es robusto contra varios tipos de errores de entrada. Dependiendo de tu caso de uso específico, es posible que desees agregar comprobaciones de errores adicionales y manejar los fallos de manera más sofisticada.
