// Created by NATSOFT Ronald Espitia.
#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Definición de constantes
const string UNIFIED = "unified.csv";
const string RESULT = "result.csv";
const string LOG_FILE = "output.log";
const vector<string> TITULOS = {
    "ID CONTRATO PROFESIONAL IS", "HONORARIO", "FECHA HONORARIO", "ID PACIENTE", "PLAN TARIFARIO",
    "PROCEDIMIENTO", "NOMBRE PROCEDIMIENTO", "SUBPROCEDIMIENTO", "NOMBRE SUBPROCEDIMIENTO",
    "ZONA", "UBICACIÓN", "VALOR EVOLUCION", "ESPECIALIDAD PROCEDIMIENTO", "FORMA PAGO",
    "ID PROFESIONAL", "CENTRO DE COSTO", "NIT", "CONCEPTO", "% HONORARIO", "VALOR CONTRATADO",
    "id honorario", "numero  contrato", "fecha  factura evolucion", "TIPO HONORARIO", "CLINICA",
    "ESPECIALIDAD PROFESIONAL", "NOMBRE PROFESIONAL", "CLASE NOMINA", "CONCEPTO HOMOLOGADO", "FECHA DEV"
};


// Función para obtener la fecha y hora actual en formato string
string getCurrentDateTime()
{
    time_t now = time(0); // Obtener el tiempo actual
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);                                // Convertir a hora local
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct); // Formatear la fecha y hora
    return string(buf);
}

// Buffer personalizado para agregar fecha y hora
class LogBuffer : public streambuf
{
private:
    streambuf *originalBuffer;
    ofstream logFile;

public:
    LogBuffer(streambuf *buffer, const string &filename)
        : originalBuffer(buffer), logFile(filename)
    {
        if (!logFile.is_open())
        {
            throw runtime_error("No se pudo abrir el archivo de log.");
        }
    }

    ~LogBuffer()
    {
        logFile.close();
    }

protected:
    virtual int overflow(int c) override
    {
        if (c == '\n')
        {
            // Agregar la fecha y hora antes de la nueva línea
            logFile << " - " << getCurrentDateTime() << endl;
        }
        else
        {
            logFile << static_cast<char>(c);
        }
        return originalBuffer->sputc(c);
    }
};

// Implementación de la función exe1
void exe1() {
// Abrir el archivo de log
    ofstream logFile(LOG_FILE);
    if (!logFile.is_open())
    {
        cerr << "Error al abrir el archivo de log: " << LOG_FILE << endl;
        return;
    }

    // Crear el buffer personalizado
    LogBuffer logBuffer(cout.rdbuf(), LOG_FILE);

    // Redirigir cout y cerr al buffer personalizado
    streambuf *coutBuffer = cout.rdbuf(); // Guardar el buffer original de cout
    streambuf *cerrBuffer = cerr.rdbuf(); // Guardar el buffer original de cerr
    cout.rdbuf(&logBuffer);               // Redirigir cout al buffer personalizado
    cerr.rdbuf(&logBuffer);               // Redirigir cerr al buffer personalizado
    vector<tuple<string, string, bool>> archivos = {
        {"GARDNom.csv", "GARANTIAS NEGATIVAS", true},
        {"HNENom.csv", "HONORARIOS NEGATIVOS", true},
        {"HONNom.csv", "HONORARIOS POSITIVOS", false},
        {"GARPNom.csv", "GARANTIAS POSITIVAS", false}
    };
    vector<string> allData;
    vector<vector<string>> datos;
    vector<string> result;
    vector<vector<string>> vectorDeVectores;

    for (const auto& archivo : archivos) {
        string fileName = get<0>(archivo);
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error al leer el archivo: " << fileName << endl;
            continue;
        }

        string linea;
        while (getline(file, linea)) {
            vector<string> elementos;
            istringstream stream(linea);
            string token;

            while (getline(stream, token, ';')) {
                elementos.push_back(token);
            }

            vector<string> nuevosElementos = {"a1", "a2", "a3", "a4", "a5"};
            if (elementos.size() == 22) {
                string valor = elementos[18];
                elementos.push_back(get<1>(archivo));
                elementos.erase(elementos.begin() + 18);
                elementos.insert(elementos.begin() + 6, "");
                elementos.insert(elementos.begin() + 8, "");
                elementos.push_back(valor);
                elementos.insert(elementos.begin() + 24, nuevosElementos.begin(), nuevosElementos.end());
            } else if (elementos.size() == 21) {
                elementos.push_back(get<1>(archivo));
                elementos.insert(elementos.begin() + 6, "");
                elementos.insert(elementos.begin() + 8, "");
                elementos.emplace_back("_");
                elementos.insert(elementos.begin() + 24, nuevosElementos.begin(), nuevosElementos.end());
            }

            datos.push_back(elementos);
        }
        file.close();
    }

    datos.insert(datos.begin(), TITULOS);

    ofstream archivo(RESULT);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << RESULT << endl;
    }

    for (const auto& linea : datos) {
        for (size_t i = 0; i < linea.size(); ++i) {
            archivo << linea[i];
            if (i < linea.size() - 1) {
                archivo << ";";
            }
        }
        archivo << "\n";
    }
    archivo.close();
    cout << "Archivo CSV guardado correctamente: " << RESULT << endl;
}
