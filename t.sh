#!/bin/bash

# Compile and execute the program to sort the data
gcc -o programC progc/t.c && ./programC

# Verify if GNUplot is installed
if ! command -v gnuplot &> /dev/null; then
    echo "GNUplot is not is not installed, please installe it and retry."
    exit 1
fi

# Name of the CSV file 
file_csv="tempT.csv"

# Verify if the CSV file exist
if [ ! -f "$file_csv" ]; then
    echo "the CSV '$file_csv' do not exist."
    exit 1
fi

# Create a temporary data file with the appropriate format for GNUplot
awk -F';' '{print $1, $2, "Depart", $3; print $1, $2, "Traverse", $4}' "$file_csv" > data_cities_plot.txt


# Create a temporary GNUplot script
echo "set terminal pngcairo enhanced font 'arial,10' size 800, 600" > script.gnu
echo "set output 'graphique_villes.png'" >> script.gnu
echo "set boxwidth 0.4" >> script.gnu
echo "set style fill solid" >> script.gnu
echo "set xlabel 'Villes'" >> script.gnu
echo "set ylabel 'Nombre de fois'" >> script.gnu
echo "set title 'Graphique des Villes : Trajets et Départs'" >> script.gnu
echo "set xtics rotate" >> script.gnu
echo "plot 'donnees_villes_plot.txt' using 2:xtic(1) title 'Départ', '' using 4 title 'Traverse'" >> script.gnu

# Run the GNUplot script
gnuplot script.gnu

# Delete temporary files
rm data_villes_plot.txt script.gnu

# Open the generated image
xdg-open graphique_villes.png
