# /!\ Attention, ce programme n'est pas du tout correct, il sert juste de maquette pour rédiger certtaines fonctions du programme principal


#!/bin/bash

# Définition des chemins
DATA_FOLDER="data"
PROGC_FOLDER="progc"
IMAGES_FOLDER="images"
TEMP_FOLDER="temp"
DEMO_FOLDER="demo"

# Fonction pour afficher l'aide
function afficher_aide {
  echo "Usage: $0 chemin_fichier_CSV [-d1 | -d2 | -l | -t | -s]"
  echo "Options:"
  echo "  -d1: Conducteurs avec le plus de trajets"
  echo "  -d2: Conducteurs et la plus grande distance"
  echo "  -l: Les 10 trajets les plus longs"
  echo "  -t: Les 10 villes les plus traversées"
  echo "  -s: Statistiques sur les étapes"
  exit 1
}

# Vérification du nombre d'arguments
if [ "$#" -lt 2 ]; then
  afficher_aide
fi

# Chemin du fichier CSV (premier argument)
CSV_FILE=$1

# Vérification de l'existence du fichier CSV
if [ ! -f "$CSV_FILE" ]; then
  echo "Erreur: Le fichier CSV n'existe pas."
  exit 1
fi

# Exemple : Affichage de l'aide si l'option est -h
if [ "$2" == "-h" ]; then
  afficher_aide
fi

# Exemple : Vérification de la présence du dossier temp
if [ ! -d "$TEMP_FOLDER" ]; then
  mkdir "$TEMP_FOLDER"
fi

# Exemple : Vérification de la présence du dossier images
if [ ! -d "$IMAGES_FOLDER" ]; then
  mkdir "$IMAGES_FOLDER"
fi

# Exemple : Vérification de la présence du dossier data
if [ ! -d "$DATA_FOLDER" ]; then
  mkdir "$DATA_FOLDER"
fi

# Exemple : Copie du fichier CSV dans le dossier data
cp "$CSV_FILE" "$DATA_FOLDER/"

# Exemple : Appel du programme C avec l'option -d1
"$PROGC_FOLDER/mon_programme_C" -d1 "$DATA_FOLDER/$CSV_FILE" "$TEMP_FOLDER/traitements_d1.txt"
