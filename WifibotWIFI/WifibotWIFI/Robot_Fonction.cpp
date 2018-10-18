#include <stdio.h>
#include <stdlib.h>

#include "WifibotClient.h"
#include "Robot_Fonction.h"


#define IP_ADRESSE "192.168.1.75"
#define PORT	15020

WifibotClient robot;
SensorData sensors_data;
int IR_SEUIL = 100;


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

void Detection_obstacle()
{
	while (sensors_data.IRLeft > IR_SEUIL || sensors_data.IRRight > IR_SEUIL)
	{
		Robot_Arreter(0, 0);
		robot.GetSensorData(&sensors_data);
	}
}