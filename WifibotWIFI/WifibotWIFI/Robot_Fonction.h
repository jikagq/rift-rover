#include "WifibotClient.h"

#pragma once


void Robot_Connexion();
void Robot_Avancer(UINT16 vitesse_gauche, UINT16 vitesse_droite);
void Robot_Reculer(UINT16 vitesse_gauche, UINT16 vitesse_droite);
void Robot_Tourner_Gauche(UINT16 vitesse_gauche, UINT16 vitesse_droite);
void Robot_Tourner_Droite(UINT16 vitesse_gauche, UINT16 vitesse_droite);
void Robot_Arreter(UINT16 vitesse_gauche, UINT16 vitesse_droite);
bool Robot_obstacleDroite();
bool Robot_obstacleGauche();
void Detection_obstacle();