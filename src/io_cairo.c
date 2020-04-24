
/**
 * \file io_cairo.c
 * \brief Implémentation des fonctions d'affichage et de gestion d'input avec cairo (Bibliothèque graphique)
 */


#include "io_cairo.h"


void cairo_curved_cell(cairo_t *cr,double x,double y, double width, double height)
{
	double aspect = 1.0;
	double corner_radius = height / 10.0; //corner curvature radius
	double radius = corner_radius / aspect;
	double degrees = M_PI / 180.0;

	cairo_new_sub_path (cr);
	cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
	cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
	cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
	cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
	cairo_close_path (cr);

	cairo_set_source_rgb(cr, 0.39607843137254901961, 0.48235294117647058824, 0.51372549019607843137);
	cairo_fill_preserve (cr);
	//Base1 147 161 161 
	cairo_set_source_rgb(cr, 0.57647058823529411765, 0.63137254901960784314, 0.63137254901960784314);
	cairo_set_line_width (cr, 5.0);
	cairo_stroke (cr);
}

void affiche_grille (grille g,cairo_surface_t *surface, layoutState lt){
	int i,j, l=g.nbl, c=g.nbc;
	cairo_t *cr;
	cr=cairo_create(surface);

	// Peindre le background en blanc
	//Background brwhite
	//253 246 227
	cairo_set_source_rgb(cr, 0.99215686274509803922, 0.96470588235294117647, 0.89019607843137254902);
	cairo_paint(cr);
	
	
	//Couleur noire pour les lignes et cases
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	
	//Peindre les lignes horizontales
	for (i=0; i<=l; ++i) 
	{
		cairo_move_to(cr, 0.0, i*lt.hauteurCase);
		cairo_rel_line_to(cr, c*lt.largeurCase, 0.0);
		cairo_set_line_width (cr, 1);
		cairo_stroke (cr);
	}
	
	//Peindre les lignes verticales
	for (i=0; i<=c; ++i) 
	{
		cairo_move_to(cr, i*lt.largeurCase, 0.0);
		cairo_rel_line_to(cr, 0.0, l*lt.hauteurCase);
		cairo_set_line_width (cr, 1);
		cairo_stroke (cr);
	}
		
	//Création et configuration des variables/structs nécessaires pour la police d'écriture
	cairo_text_extents_t extents;
	cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    int font_size =  fmin(lt.hauteurCase,lt.largeurCase) * 0.60;
    cairo_set_font_size (cr, font_size);
    
    
    
    char buffer [2];
	
	//Peint les cellules vivantes et non viables
	for (i=0; i<l; ++i) 
	{
		for (j=0; j<c; ++j) 
		{
			//Cas d'une cellule vivante
			if (g.cellules[i][j] >= 1)
			{
				//Rectangle noir pour cellule vivante
				//Base00 101 123 131
				cairo_set_source_rgb(cr, 0.39607843137254901961, 0.48235294117647058824, 0.51372549019607843137);
				cairo_curved_cell(cr,j*lt.largeurCase,i*lt.hauteurCase,lt.largeurCase,lt.hauteurCase);
				cairo_fill(cr);
				
				//Nombre en blanc indiquant le vieillissement de la cellule
				//base2 238 232 213
				cairo_set_source_rgb(cr, 0.93333333333333333333, 0.90980392156862745098, 0.83529411764705882353);
				
				//On récupère l'âge de la cellule à afficher
				snprintf(buffer, 2, "%d", g.cellules[i][j]);
				
				//Centrage du nombre
				cairo_text_extents (cr, buffer, &extents);
				int x = extents.width/2 + extents.x_bearing;
				int y = extents.height/2 + extents.y_bearing;
				
				cairo_move_to(cr,(j+0.5)*lt.largeurCase - x,(i+0.5)*lt.hauteurCase - y);
				
				//Affichage du nombre
				cairo_show_text (cr, buffer);
			}
			
			//Cas d'un espace non viable (On crée une croix)
			if (g.cellules[i][j] == -1)
			{
				cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
				
				//Diagonale partant du bord haut gauche
				cairo_move_to(cr,j*lt.largeurCase,i*lt.hauteurCase);
				cairo_rel_line_to(cr, lt.largeurCase, lt.hauteurCase);
				cairo_set_line_width (cr, 1);
				cairo_stroke (cr);
				
				//Diagonale partant du bord bas gauche
				cairo_move_to(cr,j*lt.largeurCase,(i+1)*lt.hauteurCase);
				cairo_rel_line_to(cr, lt.largeurCase, -1*lt.hauteurCase);
				cairo_set_line_width (cr, 1);
				cairo_stroke (cr);
			}
		}
	}

	cairo_destroy(cr); // Detruit le masque cairo
	
	return;
}


