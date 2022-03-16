// #include "assert.h"
// #include <stdio.h>
// #include <stdint.h>
// #include "file-ppm.h"
// #include "a2methods.h"
// #include <mem.h>
// #include "bitpack.h"
// #include "except.h"

// void news_tests();
// void newu_tests();
// void gets_tests();
// void getu_tests();
// void fitss_tests();
// void fitsu_tests();

int main()
{
//     fitsu_tests();
//     fitss_tests();
//     getu_tests();
//     gets_tests();
//     newu_tests();
//     news_tests();
    return 0;
}

// void news_tests()
// {
//     int64_t testing = (int64_t)Bitpack_news((int64_t)38, 7, 0, (int64_t)42);
//     assert(testing == 42);

//     uint64_t temp = (uint64_t) Bitpack_news(((uint64_t) 1234), 4, 2, -6);
//     printf("temp: %d\n", temp);

//     assert(Bitpack_gets(temp, 4, 2) == -6);
//     assert(temp == (uint64_t) 1258);

    
//     assert(Bitpack_gets(Bitpack_news((uint64_t)1234, 4, 2, -6), 4, 5) == 7);

//     assert(Bitpack_gets(Bitpack_news((uint64_t) 233, 5, 4, -7), 5, 4) == -7);
//     assert(Bitpack_gets(Bitpack_news(0x3f4, 6, 2, -4), 6, 2) == -4);
//     assert(Bitpack_gets(Bitpack_news((uint64_t)38, 7, 0, (uint64_t)42), 7, 0) == 42);
//     assert(Bitpack_news((int64_t)38, 7, 0, (int64_t)42) == 42);
    
//     assert(Bitpack_gets(testing, 7, 0) == 42);
//     printf("Success! All tests passed for news.\n");
// }

// void newu_tests()
// {
//     assert(Bitpack_newu((int64_t)38, 6, 0, (int64_t)42) == 42);
//     assert(Bitpack_getu(Bitpack_newu((uint64_t)5, 2, 1, (uint64_t)3), 2, 4) == Bitpack_getu((uint64_t)5, 2, 4));
//     assert(Bitpack_newu(Bitpack_newu((uint64_t)222, 4, 2, (uint64_t)3), 3, 1, 2) == 196);
//     assert(Bitpack_newu((uint64_t)206, 3, 1, (uint64_t)2) == 196);
//     assert(Bitpack_newu((uint64_t)222, 4, 2, (uint64_t)3) == 206);
//     uint64_t word2 = 652;
//     uint64_t* wordptr = &word2;
//     assert(Bitpack_getu(Bitpack_newu(*wordptr, 5, 3, (uint64_t)0), 5, 3) == 0);
    
//     // //getu(newu(word, w, lsb, val), w2, lsb2) == getu(word, w2, lsb2)
//     printf("Success! All tests passed for newu.\n");
// }

// void gets_tests()
// {
//     assert(Bitpack_gets(0x3f4, 6, 2) == -3);/*from spec*/
//     assert(Bitpack_gets(1494, 6, 1) == -21);
//     assert(Bitpack_gets(1494, 3, 3) == 2);
//     assert(Bitpack_gets(1494, 4, 3) == -6);
//     printf("Success! All test cases passed for gets.\n");
// }

// void getu_tests()
// {
//     assert(Bitpack_getu(0x3f4, 6, 2) == 61);/*from spec*/
//     assert(Bitpack_getu((uint64_t)420, 4, 2) == 9);
//     assert(Bitpack_getu((uint64_t)420, 0, 58) == 0);
//     assert(Bitpack_getu((uint64_t)420, 3, 0) == 4);
//     assert(Bitpack_getu((uint64_t)420, 4, 5) == 13);
//     assert(Bitpack_getu((uint64_t)420, 0, 5) == 0);
//     assert(Bitpack_getu((uint64_t)109, 0, 5) == 0);
//     assert(Bitpack_getu((uint64_t)109, 2, 5) == 3);
//     assert(Bitpack_getu((uint64_t)109, 3, 2) == 3);
//     assert(Bitpack_getu((uint64_t)109, 4, 0) == 13);
//     printf("Success! All tests passed for getu.\n");
// }

// void fitss_tests()
// {
//     assert(Bitpack_fitss((int64_t)5, 4));
//     assert(Bitpack_fitss((int64_t)5, 3) == false);
//     assert(Bitpack_fitss((int64_t)42, 7));
//     assert(Bitpack_fitss((int64_t)4, 8));
//     assert(Bitpack_fitss((int64_t)-4, 3));
//     assert(Bitpack_fitss((int64_t)-8, 4));
//     assert(Bitpack_fitss((int64_t)-5, 3) == false);
//     assert(Bitpack_fitss((int64_t)-5, 0) == false);
//     assert(Bitpack_fitss((int64_t)43, 0) == false);
//     printf("Success! All test cases passed for fitss.\n");
// }

// void fitsu_tests()
// {
//     assert(Bitpack_fitsu((uint64_t)5, 3));
//     assert(Bitpack_fitsu((uint64_t)42, 6));
//     assert(Bitpack_fitsu((uint64_t)8, 3) == false);
//     assert(Bitpack_fitsu((uint64_t)8, 0) == false);
//     printf("Success! All tests passed for fitsu.\n");
// }