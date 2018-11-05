#include "WifibotClient.h"

#define IP_ADRESSE "192.168.1.76"
#define PORT	15020


#pragma once



typedef struct
{
	double x = 0;     /* en pulse */
	double y = 0;
	double O = 0;     /* en rad */
} position;


void Robot_Connexion();
void Robot_Avancer(UINT16 vitesse_gauche, UINT16 vitesse_droite);
void Robot_Reculer(UINT16 vitesse_gauche, UINT16 vitesse_droite);
void Robot_Tourner_Gauche(UINT16 vitesse_gauche, UINT16 vitesse_droite);
void Robot_Tourner_Droite(UINT16 vitesse_gauche, UINT16 vitesse_droite);
void Robot_Arreter(UINT16 vitesse_gauche, UINT16 vitesse_droite);
bool Robot_obstacleDroite();
bool Robot_obstacleGauche();
bool Detection_obstacle();

void Robot_Avancer_avec_tick(UINT16 vitesse_gauche, UINT16 vitesse_droite, int consigne_tick);
void Robot_Tourner_Gauche_avec_tick(UINT16 vitesse_gauche, UINT16 vitesse_droite, int consigne_tick);
void Robot_Tourner_Droite_avec_tick(UINT16 vitesse_gauche, UINT16 vitesse_droite, int consigne_tick);

void updatesensors(void);

void calcul_position_segment(position *p, double distance, double angle);
void calcul_position_arc(position *p, double distance, double angle);
void odometrie(position *p, signed short delta_roue_droite, signed short delta_roue_gauche);
void mesure_odometre(void);

double getx(position *p);
double gety(position *p);
double getO(position *p);

void verif_limites_xy(position *p);