short v1[4] = {32, 34, 27, 4};

int   v2[5] = {12, 22, 31, 23, 6};

char  v3[4] = {0, 0, 0, 0};

long  v4[8] = {0, 0, 0, 0, 0, 0, 0, 0};



int   i = 0;

short j = 0;



void aux() {

   for (i = 0; i < 4; i++) {

      j = 0;

      while (j < 5) {

         if (i == j) {

            v3[i] = v1[i] + v2[j];

         }

         else {

            v4[i + j] += v1[i] + v2[j];

         }

         j++;

      }

   }

}