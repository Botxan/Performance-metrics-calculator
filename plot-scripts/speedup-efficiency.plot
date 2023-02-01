set term png
set output "./output/speedup-efficiency.png"
set title "Speed Up and Efficiency"
set xlabel "Processors"
set logscale x
set ylabel "Speed Up"
set y2label "Efficiency"
set y2range [0:100]
set format y2 "%g%%"
set key bottom right box
plot "./output/metrics.dat" using 1:3 with linespoints t "Speed Up" lw 2 dt 2 lc rgb "red" pt 5 axis x1y1, \
"./output/metrics.dat" using 1:($4*100) t "Efficiency" with linespoints lw 2 dt 2 lc rgb "blue" pt 2 axis x1y2
set xtics using 1