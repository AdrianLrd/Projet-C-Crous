#include<stdio.h>
#include"projet.h"
#include<stdlib.h>
#include<string.h>

Logements lireLogement(FILE *flot)
{
	Logements log;
	fscanf(flot,"%d%s%s%d ", &log.idLogements, log.type, log.handi, &log.dispo);
	if(log.dispo==1)
		fscanf(flot,"%d ", &log.idEtudiant);
	fgets(log.cite,20,flot);
	log.cite[strlen(log.cite)-1]='\0';
	return log;
}

Logements * chargeLogement(FILE *flot, int *nblog)
{
	int i;
	Logements *tlog;	
	fscanf(flot,"%d", nblog);
	tlog=(Logements *)malloc(*nblog*sizeof(Logements));
	if (tlog==NULL)
	{
		printf("pb malloc");
		exit(1);
	}
	for(i=0;i<*nblog;i++)
		tlog[i]=lireLogement(flot);
	return tlog;
	
}

void copie(Logements tlog[], int i, int j,Logements *R)
{
	int k=0;
	while(i<j)
	{
		R[k]=tlog[i];
		i=i+1;
		k=k+1;
	}
}

void fusion(Logements *R, int n, Logements *S, int m, Logements tlog[])
{
	int i=0, j=0, k=0;
	while(i<n && j<n)
	{
		if(strcmp(R[i].cite, S[j].cite)<0)
		{
			tlog[k]=R[i];
			i=i+1;
			k=k+1;
		}
		else {
			tlog[k]=S[j];
			k=k+1;
			j=j+1;
		}
	}

	while(i<n)
	{
		tlog[k]=R[i];
		i=i+1;
		k=k+1;
	}
	while(j<m)
	{
		tlog[k]=S[j];
		j=j+1;
		k=k+1;
	}


}


void trifusion(Logements tlog[], int nblog)
{
	Logements *R, *S;
	if(nblog==1)
		return;
	R=(Logements*)malloc((nblog/2)*sizeof(Logements));
	S=(Logements*)malloc((nblog-nblog/2)*sizeof(Logements));
	if(R==NULL || S==NULL)
	{
		printf("Problème malloc\n");
		return;
	}
	copie(tlog, 0, nblog/2, R);
	copie(tlog, nblog/2, nblog, S);
	trifusion(R, nblog/2);
	trifusion(S, nblog-nblog/2);
	fusion(R,nblog/2, S, nblog-nblog/2, tlog);
	free(R);
	free(S);


}



void afficherLog(Logements log)
{
		printf("Logement: %d\t Cité: %s\tType: %s\tAdapté: %s\tDispo : %d (1 = non)\n", log.idLogements, log.cite, log.type, log.handi, log.dispo);
}

void afficherLogementsDispo(Logements tlog[], int nblog)
{
	int i;

	for(i=0;i<nblog;i++)
		if(tlog[i].dispo==0)
		afficherLog(tlog[i]);
}

void affichLogOccup(Logements tlog[], int nblog)
{
	int i;

	for(i=0;i<nblog;i++)
		if(tlog[i].dispo)
			afficherLog(tlog[i]);
}





DemandesEnAttente lireDemandes(FILE *flot)
{
	DemandesEnAttente dem;
	fscanf(flot,"%d %d %d %s ", &dem.idDemande, &dem.idEtudiant, &dem.echelon, dem.type);
	fgets(dem.cite,19,flot);
	dem.cite[strlen(dem.cite)-1]='\0';
	return dem;
}

DemandesEnAttente ** chargeDemandesEnAttente(FILE *flot, int *nbdem)
{
	int i=0, max=20;
	DemandesEnAttente d, **tdem, **aux;


	tdem=(DemandesEnAttente**)malloc(max*sizeof(DemandesEnAttente*));
	if(tdem==NULL)
	{
		printf("problème de malloc.");
		exit(1);
	}

	d=lireDemandes(flot);
	while(!feof(flot))
	{
		if(i==max)
		{

			max=max+20;
			aux=(DemandesEnAttente**)realloc(tdem, max*sizeof(DemandesEnAttente*));
			if(tdem==NULL)
			{
				printf("problème de malloc.");
				exit(1);
			}
			tdem=aux;
		}
		
		tdem[i]=(DemandesEnAttente*)malloc(sizeof(DemandesEnAttente));
		if(tdem==NULL)
		{
			printf("problème de malloc.");
			exit(1);
		}
		*tdem[i]=d;
		i=i+1;
		d=lireDemandes(flot);
	}
	*nbdem=i;
	return tdem;
}


