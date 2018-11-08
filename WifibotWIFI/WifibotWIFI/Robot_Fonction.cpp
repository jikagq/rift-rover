#include <stdio.h>
#include <stdlib.h>


#include "Robot_Fonction.h"

WifibotClient robot;
SensorData sensors_data;

/*depart en 0,0 donc test d'une augmenation des valeur de +combien ?*/
#define lim_x 25000 //limite d'arriv� au bout du couloir
#define lim_y 5000 //deplacement autoriser en y


position pos;//variable position de type pos


int IR_SEUIL = 100;/*legacy*/

double old_droite = 0;
double old_gauche = 0;

double delta_roue_droite = 0;
double delta_roue_gauche = 0;

int entraxe = 30;//mesure entraxe des roues

double cpt_x = 0;//compteur en x negatif

bool flag_correction = false;


/*legacy function*/

void Robot_Connexion()
{
	bool rep = robot.ConnectToRobot(IP_ADRESSE, PORT);
	if (rep)
	{
		printf("Connection failed...\n");
		getchar();
		return;
	}
	else
	{
		printf("Connection established...\n");

		
		//robot.GetSensorData(&sensors_data);
		//sensors_data -> OdometryLeft = 0;
		//sensors_data -> OdometryRight = 0;
	}
}

void inistruc(position *p) {/*initialisation de la structure*/
	p->O = 0;
	p->x = 0;
	p->y = 0;
}


void Robot_Avancer(UINT16 vitesse_gauche, UINT16 vitesse_droite)
{
	unsigned char flags = 128 + 32 + 64 + 16 + 1;
	robot.SendCommand(vitesse_gauche, vitesse_droite, flags);
}

void Robot_Reculer(UINT16 vitesse_gauche, UINT16 vitesse_droite)
{
	unsigned char flags = 128 + 0 + 32 + 0 + 1;
	robot.SendCommand(vitesse_gauche, vitesse_droite, flags);
}

void Robot_Tourner_Gauche(UINT16 vitesse_gauche, UINT16 vitesse_droite)
{
	unsigned char flags = 128 + 0 + 32 + 16 + 1;
	robot.SendCommand(vitesse_gauche, vitesse_droite, flags);
}

void Robot_Tourner_Droite(UINT16 vitesse_gauche, UINT16 vitesse_droite)
{
	unsigned char flags = 128 + 64 + 32 + 0 + 1;
	robot.SendCommand(vitesse_gauche, vitesse_droite, flags);
}

void Robot_Arreter(UINT16 vitesse_gauche, UINT16 vitesse_droite)
{
	unsigned char flags = 128 + 64 + 32 + 16 + 1;
	robot.SendCommand(vitesse_gauche, vitesse_droite, flags);
}

