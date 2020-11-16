#include <stdlib.h> // USE exit()
#include <stdio.h> // EMPLOY printf()
#include <math.h> // USE sin() AND cos()
#include "GfxLib.h" // DO GRAPHIC
#include "BmpLib.h" // MANIPULATE BMP FILES
#include "ESLib.h" // USE valeurAleatoire()
#include "toolbox.h"

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 1200
#define HauteurFenetre 800

// Fonction de trace de cercle
void cercle(float centreX, float centreY, float rayon);
/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);


int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	
	prepareFenetreGraphique("GfxLib", LargeurFenetre, HauteurFenetre);
	
	/* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
		qui elle-meme utilise fonctionAffichage ci-dessous */
	lanceBoucleEvenements();
	
	return 0;
}


/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	// TO KNOW IF IT IS IN FULLSCREEN OR NOT
	static bool pleinEcran = false;
	
	// DESKTOP BACKGROUND PICTURE
	static DonneesImageRGB *image = NULL;
	
	// POSITION D'AFFICHAGE (MENU,OPTIONS,LEVEL,ANALYSIS)
	static int position_affichage;
	
	// OPTIONS (LEVEL,THEMES)
	static Options opt;
	
	// TABLE OF FIXED POSITIONS
	static Point pos_fixe[16];
	
	// METER
	static int j;
	
	// RGB COLOR TO DELETE
	static couleur RGB;
	
	// LEVEL STRUCTURE
	static jeux level;
	
	switch (evenement)
	{
		case Initialisation:
			
			// ENABLE PASSIVE MOUSE MANAGEMENT
			activeGestionDeplacementPassifSouris();
			
			// INITIALISATION OF FIXED POSITIONS
			initPositionFixe(pos_fixe);
						
			j = 0;
			
			position_affichage = 0;
			
			opt.level = 0;
			opt.theme = 0;
			
			RGB.r = 255;
			RGB.v = 0;
			RGB.b = 0;
			
			image = lisBMPRGB("fondProjet.bmp");
			
			srand(time(NULL));
			
			/* Le message "Initialisation" est envoye une seule fois, au debut du
			programme : il permet de fixer "image" a la valeur qu'il devra conserver
			jusqu'a la fin du programme : soit "image" reste a NULL si l'image n'a
			pas pu etre lue, soit "image" pointera sur une structure contenant
			les caracteristiques de l'image "imageNB.bmp" */
			
			// Configure le systeme pour generer un message Temporisation
			// toutes les 20 millisecondes
			demandeTemporisation(20);
			break;
		
		case Temporisation:
			
			// LEVEL
			if(position_affichage == 2)
			{
				for(int i = 0;i<level.nb_img;i++)
				{
					// IF A PICTURE IS CHOSEN
					if(level.T[i].etat_img == CHOISIE)
					{
						// SAVE THE COORDINATES OF THE MOUSE EVERY 20 MS
						gereDeplacementSouris(level.T[i].nb_deplacement,&(level.T[i].deplacement));
						
						// INCREASE THE NUMBER OF MOVEMENT
						level.T[i].nb_deplacement++;
					}
					// IF ALL PICTURES ARE AVAILABLE
					else if(level.T[i].etat_img == ACTIVE)
					{
						// RESET THE NUMBER OF MOVEMENT
						level.T[i].nb_deplacement = 0;
					}
				}
				
			}
			
			rafraichisFenetre();
			break;
			
		case Affichage:
			
			// SET THE DESKTOP BACKGROUND IN WHITE
			effaceFenetre (255, 255, 255);
			
			// DISPLAY THE DESKTOP BACKGROUND AND THE BUTTON "QUIT"
			afficheStandard(image);
			
			// MENU
			if(position_affichage == 0)
			{
				// DISPLAY THE MENU
				afficheMenu();
			}
			// OPTIONS
			else if(position_affichage == 1)
			{
				// DISPLAY THE OPTIONS
				afficheOptions(&opt);
			}
			// LEVEL
			else if(position_affichage == 2)
			{
				// IF IT IS THE FIRST TIME
				if(j == 0)
				{
					// INITIALISATION OF THE LEVEL CHOSEN
					initLevel(&level,pos_fixe,&opt);
					
					j++;
				}
				
				// DISPLAY THE LEVEL CHOSEN
				afficheNiveau(&opt,&level,RGB,&position_affichage);
			}
			// ANALYSIS
			else if(position_affichage == 3)
			{
				// DISPLAY THE ANALYSIS
				afficheAnalyse(&level,RGB);
			}
			
			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());
			
			switch (caractereClavier())
			{
				case 'Q': // LEAVE THE PROGRAM CLEANLY
				case 'q': // FREE THE STRUCTURE IMAGE TO QUIT THE PROGRAM PROPERLY
					libereDonneesImageRGB(&image);
					if(position_affichage >= 2)
					{
						for(int i = 0;i<level.nb_img;i++)
						{
							// RESET THE PICTURES
							libereDonneesImageRGB(&level.T[i].img);
						}
					}
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran; // CHANGE TO FULLSCREEN
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

				case 'R':
				case 'r':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 20 millisecondes (rapide)
					demandeTemporisation(20);
					break;

				case 'L':
				case 'l':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 100 millisecondes (lent)
					demandeTemporisation(100);
					break;

				case 'S':
				case 's':
					// Configure le systeme pour ne plus generer de message Temporisation
					demandeTemporisation(-1);
					break;
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
				//printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			else if (etatBoutonSouris() == GaucheRelache)
			{
				printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
				gereClic(&position_affichage,&opt,&level);
			}
			break;
		
		case Souris: // IF THE MOUSE MOVE
			
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			// Donc le systeme nous en informe
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
			break;
	}
}
