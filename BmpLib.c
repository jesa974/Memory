/* Veuillez reporter tout commentaire a ghislain.oudinet@isen.fr */

/*
	Version 1.2 (21/01/2009) : ajout du support en lecture des BMP orientes de haut en bas
	Version 1.1 : modification du code de libereDonneesImageRGB pour le rendre
		plus robuste.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "BmpLib.h"
#include "OutilsLib.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

//#define DEBUGMODE


float arrondit (const float x)
{
  if (0 <= x)
    return floor(x +(float)0.5);
  else
    return ceil(x -(float)0.5);
}

/* Fonction s'occupant de la liberation complete d'une structure DonneesImageRGB */
void libereDonneesImageRGB(DonneesImageRGB **structure)
{
	if
		(structure != NULL)
	{
		if
			(*structure != NULL)
		{
			if ((*structure)->donneesRGB != NULL)
			{
				free((*structure)->donneesRGB);
			}
			free(*structure);
		}
		*structure = NULL;
	}
}

/* Renvoine la longueur d'une scanline, qui doit etre multiple de quatre octets */
static int tailleScanLineRGB(int largeurImage)
{
	return (largeurImage*3+3)&(int)0x0FFFFFFFCL;
}

DonneesImageRGB *FlipVerticalBMP(DonneesImageRGB *source)
{
	DonneesImageRGB *donneesImage = (DonneesImageRGB*)calloc(1, sizeof(DonneesImageRGB));
	donneesImage->largeurImage = source->largeurImage ;
	donneesImage->hauteurImage = source->hauteurImage ;
	donneesImage->donneesRGB = NULL ;
	
	unsigned char *pointeurDonneesSrc;
	unsigned char *pointeurDonneesDest;
	
	pointeurDonneesSrc = source->donneesRGB ;
	
	if ((donneesImage->donneesRGB = (unsigned char *)malloc((unsigned int)donneesImage->largeurImage*(unsigned int)donneesImage->hauteurImage*3)) != NULL)
	{
		pointeurDonneesDest = donneesImage->donneesRGB ;
		for (unsigned int i = 0; i < (unsigned int)donneesImage->hauteurImage; i++)
		{
			pointeurDonneesSrc = source->donneesRGB + (i+1)*(unsigned int)donneesImage->largeurImage*3 ;
			for (unsigned int j = 0; j < (unsigned int)donneesImage->largeurImage*3; j+=3)
			{
				pointeurDonneesSrc-=3 ;
				memcpy(pointeurDonneesDest,pointeurDonneesSrc,3) ;
				pointeurDonneesDest+=3;
			}
		}
		
	}
	else
	{
		donneesImage->donneesRGB = NULL ;
	}
	
	return donneesImage ;
}

DonneesImageRGB *FlipHorizontalBMP(DonneesImageRGB *source)
{
	DonneesImageRGB *donneesImage = (DonneesImageRGB*)calloc(1, sizeof(DonneesImageRGB));
	donneesImage->largeurImage = source->largeurImage ;
	donneesImage->hauteurImage = source->hauteurImage ;
	donneesImage->donneesRGB = NULL ;
	
	unsigned char *pointeurDonneesSrc;
	unsigned char *pointeurDonneesDest;
	
	pointeurDonneesSrc = source->donneesRGB ;
	
	if ((donneesImage->donneesRGB = (unsigned char *)malloc((unsigned int)donneesImage->largeurImage*(unsigned int)donneesImage->hauteurImage*3)) != NULL)
	{
		pointeurDonneesDest = donneesImage->donneesRGB ;
		for (unsigned int i = 0; i < (unsigned int)donneesImage->hauteurImage; i++)
		{
			pointeurDonneesSrc = source->donneesRGB + ((unsigned int)donneesImage->hauteurImage-i-1)*(unsigned int)donneesImage->largeurImage*3 ;
			memcpy(pointeurDonneesDest,pointeurDonneesSrc,(unsigned int)donneesImage->largeurImage*3) ;
			pointeurDonneesDest+=(unsigned int)donneesImage->largeurImage*3 ;
		}
		
	}
	else
	{
		donneesImage->donneesRGB = NULL ;
	}
	
	return donneesImage ;
}

