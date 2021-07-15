#include <iostream>
#include <string>



using namespace std;

// Lat 8 chars = DDDMM.MMMM 
// Lng 9 chars = DDDMM.MMMM



void FilterSentences(int* Zeichen)
{
	int* Filter;
	Filter = (int*)strstr((const char*)Zeichen, "$GNRMC");
}


int main() {

	/* Vom Lese Daten Register


	USART->DR = temp;
	.
	.
	.
	 Eingabe zum konverter
*/



	/* $GNRMC Rausfiltern */

	void FilterSentences();


	/* ASCII to float */


	/* TO DO :
		- CrossStudio Code Implementieren
		- In C umschreiben */



	int RMC = temp.find('NRM');


	if (RMC >= 0) {

		do {

			

			
			
			//string NMEA = "$GNRMC,132453.00,A,3341.41385,N,-00755.16478,E,0.262,,130721,,,A*6F<\r> < \n>"; //Test string

			int prf = NMEA.find('-');


			if (prf < 0) {				// Vorzeichen prüfen bei Latitude und Longtitude



				//cout << "Start: " << NMEA << endl;
				//cout << endl;

				NMEA.erase(NMEA.find('$'), NMEA.find(','));		// Löschen: $GNRMC 

				int A = NMEA.find('A');
				int V = NMEA.find('V');

				if (A <= 12) {									// If Status A oder V
					NMEA.erase(NMEA.find(','), NMEA.find('A'));	// Löschen: UTC time + Status
				}
				else {
					NMEA.erase(NMEA.find(','), NMEA.find('V')); // Löschen: UTC time + Status
				}
				NMEA.erase(0, 2);								// Löschen: Status
				NMEA.erase(10, 3);								// Löschen: letzte Ziffer Lat + indicator 
				string Lat = NMEA.substr(0, 9);					// Kopieren: Latitude ín einem neuen String
				NMEA.erase(0, 10);								// Löschen: Latitude
				NMEA.erase(18, 4);								// Löschen: Letzte Ziffer Lng + indicator

				string Lng = NMEA.substr(0, 10);					// Kopieren: Longtitude in einem neuen String

				//cout << "LAT: " << Lat << endl;
				//cout << "LNG: " << Lng << endl;

				NMEA.clear();									// String leeren
				cout << endl;

				/* float to Latitude */

				int LaG;
				double GLaG;
				double Eg;
				double Eg2;
				int Eg22;
				double Eg3;
				double Eg33;
				int Eg4;
				double Eg5;
				double Eg55;


				int LnG;
				double GLnG;
				double EgL;
				double EgL2;
				int EgL22;
				double EgL3;
				double EgL33;
				int EgL4;
				double EgL5;
				double EgL55;

				/* float to Longtitude */

				LaG = atof(Lat.c_str());
				GLaG = atof(Lat.c_str());


				Eg = LaG / 100;
				cout.precision(8);
				Eg2 = GLaG / 100;
				cout.precision(8);

				Eg3 = Eg2 - Eg;
				cout.precision(8);

				Eg33 = Eg3 * 60;
				cout.precision(8);
				Eg4 = Eg33;
				cout.precision(8);

				Eg5 = Eg33 - Eg4;
				cout.precision(8);


				Eg55 = Eg5 * 60;
				cout.precision(8);


				if (GLaG > 0) {

					cout << "Laengengrad: " << Eg << "* " << Eg4 << "'" << Eg55 << " N" << endl;
				}
				else {
					cout << "Laengengrad" << Eg << "* " << Eg4 << "'" << Eg55 << " S" << endl;
				}


				LnG = atof(Lng.c_str());
				GLnG = atof(Lng.c_str());

				EgL = LnG / 100;
				cout.precision(8);
				EgL2 = GLnG / 100;
				cout.precision(8);

				EgL3 = EgL2 - EgL;
				cout.precision(8);

				EgL33 = EgL3 * 60;
				cout.precision(8);
				EgL4 = EgL33;
				cout.precision(8);

				EgL5 = EgL33 - EgL4;
				cout.precision(8);


				EgL55 = EgL5 * 60;
				cout.precision(8);


				if (GLnG > 0) {

					cout << "Breitengrad: " << EgL << "* " << EgL4 << "'" << EgL55 << " E" << endl;
				}
				else {
					cout << "Breitengrad" << EgL << "* " << EgL4 << "'" << EgL55 << " W" << endl;
				}


			}
			else {
				int Min = NMEA.find('-');
				int Min2 = NMEA.find_last_of('-');

				if (NMEA.find('-')) {
					for (int i = 0; i < NMEA.length(); i++) {
						while (NMEA.find("-") != string::npos) {
							NMEA.replace(NMEA.find("-"), 1, "");
						}
					}
				}

				//cout << "Start: " << NMEA << endl;
				//cout << endl;

				NMEA.erase(NMEA.find('$'), NMEA.find(','));		// Löschen: $GNRMC 

				int A = NMEA.find('A');
				int V = NMEA.find('V');

				if (A <= 12) {										// If Status A oder V
					NMEA.erase(NMEA.find(','), NMEA.find('A'));		// Löschen: UTC time
				}
				else {
					NMEA.erase(NMEA.find(','), NMEA.find('V'));
				}
				NMEA.erase(0, 2);								// Löschen: Status
				NMEA.erase(10, 3);								// Löschen: Letzte Ziffer Laz + indicator 
				string Lat = NMEA.substr(0, 9);					// Kopieren: Latitude ín einem neuen String
				NMEA.erase(0, 10);								// Löschen: Latitude
				NMEA.erase(18, 4);								// Löschen: Letzte Ziffer Lng + inidcator 
				string Lng = NMEA.substr(0, 10);				// Kopieren: Longtitude in einem neuen String

				//cout << "LAT: " << Lat << endl;
				//cout << "LNG: " << Lng << endl;

				NMEA.clear();									// String leeren
				cout << endl;





				/* float to Latitude */

				int LaG;
				double GLaG;
				double Eg;
				double Eg2;
				int Eg22;
				double Eg3;
				double Eg33;
				int Eg4;
				double Eg5;
				double Eg55;


				int LnG;
				double GLnG;
				double EgL;
				double EgL2;
				int EgL22;
				double EgL3;
				double EgL33;
				int EgL4;
				double EgL5;
				double EgL55;

				/* float to Longtitude */

				LaG = atof(Lat.c_str());
				GLaG = atof(Lat.c_str());


				Eg = LaG / 100;
				cout.precision(8);
				Eg2 = GLaG / 100;
				cout.precision(8);

				Eg3 = Eg2 - Eg;
				cout.precision(8);

				Eg33 = Eg3 * 60;
				cout.precision(8);
				Eg4 = Eg33;
				cout.precision(8);

				Eg5 = Eg33 - Eg4;
				cout.precision(8);


				Eg55 = Eg5 * 60;
				cout.precision(8);




				if (Min > 20) {			// If Vorzeichen bei Latitude

					cout << "Laengengrad: " << Eg << "* " << Eg4 << "'" << Eg55 << " N" << endl;
				}
				else {
					cout << "Laengengrad: " << Eg << "* " << Eg4 << "'" << Eg55 << " S" << endl;
				}


				LnG = atof(Lng.c_str());
				GLnG = atof(Lng.c_str());

				EgL = LnG / 100;
				cout.precision(8);
				EgL2 = GLnG / 100;
				cout.precision(8);

				EgL3 = EgL2 - EgL;
				cout.precision(8);

				EgL33 = EgL3 * 60;
				cout.precision(8);
				EgL4 = EgL33;
				cout.precision(8);

				EgL5 = EgL33 - EgL4;
				cout.precision(8);


				EgL55 = EgL5 * 60;
				cout.precision(8);

				GLnG = GLnG * (-1);

				if (Min2 < 20) {				// IF Vorzeichen Longtitude

					cout << "Breitengrad: " << EgL << "* " << EgL4 << "'" << EgL55 << " E" << endl;
				}
				else {
					cout << "Breitengrad: " << EgL << "* " << EgL4 << "'" << EgL55 << " W" << endl;
				}


				system("pause>0");
			}

		} while (1);

	} 
	cout << "Invalide Data" << endl;

}