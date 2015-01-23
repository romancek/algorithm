#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10

int main()
{
	double set[N]={0.0};
	for(int i = 0;i < N;i++){
		set[i] = ((double)rand() / ((double)RAND_MAX + 1))*1.0;
		printf("%lf\n",set[i]);
	}

	double sum = 0.0;
	double products = 1.0;

	for(int i = 0;i < N;i++){
		products = products * (1- set[i]);
		sum += set[i];
	}
	printf("sum:%lf,exp(-sum):%lf,product:%lf\n",sum,exp(-sum),products);
	return 0;
}