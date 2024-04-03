set title "Land Average Temperatures Between 2000 and 2015"
set xlabel "Months"
set ylabel "Temperatures (˚C)"

set key width 1
set key height 2
set key box
set key top right

set yrange [0:25]


set xrange [0:15]
set xtics 10


plot 'q10.txt' using 1:2:3 with errorbars title 'Error Bars', \
 'q10.txt' title 'Monthly Temperature' smooth mcsplines using 1:2
