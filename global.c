#include<stdio.h>
#include"projet.h"
#include<stdlib.h>
#include<string.h>

void global1(void)
{
	FILE *flot;
	int nblog;
	Logements *tlog;

	
	flot=fopen("logements.txt","r");
	if(flot==NULL)
	{
		printf("problème d'ouverture du fichier.");
		exit(1);
	}


	tlog=chargeLogement(flot, &nblog);

	trifusion(tlog, nblog);

	afficherLogementsDispo(tlog, nblog);

}

void global2(void)
{
	FILE *flot;
	int nblog;
	Logements *tlog;

	
	flot=fopen("logements.txt","r");
	if(flot==NULL)
	{
		printf("problème d'ouverture du fichier.");
		exit(1);
	}


	tlog=chargeLogement(flot, &nblog);

	affichLogOccup(tlog, nblog);

}


void global3(void)
{
	FILE *flot;
	int nbdem;
	DemandesEnAttente **tdem;

	
	flot=fopen("demandesEnAttente.txt","r");
	if(flot==NULL)
	{
		printf("problème d'ouverture du fichier.");
		exit(1);
	}


	tdem=chargeDemandesEnAttente(flot, &nbdem);

	affichDem(tdem, nbdem);


}


void global4(void)
{
	FILE *flot;
	int nbetud;
	Etudiants *tetud[20];

	
	flot=fopen("etudiants.txt","r");
	if(flot==NULL)
	{
		printf("problème d'ouverture du fichier.");
		exit(1);
	}


	nbetud=chargeEtudiants(flot, tetud, 20);

	affichEtudiants(tetud, nbetud);


}

void global(void)
{
	FILE *flot, *fe, *fr, *fb;
	int choix, nbetud, nblog, nbdem, inf, trouve, i, taillemax;
	char c='o';
	Etudiants *tetud[20], e;
	Logements *tlog;
	DemandesEnAttente **tdem, d;

	/*Ouverture des 3 fichiers*/
	flot=fopen("etudiants.txt","r+");
	if(flot==NULL)
	{
		printf("problème d'ouverture du fichier étudiants.");
		exit(1);
	}


	fe=fopen("logements.txt","r+");
	if(fe==NULL)
	{
		printf("problème d'ouverture du fichier logements.");
		exit(1);
	}

	fr=fopen("demandesEnAttente.txt","r+");
	if(fr==NULL)
	{
		printf("problème d'ouverture du fichier Demandes En Attente .");
		exit(1);
	}

	/* Chargement des 3 fichiers*/

	tlog=chargeLogement(fe, &nblog);
	
	nbetud=chargeEtudiants(flot, tetud, 20);

	tdem=chargeDemandesEnAttente(fr, &nbdem);




	printf("Bienvenue dans notre menu, ");

	while(c=='o')
	{
		printf("Choissisez votre option :\n1-Affichage de la liste des logements disponibles triée par cité\n2-Affichage de la liste des logements occupés\n3-Affichage de la liste des demandes de logements en attente\n4-Saisie d'une nouvelle demande de logement (en cours)\n5-Annuler une demande\n6-Traiter les demandes (en cours)\n");
		scanf("%d", &choix);
		/*Affichage de la liste des logements disponibles triée par cité*/

		if(choix==1)
			{
				trifusion(tlog, nblog);
				afficherLogementsDispo(tlog, nblog);
			}

		/*Affichage de la liste des logements occupés triée par cité*/

		if(choix==2)
		{
			affichLogOccup(tlog, nblog);
		}

		/*Affichage de la liste des demandes de logement en attente */

		if(choix==3)
		{
			affichDem(tdem, nbdem);
		}

		if(choix==4)
		{

			printf("id de l'étudiant: \n");
			scanf("%d", &e.idEtudiant);

			trifusionE(tetud, nbetud);

			i=rechDich(e.idEtudiant, tetud, nbetud, &trouve);

			InsertionModif(e, d, tdem, &nbdem, &taillemax, trouve, i);

			affichDem(tdem, nbdem);
		}


		if(choix==5)
		{
			int i, trouve, id;
			printf("id de la demande: ");
			scanf("%d", &id);
			i=rechDichD(id, tdem, nbdem, &trouve);
			if(trouve==1)
				supp(tdem, i, &nbdem);
			if(trouve==0)
				printf("la demande rechercher n'existe pas\n");
		}

		if(choix==6)
		{
			trifusionE(tetud, nbetud);
			traitement(tlog, tetud, tdem, nbdem, nblog , nbetud);
		}

		/*if(choix==7)
		{
			if(fb==NULL)
				{
				printf("problème d'ouverture du fichier étudiants.");
				exit(1);
				}
			sauvEtudiants(tetud, fb, nbetud);

		}*/

		if(choix>6)
		{

			printf("Pas d'options pour la demande\n");
		}

		printf("Continuez (o/n)");
		scanf("%s", &c);


	}

	fclose(flot);
	fclose(fe);
	fclose(fr);

}



int main(void)
{
	//global1();
	//global2();
	//global3();
	//global4();
	global();
	return 0;
}