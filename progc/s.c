#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

typedef struct AVLNode {
    int trajetID;
    float distanceMin;
    float distanceMax;
    float distanceMoyenne;
    float maxMoinsMin;
    struct AVLNode *gauche;
    struct AVLNode *droite;
    int hauteur;
} AVLNode;

AVLNode* ajouterDistance(AVLNode* noeud, float distance) {
    if (noeud == NULL) {
        return creerNouveauNoeud(distance);
    }

    if (distance < noeud->distance) {
        noeud->gauche = ajouterDistance(noeud->gauche, distance);
    } else if (distance > noeud->distance) {
        noeud->droite = ajouterDistance(noeud->droite, distance);
    } else {
        // Les distances égales ne sont pas ajoutées
        return noeud;
    }

    noeud->hauteur = 1 + max(hauteur(noeud->gauche), hauteur(noeud->droite));

    int balance = hauteur(noeud->gauche) - hauteur(noeud->droite);

    // Rééquilibrage de l'arbre si nécessaire
    if (balance > 1 && distance < noeud->gauche->distance) {
        return pivoterDroiteDistance(noeud);
    }
    if (balance < -1 && distance > noeud->droite->distance) {
        return pivoterGaucheDistance(noeud);
    }
    if (balance > 1 && distance > noeud->gauche->distance) {
        noeud->gauche = pivoterGaucheDistance(noeud->gauche);
        return pivoterDroiteDistance(noeud);
    }
    if (balance < -1 && distance < noeud->droite->distance) {
        noeud->droite = pivoterDroiteDistance(noeud->droite);
        return pivoterGaucheDistance(noeud);
    }

    return noeud;
}

AVLNode* pivoterDroiteDistance(AVLNode* y) {
    AVLNode* x = y->gauche;
    AVLNode* T2 = x->droite;

    x->droite = y;
    y->gauche = T2;

    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;
    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;

    return x;
}

AVLNode* pivoterGaucheDistance(AVLNode* x) {
    AVLNode* y = x->droite;
    AVLNode* T2 = y->gauche;

    y->gauche = x;
    x->droite = T2;

    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;
    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;

    return y;
}

int calculerEquilibreDistance(AVLNode *noeud) {
    if (noeud == NULL) return 0;
    return hauteur(noeud->gauche) - hauteur(noeud->droite);
}

AVLNode* creerNoeudDistance(float distance) {
    AVLNode *noeud = (AVLNode*)malloc(sizeof(AVLNode));
    if (!noeud) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour un noeud.\n");
        exit(EXIT_FAILURE);
    }
    noeud->distance = distance;
    noeud->gauche = noeud->droite = NULL;
    noeud->hauteur = 1;
    return noeud;
}

float distanceMinimale(AVLNode *noeud) {
    if (noeud == NULL) {
        return FLT_MAX;
    }
    while (noeud->gauche != NULL) {
        noeud = noeud->gauche;
    }
    return noeud->distance;
}

float distanceMaximale(AVLNode *noeud) {
    if (noeud == NULL) {
        return FLT_MIN;
    }
    while (noeud->droite != NULL) {
        noeud = noeud->droite;
    }
    return noeud->distance;
}

float calculerSommeDistances(AVLNode *noeud) {
    if (noeud == NULL) return 0.0;

    float sommeGauche = calculerSommeDistances(noeud->gauche);
    float sommeDroite = calculerSommeDistances(noeud->droite);

    return noeud->distance + sommeGauche + sommeDroite;
}

int compterEtapes(AVLNode *noeud) {
    if (noeud == NULL) return 0;

    int compteGauche = compterEtapes(noeud->gauche);
    int compteDroite = compterEtapes(noeud->droite);

    return 1 + compteGauche + compteDroite;
}

float calculerMoyenneDistance(AVLNode *noeud) {
    int totalEtapes = compterEtapes(noeud);
    if (totalEtapes == 0) return 0.0;

    float sommeTotale = calculerSommeDistances(noeud);
    return sommeTotale / totalEtapes;
}

