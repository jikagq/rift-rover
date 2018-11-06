#include <stdio.h>
#include <stdlib.h>

#include "Robot_Fonction.h"

WifibotClient robot;
SensorData sensors_data;

/*depart en 0,0 donc test d'une augmenation des valeur de +combien ?*/
#define lim_x 10000
#define lim_y 500


position pos;//variable position de type pos


int IR_SEUIL = 100;

double old_droite = 0;
double old_gauche = 0;

double delta_roue_droite = 0;
double delta_roue_gauche = 0;

int entraxe = 30;//mesure entraxe des roues
int cpt = 0;


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
		inistruc(&pos);
		//robot.GetSensorData(&sensors_data);
		//sensors_data -> OdometryLeft = 0;
		//sensors_data -> OdometryRight = 0;
	}
	

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


void Robot_Avancer_avec_tick(UINT16 vitesse_gauche, UINT16 vitesse_droite, int consigne_tick)
{
	int val_tick_droite = 0;
	int val_tick_gauche = 0;
	int val_tick_droite_depart = 0;
	int val_tick_gauche_depart = 0;

	robot.GetSensorData(&sensors_data);//aquisition
	val_tick_droite = val_tick_droite_depart = sensors_data.OdometryRight;//actualisation
	val_tick_gauche = val_tick_gauche_depart = sensors_data.OdometryLeft;//actualisation

	while ((val_tick_droite < consigne_tick + val_tick_droite_depart) && (val_tick_gauche < consigne_tick + val_tick_gauche_depart)) {

		Robot_Avancer(vitesse_gauche, vitesse_droite);
		//robot.GetSensorData(&sensors_data);//aquisition
		updatesensors();
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
	int val_tick_gauche = 0; //variable du tick mesuré
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
	int val_tick_gauche = 0; //variable du tick mesuré
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
	/*printf("Batterie : %d\n", sensors_data.BatVoltage);
	printf("IRLeft : %d\n", sensors_data.IRLeft);
	printf("IRRight : %d\n", sensors_data.IRRight);*/
	printf("odoLeft : %d\n", sensors_data.OdometryLeft);
	printf("odoRight : %d\n", sensors_data.OdometryRight);
	
	mesure_odometre();//a chaque apel mesure des nouvelles coordonées
	printf("x : %f\n", getx(&pos));
	printf("y : %f\n", gety(&pos));
	printf("O: %f\n", getO(&pos));

	//cpt++;

	//printf("============cpt : %d\n", cpt);
	
	//Sleep(100);
	
	//verif_limites_xy(&pos);//vérifie si le robot a atteint une limite à chaque mise à jour des coordonées
}





//http://geonobotwiki.free.fr/doku.php?id=robotics:odometrie

/* mise a jour la nouvelle position du robot (x, y, O)
 * par approximation de segment de droite */
void calcul_position_segment(position *p, double distance, double angle)/*pas utiliser ici*/
{
	p->x += distance * cos(p->O);
	p->y += distance * sin(p->O);
	p->O += angle / entraxe; //atan2(angle, entraxe);
}

/* mise a jour de la nouvelle position du robot (x, y, O)
 * par approximation d'arc de cercle */
void calcul_position_arc(position *p, double distance, double angle)
{
	/* rayon et angle de l'arc de cercle */
	double r, a;
	/* coordonnées du centre de l'arc de cercle */
	double xo, yo;

	if (angle == 0)
	{
		p->x += distance * cos(p->O);
		p->y += distance * sin(p->O);
	}
	else
	{
		/* calcul des caractéristiques de l'arc de cercle */
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

	//calcul_position_segment(p, delta_distance, delta_angle);
	calcul_position_arc(p, delta_distance, delta_angle);
}

void mesure_odometre(void) {/*attention au type de variable!*/
	/*mesure la distance parcourue par les roues*/
							//robot.GetSensorData(&sensors_data);

	delta_roue_droite = sensors_data.OdometryRight - old_droite;//calcul de la distance
	delta_roue_gauche = sensors_data.OdometryLeft - old_gauche;

	printf("delta droite : %f\n", delta_roue_droite);
	printf("delta gauche: %f\n", delta_roue_gauche);

	if ((delta_roue_droite > 500) || (delta_roue_droite > 500)) {
		printf("bad\n");
	}
	else {
		odometrie(&pos, delta_roue_droite, delta_roue_gauche);
	}

	

	

	old_droite = sensors_data.OdometryRight;
	old_gauche = sensors_data.OdometryLeft;

	delta_roue_droite = 0;
	delta_roue_gauche = 0;

	/*pas de remise à  ?*/
}

//extrait les positions de la structure
double getx(position *p) {

	return p->x;
}
double gety(position *p) {

	return p->y;
}
double getO(position *p) {

	return p->O;
}

void verif_limites_xy(position *p) {
	
	if (p->x > lim_x) {//stop
		Robot_Arreter(0, 0);
	}
	if (p->y > lim_y) {//alcove ! en positif
		Robot_Arreter(0, 0);//tourner sur soit meme pour se remettre dans la bonne orientation
		//à voir avec le vrai robot en test
		//sans lui j'atteint mes limites à l'aveugle

		Robot_Tourner_Droite_avec_tick(-50, 50, 2000);// faire un 180°
		//ou bien utiliser l'orientation si ça marche
		//descendre en dessous de la limite en y d'environ la valeur limite
		//tourner de 90° pour se remettre dans l'axe
		//reprendre le fonctionnement normal et avancer
		p->O;
	}
	
	
	
	
	
	
	
	
	/**if (p->y < lim_y) {//alcove ! en negatif
		Robot_Arreter(0, 0);//tourner sur soit meme pour se remettre dans la bonne orientation
		//à voir avec le vrai robot en test
		//sans lui j'atteint mes limites à l'aveugle
		p->O;
	}**/
}

void inistruc(position *p) {
	p->O = 0;
	p->x = 0;
	p->y = 0;
}