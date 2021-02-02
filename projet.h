typedef struct{
	int idLogements;
	char cite[20];
	char type[7];
	int dispo;
	char handi[3];
	int idEtudiant;
} Logements;

typedef struct{
	int idEtudiant;
	char civilite[4];
	char nom[20];
	char prenom[20];
	char boursier[3];
	int echelon;
	char handicap[3];
} Etudiants;


typedef struct{
	int idDemande;
	int idEtudiant;
	int echelon;
	char cite[19];
	char type[7];
} DemandesEnAttente;

Logements lireLogement(FILE *flot);
Logements * chargeLogement(FILE *flot, int *nbart);
void copie(Logements tlog[], int i, int j,Logements *R);
void fusion(Logements *R, int n, Logements *S, int m, Logements tlog[]);
void trifusion(Logements tlog[], int nblog);
void afficherLogementsDispo(Logements tlog[], int nblog);
void afficherLog(Logements log);
void affichLogOccup(Logements tlog[], int nblog);
DemandesEnAttente ** chargeDemandesEnAttente(FILE *flot, int *nbdem);
void affichDem(DemandesEnAttente *tdem[], int nbdem);
Etudiants lireEtudiants(FILE *flot);
int chargeEtudiants(FILE *flot, Etudiants *tetud[], int max);
void affichEtudiants(Etudiants *tetud[], int nbdem);
void copieE(Etudiants *tlog[], int i, int j, Etudiants *R[]);
void fusionE(Etudiants *R[], int n, Etudiants *S[], int m, Etudiants *tlog[]);
void trifusionE(Etudiants *tlog[], int nblog);
int rechDich(int id, Etudiants *tlog[], int n, int *trouve);
DemandesEnAttente InsertionModif(Etudiants e, DemandesEnAttente d, DemandesEnAttente *tdem[], int *nbdem, int *taillemax, int trouve, int i);
int rechDichD(int id, DemandesEnAttente *tdem[], int n, int *trouve);
void supp(DemandesEnAttente *tdem[], int i, int *nbdem);
void traitement(Logements tlog[], Etudiants *tetud[], DemandesEnAttente *tdem[], int nbdem,int nblog, int nbetud);
int rechercheDichoEtud(int idEtud, Etudiants *tetud[], int nbetud);

