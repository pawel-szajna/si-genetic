set datafile separator ","
set term png
set output "plot.png"
set xlabel "Generacje"
set ylabel "Czas wykonania"
plot 'r.csv' using 1:2 with lines title 'najlepszy', 'r.csv' using 1:3 with lines title 'srednia', 'r.csv' using 1:4 with lines title 'najgorszy'
