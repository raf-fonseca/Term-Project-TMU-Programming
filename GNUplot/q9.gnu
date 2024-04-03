set multiplot layout 1,3 title "Average, Maximum, and Minimum Temperatures For Each Century"
set xtics nomirror
set ytics nomirror

set ylabel "Temperature (C)"
set yrange [0:20]

set ytics 2
set grid y
unset xtics
set style data histogram

set boxwidth 1
set style fill pattern 1

set key top left

set title "Average Temperature"
plot "q9.txt" every ::0::0 using 1 linestyle 4 title "19th Century", "q9.txt" every ::1::1 using 2 linestyle 2 title "20th Century", "q9.txt" every ::2::2 using 2 linestyle 4 title "21st Century"

set title "Maximum Temperature"
plot "q9.txt" every ::0::0 using 2 linestyle 4 title "19th Century", "q9.txt" every ::1::1 using 2 linestyle 2 title "20th Century", "q9.txt" every ::2::2 using 2 linestyle 4 title "21st Century"

set title "Minimum Temperature"
plot "q9.txt" every ::0::0 using 3 linestyle 4 title "19th Century", "q9.txt" every ::1::1 using 3 linestyle 2 title "20th Century", "q9.txt" every ::2::2 using 3 linestyle 4 title "21st Century"