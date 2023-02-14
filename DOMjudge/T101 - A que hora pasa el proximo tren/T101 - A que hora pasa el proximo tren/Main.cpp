#include "Horas.h"

using namespace std;

void solve(Horas h, Horas horarios[], int n) {
	int i = 0; //bueno, implementamos una busqueda binaria q lo resuelva
	while (i < n) {
		if (h < horarios[i]) {
			cout << horarios[i];
			return;
		}

		i++;
	}
	
}

int main() {
	int n, m;
	Horas h[1000];
	Horas aux;

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> h[i];
	}
	for (int j = 0; j < m; j++) {
		cin >> aux;
		solve(aux, h, n);
	}

}