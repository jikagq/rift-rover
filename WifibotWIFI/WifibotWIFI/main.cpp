#include <stdio.h>
#include <stdlib.h>


#include "Robot_Fonction.h"
#include "WifibotClient.h"

UINT16 vitesse_gauche=100;
UINT16 vitesse_droite=101;

bool flag = false;
long x_test = 0;

int SharpLUT[] = { 150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,103,102,101,100,99,
		  96,95,90,88,87,86,85,84,83,82,81,80,79,77,75,74,73,72,71,70,69,68,67,66,65,65,64,64,63,62,61,61,60,60,59,59,58,58,57,57,56,56,56,55,55,55,54,54,54,53,
		  53,53,52,52,51,51,50,50,49,49,49,48,48,47,47,46,46,46,45,45,44,44,43,43,42,42,41,41,41,40,40,40,39,39,39,39,39,38,38,
				  38,38,37,37,37,37,36,36,36,36,35,35,35,35,34,34,34,34,34,34,33,33,33,33,32,32,32,32,32,31,31,31,31,30,30,30,30,30,30,30,
		  30,29,29,29,29,29,29,29,28,28,28,28,28,28,27,27,27,27,27,27,27,26,26,26,26,25,25,25,25,25,25,24,24,24,24,24,23,23,23,
		  23,23,23,22,22,22,22,22,21,21,21,21,21,21,20,20,20,20,19,19,19,19,19,19,18,18,18,18,18,18,17,17,17,16,16,15,15 };

void main(void)
{
	/*.........................*/
	/* Connection to the robot */
	/*.........................*/
	Robot_Connexion();//connection au robot
	inistruc(&pos);//initialisation de la structure à 0
	updatesensors();//mise à jour des capteurs + des coordonées /*inutile ?*/
	//double x1 = getx(&pos);//sauvegarde de la 1ere valeur de x /*inutile car maintenant demarre directe à 0?*/


	/*..............*/
	/* Main program */
	/*..............*/
	while(1)
	{
		//Robot_Avancer(vitesse_gauche, vitesse_droite);
		//updatesensors();//mise à jour des capteurs + des coordonées
		

		/*if (abs((long)getx(&pos))> 30000 ) {
			Robot_Arreter;
			while(1){}//lol
			
		}*/ /*inutile car directment dans verif fonction et update sensor*/
		
		/*if(Robot_obstacleDroite()) {
			Robot_Tourner_Gauche(0, 50);
		}
		
		if (Robot_obstacleGauche()) {
			Robot_Tourner_Droite(50, 0);			
		}*/
		//system("cls");
		//Sleep(100);

		
		
		
		
		
		
		
		
		
		/*partie pirate*/
		updatesensors();//mise à jour des capteurs + des coordonées
		if ((getDistance(LEFT, SharpLUT) <= 60) && (getDistance(RIGHT, SharpLUT) <= 60))
		{
			move(0, 0);
			printf("STOP");
		}
		else if ((getDistance(LEFT, SharpLUT) <= 60) && (getDistance(RIGHT, SharpLUT) >= 60))
		{
			move(-30, 30);
			flag = true;
			//x_test = getx(&pos);
			printf("LEFT");
		}
		else if ((getDistance(LEFT, SharpLUT) >= 60) && (getDistance(RIGHT, SharpLUT) <= 60))
		{
			move(30, -30);
			flag = true;
			//x_test = getx(&pos);
			printf("RIGHT");
		}
		else if ((getDistance(LEFT, SharpLUT) > 60) || (getDistance(RIGHT, SharpLUT) > 60))
		{
			move(30, 30);
			printf("FORWARD");

			if (flag == true) {//correction

				//Sleep(500);
				/*while (x_test < x_test + 1000) {
					move(30, 30);
				}*/
				Robot_Avancer_avec_tick(50, 50, 3000);
				while ((getO(&pos) <= -4.0) || (getO(&pos) >=0)) {

					if (getO(&pos) < -0.75) {
						move(15, -15);
					}
					else {
						move(-15, 15);
					}
				
				}
				Robot_Arreter(0,0);
				flag = false;
			}
		}

		

		Sleep(100);
	}	
}



