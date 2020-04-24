#VARIABLES/PARAMETRES

#Version du projet
VERSION = v5.3

#Mode de compilation
MODE = GRAPHIQUE

#Compilateur
CC= gcc -g

#Flags de compilation
CPPFLAGS = -Wall -I$(INC_REP)


#Flags pour l'édition de liens
LDFLAGS = -lm 

# Répertoires contenant les différents types de fichiers
SRC_REP = src
OBJ_REP = obj
BIN_REP = bin
INC_REP = include
LIB_REP = lib
TEST_REP = test

#Fichiers sources et objets et nom librairie
SOURCES = $(wildcard $(SRC_REP)/*.c)
INCLUDES = $(wildcard $(INC_REP)/*.h)
OBJETS = $(SOURCES:$(SRC_REP)/%.c=$(OBJ_REP)/%.o)
LIB = jeu


#Configuration des dépendances objets en fonction du mode
ifeq ($(MODE), GRAPHIQUE)
	OBJETS := $(filter-out $(OBJ_REP)/io.o,$(OBJETS))
	CPPFLAGS += -I/usr/include/cairo
	LDFLAGS += -lcairo -lX11
endif

ifeq ($(MODE), TEXTE)
	OBJETS := $(filter-out $(OBJ_REP)/io_cairo.o,$(OBJETS))
endif

#On exclut les fichiers .o de la bibliothèque et met à jour les LDFLAGS
LDFLAGS += -l$(LIB) -L$(LIB_REP)
OBJETS := $(filter-out $(OBJ_REP)/jeu.o $(OBJ_REP)/grille.o,$(OBJETS))

#Nom de l'exécutable
EXEC = main

#CIBLES

#Cible construite par make par défaut
all: $(BIN_REP) $(OBJ_REP) $(LIB_REP) $(LIB_REP)/lib$(LIB).a $(BIN_REP)/$(EXEC)

#Edition de liens
$(BIN_REP)/%: $(OBJETS) 
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Edition de liens réussie."
	@echo ""$(MODE)" "$(OBJETS)""

#Compilation
$(OBJ_REP)/%.o : $(SRC_REP)/%.c
	@$(CC) $(CPPFLAGS) -c $< -o $@
	@echo "Compilation de "$<" réussie."
	
#Création de la bibliothèque
$(LIB_REP)/lib$(LIB).a: $(OBJ_REP)/jeu.o $(OBJ_REP)/grille.o
	@ar -crv $@ $^
	@ranlib $@
	@echo "Création de la bibliothèque "$@" réussie."
	
#Création des répertoires pour les fichiers temporaires 
#(objets, exécutables et bibliothèques) si nécessaire
$(BIN_REP):
	@mkdir -p $@
	@echo "Répertoire "$@" créé."

$(OBJ_REP):
	@mkdir -p $@
	@echo "Répertoire "$@" créé."

$(LIB_REP):
	@mkdir -p $@
	@echo "Répertoire "$@" créé."
	
#Suppression des fichiers temporaires possiblement présents
clean: 
	@rm -rf $(OBJ_REP)/*.o $(BIN_REP)/* $(LIB_REP)/* doc/ *.tar.xz $(TEST_REP)/*.o $(TEST_REP)/test
	@echo "Fichiers objets, exécutable, documentation et tarball supprimés si présents."

#Création du fichier d'archive de rendu
dist:
	@tar -cJ -f PolitanskiLouis-GoL-$(VERSION).tar.xz $(SOURCES) $(INCLUDES) Makefile Doxyfile README.md
	@echo "Archive de rendu PolitanskiLouis-GoL-"$(VERSION)".tar.xz créée."

#Cible pour lancer le programme rapidement (NECESSITE UN DOSSIER GRILLE AVEC grille1.txt)
run:
	$(BIN_REP)/./$(EXEC) grilles/grille1.txt
	
#Cible(s) pour lancer un test du programme	
test: all $(TEST_REP)/test
	$(TEST_REP)/./$@ grilles/grille1.txt
		
$(TEST_REP)/%.o : $(TEST_REP)/%.c
	@$(CC) $(CPPFLAGS) -c $< -o $@
	@echo "Compilation de "$<" réussie."

$(TEST_REP)/test: $(TEST_REP)/test.o
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Edition de liens réussie."
	@echo ""$(MODE)" "$(OBJETS)""
	
	
	
	
	
	

