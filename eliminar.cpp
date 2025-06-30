#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    cout << "Content-type: text/html\n\n";

    string data;
    getline(cin, data);

    size_t posId = data.find("id=");
    if (posId == string::npos) {
        cout << "<p>Error: ID no recibido</p>";
        return 1;
    }

    string idStr = data.substr(posId + 3);
    ifstream archivo("C:/xampp/htdocs/agenda/agenda.txt");
    vector<string> lineas;
    string linea;

    while (getline(archivo, linea)) {
        if (!(linea.substr(0, idStr.size()) == idStr && linea[idStr.size()] == '|')) {
            lineas.push_back(linea); // Solo guardamos los que no son el que queremos eliminar
        }
    }
    archivo.close();

    ofstream salida("C:/xampp/htdocs/agenda/agenda.txt", ios::trunc);
    for (const string& l : lineas) salida << l << "\n";
    salida.close();

    cout << "<h2>Contacto eliminado correctamente</h2>";
    cout << "<a href=\"/agenda/index.html\">Volver</a>";
    return 0;
}