void affichDem(DemandesEnAttente *tdem[], int nbdem)
{
	int i;
	for(i=0;i<nbdem;i++)
		printf("idDemande: %d/\tidEtudiant: %d/\techelon: %d/\ttype: %s/\tcite: %s\n", tdem[i]->idDemande, tdem[i]->idEtudiant, tdem[i]->echelon, tdem[i]->type, tdem[i]->cite);
}





Etudiants lireEtudiants(FILE *flot)
{
	Etudiants e;
	fscanf(flot,"%d%s%d%s%s%s%s", &e.idEtudiant, e.boursier, &e.echelon, e.handicap, e.civilite, e.prenom, e.nom);
	return e;
}

int chargeEtudiants(FILE *flot, Etudiants *tetud[], int max)
{
	int i=0;

	tetud[i]=(Etudiants*)malloc(sizeof(Etudiants));
	if(tetud==NULL)
	{
		printf("problème de malloc.");
		exit(1);
	}

	*tetud[i]=lireEtudiants(flot);
	while(!feof(flot))
	{
		if(i==max)
		{
			printf("Tableau plein.");
			exit(1);
		}
		i=i+1;
		tetud[i]=(Etudiants*)malloc(sizeof(Etudiants));
		*tetud[i]=lireEtudiants(flot);
	}
	return i;
}

void affichEtudiants(Etudiants *tetud[], int nbetud)
{
	int i;
	for(i=0;i<nbetud;i++)
		printf("idEtudiant: %d/\tboursier: %s/\techelon: %d/\thandicap: %s/\tcivilite: %s/\tprénom: %s/\tnom: %s/\n", tetud[i]->idEtudiant, tetud[i]->boursier, tetud[i]->echelon, tetud[i]->handicap, tetud[i]->civilite, tetud[i]->prenom, tetud[i]->nom);
}

void copieE(Etudiants *tlog[], int i, int j, Etudiants *R[])
{
	int k=0;
	while(i<j)
	{
		R[k]=tlog[i];
		i=i+1;
		k=k+1;
	}
}

void fusionE(Etudiants *R[], int n, Etudiants *S[], int m, Etudiants *tlog[])
{
	int i=0, j=0, k=0;
	while(i<n && j<n)
	{
		if(R[i]->idEtudiant<S[j]->idEtudiant)
		{
			tlog[k]=R[i];
			i=i+1;
			k=k+1;
		}
		else {
			tlog[k]=S[j];
			k=k+1;
			j=j+1;
		}
	}

	while(i<n)
	{
		tlog[k]=R[i];
		i=i+1;
		k=k+1;
	}
	while(j<m)
	{
		tlog[k]=S[j];
		j=j+1;
		k=k+1;
	}


}


void trifusionE(Etudiants *tlog[], int nblog)
{
	Etudiants **R, **S;
	if(nblog==1)
		return;
	R=(Etudiants**)malloc((nblog/2)*sizeof(Etudiants*));
	S=(Etudiants**)malloc((nblog-nblog/2)*sizeof(Etudiants*));
	if(R==NULL || S==NULL)
	{
		printf("Problème malloc\n");
		return;
	}
	copieE(tlog, 0, nblog/2, R);
	copieE(tlog, nblog/2, nblog, S);
	trifusionE(R, nblog/2);
	trifusionE(S, nblog-nblog/2);
	fusionE(R,nblog/2, S, nblog-nblog/2, tlog);
	free(R);
	free(S);


}

int rechDich(int id, Etudiants *tlog[], int n, int *trouve)
{
	int inf=0, sup=n-1, m;

	while(inf<=sup)
	{
		m=(inf+sup)/2;
		if(tlog[m]->idEtudiant==id)
		{
			*trouve=1;
			return m;
		}
		if(tlog[m]->idEtudiant>id)
			sup=m-1;
		else inf=m+1;
	}

	*trouve=0;
	return inf;
}

