#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Global variables
unsigned int size;  // length of one side of the lattice
double P;   // probability of Ising-type spin on lattice

// Functions

// Calculate x-coordinate of minimum of function in 'tab' with size 's'
int f_min(double* tab, unsigned int s)
{
    static int i, xmin;
    static double ymin;
    xmin = -1;
    ymin = 1e9;
    for(i = 0; i < s; i++)
    {
        if(tab[i] < ymin)
        {
            ymin = tab[i];
            xmin = i;
        }
    }
    return xmin;
}

int main(int argc, char *argv[])
{
    // Reading program parameters

    if(argc == 3)
    {
        size = atoi(argv[1]);
        P = atof(argv[2]);
    }
    else
    {
        printf("Incorrect number of parameters!");
    }

    // Creating variables and initialization

    double a = -20.0 * (size/8);   // min x-coordinate of histogram
    double b = -a;   // max x-coordinate of histogram
    char c_P[4];    // probability of occurence Ising-type spins; for example, if P = 1.0, c_P = "10", or if P = 0.7, c_P = "07"
    sprintf(c_P,"%f",P);
    c_P[1] = c_P[2];
    c_P[2] = '\0';
    unsigned int number_of_n = 6; // number of different n
    unsigned int number_of_files; // number of files with results for single n
    unsigned int number_of_experiments; // number of experiments for single configuration
    unsigned int number_of_config;  // number of initial configurations
    if((P > 0.99)||(P < 0.01))
    {
        number_of_experiments = 10000000;
        number_of_config = 1;
        number_of_files = 1;
    }
    else
    {
        number_of_experiments = 100000;
        number_of_config = 100;
        number_of_files = 10;
    }
    int f, g, i, j, k, l, m;    // variables to iterate loops
    double beta_eff1, beta_eff2;
    int intersections[6];  // number of intersections of histograms
    double direction;   // direction = 1.0 if forward, direction = -1.0 if reverse
    double A;   // variable to read A from experiments
    int index; // index of bin in histogram
    unsigned int beta_range = 300;  // range of beta
    double beta_step = 0.01;    // step of beta
    double beta_tmp;    // temporary variable
    const unsigned int n[6] = {5, 10, 20, 50, 100, 200};  // number of nonequilibrium steps in experiment
    unsigned int number_of_bins[6]; // number of bins in histogram
    double* beta = (double*) malloc(beta_range * sizeof(double));   // inverse of temperature
    double* dF = (double*) malloc(beta_range * sizeof(double));
    double* diff = (double*) malloc(beta_range * sizeof(double));   // temporary variable
    double*** sum_of_exp = (double***) malloc(number_of_n * sizeof(double**));    // temporary variable
    double*** F_j = (double***) malloc(number_of_n * sizeof(double**));   // free energy from Jarzynski method
    double F_c[6];  // free energy from Crooks method
    double** x = (double**) malloc(number_of_n * sizeof(double*));    // table with x-coordinates of histograms
    int** dh = (int**) malloc(number_of_n * sizeof(int*));    // table with differences in histograms to calculate crooks results
    int*** h = (int***) malloc(number_of_n * sizeof(int**));  // table with y-coordinates of histograms
    // default bin_width[6] = {0.8, 0.4, 0.2, 0.08, 0.04, 0.02}
    const double bin_width[6] = {0.8, 0.4, 0.2, 0.08, 0.04, 0.02};    // width of single bin

    for(i = 0; i < number_of_n; i++)
    {
        number_of_bins[i] = (b-a)/bin_width[i];
        x[i] = (double*) malloc(number_of_bins[i] * sizeof(double));
        dh[i] = (int*) malloc(number_of_bins[i] * sizeof(int));
        h[i] = (int**) malloc(2 * sizeof(int*));
        sum_of_exp[i] = (double**) malloc(2 * sizeof(double*));
        F_j[i] = (double**) malloc(2 * sizeof(double*));
        for(j = 0; j < 2; j++)
        {
            h[i][j] = (int*) malloc(number_of_bins[i] * sizeof(int));
            sum_of_exp[i][j] = (double*) malloc(beta_range * sizeof(double));
            F_j[i][j] = (double*) malloc(beta_range * sizeof(double));
            for(k = 0; k < number_of_bins[i]; k++)
            {
                h[i][j][k] = 0;
            }
            for(k = 0; k < beta_range; k++)
            {
                sum_of_exp[i][j][k] = 0.0;
            }
        }
    }

    for(i = 0; i < beta_range; i++)
    {
        beta[i] = beta_step * (1 + i);
    }

    // files
    char fname1[50] = "Ising2D_";
    char fname2[50] = "Hist_x_";
    char fname3[50] = "Hist_y_";
    char fname4[50] = "Tension_";
    char fname5[50] = "Beta_eff_";
    char fname6[50] = "Console_";
    char fname7[50] = "Beta_plot_";
    char fname[50];
    char fname_end[50];
    char buffer[50];

    sprintf(buffer,"%d", size);
    strcpy(fname_end, buffer);
    strcat(fname_end, "x");
    strcat(fname_end, buffer);
    strcat(fname_end, "_P");
    strcat(fname_end, c_P);
    strcat(fname_end, ".txt");
    strcat(fname2, fname_end);
    strcat(fname3, fname_end);
    strcat(fname4, fname_end);
    strcat(fname5, fname_end);
    strcat(fname6, fname_end);
    strcat(fname7, fname_end);
    printf("%s\n", fname2);
    printf("%s\n", fname3);
    printf("%s\n", fname4);
    printf("%s\n", fname5);
    printf("%s\n", fname6);
    printf("%s\n", fname7);

    FILE* in;   // file with input data of work in experiments
    FILE* hist_y;   // file to write y coordinates of histograms
    FILE* tension;  // file to write results of interface tension
    FILE* beta_eff; // file to write results of effective beta for Jarzynski method
    FILE* console; // file to write console informations
    FILE* beta_plot; // file to write effective beta plots
    FILE* hist_x = fopen(fname2, "w");  // file to write x coordinates of histograms

    printf("a = %f\n",a);

    // calculating x-coordinates of histograms
    for(i = 0; i < number_of_n; i++)
    {
        printf("bin_width[i] = %f\n", bin_width[i]);
        for(j = 0; j < number_of_bins[i]; j++)
        {
            x[i][j] = a + bin_width[i] * ((double) j);
            fprintf(hist_x, "%f\n", x[i][j]);
        }
    }
    fclose(hist_x);
    console = fopen(fname6, "w");
    fprintf(console, "Number of bins\n");

    for(i = 0; i < number_of_n; i++)
    {
        fprintf(console, "%d\t%d\n", n[i], number_of_bins[i]);
    }

    // Main loop for reading input data for different n
    for(i = 0; i < number_of_n; i++)
    {
        // Loop for nn files
        for(j = 0; j < number_of_files; j++)
        {
            // creating input file name
            sprintf(buffer,"%d", size);
            strcpy(fname_end, buffer);
            strcat(fname_end, "x");
            strcat(fname_end, buffer);
            strcat(fname_end, "_n");
            sprintf(buffer,"%d", n[i]);
            strcat(fname_end, buffer);
            strcat(fname_end, "_P");
            strcat(fname_end, c_P);
            strcat(fname_end, "_");
            sprintf(buffer,"%d", j+1);
            strcat(fname_end, buffer);
            strcat(fname_end, ".txt");
            strcpy(fname, fname1);
            strcat(fname, fname_end);
            in = fopen(fname,"r");
            printf("%s\n",fname);

            // Loop for initial configurations
            for(f = 0; f < number_of_config; f++)
            {
                direction = 1.0;

                // Loop for forward and reverse processes
                for(g = 0; g < 2; g++)
                {
                    // change direction for reverse processes
                    if(g == 1)
                    {
                        direction = -1.0;
                    }

                    // Loop for reading data and making histograms
                    for(l = 0; l < number_of_experiments; l++)
                    {
                        // read single experiment result
                        fscanf(in, "%lf", &A);

                        // sum of exponent for Jarzynski results for different beta
                        for(k = 0; k < beta_range; k++)
                        {
                            sum_of_exp[i][g][k] = sum_of_exp[i][g][k] + exp(-beta[k] * A * direction);
                        }

                        // change A range to [0, number_of_bins]
                        A = (A + 0.0001 - a)/bin_width[i];

                        // calculate index of bin which corresponds to result of experiment
                        index = A;

                        if((index < 0) || (index >= number_of_bins[i]))
                        {
                            fprintf(console, "Index exceeded range of histogram (%d)! Change range for n = %d.\n", index, n[i]);
                        }
                        else
                        {
                            // increment appropriate histogram bar
                            h[i][g][index] = h[i][g][index] + 1;
                        }
                    }
                }
            }
            // closing input file
            fclose(in);
        }
    }

    // Data processing - calculating free energy, interface tension and beta effective
    hist_y = fopen(fname3, "w");
    beta_plot = fopen(fname7, "w");

    // Loop for different n
    for(i = 0; i < number_of_n; i++)
    {
        // Loop for writing histograms and calculating free energy from Jarzynski equation
        direction = 1.0;
        for(g = 0; g < 2; g++)
        {
            if(g == 1)
            {
                direction = -1.0;
            }

            // save histograms to file
            for(j = 0; j < number_of_bins[i]; j++)
            {
                fprintf(hist_y, "%f\n", ((double) h[i][g][j])/((double) number_of_files * number_of_experiments * number_of_config * bin_width[i]));
            }

            // calculate Jarzynski results
            for(k = 0; k < beta_range; k++)
            {
                F_j[i][g][k] = (-direction/beta[k])*log(sum_of_exp[i][g][k]/((double) number_of_files * number_of_experiments * number_of_config));
                fprintf(beta_plot, "%f\n", F_j[i][g][k]);
            }
        }
    }
    fclose(beta_plot);
    fclose(hist_y);

    tension = fopen(fname4, "w");
    beta_eff = fopen(fname5, "w");

    fprintf(tension, "Estimation of surface tension from Crooks and Jarzynski results (beta = 1.0).\n");
    fprintf(tension, "%d", size);
    fprintf(tension, "x");
    fprintf(tension, "%d", size);
    fprintf(tension, ", P = ");
    fprintf(tension, "%f", P);
    fprintf(tension, "\n");
    fprintf(tension, "n\tCrooks\t\tJarzynski_forw\tJarzynski_rev\n");

    fprintf(beta_eff, "Estimation of effective beta from Crooks and Jarzynski results (real beta = 1.0).\n");
    fprintf(beta_eff, "%d", size);
    fprintf(beta_eff, "x");
    fprintf(beta_eff, "%d", size);
    fprintf(beta_eff, ", P = ");
    fprintf(beta_eff, "%f", P);
    fprintf(beta_eff, "\n");
    fprintf(beta_eff, "n\tJarzynski_forw\tJarzynski_rev\tJarzynski_both\n");

    fprintf(console, "Free energy estimations from Crooks method\n");

    for(i = 0; i < number_of_n; i++)
    {
        // automatic calculation of Crooks results
        intersections[i] = 0;
        dh[i][0] = h[i][0][0] - h[i][1][0];
        dh[i][1] = h[i][0][1] - h[i][1][1];

        for(j = 1; j < (number_of_bins[i] - 1); j++)
        {
            dh[i][j+1] = h[i][0][j+1] - h[i][1][j+1];

            // searching for intersection
            if(((dh[i][j] > 0)&&(dh[i][j+1] < 0))||((dh[i][j] < 0)&&(dh[i][j+1] > 0)))
            {
                // interpolation of free energy
                intersections[i] = intersections[i] + 1;
                F_c[i] = x[i][j] + (bin_width[i] * ((double) abs(dh[i][j])))/((double) (abs(dh[i][j+1]) + abs(dh[i][j])));
            }
            else if(((dh[i][j-1] < 0)&&(dh[i][j] == 0)&&(dh[i][j+1] > 0))||((dh[i][j-1] > 0)&&(dh[i][j] == 0)&&(dh[i][j+1] < 0)))
            {
                intersections[i] = intersections[i] + 1;
                F_c[i] = x[i][j];
            }
        }
    }

    for(i = 0; i < number_of_n; i++)
    {
        if(intersections[i] > 1)
        {
            fprintf(console, "Multiple intersections (%d) for n = %d. Increase of bin_width is needed.\n", intersections[i], n[i]);
            fprintf(tension, "%d\tNot available\t%f\t%f\n", n[i], F_j[i][0][99]/size, F_j[i][1][99]/size);

            //Calculate beta effective from Jarzynski forw and rev method
            for(j = 0; j < beta_range; j++)
            {
                diff[j] = fabs(F_j[i][0][j] - F_j[i][1][j]);
            }
            beta_tmp = ((double)(1.0 + f_min(diff, beta_range)))*beta_step;
            fprintf(beta_eff, "%d\tNot available\tNot available\t%f\n", n[i], beta_tmp);
        }
        else if(intersections[i] == 1)
        {
            // saving interface tensions results
            fprintf(console, "%d\t%f\n", n[i], F_c[i]);
            fprintf(tension, "%d\t%f\t%f\t%f\n", n[i], F_c[i]/size, F_j[i][0][99]/size, F_j[i][1][99]/size);

            // calculate beta_effective
            // 1st method - Jarzynski forw and Crooks
            for(j = 0; j < beta_range; j++)
            {
                diff[j] = fabs(F_j[i][0][j] - F_c[i]);
            }
            beta_tmp = ((double)(1 + f_min(diff, beta_range)))*beta_step;
            fprintf(beta_eff, "%d\t%f\t", n[i], beta_tmp);

            // 2nd method - Jarzynski rev and Crooks
            for(j = 0; j < beta_range; j++)
            {
                diff[j] = fabs(F_j[i][1][j] - F_c[i]);
            }
            beta_tmp = ((double)(1 + f_min(diff, beta_range)))*beta_step;
            fprintf(beta_eff, "%f\t", beta_tmp);

            // 3rd method - Jarzynski forw and rev
            for(j = 0; j < beta_range; j++)
            {
                diff[j] = fabs(F_j[i][0][j] - F_j[i][1][j]);
            }
            beta_tmp = ((double)(1 + f_min(diff, beta_range)))*beta_step;
            fprintf(beta_eff, "%f\n", beta_tmp);
        }
        else
        {
            fprintf(console, "No intersection for n = %d.\n", n[i]);
            fprintf(tension, "%d\tNot available\t%f\t%f\n", n[i], F_j[i][0][99]/size, F_j[i][1][99]/size);

            //Calculate beta effective from Jarzynski forw and rev method
            for(j = 0; j < beta_range; j++)
            {
                diff[j] = fabs(F_j[i][0][j] - F_j[i][1][j]);
            }
            beta_tmp = ((double)(1.0 + f_min(diff, beta_range)))*beta_step;
            fprintf(beta_eff, "%d\tNot available\tNot available\t%f\n", n[i], beta_tmp);
        }
    }

    // New methods of effective beta estimations
    fprintf(beta_eff, "New methods of estimation\n");
    fprintf(beta_eff, "two-plots\n");

    //intersections[0] = 0;
    dF[0] = F_j[number_of_n-1][1][0] - F_j[number_of_n-2][1][0];
    dF[1] = F_j[number_of_n-1][1][1] - F_j[number_of_n-2][1][1];

    for(i = 1; i < (beta_range - 1); i++)
    {
        dF[i+1] = F_j[number_of_n-1][1][i+1] - F_j[number_of_n-2][1][i+1];

        // searching for intersection
        if(((dF[i] > 0)&&(dF[i+1] < 0))||((dF[i] < 0)&&(dF[i+1] > 0)))
        {
            // interpolation of free energy
            //intersections[0] = intersections[0] + 1;
            beta_eff1 = beta[i] + (beta_step * fabs(dF[i]))/(fabs(dF[i+1]) + fabs(dF[i]));
            fprintf(beta_eff, "%f\n", beta_eff1);
        }
        else if(((dF[i-1] < 0)&&(dF[i] == 0)&&(dF[i+1] > 0))||((dF[i-1] > 0)&&(dF[i] == 0)&&(dF[i+1] < 0)))
        {
            //intersections[0] = intersections[0] + 1;
            beta_eff1 = beta[i];
            fprintf(beta_eff, "%f\n", beta_eff1);
        }
    }

    fprintf(beta_eff, "three-plots\n");
    for(i = 0; i < beta_range; i++)
    {
        dF[i] = (F_j[number_of_n-1][1][i] - F_j[number_of_n-2][1][i])*(F_j[number_of_n-1][1][i] - F_j[number_of_n-2][1][i])
        + (F_j[number_of_n-1][1][i] - F_j[number_of_n-3][1][i])*(F_j[number_of_n-1][1][i] - F_j[number_of_n-3][1][i])
        + (F_j[number_of_n-3][1][i] - F_j[number_of_n-2][1][i])*(F_j[number_of_n-3][1][i] - F_j[number_of_n-2][1][i]);
    }
    beta_eff2 = ((double)(1.0 + f_min(dF, beta_range)))*beta_step;
    fprintf(beta_eff, "%f\n", beta_eff2);

    // freeing memory and closing files
    for(i = (number_of_n-1); i >= 0; i--)
    {
        free(x[i]);
        free(dh[i]);
        for (j = 1; j >= 0; j--)
        {
            free(h[i][j]);
            free(sum_of_exp[i][j]);
            free(F_j[i][j]);
        }
        free(h[i]);
        free(sum_of_exp[i]);
        free(F_j[i]);
    }

    free(x);
    free(h);
    free(dh);
    free(beta);
    free(dF);
    free(diff);
    free(sum_of_exp);
    free(F_j);

    fclose(tension);
    fclose(beta_eff);
    fclose(console);

    return 0;
}
