#include <stdlib.h> // USE exit()
#include <stdio.h> // EMPLOY printf()
#include <math.h> // USE sin() AND cos()
#include "GfxLib.h" // DO GRAPHIC
#include "toolbox.h"

void gereDeplacementSouris (int i, Point **T2)
{
	if(i == 0)
	{
		// INITIALISATION FOR I = 0
		(*T2) = (Point*)malloc(sizeof(Point)*(i+1));
		
		// SAVE THE COORDINATES INTO THE TABLE
		(*T2)[i].x = abscisseSouris();
		(*T2)[i].y = ordonneeSouris();
	}
	else
	{
		//RE-INITIALISATION FOR I != 0

		Point * newT2 ;
		newT2 = (Point*)realloc(*T2,sizeof(Point)*(i+1));
		
		if (newT2 != NULL)
		{
			*T2 = newT2;
		}
		
		(*T2)[i].x = abscisseSouris();
		(*T2)[i].y = ordonneeSouris();
		
		//free(*T2) ;
		//*T2 = newT2 ;
	}
}


void initPositionFixe (Point pos_fixe[6])
{
	// BOTTOM LEFT
	pos_fixe[0].x = 200;
	pos_fixe[0].y = 50;
	
	// MIDDLE LEFT
	pos_fixe[1].x = 200;
	pos_fixe[1].y = 250;
	
	// TOP LEFT
	pos_fixe[2].x = 200;
	pos_fixe[2].y = 450;
	
	// BOTTOM RIGHT
	pos_fixe[3].x = 800;
	pos_fixe[3].y = 50;
	
	// MIDDLE RIGHT
	pos_fixe[4].x = 800;
	pos_fixe[4].y = 250;
	
	// TOP RIGHT
	pos_fixe[5].x = 800;
	pos_fixe[5].y = 450;
}


void afficheStandard (DonneesImageRGB *image)
{
	// IF THE PICTURE EXISTS
	if (image != NULL)
	{
		// DISPLAY THE DESKTOP BACKGROUND
		ecrisImage(0, 0, largeurFenetre(), hauteurFenetre(), image->donneesRGB);
	}
	
	// BUTTON "QUIT"
	couleurCourante(200,0,0);
	epaisseurDeTrait(3);
	rectangle(227*largeurFenetre()/240,149*hauteurFenetre()/160,59*largeurFenetre()/60,39*hauteurFenetre()/40);
	
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	ligne(569*largeurFenetre()/600,187*hauteurFenetre()/200,1177*largeurFenetre()/1200,777*hauteurFenetre()/800);
	ligne(569*largeurFenetre()/600,777*hauteurFenetre()/800,1177*largeurFenetre()/1200,187*hauteurFenetre()/200);
}


void afficheMenu (void)
{
	// TITLE
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("Combination Game",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,largeurFenetre()/3,4*hauteurFenetre()/5);
	
	// BUTTON "PLAY"
	couleurCourante(184,115,51);
	epaisseurDeTrait(3);
	rectangle(31*largeurFenetre()/80,29*hauteurFenetre()/80,9*largeurFenetre()/16,hauteurFenetre()/2);
	
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("Play",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,9*largeurFenetre()/20,67*hauteurFenetre()/160);
}


