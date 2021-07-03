#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) (((a)>(b))?(a):(b))


int init_DP (int * DP, int * points, int nStair)
{
	for (int i = 3; i < nStair; i++)
	{
		DP[i] = MAX(DP[i - 3] + points[i - 1] + points[i], DP[i - 2] + points[i]);
	}

	return DP[nStair - 1];
}

int main()
{
	int nStairs, data;
	scanf("%d", &nStairs);
	int *points = (int*)malloc(sizeof(int)*nStairs);
	for (int i = 0 ; i < nStairs; i++)
	{
		scanf("%d", &data);
		points[i] = data;
	}
	int * DP = (int*)malloc(sizeof(int)*nStairs);
	DP[0] = points[0];
	DP[1] = points[0] + points[1];
	DP[2] = MAX(points[0] + points[2], points[1] + points[2]);

	printf("%d", init_DP(DP, points, nStairs));

}