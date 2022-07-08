#include <stdio.h>

int main()
{
  int nline, ncolum, all_lines, all_colums;

  scanf("%d %d", &all_lines, &all_colums);

  for (nline = 1; nline <= all_lines; nline++)
  {
    for (ncolum = 1; ncolum <= all_colums; ncolum++)
    {
      if (nline == ncolum)
      {
        break;
      }
      if (nline > 1 && ncolum < all_colums)
      {
        printf("(%d, %d) - ", nline, ncolum);
      }
      else if (ncolum == all_colums)
      {
        printf("(%d, %d)", nline, ncolum);
      }
    }
    printf("\n");
  }

  return 0;
}