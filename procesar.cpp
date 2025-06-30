#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

// Extraer valor de un campo por nombre (ej: nombre, pais, telefono)
string getCampo(const string& data, const string& campo) {
    size_t inicio = data.find(campo + "=");
    if (inicio == string::npos) return "";

    size_t valorInicio = inicio + campo.length() + 1;
    size_t fin = data.find("&", valorInicio);

    if (fin == string::npos)
        return urlDecode(data.substr(valorInicio)); // último campo
    else
        return urlDecode(data.substr(valorInicio, fin - valorInicio));
}

int main() {
    cout << "Content-type: text/html\n\n";

    string data;
    getline(cin, data);

    string nombre = getCampo(data, "nombre");
    string pais = getCampo(data, "pais");
    string telefono = getCampo(data, "telefono");

    if (nombre.empty() || pais.empty() || telefono.empty()) {
        cout << "<h2>Error: datos incompletos</h2>";
        cout << "<a href=\"/agenda/index.html\">Volver</a>";
        return 1;
    }

    // Obtener nuevo ID
    ifstream lector("C:/xampp/htdocs/agenda/agenda.txt");
    int id = 0;
    string linea;
    while (getline(lector, linea)) {
        if (!linea.empty()) id++;
    }
    lector.close();

    // Guardar contacto
    ofstream archivo("C:/xampp/htdocs/agenda/agenda.txt", ios::app);
    archivo << id << "|" << nombre << "|" << pais << "|" << telefono << "\n";
    archivo.close();

    cout << "<h2>Contacto agregado correctamente</h2>";
    cout << "<a href=\"/agenda/index.html\">Volver</a>";
    return 0;
}
