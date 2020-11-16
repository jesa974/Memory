#include <stdlib.h> // USE exit()
#include <stdio.h> // EMPLOY printf()
#include "toolbox.h"


// INITIALISE FIXED POSITIONS
void initPositionFixe (Point pos_fixe[16])
{	
	// BOTTOM
	pos_fixe[0].x = 50;
	pos_fixe[0].y = 100;
	
	pos_fixe[1].x = 180;
	pos_fixe[1].y = 100;
	
	pos_fixe[2].x = 310;
	pos_fixe[2].y = 100;
	
	pos_fixe[3].x = 440;
	pos_fixe[3].y = 100;
	
	pos_fixe[4].x = 570;
	pos_fixe[4].y = 100;
	
	pos_fixe[5].x = 700;
	pos_fixe[5].y = 100;
	
	pos_fixe[6].x = 830;
	pos_fixe[6].y = 100;
	
	pos_fixe[7].x = 960;
	pos_fixe[7].y = 100;
	
	// TOP
	pos_fixe[8].x = 50;
	pos_fixe[8].y = 300;
	
	pos_fixe[9].x = 180;
	pos_fixe[9].y = 300;
	
	pos_fixe[10].x = 310;
	pos_fixe[10].y = 300;
	
	pos_fixe[11].x = 440;
	pos_fixe[11].y = 300;
	
	pos_fixe[12].x = 570;
	pos_fixe[12].y = 300;
	
	pos_fixe[13].x = 700;
	pos_fixe[13].y = 300;
	
	pos_fixe[14].x = 830;
	pos_fixe[14].y = 300;
	
	pos_fixe[15].x = 960;
	pos_fixe[15].y = 300;
}


// INITIALISE LEVEL
void initLevel (jeux *level, Point position[16], Options *opt)
{
	int pos_aleat;
	int aleatoire;
	
	char nomConfig[100];
	
	char chemin[100];
	
	DonneesImageRGB *tmp = NULL;
	
	sprintf(nomConfig,"level%d/theme%d/config.txt",opt->level,opt->theme);
	
	// OPENING THE CONFIGURATION FILE
	FILE*f;
	f=fopen(nomConfig,"rt");
	
	// SAVE THE NUMBER OF PICTURES
	fscanf(f,"nb_img = %d\n",&(level->nb_img));
	
	level->T = (item*)malloc(sizeof(item)*(level->nb_img));
	
	level->nb_pairs = (level->nb_img)/2;
	
	level->TA = (analyse*)malloc(sizeof(analyse)*(level->nb_pairs));
	
	int T[level->nb_img];
	
	for(int j = 0;j<level->nb_img;j++)
	{
		T[j] = 0;
	}
	
	// DETERMINE IF POSITIONS OF PICTURES ARE RANDOM
	fscanf(f,"random = %d\n",&(aleatoire));
	
	for(int i = 0;i<level->nb_img;i++)
	{
		// LOAD THE PICTURES
		fscanf(f,"nom = %s\n",chemin);
		tmp = lisBMPRGB(chemin);
		level->T[i].img = tmp;
		
		level->T[i].thumbnail = downsizeBMP(level->T[i].img,level->T[i].img->largeurImage/4,level->T[i].img->hauteurImage/4);
		
		// ASSIGN AN ID TO THE PICTURES
		fscanf(f,"id = %d\n",&(level->T[i].id_img));
		
		// ASSIGN A PREDETERMINED POSITION TO THE PICTURES
		fscanf(f,"(%d,%d)\n",&(level->T[i].pos_img.x),&(level->T[i].pos_img.y));
	}
	
	for(int i = 0;i<level->nb_img;i++)
	{
		if(aleatoire == VRAI)
		{
			// ASSIGN A RANDOM POSITION TO THE PICTURES
			pos_aleat = rand_a_b(0,level->nb_img);
		
			while(T[pos_aleat] != 0)
			{
				if(pos_aleat+1 < level->nb_img)
				{
					pos_aleat++;
				}
				else
				{
					pos_aleat = 0;
				}
			}
			
			T[pos_aleat] = 1;
			
			level->T[i].pos_img.x = position[pos_aleat].x;
			level->T[i].pos_img.y = position[pos_aleat].y;
		}
	}
		
	for(int i=0;i<level->nb_img;i++)
	{
		// ASSIGN A STATE TO THE PICTURES
		level->T[i].etat_img = ACTIVE;
		
		// 
		level->T[i].timeclic = 0;
		level->T[i].deplacement = NULL;
		level->T[i].nb_deplacement = 0;
		level->T[i].clic = NULL;
		level->T[i].nb_clic = 0;
		level->T[i].erreur = NULL;
		level->T[i].nb_erreur = 0;
		level->T[i].anime = 0;
	}
	fclose(f);
	
	// 
	level->debut_jeux = time(NULL);
	level->fin_jeux = 0;
	level->sauver = 0;
	level->first_scroll = 0;
	
	level->recto = lisBMPRGB("fond/FondRecto.bmp");
	level->thumbnail_recto = downsizeBMP(level->recto,level->recto->largeurImage/4,level->recto->hauteurImage/4);
	
	level->verso = lisBMPRGB("fond/FondVerso.bmp");
	level->thumbnail_verso = downsizeBMP(level->verso,level->verso->largeurImage/4,level->verso->hauteurImage/4);
	
	for(int j = 0;j<level->nb_pairs;j++)
	{
		// 
		level->TA[j].item_depart = -1;
		level->TA[j].item_arrivee = -1;
		level->TA[j].distance_ideale = 0;
		level->TA[j].distance_user = 0;
		level->TA[j].nb_tremblement = 0;	
	}
}
