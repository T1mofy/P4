#include <iostream>
#include <cmath>
using namespace std;

/*
* Aufgabe 4a.1:
*
* Beschreibung:	Funktion zur Umwandlung einer Dezimalzahl
*				in binдre Darstellung.
*
* Ьbergabearameter:
* bit_vektor	-	Ergebnisarray, das die einzelnen Bits der Binдrzahl enthдlt
*					Das hцchstwertige Bit steht an der Stelle bit_vektor[0]
* dez_zahl		-	die umzuwandelnde Dezimalzahl
* bit_anzahl	-	Anzahl der Bits fьr die binдrere Darstellung
*
*/
void umwandlung_dez_bin(int bit_vektor[], int dez_zahl, int bit_anzahl) {
	unsigned char y = dez_zahl;

	for (int i = 0; i < bit_anzahl; i++) {
		int bit_index = bit_anzahl - 1 - i; // Index vom höchsten Bit zum niedrigsten (inklusive 0, deswegen -1)
		int maske = 1 << bit_index; // Maske für das aktuelle Bit. Verschiebung nach links um bit_index Positionen (1=000...0001, 2=000...0010, 4=000...0100, ...)
		int bit = (y & maske) >> bit_index; // Bit an die niedrigste Position verschieben
		bit_vektor[i] = bit;
	}
}

/*
* Aufgabe 4a.2:
*
* Beschreibung:	Gibt einen Vektor auf der Konsole aus.
*
* Ьbergabeparameter:
* bin_zahl		-	Array aus den Bitstellen einer Binдrzahl
* anzahl_bits	-	Anzahl der Bits, die ausgegeben werden sollen
*
*/
void ausgabe(int bin_zahl[], int anzahl_bits) {

	for (int i = 0; i < anzahl_bits; i++) {
		std::cout << bin_zahl[i];
	}
	std::cout << endl;
}



/*
* Aufgabe 4b:
*
* Beschreibung:	Funktion zur Berechnung der Ausgangsspannung
*				eines 4-Bit DA-Wandlers.
*
* Ьbergabeparameter:
* belegung_dez	- Belegung der Ausgдnge des ICs als Dezimalzahl
* R_IC			- Widerstдnde an den Ausgдngen des ICs (Ohm)
*
* Rьckgabe:
* Ausgangsspannung des 4-Bit DA-Wandlers
*
*/
double da_wandler(int belegung_dez, double R_IC[]) {
	const double U_in = 3.3;

	if (belegung_dez == 0) return 0.0;
	if (belegung_dez == 15) return U_in;

	double inv_R_high = 0.0;
	double inv_R_low = 0.0;

	for (int i = 0; i < 4; i++) { //4 bits
		int bit_index = 3 - i;
		int maske = 1 << bit_index;
		if (belegung_dez & maske) {
			inv_R_high = inv_R_high + 1.0 / R_IC[i];
		}
		else {
			inv_R_low += 1.0 / R_IC[i];
		}
	}

	double R_high = 1.0 / inv_R_high;
	//cout << "R_high: " << R_high << endl;
	//system("pause");
	double R_low = 1.0 / inv_R_low;
	//cout << "R_low: " << R_low << endl;
	//system("pause");

	double U_out = (R_low / (R_high + R_low)) * U_in;
	return U_out;
}

int main() {
	// ****************************************************************************************
	// Teilaufgabe 4a - Umwandlung und Ausgabe
	cout << "============================ Aufgabe 4a ============================\n" << endl;
	int dezimalzahl;
	cout << "Geben Sie eine Dezimalzahl ein: ";
	cin >> dezimalzahl;
	cout << endl;

	const int anzahl_bits = 8;
	int ergebnis[anzahl_bits];
	umwandlung_dez_bin(ergebnis, dezimalzahl, anzahl_bits);

	cout << "Die Zahl in 8-Bit Binaerdarstellung ist: ";
	ausgabe(ergebnis, anzahl_bits);
	cout << endl << endl;
	cout << "========================= Ende Aufgabe 4a ==========================\n" << endl;
	// ****************************************************************************************

	// ****************************************************************************************
	// Teilaufgabe 4b - 4-Bit DA-Wandler
	cout << "\n============================ Aufgabe 4b ============================\n" << endl;
	// Ausgangsspannug des DA-Wandlers (V)
	double U_out = 0.0;

	// Einlesen von 4 Werten fьr die Widerstдnde
	double R_IC[4];
	cout << "Geben Sie die vier Widerstaende an." << endl;
	for (int i = 0; i < 4; i++) {
		cout << "\t R_IC[" << i << "]: ";
		cin >> R_IC[i];
	}
	cout << endl;

	// Ausgangsbelegung des ICs
	int ausgang_IC[4] = { 0 };

	// Ausgabe der Spannungswerte fьr jede Belegung
	cout << "Belegung (dezimal) \tBelegung (binaer) \tAusgangsspannung (V) \n";

	// Iteration ьber alle mцglichen Belegungen des 4-Bit DA-Wandlers
	for (int i = 0; i < 16; i++) {
		// 1. Spalte: Ausgabe der Belegung als Dezimalzahl
		cout << i << "\t\t\t";

		// 2. Spalte: Ausgabe der Belegung als Binдrzahl
		// Umwandlung der Belegung in Binдrzahl
		umwandlung_dez_bin(ausgang_IC, i, 4);
		ausgabe(ausgang_IC, 4);
		cout << "\t\t";

		// 3. Spalte: Ausgabe der Ausgangsspannung des DA-Wandlers
		// Funktion da_wandler aufrufen
		U_out = da_wandler(i, R_IC);
		cout  << "\t\t\t\t\t"  << U_out  << endl;
	}
	cout << "\n========================= Ende Aufgabe 4b ==========================\n" << endl;
	// ****************************************************************************************

	system("pause");
	return 0;
}