void afficheOptions (Options *opt)
{
	// TITLE
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("Level",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,largeurFenetre()/8,4*hauteurFenetre()/5);
	
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("Theme",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,5*largeurFenetre()/8,4*hauteurFenetre()/5);
	
	// BUTTON "NEXT"
	couleurCourante(200,0,0);
	epaisseurDeTrait(3);
	rectangle(13*largeurFenetre()/15,7*hauteurFenetre()/160,59*largeurFenetre()/60,9*hauteurFenetre()/80);

	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("Next",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,107*largeurFenetre()/120,hauteurFenetre()/16);
	
	// NO CHOICE ALREADY DID FOR THE LEVEL AND FOR THE THEME
	if((opt->level == 0) && (opt->theme == 0))
	{
		//BUTTONS "LEVEL ..."
		couleurCourante(184,115,51);
		epaisseurDeTrait(3);
		rectangle(5*largeurFenetre()/48,3*hauteurFenetre()/8,5*largeurFenetre()/24,15*hauteurFenetre()/32);
		rectangle(5*largeurFenetre()/48,hauteurFenetre()/2,5*largeurFenetre()/24,19*hauteurFenetre()/32);
		rectangle(5*largeurFenetre()/48,5*hauteurFenetre()/8,5*largeurFenetre()/24,23*hauteurFenetre()/32);
		
		// BUTTONS "THEME ..."
		couleurCourante(184,115,51);
		epaisseurDeTrait(3);
		rectangle(29*largeurFenetre()/48,3*hauteurFenetre()/8,39*largeurFenetre()/48,15*hauteurFenetre()/32);
		rectangle(29*largeurFenetre()/48,hauteurFenetre()/2,39*largeurFenetre()/48,19*hauteurFenetre()/32);
		rectangle(29*largeurFenetre()/48,5*hauteurFenetre()/8,39*largeurFenetre()/48,23*hauteurFenetre()/32);
	}
	else
	{
		// CHOICE OF THE LEVEL
		if(opt->level != 0)
		{
			// LEVEL 1
			if(opt->level == 1)
			{
				// OTHER BUTTONS "LEVEL ..."
				couleurCourante(184,115,51);
				epaisseurDeTrait(3);
				rectangle(5*largeurFenetre()/48,3*hauteurFenetre()/8,5*largeurFenetre()/24,15*hauteurFenetre()/32);
				rectangle(5*largeurFenetre()/48,hauteurFenetre()/2,5*largeurFenetre()/24,19*hauteurFenetre()/32);
				
				// "LEVEL 1" BUTTON COLOURING
				couleurCourante(160,0,0);
				epaisseurDeTrait(3);
				rectangle(5*largeurFenetre()/48,5*hauteurFenetre()/8,5*largeurFenetre()/24,23*hauteurFenetre()/32);
			}
			// LEVEL 2
			else if(opt->level == 2)
			{
				// OTHER BUTTONS "LEVEL ..."
				couleurCourante(184,115,51);
				epaisseurDeTrait(3);
				rectangle(5*largeurFenetre()/48,3*hauteurFenetre()/8,5*largeurFenetre()/24,15*hauteurFenetre()/32);
				rectangle(5*largeurFenetre()/48,5*hauteurFenetre()/8,5*largeurFenetre()/24,23*hauteurFenetre()/32);
				
				// "LEVEL 2" BUTTON COLOURING
				couleurCourante(160,0,0);
				epaisseurDeTrait(3);
				rectangle(5*largeurFenetre()/48,hauteurFenetre()/2,5*largeurFenetre()/24,19*hauteurFenetre()/32);
			}
			// LEVEL 3
			else if(opt->level == 3)
			{
				// OTHER BUTTONS "LEVEL ..."
				couleurCourante(184,115,51);
				epaisseurDeTrait(3);
				rectangle(5*largeurFenetre()/48,hauteurFenetre()/2,5*largeurFenetre()/24,19*hauteurFenetre()/32);
				rectangle(5*largeurFenetre()/48,5*hauteurFenetre()/8,5*largeurFenetre()/24,23*hauteurFenetre()/32);
				
				// "LEVEL 3" BUTTON COLOURING
				couleurCourante(160,0,0);
				epaisseurDeTrait(3);
				rectangle(5*largeurFenetre()/48,3*hauteurFenetre()/8,5*largeurFenetre()/24,15*hauteurFenetre()/32);
			}
		}
		// NO CHOICE ALREADY DID FOR THE LEVEL
		else
		{
			// BUTTONS "LEVEL ..."
			couleurCourante(184,115,51);
			epaisseurDeTrait(3);
			rectangle(5*largeurFenetre()/48,3*hauteurFenetre()/8,5*largeurFenetre()/24,15*hauteurFenetre()/32);
			rectangle(5*largeurFenetre()/48,hauteurFenetre()/2,5*largeurFenetre()/24,19*hauteurFenetre()/32);
			rectangle(5*largeurFenetre()/48,5*hauteurFenetre()/8,5*largeurFenetre()/24,23*hauteurFenetre()/32);
		}
		
		//CHOICE OF THE THEME
		if(opt->theme != 0)
		{
			// THEME 1
			if(opt->theme == 1)
			{
				// OTHER BUTTONS "THEME ..."
				couleurCourante(184,115,51);
				epaisseurDeTrait(3);
				rectangle(29*largeurFenetre()/48,3*hauteurFenetre()/8,39*largeurFenetre()/48,15*hauteurFenetre()/32);
				rectangle(29*largeurFenetre()/48,hauteurFenetre()/2,39*largeurFenetre()/48,19*hauteurFenetre()/32);
				
				// "THEME 1" BUTTON COLOURING
				couleurCourante(160,0,0);
				epaisseurDeTrait(3);
				rectangle(29*largeurFenetre()/48,5*hauteurFenetre()/8,39*largeurFenetre()/48,23*hauteurFenetre()/32);
			}
			// THEME 2
			else if(opt->theme == 2)
			{
				// OTHER BUTTONS "THEME ..."
				couleurCourante(184,115,51);
				epaisseurDeTrait(3);
				rectangle(29*largeurFenetre()/48,3*hauteurFenetre()/8,39*largeurFenetre()/48,15*hauteurFenetre()/32);
				rectangle(29*largeurFenetre()/48,5*hauteurFenetre()/8,39*largeurFenetre()/48,23*hauteurFenetre()/32);
				
				// "THEME 2" BUTTON COLOURING
				couleurCourante(160,0,0);
				epaisseurDeTrait(3);
				rectangle(29*largeurFenetre()/48,hauteurFenetre()/2,39*largeurFenetre()/48,19*hauteurFenetre()/32);
			}
			// THEME 3
			else if(opt->theme == 3)
			{
				// OTHER BUTTONS "THEME ..."
				couleurCourante(184,115,51);
				epaisseurDeTrait(3);
				rectangle(29*largeurFenetre()/48,hauteurFenetre()/2,39*largeurFenetre()/48,19*hauteurFenetre()/32);
				rectangle(29*largeurFenetre()/48,5*hauteurFenetre()/8,39*largeurFenetre()/48,23*hauteurFenetre()/32);
				
				// "THEME 3" BUTTON COLOURING
				couleurCourante(160,0,0);
				epaisseurDeTrait(3);
				rectangle(29*largeurFenetre()/48,3*hauteurFenetre()/8,39*largeurFenetre()/48,15*hauteurFenetre()/32);
			}
		}
		// NO CHOICE ALREADY DID FOR THE THEME
		else
		{
			// BUTTONS "THEME ..."
			couleurCourante(184,115,51);
			epaisseurDeTrait(3);
			rectangle(29*largeurFenetre()/48,3*hauteurFenetre()/8,39*largeurFenetre()/48,15*hauteurFenetre()/32);
			rectangle(29*largeurFenetre()/48,hauteurFenetre()/2,39*largeurFenetre()/48,19*hauteurFenetre()/32);
			rectangle(29*largeurFenetre()/48,5*hauteurFenetre()/8,39*largeurFenetre()/48,23*hauteurFenetre()/32);
		}
	}
	
	// LEVELS 1 TO 3
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("3",25*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/8,7*largeurFenetre()/48,13*hauteurFenetre()/32);
	afficheChaine("2",25*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/8,7*largeurFenetre()/48,17*hauteurFenetre()/32);
	afficheChaine("1",25*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/8,7*largeurFenetre()/48,21*hauteurFenetre()/32);
	
	// THEMES : NATURE, SPACE AND HUMAN
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("EASTER EGG",25*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/8,30*largeurFenetre()/48,13*hauteurFenetre()/32);
	afficheChaine("CHRISTMAS",25*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/8,30*largeurFenetre()/48,17*hauteurFenetre()/32);
	afficheChaine("HALLOWEEN",25*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/8,30*largeurFenetre()/48,21*hauteurFenetre()/32);
}


