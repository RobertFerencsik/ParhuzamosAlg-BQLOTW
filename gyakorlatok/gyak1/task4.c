#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int max = 1000;
	int min = 500;
	srand(time(0));
	int randomInt = rand() % (max - min +1) + min;
	printf("\nRandom integer: %d", randomInt);
	
	max = max * 100;
	min = min * 100;
	float randomFloat = (float)(rand() % (max - min +1) + min) / 100;
	printf("\nRandom float: %.2f", randomFloat);
	return 0;
}