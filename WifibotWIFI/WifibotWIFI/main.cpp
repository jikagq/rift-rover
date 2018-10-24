#include <stdio.h>
#include <stdlib.h>

#include "WifibotClient.h"
#include "Robot_Fonction.h"

#define IP_ADRESSE "192.168.1.75"
#define PORT	15020

void main(void)
{
	/*.........................*/
	/* Connection to the robot */
	/*.........................*/
	Robot_Connexion();


	/*..............*/
	/* Main program */
	/*..............*/
	while(1)
	{
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		/**Robot_Avancer(255, 255);
		robot.GetSensorData(&sensors_data);
		//printf("Batterie : %d\n", sensors_data.BatVoltage);
		printf("IRLeft : %d\n", sensors_data.IRLeft);
		printf("IRRight : %d\n", sensors_data.IRRight);

		// Premier test afin de vérifier que les capteurs détectent bien
		Detection_obstacle();
		
		// Deuxième test : Détecter le côté dans lequel le robot doit aller
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
		//Sleep(100);**/
	}	
}



