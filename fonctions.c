#include <stdlib.h> // USE exit()
#include <stdio.h> // EMPLOY printf()
#include <math.h> // USE sin() AND cos()
#include <unistd.h> 
#include "GfxLib.h" // DO GRAPHIC
#include "toolbox.h"


// RANDOM INTEGER BETWEEN A AND B FOR A<B
int rand_a_b(int a, int b)
{
	int var = 0;
	
	var = rand()%(b-a) + a;
	
	return var;
}


// MOUSE MOVEMENT MANAGEMENT
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


// CLICK MANAGEMENT
void gereClic (int *position_affichage, Options *opt, jeux *level)
{
	int N = 0;
	
	// BUTTON "QUIT"
	if(((abscisseSouris()>227*largeurFenetre()/240) && (abscisseSouris()<59*largeurFenetre()/60)) && ((ordonneeSouris()<39*hauteurFenetre()/40) && (ordonneeSouris()>149*hauteurFenetre()/160)))
	{
		// STOP THE GAME AND CLOSE THE WINDOW
		if(*position_affichage >= 2)
		{
			for(int i = 0;i<level->nb_img;i++)
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
		int image_base = -1 ;
		
		for(int i = 0;i<level->nb_img;i++)
		{
			// IF THE MOUSE CLICKS ON THE BUTTON
			if(((abscisseSouris()>level->T[i].pos_img.x) && (abscisseSouris()<(level->T[i].pos_img.x) + (level->T[i].img->largeurImage))) && ((ordonneeSouris()<(level->T[i].pos_img.y) + (level->T[i].img->hauteurImage)) && (ordonneeSouris()>level->T[i].pos_img.y)))
			{
				// IF THE PICTURE IS AVAILABLE
				if(level->T[i].etat_img == ACTIVE)
				{
					// PICTURE BECOME CHOSEN
					level->T[i].etat_img = CHOISIE;
					
					gereClicTraj(level,&i);
					
					// SAVE THE TIME WHEN PICTURE IS CHOSEN
					level->T[i].timeclic = time(NULL);
					
					for(int k = 0;k<level->nb_img;k++)
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
								
								//level->T[i].anime = 100;
								//level->T[k].anime = 100;
								
								gereClicTraj(level,&k);
								
								image_base = -1 ;
							}
							else
							{	
								// PICTURES BECOME AVAILABLE
								level->T[i].etat_img = ACTIVE;
								level->T[k].etat_img = ACTIVE;
								
								gereErreur(level,&k,&i);
								
								// RESET THE TIME
								level->T[i].timeclic = 0;
								level->T[k].timeclic = 0;
								
								libereClicTraj(level,&i) ;
								libereClicTraj(level,&k) ;
								
								image_base = -1 ;
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
					
					libereClicTraj(level,&i) ;
					
					image_base = -1 ;
				}
			}
			else
			{
				if(level->T[i].etat_img == CHOISIE)
				{
					image_base = i ;
				}
			}
		}
		if (image_base != -1)
		{
			gereClicTraj(level,&image_base);
		}
	} 
}


void gereIDimg ()
{
	
}


void gereClicTraj(jeux *level, int *i)
{
	// IF THE NUMBER OF CLICK == 0
	if(level->T[*i].nb_clic == 0)
	{
		// INITIALISATION FOR THE NUMBER OF CLICK = 0
		level->T[*i].clic = (Point*)malloc(sizeof(Point)*(level->T[*i].nb_clic+1));
		
		level->T[*i].clic[level->T[*i].nb_clic].x = abscisseSouris();
		level->T[*i].clic[level->T[*i].nb_clic].y = ordonneeSouris();
	}
	else
	{
		// RE-INITIALISATION FOR THE NUMBER OF CLICK != 0

		Point *newTabClic ;
		newTabClic = (Point*)realloc(level->T[*i].clic,sizeof(Point)*(level->T[*i].nb_clic+1));
		
		if (newTabClic != NULL)
		{
			level->T[*i].clic = newTabClic;
		}
		
		level->T[*i].clic[level->T[*i].nb_clic].x = abscisseSouris();
		level->T[*i].clic[level->T[*i].nb_clic].y = ordonneeSouris();
	}
	
	level->T[*i].nb_clic++;
}


void libereClicTraj(jeux *level, int *i)
{
	// RESET THE NUMBER OF CLICK
	if (level->T[*i].nb_clic > 0)
	{
		level->T[*i].nb_clic = 0;
		free(level->T[*i].clic) ;
		level->T[*i].clic = NULL ;
	}
}


void gereErreur(jeux *level, int *i, int *k)
{
	// IF THE NUMBER OF ERROR == 0
	if(level->T[*i].nb_erreur == 0)
	{
		// INITIALISATION FOR THE NUMBER OF ERROR = 0
		level->T[*i].erreur = (int*)malloc(sizeof(int)*(level->T[*i].nb_erreur+1));
		
		level->T[*i].erreur[level->T[*i].nb_erreur] = level->T[*k].id_img;
	}
	else
	{
		// RE-INITIALISATION FOR THE NUMBER OF ERROR != 0

		int *newTabClic ;
		newTabClic = (int*)realloc(level->T[*i].erreur,sizeof(int)*(level->T[*i].nb_erreur+1));
		
		if (newTabClic != NULL)
		{
			level->T[*i].erreur = newTabClic;
		}
		
		level->T[*i].erreur[level->T[*i].nb_erreur] = level->T[*k].id_img;
	}
	
	level->T[*i].nb_erreur++;

}


// SAVE DATA INTO A TEXT FILE
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
	
	for(int i=0;i<level->nb_img;i++)
	{
		int trouve = 0 ;
		
		for (int j=0;j<level->nb_pairs;j++)
		{
			if (level->TA[j].item_depart == i || level->TA[j].item_arrivee == i)
			{
				trouve = 1 ;
			}
		}
		
		if (trouve == 0)
		{
			int indice_arrivee ;
			
			for (int j = i+1; j <level->nb_img;j++)
			{
				if (level->T[j].id_img == level->T[i].id_img)
				{
					indice_arrivee = j ;
				}
			}
		
			fprintf(f,"\nPaire %d\n",level->T[i].id_img);
			
			if(level->T[i].nb_deplacement > 0)
			{	
				level->TA[l].item_depart = i;
				level->TA[l].item_arrivee = indice_arrivee;
			}
			else
			{	
				level->TA[l].item_depart = indice_arrivee;
				level->TA[l].item_arrivee = i;
			}
			
			debut=*localtime(&(level->T[level->TA[l].item_depart].timeclic));
			
			fin=*localtime(&(level->T[level->TA[l].item_arrivee].timeclic));
			
			fprintf(f,"\nDebut : %d:%d:%d\n", debut.tm_hour, debut.tm_min, debut.tm_sec);
			
			fprintf(f,"Fin : %d:%d:%d\n", fin.tm_hour, fin.tm_min, fin.tm_sec);
			
			fprintf(f,"Nombre de seconde : %f\n",difftime(level->T[level->TA[l].item_arrivee].timeclic, level->T[level->TA[l].item_depart].timeclic));
			
			fprintf(f,"\n%d Erreurs\n",(level->T[level->TA[l].item_depart].nb_erreur + level->T[level->TA[l].item_arrivee].nb_erreur));
			
			for(int i = 0;i<level->T[level->TA[l].item_depart].nb_erreur;i++)
			{
				fprintf(f,"(id image fausse %d)\n",level->T[level->TA[l].item_depart].erreur[i]);
			}
			
			for(int i = 0;i<level->T[level->TA[l].item_arrivee].nb_erreur;i++)
			{
				fprintf(f,"(id image fausse %d)\n",level->T[level->TA[l].item_arrivee].erreur[i]);
			}
			
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
	}
	
	fclose(f);
}


// ANALYSE THE TRAJECTORY
void analyseTrajectoire(jeux *level)
{	
	float deltaX;
	float deltaY;
	
	float total;
	
	float traj;
	
	int direction = -1;
	
	for(int i = 0;i<level->nb_pairs;i++)
	{	
		deltaX = abs(level->T[level->TA[i].item_depart].clic[0].x - level->T[level->TA[i].item_depart].clic[level->T[level->TA[i].item_depart].nb_clic-1].x);
		deltaY = abs(level->T[level->TA[i].item_depart].clic[0].y - level->T[level->TA[i].item_depart].clic[level->T[level->TA[i].item_depart].nb_clic-1].y);
		
		total = sqrt(pow(deltaX,2) + pow(deltaY,2));
		
		level->TA[i].distance_ideale = total;
		
		
		deltaX = abs(level->T[level->TA[i].item_depart].clic[0].x - level->T[level->TA[i].item_depart].deplacement[0].x);
		deltaY = abs(level->T[level->TA[i].item_depart].clic[0].y - level->T[level->TA[i].item_depart].deplacement[0].y);
		total = sqrt(pow(deltaX,2) + pow(deltaY,2));
		
		
		for(int j = 1;j<level->T[level->TA[i].item_depart].nb_deplacement;j++)
		{
			deltaX = (float)abs(level->T[level->TA[i].item_depart].deplacement[j].x - level->T[level->TA[i].item_depart].deplacement[j-1].x);
			deltaY = (float)abs(level->T[level->TA[i].item_depart].deplacement[j].y - level->T[level->TA[i].item_depart].deplacement[j-1].y);
			
			traj = sqrt(pow(deltaX,2) + pow(deltaY,2));
			total += traj;
			
		}
		
		deltaX = abs(level->T[level->TA[i].item_depart].clic[level->T[level->TA[i].item_depart].nb_clic-1].x - level->T[level->TA[i].item_depart].deplacement[level->T[level->TA[i].item_depart].nb_deplacement-1].x);
		deltaY = abs(level->T[level->TA[i].item_depart].clic[level->T[level->TA[i].item_depart].nb_clic-1].y - level->T[level->TA[i].item_depart].deplacement[level->T[level->TA[i].item_depart].nb_deplacement-1].y);
		total += sqrt(pow(deltaX,2) + pow(deltaY,2));		
		
		level->TA[i].distance_user = total ;
		
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