void afficheNiveau (Options *opt, jeux *level, couleur RGB, int *position_affichage)
{
	int img_inactive = 0;
	char titre[50];
	
	// TITLE
	sprintf(titre,"Level %d et theme %d",opt->level,opt->theme);
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine(titre,15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,largeurFenetre()/3,7*hauteurFenetre()/8);
	
	// PICTURES
	for(int j = 0;j<6;j++)
	{
		if ((level->T[j].img != NULL) && (level->T[j].etat_img == ACTIVE)) // IF THE PICTURE EXISTS AND AVAILABLE
		{
			// DISPLAY THE PICTURE
			ecrisImageSansFond(level->T[j].pos_img.x, level->T[j].pos_img.y, level->T[j].img->largeurImage, level->T[j].img->hauteurImage, level->T[j].img->donneesRGB, RGB);
		}
		else if ((level->T[j].img != NULL) && (level->T[j].etat_img == CHOISIE)) // IF THE PICTURE EXISTS AND AVAILABLE
		{
			// DISPLAY THE PICTURE CHOSEN
			ecrisImage(level->T[j].pos_img.x, level->T[j].pos_img.y, level->T[j].img->largeurImage, level->T[j].img->hauteurImage, level->T[j].img->donneesRGB);
		}
		else
		{
			// INCREASE NUMBER OF PICTURES UNAVAILABLE
			img_inactive++;
		}
	}
	
	// IF ALL PICTURES UNAVAILABLE 
	if(img_inactive == 6)
	{
		// SAVE THE TIME
		level->fin_jeux = time(NULL);
		
		// SAVE THE DATA INTO A TEXT FILE
		if(level->sauver == 0)
		{
			sauveFichier("sauvegarde",opt,level);
			
			// SAVE ALREADY DONE
			level->sauver = 1;
		}
		
		// ANALYSE THE USER TRAJECTORY IN GAME
		analyseTrajectoire(level);
		
		// ANALYSIS DISPLAY
		*position_affichage = 3;
	}
}


