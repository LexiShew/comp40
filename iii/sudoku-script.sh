testFiles=$(ls *.pgm)
for file in $testFiles ; do
    echo "Test file: $file"
    ./sudoku $file
    echo "   exit: $?"
done