DonneesImageRGB *ReduitVerticalBMP(DonneesImageRGB *source, int ratio)
{
	DonneesImageRGB *donneesImage = (DonneesImageRGB*)calloc(1, sizeof(DonneesImageRGB));
	donneesImage->largeurImage = source->largeurImage ;
	donneesImage->hauteurImage = source->hauteurImage ;
	donneesImage->donneesRGB = NULL ;
	
	unsigned char *pointeurDonneesSrc;
	unsigned char *pointeurDonneesDest;
	
	unsigned char T[3] = {0,0,255} ;
	
	pointeurDonneesSrc = source->donneesRGB ;
	
	unsigned int centre ;
	unsigned int lignePaire ;
	
	if ((unsigned int)donneesImage->largeurImage % 2 == 0) 
	{
		lignePaire = 1 ;
		centre = (unsigned int)(((unsigned int)donneesImage->largeurImage) / (unsigned int)2) ;
	}
	else
	{
		lignePaire = 0 ;
		centre = (unsigned int)(((unsigned int)donneesImage->largeurImage+1) / (unsigned int)2) ;
	}
	
	float ratioC = (float)centre / (1.0 + ((float)centre -1.0)*(float)ratio/100.0) ;
	
 	//printf("Largeur : %d - centre : %d - lignePaire : %d - ratio : %f\n",(unsigned int)donneesImage->largeurImage,centre,lignePaire,ratioC) ;
	
	if ((donneesImage->donneesRGB = (unsigned char *)malloc((unsigned int)donneesImage->largeurImage*(unsigned int)donneesImage->hauteurImage*3)) != NULL)
	{
		pointeurDonneesDest = donneesImage->donneesRGB ;
		for (unsigned int i = 0; i < (unsigned int)donneesImage->hauteurImage; i++)
		{
			
			pointeurDonneesDest = donneesImage->donneesRGB + i*(unsigned int)donneesImage->largeurImage*3 + centre*3 ;
			pointeurDonneesSrc = source->donneesRGB + i*(unsigned int)donneesImage->largeurImage*3 + centre*3 ;
	
		
			for (unsigned int j = 0; j < centre; j++)
			{
				if ((centre + lignePaire + ((unsigned int)(j*ratioC))) > (unsigned int)donneesImage->largeurImage)
				{
					memcpy(pointeurDonneesDest-(lignePaire*3)-(j*3),T,3) ;
					memcpy(pointeurDonneesDest+(j*3),T,3) ;
				}
				else
				{
					memcpy(pointeurDonneesDest-(lignePaire*3)-(j*3),pointeurDonneesSrc-(((unsigned int)(j*ratioC))*3),3) ;
					memcpy(pointeurDonneesDest+(j*3),pointeurDonneesSrc+(((unsigned int)(j*ratioC))*3),3) ;
				}
			}
		}
	}
	else
	{
		donneesImage->donneesRGB = NULL ;
	}
	
	return donneesImage ;
}

DonneesImageRGB *downsizeBMP(DonneesImageRGB *source,int newL, int newH)
{
	DonneesImageRGB *donneesImage = (DonneesImageRGB*)calloc(1, sizeof(DonneesImageRGB));
	donneesImage->largeurImage = newL ;
	donneesImage->hauteurImage = newH ;
	donneesImage->donneesRGB = NULL ;
	
	unsigned char *pointeurDonneesSrc;
	unsigned int colonneSource;
	unsigned int colonneDestination ;
	unsigned int j;
	
	unsigned int ligneSource ;
	unsigned int ligneDestination ;
	unsigned int i ;
	
	unsigned char T[3] = {0,0,0} ;
	
	pointeurDonneesSrc = source->donneesRGB ;
	
	float ratioL ;
	float ratioH ;

	ratioL = (float)newL / (float)source->largeurImage ;
	ratioH = (float)newH / (float)source->hauteurImage ;
	
	if ((donneesImage->donneesRGB = (unsigned char *)malloc((unsigned int)donneesImage->largeurImage*(unsigned int)donneesImage->hauteurImage*3)) != NULL)
	{
		ligneSource = 0 ;
		ligneDestination = 0 ;
		i = 0 ;
		
		while (i < (unsigned int)source->hauteurImage)
		{
			if ((unsigned int)arrondit(ratioH*i) > ligneDestination || ligneDestination == (unsigned int)(donneesImage->hauteurImage-1) )
			{
				if (ligneDestination == (unsigned int)(donneesImage->hauteurImage-1))
				{
					i = (unsigned int)source->hauteurImage - 1 ;
				}
				else
				{
					i-- ;
				}
				
				colonneSource = 0 ;
				colonneDestination = 0 ;
				j = 0 ;
				
				while (j < (unsigned int)source->largeurImage)
				{
					//if ((unsigned int)arrondit(ratioL*j) > colonneDestination || j == ((unsigned int)source->largeurImage-1))
					if ((unsigned int)arrondit(ratioL*j) > colonneDestination || colonneDestination == (unsigned int)(donneesImage->largeurImage-1) )
					{
						//if ((unsigned int)arrondit(ratioL*j) > colonneDestination)
						//	j-- ;
						
						if (colonneDestination == (unsigned int)(donneesImage->largeurImage-1))
						{
							j = (unsigned int)source->largeurImage -1 ;
						}
						else
						{
							j-- ;
						}
						
						memcpy(T,pointeurDonneesSrc+(unsigned int)source->largeurImage*ligneSource*3+colonneSource*3,3) ;

						for (unsigned int i1 = ligneSource; i1<=i; i1++)
						{
							for (unsigned int j1 = colonneSource; j1<=j; j1++)
							{
								T[0] = (T[0] + *(pointeurDonneesSrc+(unsigned int)source->largeurImage*i1*3+j1*3)) / 2 ;
								T[1] = (T[1] + *(pointeurDonneesSrc+(unsigned int)source->largeurImage*i1*3+j1*3 + 1)) / 2 ;
								T[2] = (T[2] + *(pointeurDonneesSrc+(unsigned int)source->largeurImage*i1*3+j1*3 + 2)) / 2 ;
							}
						}

						memcpy(donneesImage->donneesRGB + (unsigned int)donneesImage->largeurImage*ligneDestination*3+colonneDestination*3,T,3) ;
						colonneDestination += (colonneDestination == (unsigned int)(donneesImage->largeurImage))?0:1 ;
						colonneSource = j+1; 
					}
					j++ ;
				}
				
				ligneDestination += (ligneDestination == (unsigned int)(donneesImage->hauteurImage))?0:1 ;
				ligneSource = i+1 ;		
			}
			i++ ;
		}
	}
	else
	{
		donneesImage->donneesRGB = NULL ;
	}
	
	return donneesImage ;
}