void gereClic (int *position_affichage, Options *opt, jeux *level)
{
	int N = 0;
	
	// BUTTON "QUIT"
	if(((abscisseSouris()>227*largeurFenetre()/240) && (abscisseSouris()<59*largeurFenetre()/60)) && ((ordonneeSouris()<39*hauteurFenetre()/40) && (ordonneeSouris()>149*hauteurFenetre()/160)))
	{
		// STOP THE GAME AND CLOSE THE WINDOW
		if(*position_affichage >= 2)
		{
			for(int i = 0;i<6;i++)
			{
				// RESET THE PICTURES
				libereDonneesImageRGB(&level->T[i].img);
			}
		}
		termineBoucleEvenements();
	}
	
	// MENU
	if(*position_affichage == 0)
	{
		// BUTTON "PLAY"
		if(((abscisseSouris()>465) && (abscisseSouris()<9*largeurFenetre()/16)) && ((ordonneeSouris()<hauteurFenetre()/2) && (ordonneeSouris()>29*hauteurFenetre()/80)))
		{
			// LAUNCH THE LEVEL CHOSEN
			*position_affichage = 1;
		}
	}
	// CHOICE OF THE LEVEL AND THE THEME
	else if (*position_affichage == 1)
	{	
		// BUTTON "LEVEL 1"
		if(((abscisseSouris()>5*largeurFenetre()/48) && (abscisseSouris()<5*largeurFenetre()/24)) && ((ordonneeSouris()<23*hauteurFenetre()/32) && (ordonneeSouris()>5*hauteurFenetre()/8)))
		{
			// LEVEL 1
			opt->level = 1;
		}
		// BUTTON "LEVEL 2"
		else if(((abscisseSouris()>5*largeurFenetre()/48) && (abscisseSouris()<5*largeurFenetre()/24)) && ((ordonneeSouris()<19*hauteurFenetre()/32) && (ordonneeSouris()>hauteurFenetre()/2)))
		{
			// LEVEL 2
			opt->level = 2;
		}
		// BUTTON "LEVEL 3"
		else if(((abscisseSouris()>5*largeurFenetre()/48) && (abscisseSouris()<5*largeurFenetre()/24)) && ((ordonneeSouris()<15*hauteurFenetre()/32) && (ordonneeSouris()>3*hauteurFenetre()/8)))
		{
			// LEVEL 3
			opt->level = 3;
		}
		// BUTTON "THEME 1"
		if(((abscisseSouris()>29*largeurFenetre()/48) && (abscisseSouris()<37*largeurFenetre()/48)) && ((ordonneeSouris()<23*hauteurFenetre()/32) && (ordonneeSouris()>5*hauteurFenetre()/8)))
		{
			// THEME 1
			opt->theme = 1;
		}
		// BUTTON "THEME 2"
		else if(((abscisseSouris()>29*largeurFenetre()/48) && (abscisseSouris()<37*largeurFenetre()/48)) && ((ordonneeSouris()<19*hauteurFenetre()/32) && (ordonneeSouris()>hauteurFenetre()/2)))
		{
			// THEME 2
			opt->theme = 2;
		}
		// BUTTON "THEME 3"
		else if(((abscisseSouris()>29*largeurFenetre()/48) && (abscisseSouris()<37*largeurFenetre()/48)) && ((ordonneeSouris()<15*hauteurFenetre()/32) && (ordonneeSouris()>3*hauteurFenetre()/8)))
		{
			// THEME 3
			opt->theme = 3;
		}
		
		// BUTTON "NEXT"
		if(((abscisseSouris()>13*largeurFenetre()/15) && (abscisseSouris()<59*largeurFenetre()/60)) && ((ordonneeSouris()<9*hauteurFenetre()/80) && (ordonneeSouris()>7*hauteurFenetre()/160)))
		{
			N = 1;
		}
		else
		{
			N = 0;
		}
		
		// PASSAGE OF CHOICE TO THE DESIRED LEVEL
		if((opt->level != 0) && (opt->theme != 0) && (N == 1))
		{	
			// LEVEL DISPLAY
			*position_affichage = 2;
		}
	}
	// DISPLAY OF THE LEVEL
	else if (*position_affichage == 2)
	{	
		for(int i = 0;i<6;i++)
		{
			// IF THE MOUSE CLICKS ON THE BUTTON
			if(((abscisseSouris()>level->T[i].pos_img.x) && (abscisseSouris()<(level->T[i].pos_img.x) + (level->T[i].img->largeurImage))) && ((ordonneeSouris()<(level->T[i].pos_img.y) + (level->T[i].img->hauteurImage)) && (ordonneeSouris()>level->T[i].pos_img.y)))
			{
				// IF THE PICTURE IS AVAILABLE
				if(level->T[i].etat_img == ACTIVE)
				{
					// PICTURE BECOME CHOSEN
					level->T[i].etat_img = CHOISIE;
					
					// SAVE THE TIME WHEN PICTURE IS CHOSEN
					level->T[i].timeclic = time(NULL);
					
					for(int k = 0;k<6;k++)
					{
						// IF THE PICTURE IS CHOSEN
						if((level->T[k].etat_img == CHOISIE) && (k != i))
						{
							// IF THE DIFFERENT PICTURES HAS THE SAME ID
							if(level->T[i].id_img == level->T[k].id_img)
							{
								// PICTURES BECOME UNAVAILABLE
								level->T[i].etat_img = INACTIVE;
								level->T[k].etat_img = INACTIVE;
							}
							else
							{
								// PICTURES BECOME AVAILABLE
								level->T[i].etat_img = ACTIVE;
								level->T[k].etat_img = ACTIVE;
								
								// RESET THE TIME
								level->T[i].timeclic = 0;
								level->T[k].timeclic = 0;
							}
						}
					}
				}
				// IF THE PICTURE IS CHOSEN
				else if(level->T[i].etat_img == CHOISIE)
				{
					// PICTURE BECOME AVAILABLE
					level->T[i].etat_img = ACTIVE;
					
					// RESET THE TIME
					level->T[i].timeclic = 0;
				}
			}
			
			// IF THE PICTURE IS CHOSEN
			if(level->T[i].etat_img == CHOISIE)
			{
				// IF THE NUMBER OF CLICK == 0
				if(level->T[i].nb_clic == 0)
				{
					// INITIALISATION FOR THE NUMBER OF CLICK = 0
					level->T[i].clic = (Point*)malloc(sizeof(Point)*(level->T[i].nb_clic+1));
					
					level->T[i].clic[level->T[i].nb_clic].x = abscisseSouris();
					level->T[i].clic[level->T[i].nb_clic].y = ordonneeSouris();
				}
				else
				{
					// RE-INITIALISATION FOR THE NUMBER OF CLICK != 0

					Point *newTabClic ;
					newTabClic = (Point*)realloc(level->T[i].clic,sizeof(Point)*(level->T[i].nb_clic+1));
					
					if (newTabClic != NULL)
					{
						level->T[i].clic = newTabClic;
					}
					
					level->T[i].clic[level->T[i].nb_clic].x = abscisseSouris();
					level->T[i].clic[level->T[i].nb_clic].y = ordonneeSouris();
				}
				
				level->T[i].nb_clic++;
			}
			// IF THE PICTURE IS AVAILABLE
			else if(level->T[i].etat_img == ACTIVE)
			{
				// RESET THE NUMBER OF CLICK
				level->T[i].nb_clic = 0;
			}
		}
	}
}


