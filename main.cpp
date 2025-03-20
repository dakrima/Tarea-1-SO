
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

using namespace std;

// Vector con las tareas que pueden aparecer

const vector<string> TAREAS = {
    "Onda Certera", "Láser vs. Plasma", "Quantumanía", "ÁtomoX",
    "BitFase", "Red-Arácnida", "Debug & Dragons", "Thread Wars",
    "Crypto Knight", "Bugzilla", "Stack Attack", "Compile & Conquer",
    "AlgoRhythm", "Cyberkarma"
};

// Vector con los certamenes que pueden aparecer

const vector<string> CERTAMENES = {
    "1", "2", "3"
};

// Vector con los controles que pueden aparecer

const vector<string> CONTROLES = {
    "1", "2", "3"
};

// Función para leer los archivos

string leer_archivo(const string& filename) {
    ifstream archivo(filename);
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return "";
    }

    string contenido, linea;
    while (getline(archivo, linea)) {
        contenido += linea + "\n"; // Concatena las líneas con salto de línea
    }
    archivo.close();
    return contenido;
};


// El main

int main(){

    string filename = "General/0RexmwJ3x.txt";
    string contenido = leer_archivo(filename);

    cout << "Contenido es: \n" << contenido << endl;

    return 0;

}
