inputFiles=("2x2.ppm" "5x5.ppm" "small.ppm" "2x2bw.ppm" "flowers.ppm")
textFiles=("2x2.txt" "5x5.txt" "small.txt" "2x2bw.txt" "flowers.txt")
outputFiles=("2x2-out.ppm" "5x5-out.ppm" "small-out.ppm" "2x2bw-out.ppm" "flowers-out.ppm")

# inputFiles=("2x2.ppm" "5x5.ppm" "small.ppm" "2x2bw.ppm")
# textFiles=("2x2.txt" "5x5.txt" "small.txt" "2x2bw.txt")
# outputFiles=("2x2-out.ppm" "5x5-out.ppm" "small-out.ppm" "2x2bw-out.ppm")

# inputFiles=("flowers.ppm")
# outputFiles=("flowers-out.ppm")

for i in ${!inputFiles[@]}; do
    echo "${inputFiles[$i]}"
    valgrind ./40image-6 -c ${inputFiles[$i]} > ${textFiles[$i]}
    valgrind ./40image-6 -d ${textFiles[$i]} > ${outputFiles[$i]}
    ./ppmdiff ${inputFiles[$i]}  ${outputFiles[$i]}
    cat ${inputFiles[$i]} | pnmscale 40 | display -
    cat ${outputFiles[$i]} | pnmscale 40 | display -
    echo
done