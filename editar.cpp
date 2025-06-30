#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Decodifica caracteres URL como %20, +, etc.
string urlDecode(const string& str) {
    string decoded;
    char ch;
    int i, ii;
    for (i = 0; i < str.length(); i++) {
        if (str[i] == '%') {
            sscanf(str.substr(i + 1, 2).c_str(), "%x", &ii);
            ch = static_cast<char>(ii);
            decoded += ch;
            i += 2;
        } else if (str[i] == '+') {
            decoded += ' ';
        } else {
            decoded += str[i];
        }
    }
    return decoded;
}

// Extraer campo desde el string completo (igual que en procesar.cpp)
string getCampo(const string& data, const string& campo) {
    size_t inicio = data.find(campo + "=");
    if (inicio == string::npos) return "";

    size_t valorInicio = inicio + campo.length() + 1;
    size_t fin = data.find("&", valorInicio);

    if (fin == string::npos)
        return urlDecode(data.substr(valorInicio));
    else
        return urlDecode(data.substr(valorInicio, fin - valorInicio));
}

int main() {
    cout << "Content-type: text/html\n\n";

    string data;
    getline(cin, data);

    string idStr = getCampo(data, "id");
    string nombre = getCampo(data, "nombre");
    string pais = getCampo(data, "pais");
    string telefono = getCampo(data, "telefono");

    if (idStr.empty() || nombre.empty() || pais.empty() || telefono.empty()) {
        cout << "<p>Error: datos incompletos</p>";
        return 1;
    }

    // Leer archivo y reemplazar solo la línea del ID indicado
    ifstream archivo("C:/xampp/htdocs/agenda/agenda.txt");
    vector<string> lineas;
    string linea;

    while (getline(archivo, linea)) {
        if (linea.substr(0, idStr.size()) == idStr && linea[idStr.size()] == '|') {
            lineas.push_back(idStr + "|" + nombre + "|" + pais + "|" + telefono);
        } else {
            lineas.push_back(linea);
        }
    }
    archivo.close();

    // Reescribir agenda actualizada
    ofstream salida("C:/xampp/htdocs/agenda/agenda.txt", ios::trunc);
    for (const string& l : lineas) {
        salida << l << "\n";
    }
    salida.close();

    cout << "<h2>Contacto actualizado correctamente</h2>";
    cout << "<a href=\"/agenda/index.html\">Volver</a>";
    return 0;
}