bool Robot_obstacleDroite()
{
	if (sensors_data.IRRight > IR_SEUIL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Robot_obstacleGauche()
{
	if (sensors_data.IRLeft > IR_SEUIL)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Detection_obstacle()
{
	/**while (sensors_data.IRLeft > IR_SEUIL || sensors_data.IRRight > IR_SEUIL)
	{
		Robot_Arreter(0, 0);
		robot.GetSensorData(&sensors_data);
	}**/
	
	if (sensors_data.IRLeft > IR_SEUIL || sensors_data.IRRight > IR_SEUIL) {
		return true;
	}
	else {
		return false;
	}
}


void Robot_Avancer_avec_tick(UINT16 vitesse_gauche, UINT16 vitesse_droite, int consigne_tick)/*permet d'avancer pendant un nombre de tick*/
{
	int val_tick_droite = 0;
	int val_tick_gauche = 0;
	int val_tick_droite_depart = 0;
	int val_tick_gauche_depart = 0;

	robot.GetSensorData(&sensors_data);//aquisition
	val_tick_droite = val_tick_droite_depart = sensors_data.OdometryRight;//actualisation
	val_tick_gauche = val_tick_gauche_depart = sensors_data.OdometryLeft;//actualisation

	while ((val_tick_droite < consigne_tick + val_tick_droite_depart) && (val_tick_gauche < consigne_tick + val_tick_gauche_depart)) {//tant que la consigne n'a pas �t� ateinte

		Robot_Avancer(vitesse_gauche, vitesse_droite);
		//robot.GetSensorData(&sensors_data);//aquisition
		updatesensors();//mise � jour des capteurs
		val_tick_droite = sensors_data.OdometryRight;//actualisation
		val_tick_gauche = sensors_data.OdometryLeft;//actualisation
		Sleep(100);
	}
	//Robot_Arreter(0, 0);

}

void Robot_Tourner_Gauche_avec_tick(UINT16 vitesse_gauche, UINT16 vitesse_droite, int consigne_tick)//normalement fonctionne en relatif
{
	int val_tick_droite = 0;
	int val_tick_droite_depart = 0;
	int val_tick_gauche = 0; //variable du tick mesur�
	int val_tick_gauche_depart = 0;

	robot.GetSensorData(&sensors_data);//aquisition
	val_tick_gauche = val_tick_gauche_depart = sensors_data.OdometryLeft;
	val_tick_droite = val_tick_droite_depart = sensors_data.OdometryRight;


	while ((val_tick_droite < consigne_tick + val_tick_droite_depart) && (val_tick_gauche < consigne_tick + val_tick_gauche_depart)) {

		Robot_Tourner_Gauche(vitesse_gauche, vitesse_droite);
		//robot.GetSensorData(&sensors_data);//aquisition
		updatesensors();
		val_tick_gauche = sensors_data.OdometryLeft;//actualisation
		val_tick_droite = sensors_data.OdometryRight;//actualisation
		Sleep(100);
	}
	//Robot_Arreter(0, 0);
}

void Robot_Tourner_Droite_avec_tick(UINT16 vitesse_gauche, UINT16 vitesse_droite, int consigne_tick)//normalement fonctionne en relatif
{
	int val_tick_gauche = 0; //variable du tick mesur�
	int val_tick_gauche_depart = 0;

	int val_tick_droite = 0;
	int val_tick_droite_depart = 0;

	robot.GetSensorData(&sensors_data);//aquisition
	val_tick_gauche = val_tick_gauche_depart = sensors_data.OdometryLeft;
	val_tick_droite = val_tick_droite_depart = sensors_data.OdometryRight;

	while ((val_tick_gauche < consigne_tick + val_tick_gauche_depart) && (val_tick_droite < consigne_tick + val_tick_droite_depart)) {

		Robot_Tourner_Droite(vitesse_gauche, vitesse_droite);
		//robot.GetSensorData(&sensors_data);//aquisition
		updatesensors();
		val_tick_gauche = sensors_data.OdometryLeft;//actualisation
		val_tick_droite = sensors_data.OdometryRight;//actualisation
		Sleep(100);
	}
	//Robot_Arreter(0, 0);
}

void updatesensors(void) {
	robot.GetSensorData(&sensors_data);
	printf("Batterie : %d\n", sensors_data.BatVoltage);
	printf("IRLeft : %d\n", sensors_data.IRLeft);
	printf("IRRight : %d\n", sensors_data.IRRight);
	printf("odoLeft : %d\n", sensors_data.OdometryLeft);
	printf("odoRight : %d\n", sensors_data.OdometryRight);
	
	mesure_odometre();//a chaque apel mesure des nouvelles coordon�es
	printf("x : %f\n", getx(&pos));
	printf("y : %f\n", gety(&pos));
	printf("O: %f\n", getO(&pos));


	
	//Sleep(100);
	
	verif_limites_xy(&pos);//v�rifie si le robot a atteint une limite � chaque mise � jour des coordon�es
}


//http://geonobotwiki.free.fr/doku.php?id=robotics:odometrie

/* mise a jour de la nouvelle position du robot (x, y, O)
 * par approximation d'arc de cercle */
void calcul_position_arc(position *p, double distance, double angle)
{
	/* rayon et angle de l'arc de cercle */
	double r, a;
	/* coordonn�es du centre de l'arc de cercle */
	double xo, yo;

	if (angle == 0)
	{
		p->x += distance * cos(p->O);
		p->y += distance * sin(p->O);
	}
	else
	{
		/* calcul des caract�ristiques de l'arc de cercle */
		a = angle / entraxe;
		r = distance / a;

		/* centre de l'arc de cercle */
		xo = p->x - r * sin(p->O);
		yo = p->y + r * cos(p->O);

		/* coordonnees du robot */
		p->O += a;//orientation
		p->x = xo + r * sin(p->O);//x
		p->y = yo - r * cos(p->O);//y

		//printf("x: %d y: %d O: %d\n", p->x, p->y, p->O);
	}
}

/* delta_roue_droite et delta_roue_gauche sont les distance en pulses
 * parcourue par les roues droite et gauche en un cycle */
void odometrie(position *p, double delta_roue_droite, double delta_roue_gauche)
{
	double delta_distance = 0, delta_angle = 0;

	delta_distance = (double)((delta_roue_droite + delta_roue_gauche)) / 2;
	delta_angle = (double) (delta_roue_droite - delta_roue_gauche);

	
	calcul_position_arc(p, delta_distance, delta_angle);
}

void mesure_odometre(void) {
	/*mesure la distance parcourue par les deux trains de roues*/
			

	delta_roue_droite = sensors_data.OdometryRight - old_droite;//calcul de la distance
	delta_roue_gauche = sensors_data.OdometryLeft - old_gauche;

	//printf("delta droite : %f\n", delta_roue_droite);
	//printf("delta gauche: %f\n", delta_roue_gauche);

	if ((delta_roue_droite > 500) || (delta_roue_droite > 500)) {/*fix pour filter le pic des odom�tres ? (<25000) de la distance delta au d�marrage du robot*/
		printf("bad\n");
	}
	else {
		odometrie(&pos, delta_roue_droite, delta_roue_gauche);
	}

	old_droite = sensors_data.OdometryRight;
	old_gauche = sensors_data.OdometryLeft;

	delta_roue_droite = 0;
	delta_roue_gauche = 0;
}

/*acc�s � la structure*/
double getx(position *p) {

	return p->x;
}
double gety(position *p) {

	return p->y;
}
double getO(position *p) {

	return p->O;
}

void verif_limites_xy(position *p) {/*v�rifie que le robot n'atteint pas une limite en x et en y*/

	/*remplacer tout les double en long ?*/
	/*fix pb des x negatif pour la distance*/
	if (getx(&pos) < 0) {//si x est dans les -
		/*il faut la valeur max a laquelle le robot est parti dans les n�gatifs*/
		if (getx(&pos) < cpt_x) {
			cpt_x = getx(&pos);//max en negatif ? what ?
		}//pb si une seule valeur ?
	}
	
	if ((abs((long)getx(&pos))+(abs((long)cpt_x))) > lim_x) { // � chaque passage on ajoute l'eventuelle derive en x n�gatif (cptx) au x positif
		/*fix pour arreter le robot*/
		while (1) {}//lol
	}
	
	/*detection en y*/
	/*ref en y=0 ?*/
	
	/*
	if (p->y > lim_y) {//alcove ! en positif donc +roue droite
		//Robot_Avancer(50, 150);
		vitesse_gauche = 80;
		vitesse_droite = 120;
		flag_correction = true;
	}
	
	if (p->y < (-lim_y)) {//alcove ! en negatif donc donc +roue gauche
		//Robot_Avancer(150, 50);
		vitesse_gauche =  120;
		vitesse_droite =  80;
		flag_correction = true;
	}*/

	/*fix pour la correction en y*/
	/*pansement sur une jambe de bois...*/
	/*if ((flag_correction == true) && (-20 <= p->y) && (p->y <= 20)) { //-20<0<20 -> milieu
		/*la limite y � �t� atteinte et les vitesse ont �t� modifi� donc correction de la trajectoire
		on attend que le robot atteint le milieu du couloire pour se remttre dans l'axe et remmtre les vitesses nominales
		*/
		
		// � voir avec l'orientation

		/*while (p->O != "orientation de d�part") {

		}*/


	/*	vitesse_gauche = 100;
		vitesse_droite = 101;
		flag_correction = false;// robot remis au milieu correction termin�
	}
	
	if ((p->y <= 20) && (p->y <= 20)) {

	}*/
}


int DistanceObstacle(side_IRSens side, int *LUT)/*renvoie la distance de l'obstacle grace � la look up table*/
{
	if (side == LEFT)
	{
		return LUT[sensors_data.IRLeft];
	}
	else
	{
		return LUT[sensors_data.IRRight];
	}
}

void Deplacement(int right, int left) {/**/
	unsigned char flags = 128 + 32 + ((left >= 0) ? 1 : 0) * 64 + ((right >= 0) ? 1 : 0) * 16 + 1;
	int droite, gauche;

	droite = abs((int)(255 * right / 100.f));
	gauche = abs((int)(255 * left / 100.f));
	robot.SendCommand(droite, gauche, flags);
	
	updatesensors();
	Sleep(100);

}