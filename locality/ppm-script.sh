testFiles=$(ls mobo.ppm)
for file in $testFiles ; do
    echo "Test file: $file" #$file"


    # echo "   rotate 0 default"
    # ./ppmtrans2 -rotate 0 test1.ppm > r0default.ppm
    # cat r0default.ppm | pnmscale 40 | display -
    # echo "   rotate 90 default"
    # ./ppmtrans2 -rotate 90 test1.ppm > r90default.ppm
    # cat r90default.ppm | pnmscale 40 | display -
    # echo "   rotate 180 default"
    # ./ppmtrans2 -rotate 180 test1.ppm > r180default.ppm
    # cat r180default.ppm | pnmscale 40 | display -
    # echo "   rotate 270 default"
    # ./ppmtrans2 -rotate 270 test1.ppm > r270default.ppm
    # cat r270default.ppm | pnmscale 40 | display -
    # echo "   flip horiz default"
    # ./ppmtrans2 -flip horizontal test1.ppm > fhorizdefault.ppm
    # cat fhorizdefault.ppm | pnmscale 40 | display -
    # echo "   flip vert default"
    # ./ppmtrans2 -flip vertical test1.ppm > fvertdefault.ppm
    # cat fvertdefault.ppm | pnmscale 40 | display - 
    # echo "   transpose default"
    # ./ppmtrans2 -transpose test1.ppm > tdefault.ppm
    # cat tdefault.ppm | pnmscale 40 | display -

    # echo "   rotate 0 block"
    # ./ppmtrans2 -rotate 0 -block-major test1.ppm > r0block.ppm
    # cat r0block.ppm | pnmscale 40 | display -
    # echo "   rotate 90 block"
    # ./ppmtrans2 -rotate 90 -block-major test1.ppm > r90block.ppm
    # cat r90block.ppm | pnmscale 40 | display -
    # echo "   rotate 180 block"
    # ./ppmtrans2 -rotate 180 -block-major test1.ppm > r180block.ppm
    # cat r180block.ppm | pnmscale 40 | display -
    # echo "   rotate 270 block"
    # ./ppmtrans2 -rotate 270 -block-major test1.ppm > r270block.ppm
    # cat r270block.ppm | pnmscale 40 | display -
    # echo "   flip horiz block"
    # ./ppmtrans2 -flip horizontal -block-major test1.ppm > fhorizblock.ppm
    # cat fhorizblock.ppm | pnmscale 40 | display -
    # echo "   flip vert block"
    # ./ppmtrans2 -flip vertical -block-major test1.ppm > fvertblock.ppm
    # cat fvertblock.ppm | pnmscale 40 | display - 
    # echo "   transpose block"
    # ./ppmtrans2 -transpose -block-major test1.ppm > tblock.ppm
    # cat tblock.ppm | pnmscale 40 | display -

    # echo "   rotate 0 row"
    # ./ppmtrans2 -rotate 0 -row-major test1.ppm > r0row.ppm
    # cat r0row.ppm | pnmscale 40 | display -
    # echo "   rotate 90 row"
    # ./ppmtrans2 -rotate 90 -row-major test1.ppm > r90row.ppm
    # cat r90row.ppm | pnmscale 40 | display -
    # echo "   rotate 180 row"
    # ./ppmtrans2 -rotate 180 -row-major test1.ppm > r180row.ppm
    # cat r180row.ppm | pnmscale 40 | display -
    # echo "   rotate 270 row"
    # ./ppmtrans2 -rotate 270 -row-major test1.ppm > r270row.ppm
    # cat r270row.ppm | pnmscale 40 | display -
    # echo "   flip horiz row"
    # ./ppmtrans2 -flip horizontal -row-major test1.ppm > fhorizrow.ppm
    # cat fhorizrow.ppm | pnmscale 40 | display -
    # echo "   flip vert row"
    # ./ppmtrans2 -flip vertical -row-major test1.ppm > fvertrow.ppm
    # cat fvertrow.ppm | pnmscale 40 | display - 
    # echo "   transpose row"
    # ./ppmtrans2 -transpose -row-major test1.ppm > trow.ppm
    # cat trow.ppm | pnmscale 40 | display -


    # echo "   rotate 0 col"
    # ./ppmtrans2 -rotate 0 -col-major test1.ppm > r0col.ppm
    # cat r0col.ppm | pnmscale 40 | display -
    # echo "   rotate 90 col"
    # ./ppmtrans2 -rotate 90 -col-major test1.ppm > r90col.ppm
    # cat r90col.ppm | pnmscale 40 | display -
    # echo "   rotate 180 col"
    # ./ppmtrans2 -rotate 180 -col-major test1.ppm > r180col.ppm
    # cat r180col.ppm | pnmscale 40 | display -
    # echo "   rotate 270 col"
    # ./ppmtrans2 -rotate 270 -col-major test1.ppm > r270col.ppm
    # cat r270col.ppm | pnmscale 40 | display -
    # echo "   flip horiz col"
    # ./ppmtrans2 -flip horizontal -col-major test1.ppm > fhorizcol.ppm
    # cat fhorizcol.ppm | pnmscale 40 | display -
    # echo "   flip vert col"
    # ./ppmtrans2 -flip vertical -col-major test1.ppm > fvertcol.ppm
    # cat fvertcol.ppm | pnmscale 40 | display - 
    # echo "   transpose col"
    # ./ppmtrans2 -transpose -col-major test1.ppm > tcol.ppm
    # cat tcol.ppm | pnmscale 40 | display -


    echo "NOW DO IT AGAIN... BUT TIMED..."
    # echo "   rotate 0 default"
    # ./ppmtrans2 -rotate 0 -time timefile.txt flowers.ppm > r0default.ppm
    # # cat r0default.ppm | pnmscale 40 | display -
    # echo "   rotate 90 default"
    # ./ppmtrans2 -rotate 90  -time timefile.txt flowers.ppm > r90default.ppm
    # # cat r90default.ppm | pnmscale 40 | display -
    # echo "   rotate 180 default"
    # ./ppmtrans2 -rotate 180 -time timefile.txt flowers.ppm > r180default.ppm
    # # cat r180default.ppm | pnmscale 40 | display -
    # echo "   rotate 270 default"
    # ./ppmtrans2 -rotate 270 -time timefile.txt flowers.ppm > r270default.ppm
    # # cat r270default.ppm | pnmscale 40 | display -
    # echo "   flip horiz default"
    # ./ppmtrans2 -flip horizontal -time timefile.txt flowers.ppm > fhorizdefault.ppm
    # # cat fhorizdefault.ppm | pnmscale 40 | display -
    # echo "   flip vert default"
    # ./ppmtrans2 -flip vertical -time timefile.txt flowers.ppm > fvertdefault.ppm
    # # cat fvertdefault.ppm | pnmscale 40 | display - 
    # echo "   transpose default"
    # ./ppmtrans2 -transpose -time timefile.txt flowers.ppm > tdefault.ppm
    # # cat tdefault.ppm | pnmscale 40 | display -

    echo "   rotate 0 block"
    ./ppmtrans2 -rotate 0 -block-major -time timefile.txt flowers.ppm > r0block.ppm
    # cat r0block.ppm | pnmscale 40 | display -
    echo "   rotate 90 block"
    ./ppmtrans2 -rotate 90 -block-major -time timefile.txt flowers.ppm > r90block.ppm
    # cat r90block.ppm | pnmscale 40 | display -
    echo "   rotate 180 block"
    ./ppmtrans2 -rotate 180 -block-major -time timefile.txt flowers.ppm > r180block.ppm
    # cat r180block.ppm | pnmscale 40 | display -
    echo "   rotate 270 block"
    ./ppmtrans2 -rotate 270 -block-major -time timefile.txt flowers.ppm > r270block.ppm
    # cat r270block.ppm | pnmscale 40 | display -
    echo "   flip horiz block"
    ./ppmtrans2 -flip horizontal -block-major -time timefile.txt flowers.ppm > fhorizblock.ppm
    # cat fhorizblock.ppm | pnmscale 40 | display -
    echo "   flip vert block"
    ./ppmtrans2 -flip vertical -block-major -time timefile.txt flowers.ppm > fvertblock.ppm
    # cat fvertblock.ppm | pnmscale 40 | display - 
    echo "   transpose block"
    ./ppmtrans2 -transpose -block-major -time timefile.txt flowers.ppm > tblock.ppm
    # cat tblock.ppm | pnmscale 40 | display -

    # echo "   rotate 0 row"
    # ./ppmtrans2 -rotate 0 -row-major -time timefile.txt flowers.ppm > r0row.ppm
    # # cat r0row.ppm | pnmscale 40 | display -
    # echo "   rotate 90 row"
    # ./ppmtrans2 -rotate 90 -row-major -time timefile.txt flowers.ppm > r90row.ppm
    # # cat r90row.ppm | pnmscale 40 | display -
    # echo "   rotate 180 row"
    # ./ppmtrans2 -rotate 180 -row-major -time timefile.txt flowers.ppm > r180row.ppm
    # # cat r180row.ppm | pnmscale 40 | display -
    # echo "   rotate 270 row"
    # ./ppmtrans2 -rotate 270 -row-major -time timefile.txt flowers.ppm > r270row.ppm
    # # cat r270row.ppm | pnmscale 40 | display -
    # echo "   flip horiz row"
    # ./ppmtrans2 -flip horizontal -row-major -time timefile.txt flowers.ppm > fhorizrow.ppm
    # # cat fhorizrow.ppm | pnmscale 40 | display -
    # echo "   flip vert row"
    # ./ppmtrans2 -flip vertical -row-major -time timefile.txt flowers.ppm > fvertrow.ppm
    # # cat fvertrow.ppm | pnmscale 40 | display - 
    # echo "   transpose row"
    # ./ppmtrans2 -transpose -row-major -time timefile.txt flowers.ppm > trow.ppm
    # # cat trow.ppm | pnmscale 40 | display -

    # echo "   rotate 0 col"
    # ./ppmtrans2 -rotate 0 -col-major -time timefile.txt flowers.ppm > r0col.ppm
    # # cat r0col.ppm | pnmscale 40 | display -
    # echo "   rotate 90 col"
    # ./ppmtrans2 -rotate 90 -col-major -time timefile.txt flowers.ppm > r90col.ppm
    # # cat r90col.ppm | pnmscale 40 | display -
    # echo "   rotate 180 col"
    # ./ppmtrans2 -rotate 180 -col-major -time timefile.txt flowers.ppm > r180col.ppm
    # # cat r180col.ppm | pnmscale 40 | display -
    # echo "   rotate 270 col"
    # ./ppmtrans2 -rotate 270 -col-major -time timefile.txt flowers.ppm > r270col.ppm
    # # cat r270col.ppm | pnmscale 40 | display -
    # echo "   flip horiz col"
    # ./ppmtrans2 -flip horizontal -col-major -time timefile.txt flowers.ppm > fhorizcol.ppm
    # # cat fhorizcol.ppm | pnmscale 40 | display -
    # echo "   flip vert col"
    # ./ppmtrans2 -flip vertical -col-major -time timefile.txt flowers.ppm > fvertcol.ppm
    # # cat fvertcol.ppm | pnmscale 40 | display - 
    # echo "   transpose col"
    # ./ppmtrans2 -transpose -col-major -time timefile.txt flowers.ppm > tcol.ppm
    # # cat tcol.ppm | pnmscale 40 | display -
    
done