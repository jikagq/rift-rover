/*https://github.com/jikagq/rift-rover*/
#include <stdio.h>
#include <stdlib.h>



#include "Robot_Fonction.h"
#include "WifibotClient.h"

bool flag = false; //permets de savoir si on vient d'éviter un obstacle
//long x_test = 0;

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
	inistruc(&pos);//initialisation de la structure xyO à 0
	updatesensors();//mise à jour des capteurs + des coordonées /*inutile ?*/
	//double x1 = getx(&pos);//sauvegarde de la 1ere valeur de x /*inutile car maintenant demarre directe à 0?*/



	/*..............*/
	/* Main program */
	/*..............*/

	while(1)
	{
		updatesensors();//mise à jour des capteurs + des coordonées
		if ((DistanceObstacle(LEFT, SharpLUT) <= 70) && (DistanceObstacle(RIGHT, SharpLUT) <= 70))
		{
			Deplacement(0, 0);
			printf("stop");
		}
		else if ((DistanceObstacle(LEFT, SharpLUT) <= 70) && (DistanceObstacle(RIGHT, SharpLUT) >= 70))
		{
			Deplacement(-30, 30);
			flag = true;//si le robot à tourner c'est que il a detecté un osbtacle
			//x_test = getx(&pos);
			printf("gauche");
		}
		else if ((DistanceObstacle(LEFT, SharpLUT) >= 70) && (DistanceObstacle(RIGHT, SharpLUT) <= 70))
		{
			Deplacement(30, -30);
			flag = true;//si le robot à tourner c'est que il a detecté un osbtacle
			//x_test = getx(&pos);
			printf("droite");
		}
		else if ((DistanceObstacle(LEFT, SharpLUT) > 70) || (DistanceObstacle(RIGHT, SharpLUT) > 70))
		{
			Deplacement(30, 30);
			printf("avance");
			//une fois que les capteur ne detecte plus rien le robot avance
			if (flag == true) {//si le robot à tourner c'est que il a detecté un osbtacle

				//Sleep(500);
				/*while (x_test < x_test + 1000) {
					Deplacement(30, 30);
				}*/
				Robot_Avancer_avec_tick(50, 50, 3000);//donc on contourne l'obstacle pendant 3000 tick
				while ((getO(&pos) <= -4.0) || (getO(&pos) >=0)) { // au démarage l'orientation est fixé à -0.75
					/*si le robot tourne son orientation sera modifiée*/
					/*le robot va tourner sur lui meme tant qu'il ne retombe pas dans une plage d'orientation incluant 0.75*/

					if (getO(&pos) < -0.75) {
						Deplacement(15, -15);//soit à gauche
					}
					else {
						Deplacement(-15, 15);//soit à droite
					}
				
				}
				Robot_Arreter(0,0);
				flag = false;//lorsque l'obstacle est dépasser le robot reprend son chemin
			}
		}

		

		Sleep(100);

	}	
}



