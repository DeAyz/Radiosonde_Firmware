#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void FilterSentences(int* Zeichen) // Funktion um $GNRMC zu Filtern
{
	int* Filter;
	Filter = (int*)strstr((const char*)Zeichen, "$GNRMC");
}

int main()
{
    void FilterSentences(); //$GNRMC gefiltert
    char NMEA[];
    strcpy(NMEA, Filter);   // String: FIlter kopieren an String: NMEA + String: Filter löschen.
    //Beispielstring: char NMEA[] ="$GNRMC,132453.00,A,5125.25376,N,00645.28448,E,0.262,,130721,,,A*6F";

    if (strchr(NMEA, '-')) {  // Negatives Vorzeichen ?
        char Min[] = "-";
        int Len = strcspn(NMEA, Min);

        // Plus, Minus
        if (Len > 25) { // Vorzeichen im ersten Koordinate
            char name[10];
            int data[12];
            sscanf (NMEA, "%[^,] %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s", name, &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7], &data[8], &data[9], &data[10], &data[11], &data[12]);
            char NMEA3[10];
            char x[10];
            strncpy(x, strtok(&data[6], NMEA3), 13);
            char NMEA2[10];

            double Term1 = atof(strtok(&data[3], NMEA2+1)); // Term 1 = Latitude in float
            double Term2 = atof(&x[1]); // Term 2 = Longtitude in float
            printf("%f\n", Term1);
            printf("%f\n", Term2);

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

            // Umrechnung
            int Egg = (int)Eg;
            Egg = (Term1 / 100);
            Eg2 = (Term1 / 100);
            Eg3 = (Eg2 - Egg);
            Eg33 = Eg3 * 60;
            int Egg33 = (int)Eg33;
            Eg5 = Eg33 - Egg33;
            Eg55 = Eg5 * 60;

            if (Term1 > 0) {
                printf("%d* %d'%f N \n", Egg, Egg33, Eg55);
            } else {
                printf("%d* %d'%f S \n", Egg, Egg33, Eg55);
            }

            int EggL = (int)EgL;
            EggL = (Term2 / 100)*-1;
            EgL2 = (Term2 / 100)*-1;
            EgL3 = (EgL2 - EggL);
            EgL33 = EgL3 * 60;
            int EggL33 = (int)EgL33;
            EgL5 = EgL33 - EggL33;
            EgL55 = EgL5 * 60;

            if (Term2 < 0) {
                printf("%d* %d'%f W \n", EggL, EggL33, EgL55);
            } else {
                printf("%d* %d'%f E \n", EggL, EggL33, EgL55);
            }
        }

        // Minus, Plus
        if (Len < 25) {
            char name[10];
            int data[12];
            sscanf (NMEA, "%[^,] %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s", name, &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7], &data[8], &data[9], &data[10], &data[11], &data[12]);
            char NMEA3[10];
            char x[10];
            strncpy(x, strtok(&data[6], NMEA3), 13);
            char NMEA2[10];
            double Term1 = atof(strtok(&data[3], NMEA2+1));
            double Term2 = atof(&x[2]);
            printf("%f\n", Term1);
            printf("%f\n", Term2);

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

            int Egg = (int)Eg;
            Egg = (Term1 / 100)*-1;
            Eg2 = (Term1 / 100)*-1;
            Eg3 = (Eg2 - Egg);
            Eg33 = Eg3 * 60;
            int Egg33 = (int)Eg33;
            Eg5 = Eg33 - Egg33;
            Eg55 = Eg5 * 60;

            if (Term1 > 0) {
                printf("%d* %d'%f N \n", Egg, Egg33, Eg55);
            } else {
                printf("%d* %d'%f S \n", Egg, Egg33, Eg55);
            }
            if (Term2 < 0) {
            int EggL = (int)EgL;
            EggL = (Term2 / 100)*-1;
            EgL2 = (Term2 / 100)*-1;
            EgL3 = (EgL2 - EggL);
            EgL33 = EgL3 * 60;
            int EggL33 = (int)EgL33;
            EgL5 = EgL33 - EggL33;
            EgL55 = EgL5 * 60;

            if (Term1 < 0) {
                printf("%d* %d'%f W \n", EggL, EggL33, EgL55);
            } else {
                printf("%d* %d'%f E \n", EggL, EggL33, EgL55);
            }
            } else {
            int EggL = (int)EgL;
            EggL = (Term2 / 100);
            EgL2 = (Term2 / 100);
            EgL3 = (EgL2 - EggL);
            EgL33 = EgL3 * 60;
            int EggL33 = (int)EgL33;
            EgL5 = EgL33 - EggL33;
            EgL55 = EgL5 * 60;

            if (Term2 < 0) {
                printf("%d* %d'%f W \n", EggL, EggL33, EgL55);
            } else {
                printf("%d* %d'%f E \n", EggL, EggL33, EgL55);
            }
            }

        }

    } else {

    // Plus Plus
    char name[10];
    int data[12];
    sscanf (NMEA, "%[^,] %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s %*c %s", name, &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7], &data[8], &data[9], &data[10], &data[11], &data[12]);
    char NMEA3[10];
    char x[10];
    strncpy(x, strtok(&data[6], NMEA3), 13);
    char NMEA2[10];

    double Term1 = atof(strtok(&data[3], NMEA2+1));
    double Term2 = atof(&x[1]);
    printf("%f\n", Term1);
    printf("%f\n", Term2);

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

    int Egg = (int)Eg;
    Egg = (Term1 / 100);
    Eg2 = (Term1 / 100);
    Eg3 = (Eg2 - Egg);
    Eg33 = Eg3 * 60;
    int Egg33 = (int)Eg33;
    Eg5 = Eg33 - Egg33;
    Eg55 = Eg5 * 60;

    if (Term1 > 0) {
        printf("%d* %d'%f N \n", Egg, Egg33, Eg55);
    } else {
        printf("%d* %d'%f S \n", Egg, Egg33, Eg55);
    }
    int EggL = (int)EgL;
    EggL = (Term2 / 100);
    EgL2 = (Term2 / 100);
    EgL3 = (EgL2 - EggL);
    EgL33 = EgL3 * 60;
    int EggL33 = (int)EgL33;
    EgL5 = EgL33 - EggL33;
    EgL55 = EgL5 * 60;

    if (Term2 < 0) {
        printf("%d* %d'%f W \n", EggL, EggL33, EgL55);
    } else {
        printf("%d* %d'%f E \n", EggL, EggL33, EgL55);
    }

    }
return 0;
}
