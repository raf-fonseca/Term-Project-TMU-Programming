set title "Land Average Temperatures Between 1850 and 2015"
set xlabel "Years"
set ylabel "Land Temperatures (˚C)"

set key width 1
set key height 2
set key box
set key top right

set yrange [0:25]

plot 'q8.txt' using 1:2 \
	title "Land Average Temperatures" smooth mcsplines with l lw 3, \
	'q8.txt' using 1:3 \
	title "Maximum Land Temperatures" smooth mcsplines, \
	'q8.txt' using 1:4 \
	title "Minimum Land Temperatures" smooth mcsplines