DemandesEnAttente InsertionModif(Etudiants e, DemandesEnAttente d, DemandesEnAttente *tdem[], int *nbdem, int *taillemax, int trouve, int i)
{

	DemandesEnAttente **aux, a;


	if(*nbdem==*taillemax)
		{
			
		aux=(DemandesEnAttente**)realloc(tdem, (*nbdem+3)*sizeof(DemandesEnAttente*));
		if (aux==NULL)
			{
				printf("pb realloc");
				exit(1);
			}



		*taillemax=*taillemax+3;

		tdem=aux;
	}

	if(trouve==0)
	{
		printf("Civilite de l'étudiant:\n");
		scanf("%s", e.civilite);

		printf("Nom de l'étudiant:\n");
		scanf("%s", e.nom);

		printf("Prénom de l'étudiant:\n");
		scanf("%s", e.prenom);

		printf("L'Etudiants est-il boursier ?\n");
		scanf("%s", e.boursier);


		printf("Echelon de l'étudiant: \n");
		scanf("%d", &e.echelon);

		printf("Etudiant handicapé ?\n");
		scanf("%s", e.handicap);

		printf("Type de logement:\n");
		scanf("%s", d.type);

		printf("Cite \n");
		scanf("%s", d.cite);

		printf("ok\n");

		tdem[i]->idEtudiant=e.idEtudiant;

		tdem[i]->echelon=e.echelon;

		strcpy(d.type, tdem[i]->type);

		strcpy(d.cite, tdem[i]->cite);


	}

	if(trouve)
	{

	}




}


int rechDichD(int id, DemandesEnAttente *tdem[], int n, int *trouve)
{
	int inf=0, sup=n-1, m;

	while(inf<=sup)
	{
		m=(inf+sup)/2;
		if(tdem[m]->idDemande==id)
		{
			*trouve=1;
			return m;
		}
		if(tdem[m]->idDemande>id)
			sup=m-1;
		else inf=m+1;
	}

	*trouve=0;
	return inf;
}

void supp(DemandesEnAttente *tdem[], int i, int *nbdem)
{
	int j;
	for(j=i;j<*nbdem;j++)
		tdem[j]=tdem[j+1];
	*nbdem=*nbdem-1;

}

void traitement(Logements tlog[], Etudiants *tetud[], DemandesEnAttente *tdem[], int nbdem, int nblog, int nbetud)
{
	int i=0, n=0, m;
	Logements log;
	while(i<nbdem)
	{
		m=0;
		n=rechercheDichoEtud(tdem[i]->idEtudiant, tetud, nbetud);
		printf("emplacement de l'etudiants trouver %d\n", n);
		while(m<nbdem)
		{	
			log=tlog[m];
			printf("dispo: %d\n", log.dispo);
			printf("%s\t%s\t%s\n", log.handi, log.cite, log.type);
			printf("%s\t", tetud[n]->handicap);
			printf("i : %d\n", i);
			printf("%s\t", tdem[i]->cite);
			printf("%s\n", tdem[i]->type);
			if(log.dispo==0 )
			{

				if(strcmp(log.handi, tetud[n]->handicap)==0 && strcmp(tdem[i]->cite, log.cite)==0 && strcmp(tdem[i]->type, log.type)==0)
				{
					log.idEtudiant=tetud[n]->idEtudiant;
					log.dispo=1;
					printf("ça en a trouvé un et ça la changé\n");
					supp(tdem, n, &nbdem);
				}
			}
			m++;
			log=tlog[m];
			printf("emplacement du logement %d\n", m);
		}	
		i++;
	}
}

int rechercheDichoEtud(int idEtud, Etudiants *tetud[], int nbetud)
{
	int inf, sup, m;
	inf=0;
	sup=nbetud-1;
	while(inf<=sup)
	{
		m=(inf+sup)/2;
		if(idEtud==tetud[m]->idEtudiant)
			return m;
		if(tetud[m]->idEtudiant>idEtud)
			sup=m-1;
		else inf=m+1;
	}
	printf("%d rang de l'etudiant\n", inf);
	return inf;
}

/*void sauvEtudiants(Etudiants **tetud, FILE *flot, int nbetud)
{
	flot=fopen("sauvEtud.txt","wb");
	fwrite(&nbetud, sizeof(int), 1, flot);
	fwrite(tetud, sizeof(Etudiants*), nbetud, flot);
	fclose(flot);

	flot=fopen("sauvEtud.txt","rb");
	fclose(flot);
}*/