/* Fonction essayant de lire le fichier passe en parametre, et renvoyant une structure
	contenant les informations de l'image en cas de succes, NULL sinon */
DonneesImageRGB *lisBMPRGB(char *nom)
{
	DonneesImageRGB *donneesImage = (DonneesImageRGB*)calloc(1, sizeof(DonneesImageRGB));
	bool toutOK = false;
	
	if
		(donneesImage != NULL)
	{
		/* donneesImage != NULL */

		FILE *fichierBMP;
		
		if
			((fichierBMP = fopen(nom, "rb")) != NULL)
		{
			/* fichierBMP != NULL */

			/* Si le header commence bien par 'B' et 'M'... */
			if
				(fgetc(fichierBMP) == 'B' && fgetc(fichierBMP) == 'M')
			{
				/* ... alors la suite du fichier peut etre interpretee */
				int fileHeader[3];
				
				if
					(fread(fileHeader, sizeof(fileHeader), 1, fichierBMP) == 1)
				{
					/* Lecture du header de fichier */
					int offsetDonnees = little32VersNatif(fileHeader[2]);
					
					int bitmapInfoHeader[10];
					if
						(fread(bitmapInfoHeader, sizeof(bitmapInfoHeader), 1, fichierBMP) == 1)
					{
						/* On ne lit que les images 24 bits non compressees */
						if
							((little32VersNatif(bitmapInfoHeader[3]) == 0x00180001) && (little32VersNatif(bitmapInfoHeader[4]) == 0))
						{
							bool hautVersBas = false; // Utile pour detecter les BMP allant de haut en bas au lieu de bas vers haut
							/* Lecture du header de bitmap (uniquement les informations qui nous interessent) */
							donneesImage->largeurImage = little32VersNatif(bitmapInfoHeader[1]);
							donneesImage->hauteurImage = little32VersNatif(bitmapInfoHeader[2]);

							if (donneesImage->hauteurImage < 0)
							{
								donneesImage->hauteurImage = -donneesImage->hauteurImage;
								hautVersBas = true;
							}
							
							/* On alloue la place pour lire les donnes */
							if
								((donneesImage->donneesRGB = (unsigned char *)malloc((unsigned int)donneesImage->largeurImage*(unsigned int)donneesImage->hauteurImage*3)) != NULL)
							{
								/* donneesImage->donneesRGB != NULL */
								
								unsigned char *scanline;
								/* Une scanline doit avoir une taille multiple de quatre octets */
								int tailleScanLine = tailleScanLineRGB(donneesImage->largeurImage);
								
								/* On alloue la place pour lire chaque scanline */
								if
									((scanline = (unsigned char *)malloc((unsigned int)tailleScanLine)) != NULL)
								{
									/* scanline != NULL */
									
									/* On se positionne sur le debut des donnees a lire */
									if
										(fseek(fichierBMP, offsetDonnees, SEEK_SET) == 0)
									{
										int indexLigne;
										unsigned char *pointeurDonnees;
										pointeurDonnees = donneesImage->donneesRGB +
															(hautVersBas ?
															donneesImage->largeurImage*3*(donneesImage->hauteurImage-1) :
															0);
										
										/* Tout s'est bien passe jusqu'a present */
										toutOK = true;
										for
											(indexLigne = 0; (indexLigne < donneesImage->hauteurImage) && toutOK; ++indexLigne)
										{
											/* On recopie ligne a ligne les informations */
											if
												(fread(scanline, (unsigned int)tailleScanLine, 1, fichierBMP) == 1)
											{
												memcpy(pointeurDonnees, scanline, (unsigned int)(donneesImage->largeurImage*3));
												if (hautVersBas)
													pointeurDonnees -= donneesImage->largeurImage*3;
												else
													pointeurDonnees += donneesImage->largeurImage*3;
											}
											else
											{
												toutOK = false;
											}
										}
									}
									/* Quoi qu'il arrive il faut liberer le buffer memoire de lecture d'une scanline */
									free(scanline);
								}
								
								/* Si tout ne s'est pas bien passe, il faut liberer l'espace memoire pour stocker l'image */
								if
									(!toutOK)
								{
									free(donneesImage->donneesRGB);
								}
							}
						}
					}
				}
			}
			
			
			/* Quoi qu'il arrive il faut fermer le fichier */
			fclose(fichierBMP);
		}
		
		/* Si tout ne s'est pas bien passe on libere les donnees image et on les met a NULL */
		if
			(!toutOK)
		{
			free(donneesImage);
			donneesImage = NULL;
		}
	}
	
	return donneesImage;
}

