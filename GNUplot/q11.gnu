set title "Land and Ocean Average Temperatures Between 1850 and 2015"
set xlabel "Years"
set ylabel "Temperatures (˚C)"

set key width 1
set key height 2
set key box
set key top right

set yrange [0:25]

plot 'q11.txt' using 1:2 \
	title "Land Average Temperatures" smooth mcsplines with l lw 3, \
	'q11.txt' using 1:3 \
	title "Land and Ocean Average Temperatures" smooth mcsplines, \

