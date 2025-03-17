#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    char input[9];
    
    printf("\nGive a max 8 length integer number: ");
    fgets(input, sizeof(input), stdin);
    
    input[strcspn(input, "\n")] = 0;
    
    printf("\n[%8s]\n", input);
	printf("\n[%08s]\n", input);
    
    return 0;
}
