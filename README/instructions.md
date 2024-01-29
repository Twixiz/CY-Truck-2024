/!\ Ne pas oublier de s'arroger les droits d'executions qui peuvent être nécessaire en utilisant les commandes :
chmod +x prog-principal.sh
chmod +x d1.sh
chmod +x d2.sh
chmod +x l.sh
chmod +x t.sh
chmod +x s.sh

Utilisation de la commande : ./prog-principal.sh $0 CHEMIN_DATA.CSV [-d1 | -d2 | -l | -t | -s]
Options :
-d1: Conducteurs avec le plus de trajets
-d2: Conducteurs et la plus grande distance
-l: Les 10 trajets les plus longs
-t: Les 10 villes les plus traversées
-s: Statistiques sur les étapes

Cette aide peut également être affichée en l'absence d'arguments, ou si l'argument -h est donné
