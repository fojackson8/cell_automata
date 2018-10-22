#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* This version includes code to breed in direction of most food */

// First build some arrays - for future versions, consider making separate functions to build grid based 
// on command line inputs, and to introduce more complex secondary systems (e.g. iron chelation),
// but for now just do all in main - MAKE MODULAR EVENTUALLY

// I is always grid length (up down), J is always grid width (left right)


//** TO DO: Move this function into main argument, as currently taking too many arguments
//** Separately, if time, split into modules, but for now turn into main

char* update_arrays(int** offspring_array, int** animal_array, double** food_array, double** fullness_array,double food_eat_rate, int grid_length, int grid_width, int i, int j, int breed_time)
{
	int counter,bred;
	double no_food = 0.0;

	// Make sure input arguments make sense - if not throw error
	assert(i < grid_length && "i out of bounds");
	assert(j < grid_width && "j out of bounds");

	//char* directions = (char*)malloc(4*sizeof(char));
	char* placeholder = "ABC";

	// The food_levels vector tracks the amount of food at each position (LRUD) relative
	// to the animal. Once the vector is filled, the adjacent position with the most 
	// food is selected for breeding. food_levels is refreshed at each function call

	double food_levels[4]; // These are set to 0.0. If there is no adjacent space for an animal to breed, then food levels will stay at 0.0
	int adjacent_space[] = {0,0,0,0};  
	int any_adjacent_space = 0;// If = 0, no space, so don't breed. If = 1, go ahead.
	int p;
	for (p=0;p<4;p++)
	{
		food_levels[p] = 0.0; // refresh to zero at each function call
	}


	counter = 0; // Reinitialise counter each time
	bred = 0; // same for bred


	if  (j-1 >= 0)
	{
		//Feeding
		if (food_array[i][j-1] > no_food){
		food_array[i][j-1] = food_array[i][j-1] - food_eat_rate;  
		counter +=1;
		}
		// Breeding
		if (animal_array[i][j-1] == 0 && breed_time == 1) // Food levels stay at 0.0 if no adjacent space
		{
			food_levels[0] = food_array[i][j-1]; 
			adjacent_space[0] = 1; 
			any_adjacent_space = 1;// 1 means there is adjacent space in AT LEAST 1 DIRECTION
		}
	}

	if  (j+1 < grid_width)
	{
		//Feeding
		if (food_array[i][j+1] > no_food)
		{
		food_array[i][j+1] = food_array[i][j+1] - food_eat_rate;
		counter +=1;
		}
		// Breeding
		if (animal_array[i][j+1] == 0 && breed_time == 1)
		{
			food_levels[1] = food_array[i][j+1];
			adjacent_space[1] = 1;
			any_adjacent_space = 1;
		}
	}

	if  (i-1 >= 0)
	{
		//Feeding
		if (food_array[i-1][j] > no_food)
		{
		food_array[i-1][j] = food_array[i-1][j] - food_eat_rate;
		counter +=1;
		}
		// Breeding
		if (animal_array[i-1][j] == 0 && breed_time == 1)
		{
			food_levels[2] = food_array[i-1][j];
			adjacent_space[2] = 1;		
			any_adjacent_space = 1;
		}
	}

	if  (i+1 < grid_length)
	{
		//Feeding
		if (food_array[i+1][j] > no_food)
		{
		food_array[i+1][j] = food_array[i+1][j] - food_eat_rate;
		counter +=1;
		}
		// Breeding
		if (animal_array[i+1][j] == 0 && breed_time == 1)
		{
			food_levels[3] = food_array[i+1][j];
			adjacent_space[3] = 1;
			any_adjacent_space = 1;
		}
	}

	// Find best direction to breed (where there's most food)
	
	int location = 0;
	char positions[] = {'L','R','U','D'};
	char direction;
	double maximum; 

	// ** ACTION ** at some point need to deal with equal food values (add in randomness)

	if (breed_time == 1 && any_adjacent_space == 1) // Don't go through if no adjacent space anywhere
	{
		maximum= food_levels[0];
		for (p=0;p<4;p++)
		{
			if (food_levels[p] > maximum)
			{
				maximum = food_levels[p];
				location = p;
				// if (maximum > 0.0)
				// {location = p;} // Set location to an integer, corresponding to a direction to breed
			}
		}
		direction = positions[location];
		// printf("Maximum food for animal %d %d = %f in direction %c\n",i,j,maximum,direction);
		// printf("\n Location value = %d\n", location);

		// Couldn't get switch case to work as wanted, so using if for now - TEMP**
		// switch (location)
		// {
		// 	case 0:
		// 		offspring_array[i][j-1] = 1;
		// 		printf("\nAnimal %d %d bred 1 new animal at position %d %d \n", i,j,i,j-1); 
		// 	case 1:
		// 		offspring_array[i][j+1] = 1;
		// 		printf("\nAnimal %d %d bred 1 new animal at position %d %d \n", i,j,i,j+1); 

		// 	case 2:
		// 		offspring_array[i-1][j] = 1;
		// 		printf("\nAnimal %d %d bred 1 new animal at position %d %d \n", i,j,i-1,j); 

		// 	case 3:
		// 		offspring_array[i+1][j] = 1;
		// 		printf("\nAnimal %d %d bred 1 new animal at position %d %d \n", i,j,i+1,j); 

		// }	


		if (location ==0 && adjacent_space[0] == 1) // if location ==0, there is most feed directly up, so breed up.
		{
			offspring_array[i][j-1] = 1;
			//printf("\nAnimal %d %d bred 1 new animal at position %d %d, ", i,j,i,(j-1)); 
		}
		else if (location ==1 && adjacent_space[1] == 1)
		{
			offspring_array[i][j+1] = 1;
			//printf("\nAnimal %d %d bred 1 new animal at position %d %d, ", i,j,i,(j+1)); 
		}
		else if (location ==2 && adjacent_space[2] == 1)
		{
			offspring_array[i-1][j] = 1;
			//printf("\nAnimal %d %d bred 1 new animal at position %d %d, ", i,j,(i-1),j); 
		}
		else if (location ==3 && adjacent_space[3] == 1)
		{
			offspring_array[i+1][j] = 1;
			//printf("\nAnimal %d %d bred 1 new animal at position %d %d, ", i,j,(i+1),j); 
		}
	}

	// Update fullness array, according to how much has been eaten
	fullness_array[i][j] += food_eat_rate*counter;
	//printf(" has eaten %f food\n", 0.1*counter);
	
	return(placeholder);

	//free(directions);
}




	






