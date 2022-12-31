#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

// Global variables
unsigned int size;  // length of one side of the lattice
unsigned int n; // number of steps in nonequilibrium protocol
int* forw;  // table of forward indices
int* back;  // table of backward indices
double* my_exp; // table of exponents
double P;   // probability of Ising-type spin on lattice

// Functions

// Prints table 'tab'
void print_lattice(int** tab)
{
    static int i, j;

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Saves table 'tab' to txt file 'f'
void save_lattice(int** tab, FILE* f)
{
    static int i, j;

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            fprintf(f, "%d\t", tab[i][j]);
        }
        fprintf(f,"\n");
    }
}

// Performs nn MC steps of heath-bath or voter algorithm on lattice 'tab' with control parameter 'J' or 'p'
void Dynamics(int** tab, int** tab2, double J, double p, unsigned int nn)
{
    static unsigned int x;  // x component of random spin
    static unsigned int y;  // y component of random spin
    static unsigned int z;  // neighbour of random spin: z = 0 right, z = 1 up, z = 2 left, z = 3 down
    static double hi;   // sum of neighbour spins
    static double rand_num; // random number
    static int i, index;    // temporary variables

    for(i = 0; i < nn; i++)
    {
        x = rand() % size;
        y = rand() % size;

        rand_num = ((double) rand())/((double) RAND_MAX + 1.0); // random real number in range [0,1)

        if(tab2[x][y] == 0) // heat-bath dynamics
        {
            if(x == 0)  // if the spin lies in the 0th row
        	{
           		hi = tab[forw[x]][y] + tab[x][forw[y]] + J * tab[back[x]][y] + tab[x][back[y]];
        	}
        	else if(x == (size - 1))    // if the spin lies in size-1 row
        	{
            	hi = J * tab[forw[x]][y] + tab[x][forw[y]] + tab[back[x]][y] + tab[x][back[y]];
        	}
        	else
        	{
            	hi = tab[forw[x]][y] + tab[x][forw[y]] + tab[back[x]][y] + tab[x][back[y]];
        	}

            index = (hi + 4.0001)*((double) n)/2.0;

        	if(rand_num <= 1/(1+my_exp[index]))
        	{
            	tab[x][y] = 1;
        	}
            else
            {
                tab[x][y] = -1;
            }
        }
        else    // voter dynamics
        {
            z = rand() % 4;

            if((x == 0)&&(z == 1))  // if spin lies in 0th row and neighbour lies through the upper boundary
            {
                if(rand_num <= p)
        		{
            		tab[x][y] = tab[size - 1][y];
        		}
        		else
        		{
            		tab[x][y] = -tab[size - 1][y];
        		}
            }
            else if((x == (size - 1))&&(z == 3))    // if spin lies in (size - 1)th row and neighbour lies through the lower boundary
            {
                if(rand_num <= p)
        		{
            		tab[x][y] = tab[0][y];
        		}
        		else
        		{
            		tab[x][y] = -tab[0][y];
        		}
            }
            else
            {
                switch(z)
        		{
            		case 0: // neighbour from the right
                			tab[x][y] = tab[x][forw[y]];
                			break;
            		case 1: // neighbour from the top
                			tab[x][y] = tab[back[x]][y];
                			break;
            		case 2: // neighbour from the left
                			tab[x][y] = tab[x][back[y]];
                			break;
            		case 3: // neighbour from the bottom
                			tab[x][y] = tab[forw[x]][y];
                			break;
        		}
    		}
        }
    }
}