AVLNode* creerNoeudTrajet(int trajetID, float distance) {
    AVLNode *noeud = (AVLNode*)malloc(sizeof(AVLNode));
    if (noeud == NULL) {
        perror("Erreur d'allocation de mémoire pour un noeud de trajet");
        exit(EXIT_FAILURE);
    }

    noeud->trajetID = trajetID;
    noeud->distance = distance;
    noeud->gauche = noeud->droite = NULL;
    noeud->hauteur = 1;

    return noeud;
}

AVLNode* pivoterDroiteTrajet(AVLNode* y) {
    AVLNode* x = y->gauche;
    AVLNode* T2 = x->droite;

    x->droite = y;
    y->gauche = T2;

    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;
    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;

    return x;
}

AVLNode* pivoterGaucheTrajet(AVLNode* x) {
    AVLNode* y = x->droite;
    AVLNode* T2 = y->gauche;

    y->gauche = x;
    x->droite = T2;

    x->hauteur = max(hauteur(x->gauche), hauteur(x->droite)) + 1;
    y->hauteur = max(hauteur(y->gauche), hauteur(y->droite)) + 1;

    return y;
}

int calculerEquilibreTrajet(AVLNode* noeud) {
    if (noeud == NULL) return 0;
    return hauteur(noeud->gauche) - hauteur(noeud->droite);
}

AVLNode* ajouterTrajet(AVLNode* noeud, int trajetID, float distance) {
    if (noeud == NULL) {
        return creerNoeudTrajet(trajetID, distance);
    }

    if (trajetID < noeud->trajetID) {
        noeud->gauche = ajouterTrajet(noeud->gauche, trajetID, distance);
    } else if (trajetID > noeud->trajetID) {
        noeud->droite = ajouterTrajet(noeud->droite, trajetID, distance);
    } else {
        return noeud; // Pas de duplicatas
    }

    noeud->hauteur = 1 + max(hauteur(noeud->gauche), hauteur(noeud->droite));

    int balance = calculerEquilibreTrajet(noeud);

    // Rééquilibrage de l'arbre
    if (balance > 1 && trajetID < noeud->gauche->trajetID) {
        return pivoterDroiteTrajet(noeud);
    }
    if (balance < -1 && trajetID > noeud->droite->trajetID) {
        return pivoterGaucheTrajet(noeud);
    }
    if (balance > 1 && trajetID > noeud->gauche->trajetID) {
        noeud->gauche = pivoterGaucheTrajet(noeud->gauche);
        return pivoterDroiteTrajet(noeud);
    }
    if (balance < -1 && trajetID < noeud->droite->trajetID) {
        noeud->droite = pivoterDroiteTrajet(noeud->droite);
        return pivoterGaucheTrajet(noeud);
    }

    return noeud;
}

AVLNode* ajouterStatistique(AVLNode* racine, TrajetStat stat) {
    if (racine == NULL) {
        return creerNoeudTrajet(stat.trajetID, stat.distanceMin, stat.distanceMax);
    }

    if (diff(stat) < diff(racine->data)) {
        racine->gauche = ajouterStatistique(racine->gauche, stat);
    } else if (diff(stat) > diff(racine->data)) {
        racine->droite = ajouterStatistique(racine->droite, stat);
    } else {
        return racine; // Pas de duplicatas
    }

    racine->hauteur = 1 + max(hauteur(racine->gauche), hauteur(racine->droite));

    int balance = calculerEquilibreStatistique(racine);
    // Rééquilibrage de l'arbre
    return effectuerRotation(racine, balance, diff(stat));
}

AVLNode* pivoterDroiteStatistique(AVLNode* y) {
    AVLNode* x = y->gauche;
    AVLNode* T2 = x->droite;

    x->droite = y;
    y->gauche = T2;

    y->hauteur = 1 + max(hauteur(y->gauche), hauteur(y->droite));
    x->hauteur = 1 + max(hauteur(x->gauche), hauteur(x->droite));

    return x;
}