void affiche_barre_etat (cairo_surface_t *surface, layoutState lt, logicState *lgc){
	cairo_t *cr;
	cr=cairo_create(surface);

	// Peindre le background en blanc
	//base2 238 232 213
	cairo_set_source_rgb(cr, 0.93333333333333333333, 0.90980392156862745098, 0.83529411764705882353);
	cairo_rectangle(cr,0,lt.gridH,lt.gridW,lt.hauteurCase);
	cairo_fill(cr);
	
	//Couleur noire pour les lignes et cases
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	
	//Création et configuration des variables/structs nécessaires pour la police d'écriture
	cairo_text_extents_t extents;
	cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    int font_size = (int)(lt.tailleBarre * 0.7);
    cairo_set_font_size (cr, font_size);
	
	//Calcul de la hauteur Y ou se placer pour afficher du texte
	char buffer [35];
	snprintf(buffer, 20, "O");
	cairo_text_extents (cr, buffer, &extents);
	int yTxt = lt.gridH + lt.tailleBarre -(lt.tailleBarre/2  + extents.height/2 + extents.y_bearing);
	int x;
	
	//Largeur des sections de la barre
	int oscillWidth = 220;
	int evolWidth = 160;
	int indicateurWidth = 20;
	int buttonWidth = 50;
	
	//Position en X des sections de la barre
	int oscillX = lt.gridW - oscillWidth - evolWidth -(indicateurWidth + buttonWidth)*2;
	int evolX = oscillX + oscillWidth;
	int agingIndX = evolX + evolWidth;
	int agingButtonX = agingIndX + indicateurWidth;
	int cycleIndX = agingButtonX + buttonWidth;
	int cycleButtonX = cycleIndX + indicateurWidth;
	
	//Affichage de la dernière action effectuée
	//Base00 101 123 131
	cairo_set_source_rgb(cr, 0.39607843137254901961, 0.48235294117647058824, 0.51372549019607843137);
	snprintf(buffer, 35, "%s",lgc->lastAction);
	cairo_move_to(cr,10,yTxt);
	cairo_show_text (cr, buffer);
	
	//Affichage de l'oscillation
	//Base1 147 161 161 
	cairo_set_source_rgb(cr, 0.57647058823529411765, 0.63137254901960784314, 0.63137254901960784314);
	cairo_rectangle(cr,oscillX,lt.gridH,oscillWidth,lt.tailleBarre);
	cairo_fill(cr);
	
	cairo_set_source_rgb(cr, 0.99215686274509803922, 0.96470588235294117647, 0.89019607843137254902);
	if (lgc->periodeOsc == -1)
		snprintf(buffer, 20, "O : Inconnue");
	else if (lgc->periodeOsc == 1)
		snprintf(buffer, 20, "O : Etat stable");
	else
		snprintf(buffer, 20, "O : Periode de %d",lgc->periodeOsc);
	cairo_text_extents (cr, buffer, &extents);
	x = oscillWidth/2 - extents.width/2 - extents.x_bearing;
	cairo_move_to(cr,oscillX+x,yTxt);
	cairo_show_text (cr, buffer);
	
	//Affichage du nombre de pas d'évolution
	//Base00 101 123 131
	cairo_set_source_rgb(cr, 0.39607843137254901961, 0.48235294117647058824, 0.51372549019607843137);
	cairo_rectangle(cr,evolX,lt.gridH,evolWidth,lt.tailleBarre);
	cairo_fill(cr);
	
	cairo_set_source_rgb(cr, 0.99215686274509803922, 0.96470588235294117647, 0.89019607843137254902);
	snprintf(buffer, 20, "Temps : %d", lgc->tpsEvol);
	cairo_text_extents (cr, buffer, &extents);
	x = evolWidth/2 - extents.width/2 - extents.x_bearing;
	cairo_move_to(cr,evolX+x,yTxt);
	cairo_show_text (cr, buffer);
	
	//Affichage de l'indicateur de vieillissement
	//Base00 101 123 131
	cairo_set_source_rgb(cr, 0.39607843137254901961, 0.48235294117647058824, 0.51372549019607843137);
	snprintf(buffer, 20, "V");
	cairo_text_extents (cr, buffer, &extents);
	x = indicateurWidth/2 - extents.width/2 - extents.x_bearing;
	cairo_move_to(cr,agingIndX+x,yTxt);
	cairo_show_text (cr, buffer);
	
	//ON/OFF du vieillissement
	if (lgc->vieillissement == 1)
	{ 
		//green 133 153   0 
		cairo_set_source_rgb(cr, 0.52156862745098039216, 0.6, 0.0);
		snprintf(buffer, 20, "ON"); 
	}
	else
	{ 
		//Base1 147 161 161 
		cairo_set_source_rgb(cr, 0.57647058823529411765, 0.63137254901960784314, 0.63137254901960784314);
		snprintf(buffer, 20, "OFF"); 
	}
	cairo_rectangle(cr,agingButtonX,lt.gridH,buttonWidth,lt.tailleBarre);
	cairo_fill(cr);
	
	cairo_set_source_rgb(cr, 0.99215686274509803922, 0.96470588235294117647, 0.89019607843137254902);
	cairo_text_extents (cr, buffer, &extents);
	x = buttonWidth/2 - extents.width/2 - extents.x_bearing;
	cairo_move_to(cr,agingButtonX+x,yTxt);
	cairo_show_text (cr, buffer);
	
	//Affichage du mode de calcul du voisinage
	cairo_set_source_rgb(cr, 0.39607843137254901961, 0.48235294117647058824, 0.51372549019607843137);
	snprintf(buffer, 20, "C");
	cairo_text_extents (cr, buffer, &extents);
	x = indicateurWidth/2 - extents.width/2 - extents.x_bearing;
	cairo_move_to(cr,cycleIndX+x,yTxt);
	cairo_show_text (cr, buffer);
	
	//ON/OFF du voisinage
	if (lgc->compte_voisins_vivants == &compte_voisins_vivants_cycle)
	{ 
		//green 133 153   0 
		cairo_set_source_rgb(cr, 0.52156862745098039216, 0.6, 0.0);
		snprintf(buffer, 20, "ON"); 
	}
	else
	{ 
		//Base1 147 161 161 
		cairo_set_source_rgb(cr, 0.57647058823529411765, 0.63137254901960784314, 0.63137254901960784314);
		snprintf(buffer, 20, "OFF"); 
	}
	cairo_rectangle(cr,cycleButtonX,lt.gridH,buttonWidth,lt.tailleBarre);
	cairo_fill(cr);
	
	cairo_set_source_rgb(cr, 0.99215686274509803922, 0.96470588235294117647, 0.89019607843137254902);
	cairo_text_extents (cr, buffer, &extents);
	x = buttonWidth/2 - extents.width/2 - extents.x_bearing;
	cairo_move_to(cr,cycleButtonX+x,yTxt);
	cairo_show_text (cr, buffer);

	cairo_destroy(cr); // destroy cairo mask
	
	return;
}

