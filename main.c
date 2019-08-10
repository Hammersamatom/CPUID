#include <stdio.h>
#include <stdlib.h>

char* spaceBytes(char* input, int size)
{
  int newSize = size + size/8;        // Specifying new size for output array. The subtraction is to avoid the first space from the array.

  char* output = (char*)malloc(newSize);

  int offset = 0;
  for (int i = 0; i < size; i++)
  {
    if (i % 8 == 0/* && i != 0*/)
    {
      output[i+offset] = ' ';
      offset++; 
    }

    output[i+offset] = input[i];
  }

  return output;
}

char* binary(int input, int size)
{
	char* output = (char*)malloc(size);
	
  for (int i = 0; i < size; i++)
  {
      output[(size-1)-i] = (input & (1 << i)) >> i ? '1' : '0';    
  }

	return output;
}

char* getNiceBytes(int input, int size)
{
  return spaceBytes(binary(input, size), size);
}

int main()
{
  int i, a, b, c, d;

  for (i = 0; i < 8; i++)
  {
    __asm__(
            "cpuid"
            :"=a"(a), "=b"(b), "=c"(c), "=d"(d) // EAX into a (output)
            :"0"(0x80000000+i)                  // i into EAX (input)
            //:"%ecx","%edx"                    // clobbered registers are unused or trashed by other instructions
            ); 

    printf("The code %i gives >> (EAX)%s (EBX)%s (ECX)%s (EDX)%s\n", i, getNiceBytes(a, 32), getNiceBytes(b, 32), getNiceBytes(c, 32), getNiceBytes(d, 32));
  }
  
  return 0;
}
