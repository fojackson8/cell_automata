#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Does this change things? //

// First build some arrays - for future versions, consider making separate functions to build grid based 
// on command line inputs, and to introduce more complex secondary systems (e.g. iron chelation),
// but for now just do all in main - MAKE MODULAR EVENTUALLY

// I is always grid length (up down), J is always grid width (left right)


int find_free_space(int argc, char* argv[])
{
	int array_length = (int)argv[1]
	int array_width = (int)argv[2]
	int i = (int)argv[3]
	int j = (int)argv[4]

	// printf("Set array length, then array width, then i, then j\n");
	// scanf("%d \n %d \n %d \n %d \n ",&array_length,&array_width,&i,&j);

	printf("Array length = %d\n", array_length);
	printf("Array width = %d\n", array_width);
	printf("I = %d\n", i);
	printf("J = %d\n", j);

	char directions[4];

	assert(i < array_length && "i out of bounds");
	assert(j < array_width && "j out of bounds");

	if  (j-1 >= 0)
	{
		directions[0] = 'L';
	}
	else 
	{
		directions[0] = 'X';
	}


	if  (j+1 <= array_width)
	{
		directions[1] = 'R';
	}
	else 
	{
		directions[1] = 'X';
	}


	if  (i-1 >= 0)
	{
		directions[2] = 'U';
	}
	else 
	{
		directions[2] = 'X';
	}

	if  (i+1 <= array_length)
	{
		directions[3] = 'D';
	}
	else 
	{
		directions[3] = 'X';
	}

	int k;
	for (k=0;k<4;k++)
	{
		printf("%c \n", directions[k]);
	}
	

}



	



int main(void)
{	
	/* BUILD ARRAYS */
	// Initialise variables and constants in model
	int grid_width;
	int grid_length;
	int i,j; // These will be used to iterate through the grid

	printf("Specify width and length of array \n");
	scanf("%d \n %d", &grid_width,&grid_length);

	// First build 2d animal_array
	int** animal_array = (int**)malloc(grid_width * sizeof(int*)); // pointer to a pointer to an array
	
	for (i=0;i<grid_length;i++)
	{
		animal_array[i] = (int*)malloc(grid_length * sizeof(int)); // each column of array is now an address pointing to a 4 byte location in memory, where we'll store some ints
	
	}

	for (i=0;i<grid_width;i++)
	{
		for (j=0;j<grid_width;j++)
		{
			animal_array[i][j] = 0;
		}
	}


	// Test array has been built properly
	printf("Array element 2,1  = %d\n", animal_array[2][1]);




	// Now build 2d food array
	double** food_array = (double**)malloc(grid_width * sizeof(double*)); // pointer to a pointer to an array
	
	for (i=0;i<grid_length;i++)
	{
		food_array[i] = (double*)malloc(grid_length * sizeof(int)); // each column of array is now an address pointing to a 4 byte location in memory, where we'll store some ints
	int i,j;
	}


	for (i=0;i<grid_length;i++)
	{
		for (j=0;j<grid_width;j++)
		{
			food_array[i][j]= 1.0;
		}
	}


	// Test array has been built properly
	printf("Food Array element 2,1  = %f\n", food_array[2][1]);


	
	



	// ---------- //

	/* ADD AGENTS 	*/

	// Start by allocating 5 in the centre 
	// First find centre, and logic to build + shape distribution around it

	double grid_width_double = (double) grid_width;
	double grid_length_double = (double) grid_length;
	int width_centre = ceil(grid_width_double/2)-1;
	int length_centre = ceil(grid_length_double/2)-1;
	printf("Centre of grid is %d %d\n", width_centre,length_centre);

	animal_array[length_centre][width_centre] = 1;

	for (i=0;i<grid_width;i++)
	{
		for (j=0;j<grid_length;j++)
		{
			if ((abs(j-width_centre) < 1 && abs(i - width_centre) <= 1) || (abs(j-width_centre) <= 1 && abs(i - width_centre) < 1))
			{	
				animal_array[i][j] = 1;				
			}
		}
	}




// Print array to check progress
	for (i=0;i<grid_length;i++)
	{
		for (j=0;j<grid_width;j++)
		{
			printf("%d ", animal_array[i][j]);
		}
		printf("\n");
	}




	/* RUN THE GAME  */
	/* First, I'll assume that animals are alive as long as they can feed each turn. */
	/* As soon as they can't feed, they die. This is basically saying that their feed rate*/ 
	/* is much faster than a single time interval*/

	// May need to sometimes iterate through agents in different order, to stop top heavy bias
	
	// Set constants
	double food_growth_rate = 0.2;
	double food_eat_rate = 0.1

	// For each agent, need to determine n_Free_cells surrounding it. Then divide the
	// total eat rate it requires by n_Free_cells

	int t = 0;
	// Begin time simulation 
	while (t< 100)
	{  
		for (i=0;i<grid_length;i++) // First loop through the agents and find free space
		{
			for (j=0;j<grid_width;j++) 
			{
				if 
			}

		}
		


		t+=1;
	}



		

}