void initLevel (jeux *level, Point position[6], Options *opt)
{
	char chemin[100];
	DonneesImageRGB *tmp = NULL;
	
	// INITIALIZE THE STRUCTURE "JEUX"
	for(int i = 0;i<6;i++)
	{
		// LOAD THE PICTURES
		sprintf(chemin,"level%d/theme%d/image%d.bmp",opt->level,opt->theme,i+1);
		tmp = lisBMPRGB(chemin);
		level->T[i].img = tmp;
		
		// ASSIGN AND ID TO THE PICTURES
		level->T[i].id_img = (i+1) + (i+1)%2;
		
		// ASSIGN A POSITION TO THE PICTURES
		level->T[i].pos_img.x = position[i].x;
		level->T[i].pos_img.y = position[i].y;
		
		// ASSIGN A STATE TO THE PICTURES
		level->T[i].etat_img = ACTIVE;
		
		// 
		level->T[i].timeclic = 0;
		level->T[i].deplacement = NULL;
		level->T[i].nb_deplacement = 0;
		level->T[i].clic = NULL;
		level->T[i].nb_clic = 0;
	}
	
	// 
	level->debut_jeux = time(NULL);
	level->fin_jeux = 0;
	level->sauver = 0;
	
	for(int j = 0;j<3;j++)
	{
		// 
		level->TA[j].item_depart = 0;
		level->TA[j].item_arrivee = 0;
		level->TA[j].distance_ideale = 0;
		level->TA[j].distance_user = 0;
		level->TA[j].nb_tremblement = 0;	
	}
}


