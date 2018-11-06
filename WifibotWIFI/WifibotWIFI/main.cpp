#include <stdio.h>
#include <stdlib.h>


#include "Robot_Fonction.h"
#include "WifibotClient.h"


void main(void)
{
	/*.........................*/
	/* Connection to the robot */
	/*.........................*/
	Robot_Connexion();
	updatesensors();//mise à jour des capteurs + des coordonées
	double x1 = getx(&pos);
	
	

	/*..............*/
	/* Main program */
	/*..............*/
	while(1)
	{
		Robot_Avancer(100, 100);
		updatesensors();//mise à jour des capteurs + des coordonées
		

		if (abs((long)getx(&pos))> 30000 ) {
			Robot_Arreter;
			while(1){}//lol
			
		}
		
		if(Robot_obstacleDroite()) {
			Robot_Tourner_Gauche(0, 50);
			/*Robot_Tourner_Gauche_avec_tick(50,-50,2000);
			Robot_Avancer_avec_tick(50, 50, 5000);
			Robot_Tourner_Droite_avec_tick(-50, 50, 2000);*/
			
		}
		
		if (Robot_obstacleGauche()) {
			Robot_Tourner_Droite(50, 0);
			/*Robot_Tourner_Droite_avec_tick(-50, 50, 2000);
			Robot_Avancer_avec_tick(50, 50, 5000);
			Robot_Tourner_Gauche_avec_tick(50, -50, 2000);*/
			
		}
		//system("cls");
		Sleep(100);
	}	
}



