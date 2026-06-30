unsigned char letters[] = "abcdefghij";

int even = 0;

int odd = 0;



void ex02()

{

   unsigned int count = 0;



   while (letters[count]) {

      if (letters[count++] & 1)

        odd++;

      else

        even++;

   }

}