AVLNode* pivoterGaucheStatistique(AVLNode* x) {
    AVLNode* y = x->droite;
    AVLNode* T2 = y->gauche;

    y->gauche = x;
    x->droite = T2;

    x->hauteur = 1 + max(hauteur(x->gauche), hauteur(x->droite));
    y->hauteur = 1 + max(hauteur(y->gauche), hauteur(y->droite));

    return y;
}

int calculerEquilibreStatistique(AVLNode* noeud) {
    if (noeud == NULL) return 0;
    return hauteur(noeud->gauche) - hauteur(noeud->droite);
}

void traiterEtAjouterStatistiquesTrajet(AVLNode** racine, int trajetID, float distance) {
    if (*racine == NULL) {
        *racine = creerNoeudTrajet(trajetID, distance);
        return;
    }

    if (trajetID < (*racine)->trajetID) {
        traiterEtAjouterStatistiquesTrajet(&(*racine)->gauche, trajetID, distance);
    } else if (trajetID > (*racine)->trajetID) {
        traiterEtAjouterStatistiquesTrajet(&(*racine)->droite, trajetID, distance);
    } else {
        // Traiter la distance pour le même trajetID
        (*racine)->distanceTotal += distance;
        (*racine)->nombreEtapes++;
        (*racine)->distanceMin = fmin((*racine)->distanceMin, distance);
        (*racine)->distanceMax = fmax((*racine)->distanceMax, distance);
    }

    // Mise à jour de la hauteur et rééquilibrage
    (*racine)->hauteur = 1 + max(hauteur((*racine)->gauche), hauteur((*racine)->droite));
    *racine = reequilibrerArbre(*racine);
}

void explorerEtExtraireTopValeurs(AVLNode* noeud, AVLNode* topValeurs[], int* index, int limite) {
    if (noeud == NULL || *index >= limite) return;

    explorerEtExtraireTopValeurs(noeud->droite, topValeurs, index, limite);

    if (*index < limite) {
        topValeurs[*index] = noeud;
        (*index)++;
    }

    explorerEtExtraireTopValeurs(noeud->gauche, topValeurs, index, limite);
}

void enregistrerStatistiquesTopValeurs(AVLNode* topValeurs[], int limite, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        perror("Erreur en ouvrant le fichier pour l'écriture");
        return;
    }

    fprintf(fichier, "TrajetID,MinDistance,MaxDistance,TotalDistance,NombreEtapes\n");
    for (int i = 0; i < limite; i++) {
        fprintf(fichier, "%d,%f,%f,%f,%d\n",
                topValeurs[i]->trajetID, topValeurs[i]->distanceMin,
                topValeurs[i]->distanceMax, topValeurs[i]->distanceTotal,
                topValeurs[i]->nombreEtapes);
    }

    fclose(fichier);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Utilisation : %s <chemin_fichier>\n", argv[0]);
        return 1;
    }

    const char* cheminFichier = argv[1];
    FILE* fichier = fopen(cheminFichier, "r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    char ligne[1024];
    AVLNode* racine = NULL;
    fgets(ligne, sizeof(ligne), fichier); // Ignorer l'en-tête du fichier

    while (fgets(ligne, sizeof(ligne), fichier)) {
        int trajetID;
        float distance;

        if (sscanf(ligne, "%d,%*[^,],%*[^,],%*[^,],%f", &trajetID, &distance) == 2) {
            traiterEtAjouterStatistiquesTrajet(&racine, trajetID, distance);
        } else {
            printf("Erreur lors de l'analyse de la ligne: %s\n", ligne);
        }
    }

    fclose(fichier);

    AVLNode* topValeurs[50];
    int index = 0;
    explorerEtExtraireTopValeurs(racine, topValeurs, &index, 50);

    const char* nomFichierSortie = "out.txt";
    enregistrerStatistiquesTopValeurs(topValeurs, 50, nomFichierSortie);

    // appel à gnuplot pour effetuer le grapgique à partir des données du systeme (gnuplot options.gp");

    libererArbre(racine);
    return 0;
}
