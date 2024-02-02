# Configuration du terminal et du fichier de sortie
set terminal pngcairo enhanced font "Arial,12" size 1800,500
set output "statistiques.png"

# Configuration du titre
set title "Courbes des distances maximale, minimale et moyenne par trajet" font "Arial,14"

# Configuration de la légende
set key outside right top font "Arial,10"

# Style de ligne et couleurs
set style line 1 lc rgb '#E41A1C' lw 2  # Rouge pour la distance maximale
set style line 2 lc rgb '#377EB8' lw 2  # Bleu pour la distance minimale
set style line 3 lc rgb '#4DAF4A' lw 2  # Vert pour la distance moyenne

# Configuration des axes
set xlabel "Identifiant du trajet"
set ylabel "Distance (km)"
set xtic rotate by -45 scale 0 

# Nom du fichier de données
datafile = 'output.csv'

# Tracé des courbes pour les distances maximale, minimale et moyenne
plot datafile using 1:4:xtic(2) with lines linestyle 1 title "Distance Maximale", \
     datafile using 1:5:xtic(2) with lines linestyle 2 title "Distance Minimale", \
     datafile using 1:6:xtic(2) with lines linestyle 3 title "Distance Moyenne"
