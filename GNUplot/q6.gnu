set title "Yearly Temperatures (1760-2015)"
set xlabel "Years"
set ylabel "Temperatures (˚C)"

set key width 1
set key height 2
set key box
set key top right

set yrange [0: 15]

plot "q6.txt" using 1:2 title "Yearly Temperatures" smooth mcsplines
