#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int Lat; //latitude_bd;					//Latitude is expanded by 100000 times, and it is actually divided by 100000
	int Lng; //nshemi_bd;						//North latitude/south latitude, N: north latitude; S: south latitude
	int IndiNS; //longitude_bd;			  //Longitude is expanded by 100000 times, and it is actually divided by 100000
	int IndiOW; //ewhemi_bd;						//East longitude/West longitude, E: East longitude; W: West longitude
}LatLan;


typedef struct
{
    float  Lat2;		//longitude
    float  Lng2;        //latitude
} E53_ST1_Data_TypeDef;

LatLan latlan;
static unsigned char gps_uart[1000];
E53_ST1_Data_TypeDef E53_ST1_Data;

int Komma(int *grade ,int x)
{
	int *a = grade;
	while(x) {
		if (*grade=='*'||*grade<' '||*grade>'z') {
                return 1;
		}
		if (*grade==',') {
                x--;
		}
		grade++;
	}
	return (grade - a);
}




int String(int a,int b)
{
	int Ergebnis = 1;
	while (b--) {
        Ergebnis *= a;
	}
	return Ergebnis;
}




int String2(int *grade, int *x)
{
	int *p = grade;
	int ires = 0,fres = 0;
	int ilen = 0,flen = 0,i;
	int mask = 0;
	int res;
	while(1)
	{
		if(*p=='-'){mask |= 0x02;p++;}//Indicates that there are negative numbers
		if(*p==','||*p=='*')break;//End character encountered
		if(*p=='.'){mask |= 0x01;p++;}//Encountered a decimal point
		else if(*p>'9'||(*p<'0'))//The number is not between 0 and 9, indicating illegal characters
		{
			ilen = 0;
			flen = 0;
			break;
		}
		if(mask&0x01)flen++;//The number of decimal places
		else ilen++;//str length plus one
		p++;//Next character
	}
	if(mask&0x02)grade++;//Move to the next place, remove the negative sign
	for(i=0;i<ilen;i++)//Get the integer part of the data
	{
		ires += NMEA_Pow(10,ilen-1-i)*(grade[i]-'0');
	}
	if(flen>5)flen=5;//Take up to five decimal places
	*dx = flen;
	for(i=0;i<flen;i++)//Get the fractional data
	{
		fres +=NMEA_Pow(10,flen-1-i)*(grade[ilen+1+i]-'0');
	}
	res = ires*NMEA_Pow(10,flen)+fres;
	if(mask&0x02)res = -res;
	return res;
}





void Stringanalyse(LatLan *grade ,int *x)
{
	int *E;
	int Bit;
	int temp;
	int Dez;
	float temp2;


	E = (int*)strstr((const char *)x, "$GPRMC");//"$GPRMC", there are often cases where & is separated from GPRMC, so only GPRMC is judged.

	Bit = Komma(E, 3);								//Get the latitude
	if (Bit != 1) {

		temp = String2 (E + Bit, &Dez);
		grade->Lat = temp / NMEA_Pow(10, Dez + 2);	//Get °
		temp2 = temp % NMEA_Pow(10, Dez +2 );				//Get'
		grade->Lat = grade->Lat * NMEA_Pow(10, 5) + (temp2* NMEA_Pow(10, 5 - Dez)) / 60;//Convert to °
	}
	Bit = Komma(E, 4);								//South latitude or north latitude
	if (Bit != 1) grade->IndiNS = *(E + Bit);
 	Bit = Komma(E, 5);								//Get longitude
	if (Bit != 1)
	{
		temp = String2 (E + Bit, &Dez);
		grade->Lng = temp / NMEA_Pow(10, Dez + 2);	//Get °
		temp2 = temp % NMEA_Pow(10, Dez + 2);				//Get'
		grade->Lng = grade->Lng * NMEA_Pow(10, 5) + (temp2 * NMEA_Pow(10, 5 - Dez)) / 60;//Convert to °
	}
	Bit = Komma(E ,6);								//East longitude or west longitude
	if (Bit != 1)grade->IndiOW = *(E + Bit);
}















int main()
{

char NMEA[] = "$GNRMC,132453.00,A,5125.25376,N,-00645.28448,E,0.262,,130721,,,A*6F<\r> < \n>";


while (1)
  {


  }
}
