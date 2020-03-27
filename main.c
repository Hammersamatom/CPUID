#include <stdio.h>
#include <stdlib.h>


char* IntToCharPointer(int input)
{
    int totalChars = sizeof(input);
    char* output = (char*)malloc(totalChars);

    for (int byte = 0; byte < totalChars; byte++)
    {
        /*
        for (int bit = 0; bit < 8; bit++)
        {
            int stepper = bit + (byte * 8);
            int shifted = 1 << stepper;
            int ordbyte = (input & shifted) >> byte*8;
            output[(totalChars-1)-byte] |= ordbyte;  
        }
        */
        int stepper = 8 * byte;
        int shifted = 0xff << stepper;
        int ordbyte = (input & shifted) >> stepper;
        output[(totalChars-1)-byte] |= ordbyte;
    }

    return output;
}                                                            


char* ReverseCharPointer(char* array, int size)
{
    char* output = (char*)malloc(size);

    for (int i = 0; i < size; i++)
    {
        output[(size-1)-i] = array[i];
    }

    return output;
}


// Spaces out a char* every 8th character
char* spaceBytes(char* input, int size)
{
    int newSize = size + size/8;        // Specifying new size for output array. The subtraction is to avoid the first space from the array.

    char* output = (char*)malloc(newSize);

    int offset = 0;
    for (int i = 0; i < size; i++)
    {
        if (i % 8 == 0)
        {
            output[i+offset] = ' ';
            offset++; 
        }

        output[i+offset] = input[i];
    }
    
    return output;
}


// Takes a INT32 as an input and outputs it's binary equivalent as characters in a char*
char* binary(int input, int size)
{
	char* output = (char*)malloc(size);
	
    for (int i = 0; i < size; i++)
    {
        output[(size-1)-i] = (input & (1 << i)) >> i ? '1' : '0';    
    }

	return output;
}



// Spaces a string output every 8th character <<<< This functions like a macro and doesn't have to exist >>>>
char* getNiceBytes(int input, int size)
{
    return spaceBytes(binary(input, size), size);
}

void cpuid(int address, int* registers)
{
    __asm__(
            "cpuid"
            :"=a"(registers[0]), "=b"(registers[1]), "=c"(registers[2]), "=d"(registers[3]) // Assigning 
            :"0"(address) // Address into EAX
           );
}

int main()
{
    int regNum = 4; // EAX, EBX, ECX, EDX
    int* regs = (int*)malloc(4);
    char* processor = (char*)malloc(48);
    

    for (int i = 0; i < 3; i++)
    {
        int offset = 0x80000002 + i;
        cpuid(offset, regs); 
        /*                                                                                                                                                                                  
        printf("%Xh:(EAX) %s (EBX) %s (ECX) %s (EDX) %s\n", offset, ReverseCharPointer(IntToCharPointer(regs[0]), 4),
                                                                    ReverseCharPointer(IntToCharPointer(regs[1]), 4),
                                                                    ReverseCharPointer(IntToCharPointer(regs[2]), 4),
                                                                    ReverseCharPointer(IntToCharPointer(regs[3]), 4));
        */
        for (int j = 0; j < 16; j++)
        {
            processor[j+(i*16)] = ReverseCharPointer(IntToCharPointer(regs[j/4]), 4)[j%4];
        }
    }

    printf("String: %s\n", processor);
    return 0;
}
