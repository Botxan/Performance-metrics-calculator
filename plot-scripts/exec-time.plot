set term png
set output "./output/exec-time.png"
set title "Exec. time"
set xlabel "Processors"
set ylabel "Runtime (ms)"
set style data lines
plot "./output/metrics.dat" using 2:xticlabels(1) t "" with linespoints lw 2 dt 2 lc rgb "blue" pt 5