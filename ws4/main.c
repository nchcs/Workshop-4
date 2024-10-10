#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//#define MAX_FACTORIALS 10000
//#define NUM_FACTS 100

#define MAX_FACTORIALS 100
#define NUM_FACTS 100
struct FactorialResults
{
	//up to 12?
	//int results[MAX_FACTORIALS];
	//
	unsigned long long results[MAX_FACTORIALS];
	int numResults;
};

unsigned long long factorial(const int n)
//int factorial(const int n)
{
	return (n > 0) ? n * factorial(n - 1) : 1;	// correct
}

//This literally does nothing?
unsigned long long reduceFactorial(const int n)
//int reduceFactorial(const int n)
{
	return (n > 0) ? (n / n) : 1;	
}

//void computeFactorials(struct FactorialResults results, int numFactorials)	// copies large array to stack
void computeFactorials(struct FactorialResults* results, int numFactorials)	// correct
{
	int i;

	for (i = 0; i < numFactorials; i++)
	{
		results->results[i] = factorial(i);
	}
	results->numResults = numFactorials;
}

int main(void)
{
	struct FactorialResults results = { {0}, 0 };
	int i;

	computeFactorials(&results, NUM_FACTS);

	for (i = 0; i < NUM_FACTS; i++)
	{
		//for ull
		//printf("%5d %20llu\n", i, results.results[i]);
		//results.results[i] = reduceFactorial(results.results[i]);
		printf("%5d %20llu\n", i, results.results[i]);
	}

	return 0;
}