layoutState initLayoutState(int winWidth, int winHeight, int nbColonnes, int nbLignes)
{
	layoutState lt;
	lt.tailleBarre = 30;
	lt.largeurCase = (double) winWidth / nbColonnes;
	lt.hauteurCase = (double)(winHeight-lt.tailleBarre) / nbLignes;
	lt.gridW = nbColonnes*lt.largeurCase;
	lt.gridH = nbLignes*lt.hauteurCase;
	return lt;
}

void debut_jeu(grille *g, grille *gc){
	
	//CONFIGURATION CAIRO/XLIB
	
	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	int scr;
	
	// Initialisation de l'écran
	if(!(dpy=XOpenDisplay(NULL))) 
	{
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}
	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);
	
	//Création et configuration de la fenêtre
	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, 200, 200, 0, 
							BlackPixel(dpy, scr), BlackPixel(dpy, scr));
	
	//Taille minimum pour la fenêtre
	XSizeHints *hints;
	hints = XAllocSizeHints();
	hints->flags = PMinSize;
	hints->min_width = 520;
	hints->min_height = 100;
	XSetWMNormalHints(dpy, win, hints);
	XFree(hints);
	
	//Renommage de la fenêtre
	XStoreName(dpy, win, "Jeu de la vie");
	
	//Sélection des types d inputs/évènements que l'on souhaitera détecter par la suite
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask|StructureNotifyMask);
	XMapWindow(dpy, win);
	
	//Détection des dimensions de la fenêtre
	XWindowAttributes xwa;
	XGetWindowAttributes(dpy, win, &xwa);
	
	//Création de la surface cairo 
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), xwa.width, xwa.height);
	
	
	//CREATION DES STRUCTURES 
	
	//Initialisation des données du layout l'affichage
	layoutState lt = initLayoutState(xwa.width,xwa.height,g->nbc,g->nbl);
	
	//Initialisation des données déterminant le mode de fonctionnement du programme
	logicState lgc;
	initLogicState(&lgc);
	
	XEvent e;
    KeySym key;
	// Boucle d'évènements
	while(1) 
	{
		XNextEvent(dpy, &e);
		switch(e.type)
		{
			case ButtonPress:
			{
				//Clic gauche
				if(e.xbutton.button==1)
				{
					evolue(g,gc,&lgc);
					
					lgc.tpsEvol++;
					snprintf(lgc.lastAction,35,"> Evolution");
					affiche_grille(*g,cs,lt);
					affiche_barre_etat(cs,lt,&lgc);
				}
				//Clic droit
				if(e.xbutton.button==3)
				{
					cairo_surface_destroy(cs); // Détruit la surface cairo
					XCloseDisplay(dpy); // On ferme le display
					return;
				}
				
				break;
			}	
			case KeyPress:
			{
				//On convertit le keycode de l'évènement e en valeur keysim (définies dans keysimdef.h) 
				key = XkbKeycodeToKeysym( dpy, e.xkey.keycode, 0, 0 );
				switch(key)
				{
					case XK_Return : 
					{ // touche "Entree" pour évoluer
						evolue(g,gc,&lgc);
						lgc.tpsEvol++;
						snprintf(lgc.lastAction,35,"> Evolution");
						//efface_grille(cs);
						//printf("Temps d'evolution: %i",tpsEvol);
						affiche_grille(*g,cs,lt);
						break;
					}
			
					case XK_n : 
					{ // touche "n" pour entrer nom d'une nouvelle grille
						
						libere_grille(g);
						libere_grille(gc);
						
						char grille[256];
						scanf("%s", grille);
						
						init_grille_from_file(grille,g);
						alloue_grille (g->nbl, g->nbc, gc);
						initLogicState(&lgc);
						
						
						XGetWindowAttributes(dpy, win, &xwa);
				
						lt.hauteurCase = (xwa.height-lt.tailleBarre) / g->nbl;
						lt.largeurCase = (double) xwa.width / g->nbc;
						
						cairo_xlib_surface_set_size (cs,xwa.width,xwa.height);
						affiche_grille(*g,cs,lt);
						snprintf(lgc.lastAction,35,"> Nouvelle grille chargée");
						break;
					}
			
					case XK_c : 
					{ // touche "c" pour activer/désactiver le voisinage cyclique
						if (lgc.compte_voisins_vivants == &compte_voisins_vivants_cycle)
						{
							lgc.compte_voisins_vivants = &compte_voisins_vivants_no_cycle;
							snprintf(lgc.lastAction,35,"> Voisinage cyclique désactivé");
						}
						else
						{
							lgc.compte_voisins_vivants = &compte_voisins_vivants_cycle;
							snprintf(lgc.lastAction,35,"> Voisinage cyclique activé");
						}
						break;
					}
			
					case XK_v : 
					{ // touche "v" pour activer/désactiver le vieillissement
						if (lgc.vieillissement == 1)
						{
							lgc.vieillissement = 0;
							snprintf(lgc.lastAction,35,"> Vieillissement désactivé");
						}
						else
						{
							lgc.vieillissement = 1;
							snprintf(lgc.lastAction,35,"> Vieillissement activé");
						}
						affiche_barre_etat(cs,lt,&lgc);
						break;
					}
					case XK_q : 
					{ // touche "q" pour quitter
						cairo_surface_destroy(cs);
						XCloseDisplay(dpy);
						return;
						
						break;
					}
					
					case XK_o : 
					{ // touche "o" pour détecter l'oscillation
						
						if (lgc.periodeOsc != -1)
						snprintf(lgc.lastAction,35,"> Oscillation déjà détectée");
						else
						{
							//Créer une nouvelle grille T à partir de la grille actuelle
							grille *t;
							t = malloc(sizeof(grille));
							alloue_grille (g->nbl, g->nbc, t);
							copie_grille (*g,*t);
							
							//Créer un tableau de 1000 pointeurs de grille
							grille *tabEtats[1000];
							
							int flagPeriode=0,i,j,k,l;
							
							for (i=0; i<1000 && flagPeriode !=1; i++)
							{
								//Stocker l'état de T dans le tableau
								tabEtats[i] = malloc(sizeof(grille));
								alloue_grille (g->nbl, g->nbc, tabEtats[i]);
								copie_grille (*t,*tabEtats[i]);
							
								//On parcourt le tableau d'états précédents en sens inverse
								for (l = i-1; l >= 0 && flagPeriode != 1; l--)
								{
									//On teste si les deux grilles sont identiques
									flagPeriode = 1;
									for (j=0; j<t->nbl; j++)
									{
										for (k=0; k<t->nbc && flagPeriode != 0; ++k)
										{
											if (t->cellules[j][k] != tabEtats[l]->cellules[j][k])
											{
												//Si une différence est détectée on stoppe la comparaison entre les 2 états et on passe à l'état suivant.
												flagPeriode = 0;
											}
										}
									}
								}
								//Si une oscillation ou état stable a été détecté(e)
								if (flagPeriode == 1)
								{
									//Une valeur de 1 pour i-l indique un état stable;
									lgc.periodeOsc = i-l-1;
								}
								else
								{
									evolue(t,gc,&lgc);
								}
							}
							//On libère les pointeurs de grille que l'on a assignés.
							for (l = 0; l<i ; l++)
							{
								libere_grille(tabEtats[l]);
							}
							libere_grille(t);
						}
						break;
					}
					default : 
					{ // touche non traitée
						break;
					}
				}
				break;
			}
			case Expose:
			{
				if(e.xexpose.count<1)
				{
					affiche_grille(*g,cs,lt);
					affiche_barre_etat(cs,lt,&lgc);
				}
				break;
			}
			case ConfigureNotify:
			{//Evenement de modification de la fenêtre
				
				XGetWindowAttributes(dpy, win, &xwa);
				
				//On met à jour le layout si la fenêtre est redimensionnée
				lt.hauteurCase = (xwa.height-lt.tailleBarre) / g->nbl;
				lt.largeurCase = (double) xwa.width / (double) g->nbc;
				lt.gridW = lt.largeurCase * g->nbc;
				lt.gridH = lt.hauteurCase * g->nbl;
				cairo_xlib_surface_set_size (cs,xwa.width,xwa.height);
				
				affiche_grille(*g,cs,lt);
				
				break;
			}
		}
		affiche_barre_etat(cs,lt,&lgc);
	}
}
