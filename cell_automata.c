#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

// Does this change things? //

// First build some arrays - for future versions, consider making separate functions to build grid based 
// on command line inputs, and to introduce more complex secondary systems (e.g. iron chelation),
// but for now just do all in main - MAKE MODULAR EVENTUALLY

// I is always grid length (up down), J is always grid width (left right)


//** TO DO: Move this function into main argument, as currently taking too many arguments
//** Separately, if time, split into modules, but for now turn into main

char* find_free_space(int** animal_array, double** food_array, double** fullness_array,double food_eat_rate, int grid_length, int grid_width, int i, int j, int breed_time)
{

	printf("Function find_free_space received the following params:\n");
	printf("Array length = %d\n", grid_length);
	printf("Array width = %d\n", grid_width);
	printf("I = %d\n", i);
	printf("J = %d\n", j);
	int counter;
	double no_food = 0.0;


	assert(i < grid_length && "i out of bounds");
	assert(j < grid_width && "j out of bounds");

	char* directions = (char*)malloc(4*sizeof(char));


	counter = 0; // Reinitialise counter each time
	if  (j-1 >= 0)
	{
		directions[0] = 'L';

		if (food_array[i][j-1] > no_food){
		food_array[i][j-1] = food_array[i][j-1] - food_eat_rate;  
		counter +=1;
		}

		if (animal_array[i][j-1] > 0 && animal_array[i][j] == 0 && breed_time == 1)
		{
			animal_array[i][j] = 1;
		}
	}
	else 
	{
		directions[0] = 'X';
	}


	if  (j+1 < grid_width)
	{
		directions[1] = 'R';
		
		if (food_array[i][j+1] > no_food)
		{
		food_array[i][j+1] = food_array[i][j+1] - food_eat_rate;
		counter +=1;
		}
	}
	else 
	{
		directions[1] = 'X';
	}


	if  (i-1 >= 0)
	{
		directions[2] = 'U';
		if (food_array[i-1][j] > no_food)
		{
		food_array[i-1][j] = food_array[i-1][j] - food_eat_rate;
		counter +=1;
		}
	}
	else 
	{
		directions[2] = 'X';
	}

	if  (i+1 < grid_length)
	{
		directions[3] = 'D';
		if (food_array[i-1][j] > no_food)
		{
		food_array[i+1][j] = food_array[i+1][j] - food_eat_rate;
		counter +=1;
		}
	}
	else 
	{
		directions[3] = 'X';
	}

	fullness_array[i][j] += 0.1*counter;
	return(directions);
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

	for (i=0;i<grid_length;i++)
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
	}


	for (i=0;i<grid_length;i++)
	{
		for (j=0;j<grid_width;j++)
		{
			food_array[i][j]= 1.0;
		}
	}


	// Now build fullness array

	double** fullness_array = (double**)malloc(grid_width * sizeof(double*)); // pointer to a pointer to an array
	
	for (i=0;i<grid_length;i++)
	{
		fullness_array[i] = (double*)malloc(grid_length * sizeof(int)); // each column of array is now an address pointing to a 4 byte location in memory, where we'll store some ints
	}

	for (i=0;i<grid_length;i++)
	{
		for (j=0;j<grid_width;j++)
		{
			fullness_array[i][j]= 1.0;
		}
	}



	

	// TEMP - DELETE 
		printf("Food array updated as follows:\n");
		for (i=0;i<grid_length;i++)
		{
			for (j=0;j<grid_width;j++)
			{
				//food_array[i][j] += food_growth_rate
				printf("%f ", food_array[i][j]);
			}
			printf("\n");
		}



	// Test array has been built properly
	printf("Food Array element 4,3  = %f\n", food_array[4][3]);

	// ----------------------------------------------------------------//

	/* ADD AGENTS 	*/

	// Start by simply placing 5 in the centre 
	// First find centre, and logic to build + shape distribution around it

	double grid_width_double = (double) grid_width;
	double grid_length_double = (double) grid_length;
	int width_centre = ceil(grid_width_double/2)-1;
	int length_centre = ceil(grid_length_double/2)-1;
	printf("Centre of grid is %d %d\n", width_centre,length_centre);

	animal_array[length_centre][width_centre] = 1;

	for (i=0;i<grid_length;i++)
	{
		for (j=0;j<grid_width;j++)
		{
			if ((abs(j-width_centre) < 1 && abs(i - width_centre) <= 1) || (abs(j-width_centre) <= 1 && abs(i - width_centre) < 1))
			{	
				animal_array[i][j] = 1;				
			}
		}
	}




// Print animal_array to check progress
	printf("Animal grid currently looks like this:\n");
	for (i=0;i<grid_length;i++)
	{
		for (j=0;j<grid_width;j++)
		{
			printf("%d ", animal_array[i][j]);
		}
		printf("\n");
	}

	printf("\n-------------------------------------------------------------\n\n");



	// ----------------------------------------------------------------//


	/* RUN THE GAME  */


	/* First, I'll assume that animals are alive as long as they can feed each turn. */
	/* As soon as they can't feed, they die. This is basically saying that their feed rate*/ 
	/* is much faster than a single time interval*/

	// May need to sometimes iterate through agents in different order, to stop top heavy bias
	
	// Set constants
	double food_growth_rate = 0.2;
	double food_eat_rate = 0.1;

	// For each agent, need to determine n_Free_cells surrounding it. Then divide the
	// total eat rate it requires by n_Free_cells

	// Make space for a char array called directions
	char* directions;


	int t = 0; // time variable to track game progress
	int k; // just a loop variable to print
	int breed_time = 0;
	// Begin time simulation 
	while (t< 1)
	{  
		for (i=0;i<grid_length;i++) // First loop through the agents and find free space
		{
			for (j=0;j<grid_width;j++) 
			{
				if (animal_array[i][j] == 1)
				{
					// Find space around each position
					directions = find_free_space(animal_array,food_array,fullness_array,food_eat_rate,grid_length,grid_width,i,j,breed_time);
					printf("\nDirections position %d %d can move are:\n",i,j);
					
					for (k=0;k<4;k++)
					{
						printf("%c ", directions[k]);
					}
					printf("\n ----------------------------------------------------\n");


					// Add in hunger
					fullness_array[i][j] = fullness_array[i][j] - 0.2;

					// Kill off any starved animals
					if (fullness_array[i][j] < 0.5)
					{
						animal_array[i][j] = 0;
					}

				}
			}

		}
		breed_time = t % 2;
		// Grow food each turn
		printf("Food array updated as follows:\n");
		for (i=0;i<grid_length;i++)
		{
			for (j=0;j<grid_width;j++)
			{
				//food_array[i][j] += food_growth_rate
				printf("%f ", food_array[i][j]);
			}
			printf("\n");
		}

		t+=1;
	}


	free(food_array);
	free(animal_array);
	free(fullness_array);
		

}


