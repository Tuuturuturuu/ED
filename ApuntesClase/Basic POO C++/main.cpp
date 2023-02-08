#include "Fecha.cpp"
#include "Persona.cpp"

using namespace std;

int main(){
        Fecha f1 = {28,8,2019};//usaria el constructor por paramertros e imprime 28/08/2019

        //se puede hacer tambien: Fecha f1(28,8,2019);

        Fecha f2 = {2019};//usa la sobrecarga de constructores e imprime 01/01/2019

        f1.set_dia(28);
        f1.set_mes(8);
        f1.set_anyo(2019);

        cout << "Fecha: ";
        f1.imprimir();
        cout << " ";
        f2.imprimir();

        if(esNavidad(f1)){
            cout << "Es Navidad! "<< endl;
        }
        return 0;
    }