int main(int argc, char *argv[])
{
    // Reading program parameters

    if(argc == 5)
    {
        size = atoi(argv[1]);
        n = atoi(argv[2]);
        P = atof(argv[3]);
    }
    else
    {
        printf("Incorrect number of parameters!");
    }

    // Creating variables and initialization

    double A;   // variable for calculating energy change
    double direction;   // direction = 1.0 if forward, direction = -1.0 if reverse
    int g, h, i, iter, j, k, l; // variables to iterate loops
    int sum;    // temporary variable
    double random_num;  // random number
    unsigned int number_of_exp; // number of experiments for single configuration of spin types
    unsigned int number_of_config;  // number of different configurations of spin types
    unsigned int eqsteps = 100000;  // number of steps (per spin) to equilibrate the system
    double beta = 1.0;  // inverse of temperature
    double** lambda_heatbath = (double**) malloc(2 * sizeof(double*));  // table of control parameters for heat-bath
    double** lambda_voter = (double**) malloc(2 * sizeof(double*)); // table of control parameters for voter
    for(i = 0; i < 2; i++)
    {
        lambda_heatbath[i] = (double*) malloc(n * sizeof(double));
        lambda_voter[i] = (double*) malloc(n * sizeof(double));
    }
    int** lattice = (int**) malloc(size * sizeof(int*));    // main 2D lattice from which initial configurations are taken
    int** ilattice = (int**) malloc(size * sizeof(int*));   // temporary 2D lattice for experiments
    int** types = (int**) malloc(size * sizeof(int*));  // lattice of spin types: 0 = heat-bath, 1 = voter
    for(i = 0; i < size; i++)
    {
        lattice[i] = (int*) malloc(size * sizeof(int));
        ilattice[i] = (int*) malloc(size * sizeof(int));
        types[i] = (int*) malloc(size * sizeof(int));
    }
    forw = (int*) malloc(size * sizeof(int));
    back = (int*) malloc(size * sizeof(int));
    for(i = 0; i < size; i++)
    {
        forw[i] = i + 1;
        back[i] = i - 1;
    }
    forw[size - 1] = 0;
    back[0] = size - 1;

    if((P > 0.99)||(P < 0.01))
    {
        number_of_exp = 10000000;
        number_of_config = 1;
    }
    else
    {
        number_of_exp = 100000;
        number_of_config = 100;
    }

    my_exp = (double*) malloc((4*n + 1) * sizeof(double));
    for(i = 0; i < (4*n + 1); i++)
    {
        my_exp[i] = exp(-2.0 * (-4.0 + (2.0*((double) i))/((double) n)) * beta);
    }

    for(i = 0; i < n; i++)
    {
        lambda_heatbath[0][i] = 1.0 - (2.0 * i)/((double) n);
        lambda_heatbath[1][i] = -1.0 + (2.0 * i)/((double) n);
        lambda_voter[0][i] = 1.0 - ((double) i)/((double) n);
        lambda_voter[1][i] = ((double) i)/((double) n);
    }

    // Creating output file
    char fname[50] = "Ising2D_";
    char* prob = argv[3];
    prob[1] = prob[2];
    prob[2] = '\0';
    const char* prob2 = prob;
    strcat(fname, argv[1]);
    strcat(fname, "x");
    strcat(fname, argv[1]);
    strcat(fname, "_n");
    strcat(fname, argv[2]);
    strcat(fname, "_P");
    strcat(fname, prob2);
    strcat(fname, "_");
    strcat(fname, argv[4]);
    strcat(fname, ".txt");
    printf("%s\n", fname);
    FILE* file = fopen(fname,"w");  // file to write results of experiments

    srand(time(NULL));

    // Loop over initial spin types configurations
    for(h = 0; h < number_of_config; h++)
    {
        // Draw of spin types: 0 = heat-bath, 1 = voter
        for(i = 0; i < size; i++)
        {
            for(j = 0; j < size; j++)
            {
                random_num = ((double) rand())/((double) RAND_MAX + 1.0); // random real number in range [0,1)
                if(random_num < P)
                {
                    types[i][j] = 0;
                }
                else
                {
                    types[i][j] = 1;
                }
            }
        }

        // Set forward direction
        direction = 1.0;

        // Loop for processes (forward = 0, reverse = 1)
        for(g = 0; g < 2; g++)
        {
            // change direction for reverse processes
            if(g == 1)
            {
                direction = -1.0;
            }

            // Filling lattice with random spins
            for(i = 0; i < size; i++)
            {
                for(j = 0; j < size; j++)
                {
                    lattice[i][j] = 2 * (rand() % 2) - 1; // random number -1 or +1
                }
            }

            // Equilibration
            Dynamics(lattice, types, lambda_heatbath[g][0], lambda_voter[g][0], eqsteps*size*size);

            // Nonequilibrium experiments
            for(i = 0; i < number_of_exp; i++)
            {
                sum = 0;

                // 100 steps of algorithm
                Dynamics(lattice, types, lambda_heatbath[g][0], lambda_voter[g][0], 100);

                // Initial lattice configuration save
                for(k = 0; k < size; k++)
                {
                    for(l = 0; l < size; l++)
                    {
                        ilattice[k][l] = lattice[k][l];
                    }
                }

                // First energy change calculation
                for(j = 0; j < size; j++)
                {
                    sum = sum + ilattice[0][j] * ilattice[size - 1][j];
                }

                for(iter = 1; iter < n; iter++)
                {
                    // Thermalization - algorithm with control parameter
                    Dynamics(ilattice, types, lambda_heatbath[g][iter], lambda_voter[g][iter], size*size);

                    // Energy change calculation
                    for(j = 0; j < size; j++)
                    {
                        sum = sum + ilattice[0][j] * ilattice[size - 1][j];
                    }
                }

                A = ((double) sum * direction * 2.0)/((double) n);

                // change of sign for reverse procesess; we need P(-A) for them
                A = A * direction;

                // Printing results
                fprintf(file, "%f\n", A);
            }
        }
    }


    // 5. Freeing memory and closing files
    for(i = (size-1); i >= 0; i--)
    {
        free(lattice[i]);
        free(ilattice[i]);
        free(types[i]);
    }
    for(i = 1; i >= 0; i--)
    {
        free(lambda_heatbath[i]);
        free(lambda_voter[i]);
    }
    free(lambda_heatbath);
    free(lambda_voter);
    free(my_exp);
    free(lattice);
    free(ilattice);
    free(types);
    free(forw);
    free(back);

    fclose(file);

    return 0;
}
