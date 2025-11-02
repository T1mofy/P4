/*#include <iostream>
using namespace std;

int main() {
    int dez_zahl;
    int bit_vektor[8];

    cout << "GIB EINE ZAHL VON -255 - 255 EIN: ";
    cin >> dez_zahl;

    unsigned char y = dez_zahl;

    cout << "DIE BINARRE DARSTELLUNG IST:\n";

    for (int a = 7; a >= 0; a--) {
        int maske = 1 << a;
        int bit = (y & maske) >> a;
        bit_vektor[a] = bit;
        cout << bit_vektor[a];
    }

    cout << endl;
    return 0;
}*/

#include <iostream>
using namespace std;

void umwandlung_dez_bin(int bit_vektor[], int dez_zahl, int bit_anzahl) {
    unsigned char y = dez_zahl;

    for (int i = 0; i < bit_anzahl; i++) {
		int bit_index = bit_anzahl - 1 - i; // Index vom höchsten Bit zum niedrigsten (inklusive 0, deswegen -1)
		int maske = 1 << bit_index; // Maske für das aktuelle Bit. Verschiebung nach links um bit_index Positionen (1=000...0001, 2=000...0010, 4=000...0100, ...)
		int bit = (y & maske) >> bit_index; // Bit an die niedrigste Position verschieben
        bit_vektor[i] = bit;
    }
}
