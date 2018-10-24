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
		robot.GetSensorData(&sensors_data);//aquisition
		val_tick_droite = sensors_data.OdometryRight;//actualisation
		val_tick_gauche = sensors_data.OdometryLeft;//actualisation
		Sleep(100);
	}
	Robot_Arreter(0, 0);

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
		robot.GetSensorData(&sensors_data);//aquisition
		val_tick_gauche = sensors_data.OdometryLeft;//actualisation
		val_tick_droite = sensors_data.OdometryRight;//actualisation
		Sleep(100);
	}
	Robot_Arreter(0, 0);
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
		robot.GetSensorData(&sensors_data);//aquisition
		val_tick_gauche = sensors_data.OdometryLeft;//actualisation
		val_tick_droite = sensors_data.OdometryRight;//actualisation
		Sleep(100);
	}
	Robot_Arreter(0, 0);
}

void updatesensors(void) {
	robot.GetSensorData(&sensors_data);
	printf("IRLeft : %d\n", sensors_data.IRLeft);
	printf("IRRight : %d\n", sensors_data.IRRight);
	printf("odoLeft : %d\n", sensors_data.OdometryLeft);
	printf("odoRight : %d\n", sensors_data.OdometryRight);
	printf("Batterie : %d\n", sensors_data.BatVoltage);
}