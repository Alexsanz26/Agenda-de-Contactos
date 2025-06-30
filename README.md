# Agenda de Contactos

###### Este proyecto es una agenda de contactos moderna construida en C++ usando CGI, HTML, CSS y JavaScript. Permite agregar, editar y eliminar contactos usando formularios web y almacenamiento en archivos planos.

## Características

-  Agregar, editar y eliminar contactos
-  Selector de país con código internacional (+51, +52, etc.)
-  Contactos almacenados en archivo plano (`agenda.txt`)
-  Cada contacto tiene un `ID` único (no repetible)
-  Interfaz simple con formulario y edición modal
-  Hecho sin base de datos ni frameworks pesados

---

## Estructura del proyecto

C:/xampp/htdocs
1. agenda
1.1 index.html
1.2 agenda.txt
1.3 paises.txt
1.4 README.md
1.5 .gitignore

C:/xampp/cgi-bin
1. procesar.cpp
1.1 mostrar.cpp
1.2 editar.cpp
1.3 eliminar.cpp
1.4 *.cgi

---

## ¿Cómo ejecutar?

###### 1. Compila los archivos C++ (cpp) en cgi, por ejemplo:

`g++ -o procesar.cgi procesar.cpp`

`g++ -o mostrar.cgi mostrar.cpp`

`g++ -o editar.cgi editar.cpp`

`g++ -o eliminar.cgi eliminar.cpp`

###### Esto hace que los archivos de cgi pasen a `C:/xampp/cgi-bin/` de manera automatica.

---

## ¿Como puedo ejecutarlo completamente?

###### Teniendo todo listo, los archivos como agenda en htdocs (`C:/xampp/htdocs/agenda`) y compilar los archivos de cgi, es hora de abrir el xampp y prender el apache, de esa manera hara que funcione correctamente sin imterrupciones, si no prendes el apache en xampp no funcionara correctamente.