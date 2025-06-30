#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

// Cargar banderas por país ISO desde paises.txt
map<string, string> cargarBanderas(const string& archivo) {
    map<string, string> banderas;
    ifstream file(archivo);
    if (!file.is_open()) return banderas;

    string linea;
    while (getline(file, linea)) {
        size_t pos = linea.find('=');
        if (pos != string::npos) {
            string pais = linea.substr(0, pos);     // PE, US, MX...
            string bandera = linea.substr(pos + 1); // 🇵🇪
            banderas[pais] = bandera;
        }
    }
    return banderas;
}

int main() {
    cout << "Content-type: text/html\n\n";

    map<string, string> banderas = cargarBanderas("C:/xampp/htdocs/agenda/paises.txt");

    ifstream archivo("C:/xampp/htdocs/agenda/agenda.txt");
    if (!archivo.is_open()) {
        cout << "<p>Error al abrir agenda.txt</p>";
        return 1;
    }

    cout << "<table border='1' cellpadding='8' cellspacing='0' style='width:100%; border-collapse: collapse; background-color: #fdfdfd;'>";
    cout << "<tr style='background-color:#e0e0e0'><th>ID</th><th>Nombre</th><th>Teléfono</th><th>Acciones</th></tr>";

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, nombre, pais, telefono;

        getline(ss, id, '|');
        getline(ss, nombre, '|');
        getline(ss, pais, '|');
        getline(ss, telefono);

        string bandera = banderas.count(pais) ? banderas[pais] + " " : "";

        cout << "<tr>";
        cout << "<td>" << id << "</td>";
        cout << "<td>" << nombre << "</td>";
        cout << "<td>" << bandera << telefono << "</td>";
        cout << "<td class='acciones'>";
        cout << "<button style='background-color:#f39c12;color:white;border:none;padding:5px 10px;border-radius:4px;cursor:pointer;'"
             << " onclick=\"abrirModalEditar(" << id << ", '" << nombre << "', '" << pais << "', '" << telefono << "')\">Editar</button>";
        cout << "<form method='POST' action='/cgi-bin/eliminar.cgi' style='display:inline;'>"
             << "<input type='hidden' name='id' value='" << id << "'>"
             << "<button type='submit' style='background-color:#e74c3c;color:white;border:none;padding:5px 10px;border-radius:4px;cursor:pointer;'"
             << " onclick=\"return confirm('¿Eliminar contacto " << nombre << "?')\">Eliminar</button></form>";
        cout << "</td></tr>";
    }

    cout << "</table>";
    archivo.close();
    return 0;
}