int main(int argc, char* argv[])
{	
	/* BUILD ARRAYS */
	// Initialise variables and constants in model
	

	// Assign parameters- 
	int grid_length = atoi(argv[1]);
	int grid_width = atoi(argv[2]);
	double food_growth_rate = atof(argv[3]);
	double food_eat_rate = atof(argv[4]);
	double hunger_constant = atof(argv[5]);
	int time_limit = atoi(argv[6]);
	int breed_frequency = atoi(argv[7]);

	// double food_growth_rate = 0.2;
	// double food_eat_rate = 0.1;
	// double hunger_constant = 0.2;
	// int time_limit = 20;
	// int breed_frequency = 2;

	int i,j; // These will be used to iterate through all arrays

	// printf("Specify width and length of array \n");
	// scanf("%d \n %d", &grid_width,&grid_length);

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
	printf("\n\n**INITIALISE**\n\n");
	printf("Array element 2,1  = %d\n", animal_array[2][1]);




	// Now build 2d food array
	double** food_array = (double**)malloc(grid_width * sizeof(double*)); // pointer to a pointer to an array
	
	for (i=0;i<grid_length;i++)
	{
		food_array[i] = (double*)malloc(grid_length * sizeof(double)); // each column of array is now an address pointing to a 4 byte location in memory, where we'll store some ints
	}


	for (i=0;i<grid_length;i++)
	{
		for (j=0;j<grid_width;j++)
		{
			food_array[i][j]= 1.0;
		}
	}


	// Now build offspring array

	int** offspring_array = (int**)malloc(grid_width * sizeof(int*)); // pointer to a pointer to an array
	
	for (i=0;i<grid_length;i++)
	{
		offspring_array[i] = (int*)malloc(grid_length * sizeof(int)); // each column of array is now an address pointing to a 4 byte location in memory, where we'll store some ints
	}

	for (i=0;i<grid_length;i++)
	{
		for (j=0;j<grid_width;j++)
		{
			offspring_array[i][j]= 0;
		}
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

	// Distribute around centre
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
	printf("Animal grid starts like this:\n");
	for (i=0;i<grid_length;i++)
	{
		for (j=0;j<grid_width;j++)
		{
			printf("%d ", animal_array[i][j]);
		}
		printf("\n");
	}

	// Print food array also
	printf("Food grid starts like this:\n");
	for (i=0;i<grid_length;i++)
	{
		for (j=0;j<grid_width;j++)
		{
			printf("%f ", food_array[i][j]);
		}
		printf("\n");
	}


	// Now build fullness array
	// Need to introduce hack to make fullness correspond to animal array - multiply each position by corresponding position in animal array

	double** fullness_array = (double**)malloc(grid_width * sizeof(double*)); // pointer to a pointer to an array
	for (i=0;i<grid_length;i++)
	{
		fullness_array[i] = (double*)malloc(grid_length * sizeof(double)); // each column of array is now an address pointing to a 4 byte location in memory, where we'll store some ints
	}

	for (i=0;i<grid_length;i++)
	{
		for (j=0;j<grid_width;j++)
		{		
			fullness_array[i][j]= 1.0*animal_array[i][j];
		}
	}


	printf("\n Fullness array before start:\n");
	for (i=0;i<grid_length;i++)
	{
		for (j=0;j<grid_width;j++)
		{
			//fullness_array[i][j] = fullness_array[i][j]*animal_array[i][j]; // update fullness_array, so that if an animal dies, it corresponds to 0
			printf("%f ", fullness_array[i][j]);
		}
		printf("\n");
	}





	printf("\n-------------------------------------------------------------\n\n");









	// ----------------------------------------------------------------//
	// ----------------------------------------------------------------//
	// ----------------------------------------------------------------//











	/* RUN THE GAME  */



	// May need to sometimes iterate through agents in different order, to stop top heavy bias
	

	// Make space for a char array called directions
	char* directions;

	int t = 0; // time variable to track game progress
	int k; // just a loop variable to print
	int breed_time = 0;  
	// Begin time simulation 

	printf("**RUN SIMULATION**\n\n");
	while (t< time_limit)
	{  
		printf("T = %d\n\n", t);
		// First decide whether it's breed time
		breed_time = t % breed_frequency; 

		for (i=0;i<grid_length;i++) // First loop through the agents and find free space
		{
			for (j=0;j<grid_width;j++) 
			{
				if (animal_array[i][j] == 1)
				{
					//printf("%d,%d ", i,j);
					// Find space around each position
					directions  = update_arrays(offspring_array,animal_array,food_array,fullness_array,food_eat_rate,grid_length,grid_width,i,j,breed_time);
					
					// Add in hunger
					fullness_array[i][j] = fullness_array[i][j] - hunger_constant; // Subtract some food from each animal

					// Kill off any starved animals
					if (fullness_array[i][j] < 0.5)
					{
						animal_array[i][j] = 0;
					}

					//printf("\nDirections position %d %d can move are:\n",i,j);
					
					// for (k=0;k<4;k++)
					// {
					// 	printf("%c ", directions[k]);
					// }
					//printf("\n ----------------------------------------------------\n");

				}

			}
			printf("\n");
		}
		

	




		// Add in new animals to animal array, grow food,
		// EVERYTIME you update animal array, must also update fullness_array
		//printf("\nOffspring array at end of t = %d: \n",t);
		for (i=0;i<grid_length;i++)
		{
			for (j=0;j<grid_width;j++)
			{
				//printf("%d ",offspring_array[i][j]);
				animal_array[i][j] = animal_array[i][j] + offspring_array[i][j]; // Update animal array with new offspring
				fullness_array[i][j] = fullness_array[i][j] + (double)offspring_array[i][j];
				fullness_array[i][j] = fullness_array[i][j]*animal_array[i][j]; // update fullness_array, so that if an animal dies, it corresponds to 0

				food_array[i][j] += food_growth_rate; // Let more food grow
			}
			//printf("\n");
		}

		// refresh offspring array
		for (i=0;i<grid_length;i++)
		{
			for (j=0;j<grid_width;j++)
			{
				offspring_array[i][j]= 0; // Refresh offspring array to 0
			}
			//printf("\n");
		}



		// Now print animal array
		printf("\nAnimal array at end of t = %d:\n",t);
		for (i=0;i<grid_length;i++)
		{
			for (j=0;j<grid_width;j++)
			{
				printf("%d ", animal_array[i][j]);
			}
			printf("\n");
		}
		
		// // Now print fullness array
		// printf("\n Fullness array at end of t = %d:\n",t);
		// for (i=0;i<grid_length;i++)
		// {
		// 	for (j=0;j<grid_width;j++)
		// 	{
		// 		printf("%f ", fullness_array[i][j]);
		// 	}
		// 	printf("\n");
		// }

		// Now print Food array
		// printf("\nFood array at end of t = %d:\n",t);
		// for (i=0;i<grid_length;i++)
		// {
		// 	for (j=0;j<grid_width;j++)
		// 	{
		// 		printf("%f ", food_array[i][j]);
		// 	}
		// 	printf("\n");
		// }

		printf("\n ---------------------------------------------- \n");





		t+=1;
	}


	free(food_array);
	free(animal_array);
	free(fullness_array);
		

}