/* Fonction ecrivant les informations de l'image dans le fichier passe en parametre.
	Renvoie faux en cas de probleme, vrai sinon */
bool ecrisBMPRGB_Dans(DonneesImageRGB *donneesImage, char *nom)
{
	FILE *fichierBMP;
	bool toutOK = false;
	
	if
		((fichierBMP = fopen(nom, "wb")) != NULL)
	{
		/* fichierBMP != NULL */

		/* Le header commence par 'B' et 'M' */
		if
			(fwrite("BM", 2, 1, fichierBMP) == 1)
		{
			int headerBMP[14]; /* Sert a memoriser toutes les informations relatives au BMP */
			int tailleScanLine = tailleScanLineRGB(donneesImage->largeurImage);
			
			memset(headerBMP, 0, 14*4);
			/* Taille du fichier */
			headerBMP[0] = natif32VersLittle(2+12+40+4+tailleScanLine*donneesImage->hauteurImage);
			headerBMP[1] = 0;
			/* Offset a partir duquel commencent les donnees */
			headerBMP[2] = natif32VersLittle(2+12+40+4);
			/* Taille de la structure BITMAPINFOHEADER qui doit faire 40 octets */
			headerBMP[3] = natif32VersLittle(40);
			/* Largeur de l'image */
			headerBMP[4] = natif32VersLittle(donneesImage->largeurImage);
			/* Hauteur de l'image */
			headerBMP[5] = natif32VersLittle(donneesImage->hauteurImage);
			/* Image monoplan de 24 bits */
			headerBMP[6] = natif32VersLittle(0x00180001);
			/* Image non compressee */
			headerBMP[7] = 0;
			/* Les six champs suivants ne nous sont pas utiles */
			headerBMP[8] = 0;
			headerBMP[9] = 0;
			headerBMP[10] = 0;
			headerBMP[11] = 0;
			headerBMP[12] = 0;
			headerBMP[13] = 0;
			
			/* Ecriture du header de fichier */
			if
				(fwrite(headerBMP, 14*4, 1, fichierBMP) == 1)
			{
				unsigned char *scanline;
				
				/* On alloue la place pour ecrire chaque scanline */
				if
					((scanline = (unsigned char *)malloc((unsigned int)tailleScanLine)) != NULL)
				{
					/* scanline != NULL */
					
					int indexLigne;
					unsigned char *pointeurDonnees = donneesImage->donneesRGB;
					
					/* Tout s'est bien passe jusqu'a present */
					toutOK = true;
					
					for
						(indexLigne = 0; (indexLigne < donneesImage->hauteurImage) && toutOK; ++indexLigne)
					{
						/* On recopie ligne a ligne les informations */
						memcpy(scanline, pointeurDonnees, (unsigned int)(donneesImage->largeurImage*3));
						pointeurDonnees += donneesImage->largeurImage*3;
						
						if
							(fwrite(scanline, (unsigned int)tailleScanLine, 1, fichierBMP) != 1)
						{
							toutOK = false;
						}
					}

					/* Quoi qu'il arrive il faut liberer le buffer memoire d'ecriture d'une scanline */
					free(scanline);
				}
			}
		}
		
		
		/* Quoi qu'il arrive il faut fermer le fichier */
		fclose(fichierBMP);
	}
	
	return toutOK;
}
