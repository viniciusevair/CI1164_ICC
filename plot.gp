## set encoding iso_8859_15
set encoding utf

# set terminal qt persist

set grid

set style data point
set style function line
set style line 1 lc 3 pt 7 ps 0.3
set boxwidth 1
set xtics
# set xrange [0:]
set xlabel  "N (size)"

set key outside right # posição da legenda: outside {left | right}
unset logscale x
set datafile separator whitespace
set ylabel  ARG3
set title   ARG2
#set terminal qt 1 title ARG2
#plot ARG1 using 1:2 title "Sem otimização" with linespoints, \
#     '' using 1:3 title "Com otimização" with linespoints

# Gerando figura PNG
set terminal png
set output ARG4
plot ARG1 using 1:2 title "Sem otimização" with linespoints, \
     '' using 1:3 title "Com otimização" with linespoints
replot

unset output
