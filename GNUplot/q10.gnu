set title "Land and Ocean Average Temperatures Between 2000 and 2015"
set xlabel "Months"
set ylabel "Temperatures (˚C)"

set key width 1
set key height 2
set key box
set key top right

set yrange [0:25]


set xrange [0:6]
set xtics 1


plot 'q10.txt' using 1:2 \
	title "Land Average Temperatures" smooth mcsplines with l lw 3, \
	'q10.txt' using 1:3 with errorbars \
	title "Uncertainty" smooth mcsplines, \
    