void sauveFichier(char nomFichier[20], Options *opt, jeux *level)
{	
	int l = 0;
	
	struct tm debut;
	struct tm fin;
	
	FILE*f;
	f=fopen(nomFichier,"wt");
	if(f==NULL)
	{
		return;
	}
	
	fprintf(f,"Level %d & Theme %d\n",opt->level,opt->theme);
	
	fprintf(f,"Temps de resolution total : %f\n",difftime(level->fin_jeux, level->debut_jeux));
	
	for(int i=0;i<6;i+=2)
	{
		fprintf(f,"\nPaire %d\n",i+1);
		
		if(level->T[i].nb_deplacement > 0)
		{	
			level->TA[l].item_depart = i;
			level->TA[l].item_arrivee = i+1;
		}
		else
		{	
			level->TA[l].item_depart = i+1;
			level->TA[l].item_arrivee = i;
		}
		
		debut=*localtime(&(level->T[level->TA[l].item_depart].timeclic));
		
		fin=*localtime(&(level->T[level->TA[l].item_arrivee].timeclic));
		
		fprintf(f,"\nDebut : %d:%d:%d\n", debut.tm_hour, debut.tm_min, debut.tm_sec);
		
		fprintf(f,"Fin : %d:%d:%d\n", fin.tm_hour, fin.tm_min, fin.tm_sec);
		
		fprintf(f,"Nombre de seconde : %f\n",difftime(level->T[level->TA[l].item_arrivee].timeclic, level->T[level->TA[l].item_depart].timeclic));
		
		fprintf(f,"\n%d Deplacement\n",level->T[level->TA[l].item_depart].nb_deplacement);
		
		for(int k = 0;k<level->T[level->TA[l].item_depart].nb_deplacement;k++)
		{
			fprintf(f,"(%d,%d)\n",level->T[level->TA[l].item_depart].deplacement[k].x,level->T[level->TA[l].item_depart].deplacement[k].y);
		}
		
		fprintf(f,"\n%d Clics\n",level->T[level->TA[l].item_depart].nb_clic);
		
		for(int j = 0;j<level->T[level->TA[l].item_depart].nb_clic;j++)
		{
			fprintf(f,"(%d,%d)\n",level->T[level->TA[l].item_depart].clic[j].x,level->T[level->TA[l].item_depart].clic[j].y);
		}
		
		l++;
	}
	
	fclose(f);
}


