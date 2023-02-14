#include "Fecha.cpp"
#include "Persona.cpp"

using namespace std;

int main(){

    //-----------------------------
    //al crear un objeto con un new, se crea con MEMORIA DINAMICA, para borrar es con delete
    int x = 3;
    int *y = new int; //creo un puntero en la pila, q apunta a la memoria dinamica (heap)
    *y = 3; // al contenido de ese puntero le añado el valor 3
    *y = x; //el contenido de y apunta al contenido de x (osea tambien vale 3)

    //------------------------------

    Fecha a1[3];//array normal de la pila
    a1[0] = Fecha [dias:9, mes:2, anyo:2023];
    a1[1] = Fecha [dias:10, mes:2, anyo:2023];
    a1[2] = Fecha [dias:11, mes:2, anyo:2023];

    Fecha *a2[3];//es un array de la pila, no es un array dinamico como a3 (no se inicializa con new)
    a2[0] = new Fecha [dias:9, mes:2, anyo:2023];
    a2[1] = new Fecha [dias:10, mes:2, anyo:2023];
    a2[2] = new Fecha [dias:11, mes:2, anyo:2023];

    // para borrarlo borras sus posiciones
    delete a2[0];
    delete a2[1];
    delete a2[2];

    Fecha **a3 = new Fecha *[3]; // array de cosas q son punteros en memoria dinamica(new Fecha*[3])
    a3[0] = new Fecha [dias:9, mes:2, anyo:2023];
    a3[1] = new Fecha [dias:10, mes:2, anyo:2023];
    a3[2] = new Fecha [dias:11, mes:2, anyo:2023];
 
    // para borrarlo hay que borrar las posiciones primero antes del array, importa el orden (es distinto xq es dianmico (new) (esta en el heap))
    delete a2[0];
    delete a2[1];
    delete a2[2];
    delete[] a3;

    Fecha *a4 = new Fecha[3]; //creas un array dinamico de fechas(pero los objetos de dentro no tienen pk ser punteros)
    a4[0] = new Fecha [dias:9, mes:2, anyo:2023];
    a4[1] = new Fecha [dias:10, mes:2, anyo:2023];
    a4[2] = new Fecha [dias:11, mes:2, anyo:2023];

    //------------------------------
    Fecha f1 = {28, 8, 2019}; // usaria el constructor por paramertros e imprime 28/08/2019

    // se puede hacer tambien: Fecha f1(28,8,2019);

    Fecha f2 = {2019}; // usa la sobrecarga de constructores e imprime 01/01/2019

    f1.set_dia(28);
    f1.set_mes(8);
    f1.set_anyo(2019);

    cout << "Fecha: ";
    f1.imprimir();
    cout << " ";
    f2.imprimir();

    if (esNavidad(f1))
    {
        cout << "Es Navidad! " << endl;
    }

    return 0;
}
