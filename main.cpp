
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <sstream>

using namespace std;

// Vector con las tareas que pueden aparecer

const vector<string> TAREAS = {
    "Onda Certera", "Laser vs. Plasma", "Quantumania", "AtomoX",
    "BitFase", "Red-Aracnida", "Debug & Dragons", "Thread Wars",
    "Crypto Knight", "Bugzilla", "Stack Attack", "Compile & Conquer",
    "AlgoRhythm", "Cyberkarma"};

// Vector con los certamenes que pueden aparecer

const vector<string> CERTAMENES = {
    "1", "2", "3"};

// Vector con los controles que pueden aparecer

const vector<string> CONTROLES = {
    "1", "2", "3"};

// Función para leer los archivos línea por línea

string leer_archivo(const string &filename)
{
    ifstream archivo(filename);
    if (!archivo)
    {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return "";
    }

    string contenido, linea;
    while (getline(archivo, linea))
    {
        contenido += linea + "\n"; // Concatena las líneas con salto de línea
    }
    archivo.close();
    return contenido;
};

// Función que obtiene la data del archivo

void obtener_data(const string &contenido, string &tipo, string &numero, string &semestre, string &nombre)
{
    stringstream ss(contenido);
    string palabra;

    while (ss >> palabra)
    {

        // Acá busca la palabra "tipo" y guarda la palabra que le sigue en tipo

        if (palabra == "tipo:")
        {
            ss >> tipo;
            if (tipo == "tarea")
            {
                for (const string &nombre_tarea : TAREAS)
                {
                    if (contenido.find(nombre_tarea) != string::npos)
                    {
                        nombre = nombre_tarea;
                        break;
                    }
                }
            }
        }

        // Acá se hace lo mismo pero para "numero:"

        else if (palabra == "numero:")
        {
            ss >> numero;
        }

        // Acá lo mismo pero con semestre

        else if (palabra == "semestre_publicacion:")
        {
            ss >> semestre;
        }
    }
};

// Función que lee todos los archivos de la carpeta "General"

void leer_todos_los_archivos()
{
    string file = "General/";
    int count = 1;

    for (const auto &entry : filesystem::directory_iterator(file)){
        string filename = entry.path().string();

        string contenido = leer_archivo(filename);
        if (contenido.empty())
        {
            continue;
        }

        string tipo, numero, semestre, nombre;

        obtener_data(contenido, tipo, numero, semestre, nombre);


        cout << "Nombre archivo: " << filename << endl;
        cout << "Tipo: " << tipo << endl;
        if (tipo == "certamen" || tipo == "control")
        {
            cout << "Numero: " << numero << endl;
        }
        else if (tipo == "tarea")
        {
            cout << "Nombre: " << nombre << endl;
        }
        cout << "Semestre: " << semestre << endl;
        cout << count << endl;
        cout << " " << endl;
        count++;
    }
}

// El main

int main()
{

    leer_todos_los_archivos();

    return 0;
}