void analyseTrajectoire(jeux *level)
{	
	Point milieu_img1;
	Point milieu_img2;
	
	int deltaX;
	int deltaY;
	
	int traj;
	
	int direction = -1;
	
	for(int i = 0;i<3;i++)
	{
		milieu_img1.x = ((level->T[level->TA[i].item_depart].pos_img.x) + (level->T[level->TA[i].item_depart].img->largeurImage))/2;
		milieu_img1.y = ((level->T[level->TA[i].item_depart].pos_img.y) + (level->T[level->TA[i].item_depart].img->hauteurImage))/2;
		
		milieu_img2.x = ((level->T[level->TA[i].item_arrivee].pos_img.x) + (level->T[level->TA[i].item_arrivee].img->largeurImage))/2;
		milieu_img2.y = ((level->T[level->TA[i].item_arrivee].pos_img.y) + (level->T[level->TA[i].item_arrivee].img->hauteurImage))/2;
		
		deltaX = abs(milieu_img1.x - milieu_img2.x);
		deltaY = abs(milieu_img1.y - milieu_img2.y);
		
		level->TA[i].distance_ideale = sqrt(pow(deltaX,2) + pow(deltaY,2));
		
		for(int j = 1;j<level->T[level->TA[i].item_depart].nb_deplacement;j++)
		{
			traj = sqrt(pow(abs(level->T[level->TA[i].item_depart].deplacement[j].x - level->T[level->TA[i].item_depart].deplacement[j-1].x),2) + pow(abs(level->T[level->TA[i].item_depart].deplacement[j].y - level->T[level->TA[i].item_depart].deplacement[j-1].y),2));
			level->TA[i].distance_user += traj;
		}
		
		for(int k = 1;k<level->T[level->TA[i].item_depart].nb_deplacement;k++)
		{
			if((level->T[level->TA[i].item_depart].deplacement[k].x > level->T[level->TA[i].item_depart].deplacement[k-1].x) && (level->T[level->TA[i].item_depart].deplacement[k].y > level->T[level->TA[i].item_depart].deplacement[k-1].y) && direction != HAUT_DROITE)
			{
				direction = HAUT_DROITE;
				level->TA[i].nb_tremblement++;
			}
			else if((level->T[level->TA[i].item_depart].deplacement[k].x > level->T[level->TA[i].item_depart].deplacement[k-1].x) && (level->T[level->TA[i].item_depart].deplacement[k].y < level->T[level->TA[i].item_depart].deplacement[k-1].y) && direction != BAS_DROITE)
			{
				direction = BAS_DROITE;
				level->TA[i].nb_tremblement++;
			}
			else if((level->T[level->TA[i].item_depart].deplacement[k].x < level->T[level->TA[i].item_depart].deplacement[k-1].x) && (level->T[level->TA[i].item_depart].deplacement[k].y < level->T[level->TA[i].item_depart].deplacement[k-1].y) && direction != BAS_GAUCHE)
			{
				direction = BAS_GAUCHE;
				level->TA[i].nb_tremblement++;
			}
			else if((level->T[level->TA[i].item_depart].deplacement[k].x < level->T[level->TA[i].item_depart].deplacement[k-1].x) && (level->T[level->TA[i].item_depart].deplacement[k].y > level->T[level->TA[i].item_depart].deplacement[k-1].y) && direction != HAUT_GAUCHE)
			{
				direction = HAUT_GAUCHE;
				level->TA[i].nb_tremblement++;
			}
		}
	}
}


