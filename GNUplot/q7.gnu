set title "Yearly Temperatures (19th - 20th Century)"
set xlabel "Years"
set ylabel "Temperatures (˚C)"

set key width 1
set key height 2
set key box
set key top right

set yrange [0: 15]

plot "century19th.txt" using 1:2 title "19th Century" smooth mcsplines, \
	 "century20th.txt" using 1:2 title "20th Century" smooth mcsplines

