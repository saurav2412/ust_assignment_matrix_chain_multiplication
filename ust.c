// MATRIX CHAIN MULTIPLICATION

// Objective: Given a sequence of matrices, find the order which require least number of multiplications.

// Here two approaches are discussed one being optimal substructre and the other is dynamic programming.

/* INPUT SAMPLE: Given an array arr[], this represents the dimension of the matrices present. Such that
                 the i'th matrices will have  arr[i-1]*arr[i] dimensions. 

		 e.g- 
			arr[] = {1, 2, 3, 4, 3}

		 	Here, there are 4 matrices with dimsensions 1*2, 2*3, 3*4, 4*3.
*/



/* FIRST APPROACH: OPTIMAL SUBSTRUCTRE */

/* This is a recursive approach to multiply the given sequence of matrices, that is by placing
   paranthesis at all possible places and calculate the cost for each placement and return the 
   minimum value. If there are n number of matrices then there are n-1 ways to place paranthesis. */

/* EXAMPLE: If there are 4 matrices X,Y,Z,W. Then there are 3 ways to multiply them as (X)YZW, (XY)(ZW),
            (XYZ)(W). Now one with the minimum number of multiplications will be the order we are looking
	    for. */

// Optimal substructure implementation

#include<stdio.h>

int matrix_mul(int *arr,int l, int u)
{
	// base case	
	if(l == u)
		return 0;

	int i;
	int min = 20000;
	int cal;

	for(i = l; i < u; i++)
	{
		cal = matrix_mul(arr, l, i) + matrix_mul(arr, i+1, u) + arr[l-1] * arr[i] * arr[u];

		if(cal < min)
			min = cal;
		else
			;
	}

	return min;
}

int main()
{
	int n;

	printf("Enter number of matrices: ");
	scanf("%d", &n);

	// Array storing there dimensions
	int arr[n+1];

	int i;
	int temp;

	printf("Enter there dimensions: ");

	for(i = 0; i < n+1; i++)
	{
		scanf("%d", &temp);
		arr[i] = temp;
	}

	int min = matrix_mul(arr, 1, n);

	printf("Minimum number of mul: %d", min);

	return 0;
}

/* OUTPUT: Enter number of matrices: 4
	   Enter there dimensions: 1 2 3 4 3

	   Minimum number of multiplications are: 30
*/ 

/* Time comlpexity analysis: The time complexity of the above programme is exponential, as can be 
                             seen that this approach compute the same subproblem again and again.
			     Which is a kind of brute force approach.  */



/* SECOND APPROACH: DYNAMIC PROGRAMMING */

/* The first step of the dynamic programming paradigm is to characterize the structure of an optimal
   solution. For the matrix chain multipliction problem, like other dynamic programming problems, involves 
   determining the overlapping subproblems. We would like to break the problem into subproblems, whose 
   solutions can be combined to obtain a solution to the global problem. Unlike optimal structure approach 
   where the overlapping subproblems were neglected. Here once they are calculated they will be stored in 
   table and will be used when encountered again. */

/* FORMULATION: A table will be maintained to keep track of the solutions of the subproblems that have been 
                encountered. We will use and build table in bottom up manner. For {1 <= i <= j <= n}, let m[i,j]
		be the minimum number of scalar multiplications needed to compute the A[i to j]. */

// Dynamic programming implementation

#include<stdio.h>

int matrix_mul(int *arr, int n)
{
	int m[n][n];

	int i;
	int j;
	int k;
	int L;
	int q;

	for(i = 1; i < n; i++)
		m[i][i] = 0;

	for(L = 2; L < n; L++)
	{
		for(i = 1; i < n-L+1; i++)
		{
			j = i + L - 1;
			m[i][j] = 20000;

			for(k = 1; k <= j - 1; k++)
			{
				q = m[i][k] + m[k+1][j] + arr[i-1] * arr[k]*arr[j];

				if(q < m[i][j])
					m[i][j] = q;
			}
		}
	}

	return m[1][n-1];
}

int main()
{
	int n;

	printf("Enter number of matrices: ");
	scanf("%d", &n);

	// Array storing there dimensions
	int arr[n+1];

	int i;
	int temp;

	printf("Enter there dimensions: ");

	for(i = 0; i < n+1; i++)
	{
		scanf("%d", &temp);
		arr[i] = temp;
	}

	int min = matrix_mul(arr, n+1);

	printf("Minimum number of mul: %d", min);

	return 0;
}


/* OUTPUT: Enter number of matrices: 4
	   Enter there dimensions: 1 2 3 4 3

	   Minimum number of multiplications are: 30
*/ 

/* Time comlpexity analysis: Time complexity for this approach will be just bcs of the three
                             for loops. That will result in O(n^3). Which is far less than what
			     was for optimal substructure solution. */