void afficheAnalyse(jeux *level)
{
	int x1 = 100;
	int y1 = 600;
	
	int pasY = -20;
	int pasYItem = -70;
	
	int tremblTotal = 0;
	
	// NUMBER OF ELEMENTS IN DESCRIPTION
	int nbTexte = 0;
	
	// ELEMENTS OF DESCRIPTION
	char nomPaire[20];
	char distIdeal[50];
	char distParc[50];
	char nbTrembl[50];
	
	// TITLE
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine("Analysis",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,largeurFenetre()/2,7*hauteurFenetre()/8);
	
	// DESCRIPTION
	for(int i = 0;i<3;i++)
	{
		sprintf(nomPaire,"Paire %d:\n",i+1);
		sprintf(distIdeal,"La distance ideale serait de %d\n",level->TA[i].distance_ideale);
		sprintf(distParc,"Vous avez effectue une distance de %d\n",level->TA[i].distance_user);
		sprintf(nbTrembl,"Pour un nombre de tremblement egal a %d\n",level->TA[i].nb_tremblement);
		
		couleurCourante(255,255,255);
		epaisseurDeTrait(3);
		
		// DISPLAY ELEMENT
		afficheChaine(nomPaire,18,x1,y1+(pasYItem*i)+(pasY*nbTexte));
		
		// INCREASE THE NUMBER OF ELEMENT
		nbTexte++;
		
		// DISPLAY ELEMENT
		afficheChaine(distIdeal,18,x1,y1+(pasYItem*i)+(pasY*nbTexte));
		
		// INCREASE THE NUMBER OF ELEMENT
		nbTexte++;
		
		// DISPLAY ELEMENT
		afficheChaine(distParc,18,x1,y1+(pasYItem*i)+(pasY*nbTexte));
		
		// INCREASE THE NUMBER OF ELEMENT
		nbTexte++;
		
		// DISPLAY ELEMENT
		afficheChaine(nbTrembl,18,x1,y1+(pasYItem*i)+(pasY*nbTexte));
		
		// INCREASE THE NUMBER OF ELEMENT
		nbTexte++;
		
		tremblTotal += level->TA[i].nb_tremblement;
	}
	
	// CONCLUSION
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	
	if(tremblTotal <= 3)
	{
		afficheChaine("Ne tremble pas du tout",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,40*largeurFenetre()/120,hauteurFenetre()/16);
	}
	else if((tremblTotal > 3) && (tremblTotal <= 5))
	{
		afficheChaine("Tremble un peu",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,45*largeurFenetre()/120,hauteurFenetre()/16);
	}
	else if((tremblTotal > 5) && (tremblTotal <= 10))
	{
		afficheChaine("Tremble moyennement",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,45*largeurFenetre()/120,hauteurFenetre()/16);
	}
	else if((tremblTotal > 10) && (tremblTotal <= 15))
	{
		afficheChaine("Tremble beaucoup",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,45*largeurFenetre()/120,hauteurFenetre()/16);
	}
	else
	{
		afficheChaine("Tremble enormement",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,45*largeurFenetre()/120,hauteurFenetre()/16);
	}
}
