#! /bin/sh
testFiles=$(ls *.um)
echo $testFiles
echo
echo LOOPS
for testFile in $testFiles ; do   
    echo $testFile
    
    testName=$(echo $testFile | sed -E 's/(.*).um/\1/')
    testGT=$testName".1"
    um $testfile > $testGT

    echo $testGT
    if [ -f $testGT ] ; then
        testOut=$testName".out"
        ./um $testFile > $testOut
    else 
        echo "$testName has no output!" 
    fi
done
echo