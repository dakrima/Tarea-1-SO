
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <sstream>
#include <regex>

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

// Esto me valida si el semestre tiene 4 digitos y el guión

bool semestre_valido(const string &semestre)
{
    if (!regex_match(semestre, regex(R"(\d{4}-[12])")))
        return false;

    int anio = stoi(semestre.substr(0, 4));
    return anio <= 2025;
}


bool esta_en(const string &valor, const vector<string> &lista)
{
    return find(lista.begin(), lista.end(), valor) != lista.end();
}

// esta función me crea las carpetas y mete los archivos según corresponda

void organizar_carpetas()
{
    string carpeta_general = "General/";

    for (const auto &entry : filesystem::directory_iterator(carpeta_general))
    {
        string ruta_original = entry.path().string();
        string contenido = leer_archivo(ruta_original);
        if (contenido.empty())
            continue;

        string tipo, numero, semestre, nombre;
        obtener_data(contenido, tipo, numero, semestre, nombre);

        bool valido = true;
        string destino_final;

        if (tipo == "certamen")
        {
            if (!esta_en(numero, CERTAMENES) || !semestre_valido(semestre))
            {
                valido = false;
            }
            else
            {
                string nueva_ruta = "OUTPUT/Certamenes/" + semestre;
                filesystem::create_directories(nueva_ruta);
                destino_final = nueva_ruta + "/C" + numero + ".txt";
            }
        }
        else if (tipo == "control")
        {
            if (!esta_en(numero, CONTROLES) || !semestre_valido(semestre))
            {
                valido = false;
            }
            else
            {
                string nueva_ruta = "OUTPUT/Controles/" + semestre;
                filesystem::create_directories(nueva_ruta);
                destino_final = nueva_ruta + "/Q" + numero + ".txt";
            }
        }
        else if (tipo == "tarea")
        {
            if (nombre.empty() || !semestre_valido(semestre))
            {
                valido = false;
            }
            else
            {
                string nueva_ruta = "OUTPUT/Tareas/" + semestre;
                filesystem::create_directories(nueva_ruta);
                destino_final = nueva_ruta + "/" + nombre + ".txt";
            }
        }
        else
        {
            valido = false;
        }

        if (!valido)
        {
            filesystem::create_directories("OUTPUT/Corruptos");
            string nombre_corrupto = entry.path().filename().string();
            destino_final = "OUTPUT/Corruptos/" + nombre_corrupto;
        }

        filesystem::rename(entry.path(), destino_final);
        cout << "Movido a: " << destino_final << endl;
    }
}

// Función que lee todos los archivos de la carpeta "General"

void leer_todos_los_archivos()
{
    string file = "General/";
    int count = 1;

    for (const auto &entry : filesystem::directory_iterator(file))
    {
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
    organizar_carpetas();

    return 0;
}
