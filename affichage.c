#include <stdlib.h> // USE exit()
#include <stdio.h> // EMPLOY printf()
#include <math.h> // USE sin() AND cos()
#include "GfxLib.h" // DO GRAPHIC
#include "toolbox.h"


// DISPLAY THE DESKTOP BACKGROUND AND THE BUTTON "QUIT"
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


// DISPLAY THE MENU
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
	int anime1 = -1;
		
	int img_inactive = 0;
	
	char titre[50];
	
	DonneesImageRGB *donneesImage = NULL ;
	DonneesImageRGB *faceImage = NULL ;
	
	// TITLE
	sprintf(titre,"Level %d et theme %d",opt->level,opt->theme);
	couleurCourante(255,255,255);
	epaisseurDeTrait(3);
	afficheChaine(titre,15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,largeurFenetre()/3,7*hauteurFenetre()/8);
	
	// PICTURES
	for(int j = 0;j<level->nb_img;j++)
	{	
		if ((level->T[j].img != NULL) && (level->T[j].etat_img == ACTIVE)) // IF THE PICTURE EXISTS AND AVAILABLE
		{
			// DISPLAY THE PICTURE
			ecrisImageSansFond(level->T[j].pos_img.x, level->T[j].pos_img.y, level->verso->largeurImage, level->verso->hauteurImage, level->verso->donneesRGB, RGB);
		}
		else if ((level->T[j].img != NULL) && (level->T[j].etat_img == CHOISIE)) // IF THE PICTURE EXISTS AND CHOSEN
		{
			couleurCourante(255,0,0);
			epaisseurDeTrait(3);
			rectangle(level->T[j].pos_img.x - 2, level->T[j].pos_img.y - 2,level->T[j].pos_img.x + level->recto->largeurImage + 2, level->T[j].pos_img.y + level->recto->hauteurImage + 2) ;
			
			// DISPLAY THE PICTURE CHOSEN
			ecrisImageSansFond(level->T[j].pos_img.x, level->T[j].pos_img.y, level->recto->largeurImage, level->recto->hauteurImage, level->recto->donneesRGB, RGB);
			ecrisImageSansFond(level->T[j].pos_img.x, level->T[j].pos_img.y, level->T[j].img->largeurImage, level->T[j].img->hauteurImage, level->T[j].img->donneesRGB, RGB);
		}
		else
		{
			// INCREASE NUMBER OF PICTURES UNAVAILABLE
			img_inactive++;
			
			if (level->T[j].anime <= 0)
			{
				ecrisImageSansFond(level->T[j].pos_img.x, level->T[j].pos_img.y, level->recto->largeurImage, level->recto->hauteurImage, level->recto->donneesRGB, RGB);
				ecrisImageSansFond(level->T[j].pos_img.x, level->T[j].pos_img.y, level->T[j].img->largeurImage, level->T[j].img->hauteurImage, level->T[j].img->donneesRGB, RGB);
			}
			else
			{
				anime1 = 1 ;
			}
		}
	}
	
	if (anime1 != -1)
	{
		int vitesse ;
		
		for (int i=0; i<level->nb_img; i++)
		{
			if (level->T[i].anime > 0)
			{
				level->T[i].anime-=2 ;
 				if (level->T[i].anime<0)
 				{
 					level->T[i].anime=0 ;
 				}
				if (level->T[i].anime >= 50)
				{
					vitesse = (level->T[i].anime - 50) * 2 ;
					faceImage = ReduitVerticalBMP(level->recto,vitesse) ;
					ecrisImageSansFond(level->T[i].pos_img.x, level->T[i].pos_img.y, faceImage->largeurImage, faceImage->hauteurImage, faceImage->donneesRGB, RGB);	
					libereDonneesImageRGB(&faceImage) ;
		
					donneesImage = ReduitVerticalBMP(level->T[i].img,vitesse) ;
					ecrisImageSansFond(level->T[i].pos_img.x, level->T[i].pos_img.y, donneesImage->largeurImage, donneesImage->hauteurImage, donneesImage->donneesRGB, RGB);
					libereDonneesImageRGB(&donneesImage) ;
				}
				else
				{
					vitesse = 100-(level->T[i].anime * 2) ;
					faceImage = ReduitVerticalBMP(level->verso,vitesse) ;
					ecrisImageSansFond(level->T[i].pos_img.x, level->T[i].pos_img.y, faceImage->largeurImage, faceImage->hauteurImage, faceImage->donneesRGB, RGB);
					libereDonneesImageRGB(&faceImage) ;
				}
			}
		}
	}
	
	// IF ALL PICTURES UNAVAILABLE 
	if((img_inactive == level->nb_img) && (anime1 == -1))
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


