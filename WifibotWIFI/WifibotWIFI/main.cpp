#include <stdio.h>
#include <stdlib.h>

#include "WifibotClient.h"
#include "Robot_Fonction.h"

#define IP_ADRESSE "192.168.1.75"
#define PORT	15020

WifibotClient robot;
SensorData sensors_data;
int IR_SEUIL = 100;



int SharpLUT[]={150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,103,102,101,100,99,
          96,95,90,88,87,86,85,84,83,82,81,80,79,77,75,74,73,72,71,70,69,68,67,66,65,65,64,64,63,62,61,61,60,60,59,59,58,58,57,57,56,56,56,55,55,55,54,54,54,53,
          53,53,52,52,51,51,50,50,49,49,49,48,48,47,47,46,46,46,45,45,44,44,43,43,42,42,41,41,41,40,40,40,39,39,39,39,39,38,38,
                  38,38,37,37,37,37,36,36,36,36,35,35,35,35,34,34,34,34,34,34,33,33,33,33,32,32,32,32,32,31,31,31,31,30,30,30,30,30,30,30,
          30,29,29,29,29,29,29,29,28,28,28,28,28,28,27,27,27,27,27,27,27,26,26,26,26,25,25,25,25,25,25,24,24,24,24,24,23,23,23,
          23,23,23,22,22,22,22,22,21,21,21,21,21,21,20,20,20,20,19,19,19,19,19,19,18,18,18,18,18,18,17,17,17,16,16,15,15};


void main(void)
{
	/*.........................*/
	/* Connection to the robot */
	/*.........................*/
	Robot_Connexion();


	/*..............*/
	/* Main program */
	/*..............*/
	SensorData sensors_data;
	while(1)
	{
		Robot_Avancer(255, 255);
		robot.GetSensorData(&sensors_data);
		//printf("Batterie : %d\n", sensors_data.BatVoltage);
		printf("IRLeft : %d\n", sensors_data.IRLeft);
		printf("IRRight : %d\n", sensors_data.IRRight);

		// Premier test afin de v�rifier que les capteurs d�tectent bien
		Detection_obstacle();
		
		// Deuxi�me test : D�tecter le c�t� dans lequel le robot doit aller
		if (Robot_obstacleDroite())
		{
			do
			{
				Robot_Tourner_Gauche(255, 0);
				robot.GetSensorData(&sensors_data);
			} while (Robot_obstacleDroite());
		}
		else 
		{
			do
			{
				Robot_Tourner_Droite(255, 0);
				robot.GetSensorData(&sensors_data);
			} while (Robot_obstacleGauche());
		}
		//Sleep(100);
	}	
}



