#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int *result;
int iter=1;

void *faktorial(void *arg)
{
	int i, j;
	int res;
	int *num = (int*) arg;
	res = 1;
	for(i=2;i<=*num;i++) {
		res*=i;
	}
	result[iter] = res;
	iter++;
}

void sort (int A[], int n)
{
	int a, i, j;
	for (i = 1; i < n; ++i) 
	{
		for (j = i + 1; j < n; ++j)
		{
			if (A[i] > A[j]) 
			{
				a = A[i];
				A[i] = A[j];
				A[j] = a;
			}
		}
	}
}
 
int main(int argc, char* argv[])
{
	int size=argc;
	int num[size];
	int i;

	result = malloc(sizeof(int) * size);

	for(i=1;i<size;i++) {
		num[i] = atoi(argv[i]);
	}

	sort(num, size);

	pthread_t tid[size];

	for(i=1;i<size;i++) {
		pthread_create(&tid[i], NULL, faktorial, &num[i]);
	}
	for(i=1;i<size;i++) {
		pthread_join(tid[i], NULL);
	}

	sort(result, size);

	for(i=1;i<size;i++) {
		printf("%d! = %d\n", num[i], result[i]);
	}
	return 0;
}