// DISPLAY THE ANALYSIS
void afficheAnalyse(jeux *level, couleur RGB)
{
	int x1 = 100;
	int y1 = 600;
	
	int pasY = -20;
	int pasYItem = -40;
	
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
	for(int i = level->first_scroll;i<level->nb_pairs && i<level->first_scroll+4;i++)
	{
		sprintf(nomPaire,"Pair %d:\n",level->T[level->TA[i].item_depart].id_img);
		sprintf(distIdeal,"The ideal distance was %d\n",level->TA[i].distance_ideale);
		sprintf(distParc,"You did a distance of %d\n",level->TA[i].distance_user);
		sprintf(nbTrembl,"For a number of tremor equal to %d\n",level->TA[i].nb_tremblement);
		
		couleurCourante(255,255,255);
		epaisseurDeTrait(3);
		
		// DISPLAY ELEMENT
		afficheChaine(nomPaire,18,x1,y1+(pasYItem*i)+(pasY*nbTexte));
		
		// INCREASE THE NUMBER OF ELEMENT
		nbTexte++;
		
		// DISPLAY THUMBNAIL
		ecrisImageSansFond(x1-85,y1+(pasYItem*i)+(pasY*nbTexte), level->thumbnail_recto->largeurImage, level->thumbnail_recto->hauteurImage, level->thumbnail_recto->donneesRGB, RGB);
		ecrisImageSansFond(x1-85,y1+(pasYItem*i)+(pasY*nbTexte), level->T[level->TA[i].item_depart].thumbnail->largeurImage, level->T[level->TA[i].item_depart].thumbnail->hauteurImage, level->T[level->TA[i].item_depart].thumbnail->donneesRGB, RGB);
		
		ecrisImageSansFond(x1-50,y1+(pasYItem*i)+(pasY*nbTexte), level->thumbnail_recto->largeurImage, level->thumbnail_recto->hauteurImage, level->thumbnail_recto->donneesRGB, RGB);
		ecrisImageSansFond(x1-50,y1+(pasYItem*i)+(pasY*nbTexte), level->T[level->TA[i].item_arrivee].thumbnail->largeurImage, level->T[level->TA[i].item_arrivee].thumbnail->hauteurImage, level->T[level->TA[i].item_arrivee].thumbnail->donneesRGB, RGB);
		
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
		afficheChaine("Do not tremble at all",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,40*largeurFenetre()/120,hauteurFenetre()/16);
	}
	else if((tremblTotal > 3) && (tremblTotal <= 5))
	{
		afficheChaine("Tremble a little",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,45*largeurFenetre()/120,hauteurFenetre()/16);
	}
	else if((tremblTotal > 5) && (tremblTotal <= 10))
	{
		afficheChaine("Tremble moderately",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,45*largeurFenetre()/120,hauteurFenetre()/16);
	}
	else if((tremblTotal > 10) && (tremblTotal <= 15))
	{
		afficheChaine("Tremble a lot",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,45*largeurFenetre()/120,hauteurFenetre()/16);
	}
	else
	{
		afficheChaine("Tremble enormously",15*pow(10,-5)*(largeurFenetre()*hauteurFenetre())/4,45*largeurFenetre()/120,hauteurFenetre()/16);
	}
}
