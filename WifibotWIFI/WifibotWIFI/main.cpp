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
		updatesensors();//mise à jour des capteurs + des coordonées
		Robot_Avancer(255, 255);
		
		if(Robot_obstacleDroite()) {
			//Robot_Tourner_Gauche(255, 0);
			Robot_Tourner_Gauche_avec_tick(50,-50,2000);
			Robot_Avancer_avec_tick(50, 50, 5000);
			Robot_Tourner_Droite_avec_tick(-50, 50, 2000);
		}
		
		if (Robot_obstacleGauche()) {
			//Robot_Tourner_Droite(255, 0);
			Robot_Tourner_Droite_avec_tick(-50, 50, 2000);
			Robot_Avancer_avec_tick(50, 50, 5000);
			Robot_Tourner_Gauche_avec_tick(50, -50, 2000);
		}
		
		Sleep(100);
	}	
}



