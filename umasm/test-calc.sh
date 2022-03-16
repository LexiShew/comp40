testInputs=$(ls ./test/*.test)
echo
echo "TESTING FILES:"
for testInput in $testInputs ; do

    testName=$(echo $testInput | sed -E 's/.\/test\/(.*).test/\1/')
    echo $testName
    echo
        
    testRef="./test/"$testName".ref"
    testOut="./test/"$testName".out"
    
    /comp/40/bin/calc40 < $testInput > $testRef      # get the reference's output 
    
    # um rpn-calc.um $testInput < $testIn > $testOut      # get our calc's output

    # diff $testRef $testOut                       # diff check our's against ref

done
echo