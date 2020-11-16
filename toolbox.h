#include <time.h> // USE TIME FUNCTIONS
#include "BmpLib.h" // MANIPULATE BMP FILES
#include "imageSF.h" // SET A PICTURE WITHOUT THE BACKGROUND

#define FAUX 0
#define VRAI 1

typedef struct Point {
	int x,y;
}Point;

typedef struct Options {
	int level,theme;
}Options;

#define ACTIVE 1
#define INACTIVE 2
#define CHOISIE 3

typedef struct item {
	DonneesImageRGB *img;
	int id_img;
	Point pos_img;
	int etat_img;
	time_t timeclic;
	Point *deplacement;
	int nb_deplacement;
	Point * clic;
	int nb_clic;
	int *erreur;
	int nb_erreur;
	int anime;
	DonneesImageRGB *thumbnail;
}item;

#define HAUT_DROITE 1
#define BAS_DROITE 2
#define BAS_GAUCHE 3
#define HAUT_GAUCHE 4

typedef struct analyse {
	int item_depart;
	int item_arrivee;
	int distance_ideale;
	int distance_user;
	int nb_tremblement;
}analyse;

typedef struct jeux {
	item *T;
	time_t debut_jeux;
	time_t fin_jeux;
	int nb_img;
	int nb_pairs;
	int sauver;
	analyse *TA;
	int first_scroll;
	DonneesImageRGB *recto;
	DonneesImageRGB *verso;
	DonneesImageRGB *thumbnail_recto;
	DonneesImageRGB *thumbnail_verso;
}jeux;

void gereDeplacementSouris (int i, Point **T2);
void initPositionFixe (Point pos_fixe[6]);
void afficheStandard (DonneesImageRGB *image);
void afficheMenu (void);
void afficheOptions (Options *opt);
void afficheNiveau (Options *opt, jeux *level, couleur RGB, int *position_affichage);
void gereClic (int *position_affichage, Options *opt, jeux *level);
void initLevel (jeux *level, Point position[6], Options *opt);
void sauveFichier(char nomFichier[20], Options *opt, jeux *level);
void analyseTrajectoire(jeux *level);
void afficheAnalyse(jeux *level, couleur RGB);
int rand_a_b(int a, int b);
void gereClicTraj(jeux *level, int *i);
void libereClicTraj(jeux *level, int *i);
void gereErreur(jeux *level, int *i, int *k);
