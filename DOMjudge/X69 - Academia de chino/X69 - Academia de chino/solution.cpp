// Academia de Chino
// -----------------
// Estructuras de datos

// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>


using namespace std;


class AcademiaChino {
public:

    AcademiaChino() {  }

    void nuevo_estudiante(const std::string& dni, int grupo) {
        if (mapaAlumnos.count(dni)) {
            throw domain_error("Estudiante existente");
        }
        if (grupo < 1 || grupo > 6) {// !mapaGrupos.count(dni)--------------------------------puede fallar---------------------------------
            throw domain_error("Grupo incorrecto");
        }
        //añadimos al estudiante a la academia en el grupo que corresponde
        mapaGrupos[grupo].push_front(dni);
        //añadimos la informacion del alumno al maa de alumnos
        mapaAlumnos[dni].alumnoEnGrupo = mapaGrupos[grupo].begin();
        mapaAlumnos[dni].grupo = grupo;
    }

    int grupo_estudiante(const std::string& dni) const {
        if (!mapaAlumnos.count(dni)) {
            throw domain_error("Estudiante no existente");
        }
        if (mapaAlumnos.at(dni).grupo == 7) {//asi o mayor que 6?----------------------------------------------------
            throw domain_error("Estudiante ya graduado");
        }
        return mapaAlumnos.at(dni).grupo;
    }


    void promocionar(const std::string& dni) {
        if (!mapaAlumnos.count(dni)) {
            throw domain_error("Estudiante no existente");
        }
        if (mapaAlumnos[dni].grupo == 7) {//asi o mayor que 6?----------------------------------------------------
            throw domain_error("Estudiante ya graduado");
        }

        //eliminar al estudiante del grupo en el que estaba
        int& grupo = mapaAlumnos[dni].grupo;
        mapaGrupos[grupo].erase(mapaAlumnos[dni].alumnoEnGrupo);

        //añadir el alumno a la clase superior en el mapa de grupos
        mapaGrupos[grupo + 1].push_front(dni);
        mapaAlumnos[dni].alumnoEnGrupo = mapaGrupos[grupo + 1].begin();

        //actualizas el grupo de estudiante en el mapa de Almunos
        mapaAlumnos[dni].grupo = grupo + 1;
    }

    list<std::string> graduados() const {//alfabeticamente bruh
        if (!mapaGrupos.count(7) || mapaGrupos.at(7).empty()) {
            throw domain_error("Grupo vacio");
        }
        list<string>  listaGraduados;
        for (auto it = mapaGrupos.at(7).begin(); it != mapaGrupos.at(7).end(); ++it) {
            listaGraduados.push_back(*it);
        }

        listaGraduados.sort(); // N*logN

        return listaGraduados;
    }

    std::string novato(int grupo) const {
        if (!mapaGrupos.count(grupo)) {
            throw domain_error("Grupo vacio");
        }
        if (grupo < 1 || grupo > 6) {// !mapaGrupos.count(dni)--------------------------------puede fallar---------------------------------
            throw domain_error("Grupo incorrecto");
        }
        if (mapaGrupos.at(grupo).empty()) {
            throw domain_error("Grupo vacio");
        }
        return mapaGrupos.at(grupo).front();
    }

private:
    struct infoAlumno {
        int grupo = 1;//se inicializa a 1, pues el primer grupo
        list<string>::iterator alumnoEnGrupo;
    };
    //la clave es el numero del curso (del 1 al 7 siendo 7 los alumnos ya graduados) y el valior una lista de los dnis de 
    //aquellso alumnos que pertenezcan al curso
    map<int, list<string>> mapaGrupos;

    //almacena todos los alumnos que atienden;han atendido la academia siendo la clave es el dni de los alumnos
    //y el valor el curso al que ertenecen (siendo este 7 si ya estangraduados)
    unordered_map<string, infoAlumno> mapaAlumnos;

};



bool tratar_caso() {
    AcademiaChino ac;
    string comando;
    cin >> comando;
    if (cin.eof()) return false;

    while (comando != "FIN") {
        try {
            if (comando == "nuevo_estudiante") {
                string dni;
                int grupo;
                cin >> dni >> grupo;
                ac.nuevo_estudiante(dni, grupo);
            }
            else if (comando == "grupo_estudiante") {
                string dni;
                cin >> dni;
                int grupo = ac.grupo_estudiante(dni);
                cout << dni << " esta en el grupo " << grupo << "\n";
            }
            else if (comando == "promocionar") {
                string dni;
                cin >> dni;
                ac.promocionar(dni);
            }
            else if (comando == "graduados") {
                list<string> graduados = ac.graduados();
                cout << "Lista de graduados:";
                for (const string& s : graduados) {
                    cout << " " << s;
                }
                cout << "\n";
            }
            else if (comando == "novato") {
                int grupo;
                cin >> grupo;
                string novato = ac.novato(grupo);
                cout << "Novato de " << grupo << ": " << novato << "\n";
            }
        }
        catch (std::domain_error& e) {
            cout << "ERROR: " << e.what() << "\n";
        }

        cin >> comando;
    }
    cout << "---\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}