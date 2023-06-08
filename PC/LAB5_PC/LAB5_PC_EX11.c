#include <stdio.h>
#include <stdint.h>

void print_bit_32 (uint32_t nr)
{
  uint32_t mask = 0x80000000; 
  uint8_t i = 0;
  for (i = 0; i < 32; i++)
    {
      if ((nr & mask) == 0)
        {
          printf ("0");
        }
      else
        {
          printf ("1");
        }
      mask = mask >> 1; 
    }
  printf ("\n");
}

int main ()
{
    int s = 0;
    uint32_t n , mask;
    scanf("%u" , &n);
    mask = 1;
    for ( int i = 0 ; i < 4 ; i++)
    {
        mask = 1 << i;
        if ( (n & mask) != 0)
        {
            s++;
        }
    }
    print_bit_32(n);
    printf("%d\n" , s);
    return 0;
}

/*
  0000 0000
  
  0001 1
  0010 2
  0011 3
  0100 4
  0101 5
  0110 6
  0111 7
  1000 8
  1001 9
  1010 10
  

 */
