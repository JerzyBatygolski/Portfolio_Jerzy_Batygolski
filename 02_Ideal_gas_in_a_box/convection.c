#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

struct Particle{
    double x;
    double y;
    double vx;
    double vy;
    double col_time;
    int partner;
};

const unsigned int N = 10000; // number of particles in big box
const double size_x = 100.0; // width of big box
const double size_y = 100.0; // height of big box
unsigned int number_of_columns; // number of columns for histogram
unsigned int number_of_rows; // number of rows for histogram
const unsigned int number_of_histograms = 3; // number of histograms
const double big_number = 1.0e+10; // very big number
const double eps = 1.0e-10; // very small number
const double g = 9.80665; // gravity acceleration
const double diameter = sqrt(0.4); // diameter of a single particle
const double mass = 1.0; // mass of a single particle
const double T0 = 273.0; // initial temperature of gas
double dQ; // amount of heat transferred through the bottom wall
double** cdf; // cumulation distribution function for Maxwell-Boltzmann distribution
double*** hist_tab; // table for histograms
unsigned int** count; // table for number density of particles
unsigned int T_star; // input parameter of heating in range [1,25] (integer)

void draw_pos(struct Particle* p) // draw position of particle p in range
{
    p->x = (size_x - diameter) * ((double) rand() + 1.0)/((double) RAND_MAX + 2.0) - (size_x/2.0 - diameter/2.0); // random x-position in range (-size_x/2, size_x/2) +-diameter/2
    p->y = (size_y - diameter) * ((double) rand() + 1.0)/((double) RAND_MAX + 2.0) - (size_y/2.0 - diameter/2.0); // random y-position in range (-size_y/2, size_y/2) +-diameter/2
}

void draw_vel(struct Particle* p, double T) // draw velocity with magnitude sqrt(3T)
{
    static double angle;
    angle = 2 * M_PI * ((double) rand())/((double) RAND_MAX + 1.0) - M_PI; // random angle in range [-pi, pi)
    p->vx = sqrt(3.0 * T) * cos(angle);
    p->vy = sqrt(3.0 * T) * sin(angle);
}

void save_hist_to_file(struct Particle* p, FILE* hist_file, char* fname)
{
    static int i, j, k, index_x, index_y;
    static double v;

    // Reset of variables
    for(i = 0; i < number_of_histograms; i++)
    {
        for(j = 0; j < number_of_columns; j++)
        {
            for(k = 0; k < number_of_rows; k++)
            {
                hist_tab[i][j][k] = 0.0;
            }
        }
    }
    for(i = 0; i < number_of_columns; i++)
    {
        for(j = 0; j < number_of_rows; j++)
        {
            count[i][j] = 0;
        }
    }

    // Data calculations
    for(i = 0; i < N; i++)
    {
        index_x = (p[i].x + size_x/2.0) * ((double) number_of_columns) / size_x;
        index_y = (p[i].y + size_y/2.0) * ((double) number_of_rows) / size_y;
        count[index_x][index_y]++;
        hist_tab[0][index_x][index_y] += p[i].vx;
        hist_tab[1][index_x][index_y] += p[i].vy;
        hist_tab[2][index_x][index_y] += mass * ((p[i].vx * p[i].vx) + (p[i].vy * p[i].vy)) / 2.0 + mass * g * (p[i].y + size_y/2.0); // U
    }

    for(i = 0; i < number_of_columns; i++)
    {
        for(j = 0; j < number_of_rows; j++)
        {
            hist_tab[0][i][j] /= ((double) count[i][j]);
            hist_tab[1][i][j] /= ((double) count[i][j]);
            hist_tab[2][i][j] /= ((double) count[i][j]);
            v = sqrt((hist_tab[0][i][j])*(hist_tab[0][i][j]) + (hist_tab[1][i][j])*(hist_tab[1][i][j]));
            hist_tab[0][i][j] *= 5.0/v; // the best histograms are when vector magnitude is half of the bin width, e.g. for size_x = 100, num_of_col = 20, magnitude should be 2.5
            hist_tab[1][i][j] *= 5.0/v;
        }
    }

    // save data to file
    hist_file = fopen(fname, "w");
    for(i = 0; i <= number_of_histograms; i++)
    {
        for(j = number_of_rows - 1; j >= 0; j--)
        {
            for(k = 0; k < number_of_columns; k++)
            {
                if(i == number_of_histograms)
                    fprintf(hist_file, "%d\t", count[k][j]);
                else
                    fprintf(hist_file, "%f\t", hist_tab[i][k][j]);
            }
            fprintf(hist_file, "\n");
        }
    }
    fclose(hist_file);
}

void search_collision_with_walls(struct Particle* p)
{
    static double tij, t1, t2, a, b, c, delta;

    if(p->vx > 0) // collision with right wall possible
    {
        tij = ((size_x - diameter) / 2.0 - p->x) / p->vx;
        if(tij < p->col_time)
        {
            p->col_time = tij;
            p->partner = -4;
        }
    }
    else if(p->vx < 0) // collision with left wall possible
    {
        tij = ((-size_x + diameter)/ 2.0 - p->x) / p->vx;
        if(tij < p->col_time)
        {
            p->col_time = tij;
            p->partner = -3;
        }
    }

    // collision with top wall
    a = -g / 2.0;
    b = p->vy;
    c = p->y - (size_y - diameter)/ 2.0;
    delta = b*b - 4*a*c;
    if(delta >= 0)
    {
        t1 = (-b + sqrt(delta))/(2*a);
        t2 = (-b - sqrt(delta))/(2*a);
        if((t1 >= 0)||(t2 >= 0))
        {
            if((t1 >= 0)&&(t2 >= 0))
            {
                if(t1 <= t2)
                    tij = t1;
                else
                    tij = t2;
            }
            else if(t1 >= 0)
                tij = t1;
            else
                tij = t2;

            if(tij < p->col_time)
            {
                p->col_time = tij;
                p->partner = -5;
            }
        }
    }

    // collision with bottom wall
    c = p->y + ((size_y - diameter) / 2.0);
    delta = b*b - 4*a*c;
    if(delta >= 0)
    {
        t1 = (-b + sqrt(delta))/(2*a);
        t2 = (-b - sqrt(delta))/(2*a);
        if((t1 >= 0)||(t2 >= 0))
        {
            if((t1 >= 0)&&(t2 >= 0))
            {
                if(t1 <= t2)
                    tij = t1;
                else
                    tij = t2;
            }
            else if(t1 >= 0)
                tij = t1;
            else
                tij = t2;

            if(tij < p->col_time)
            {
                p->col_time = tij;
                p->partner = -2;
            }
        }
    }
}

void check_collision_of_particles(struct Particle* pi, struct Particle* pj, int i, int j)
{
    static double rxij, ryij, vxij, vyij, bij, rijsq, vijsq, delta, tij;

    rxij = pi->x - pj->x;
    ryij = pi->y - pj->y;
    vxij = pi->vx - pj->vx;
    vyij = pi->vy - pj->vy;
    bij = rxij*vxij + ryij*vyij;

    if(bij < 0) // particles are approaching each other
    {
        rijsq = rxij*rxij + ryij*ryij;
        vijsq = vxij*vxij + vyij*vyij;
        delta = bij*bij - vijsq*(rijsq - diameter*diameter);

        if(delta >= 0) // particles i and j will collide
        {
            tij = (-bij - sqrt(delta)) / vijsq;
            if(tij < pi->col_time)
            {
                pi->col_time = tij;
                pi->partner = j;
            }
            if(tij < pj->col_time)
            {
                pj->col_time = tij;
                pj->partner = i;
            }
        }
    }
}

void collision_of_particles(struct Particle* pi, struct Particle* pj)
{
    static double deltavx, deltavy, rxij, ryij, vxij, vyij, bij;
    deltavx = 0;
    deltavy = 0;
    rxij = pi->x - pj->x;
    ryij = pi->y - pj->y;
    vxij = pi->vx - pj->vx;
    vyij = pi->vy - pj->vy;
    bij = rxij*vxij + ryij*vyij;
    deltavx = -bij / (diameter*diameter) * rxij;
    deltavy = -bij / (diameter*diameter) * ryij;
    pi->vx += deltavx;
    pi->vy += deltavy;
    pj->vx -= deltavx;
    pj->vy -= deltavy;
}

void collision_with_bottom_wall(struct Particle* p, double T)
{
    static double rand_num, v, angle, U1, U2;
    static int i, j, iT;
    rand_num = ((double) rand() + 1.0)/((double) RAND_MAX + 2.0); // random number in range (0,1)
    U1 = mass * ((p->vx)*(p->vx) + (p->vy)*(p->vy)) / 2.0;
    if(T > T0)
        iT = 1;
    else
        iT = 0;
    for(i = 1; i < 90000; i++)
    {
        if((cdf[iT][i-1] <= rand_num)&&(cdf[iT][i] >= rand_num))
        {
            j = i;
            break;
        }
    }
    v = 0.005 * (1 + j);
    angle = M_PI * ((double) rand() + 1.0)/((double) RAND_MAX + 2.0); // random angle in range (0,pi)
    p->vx = v * cos(angle);
    p->vy = v * sin(angle);
    p->y += eps;
    U2 = mass * ((p->vx)*(p->vx) + (p->vy)*(p->vy)) / 2.0;
    dQ += (U2 - U1);
}

void collision_with_top_wall(struct Particle* p, double T)
{
    static double rand_num, v, angle;
    static int i, j, iT;
    rand_num = ((double) rand() + 1.0)/((double) RAND_MAX + 2.0); // random number in range (0,1)
    if(T > T0)
        iT = 1;
    else
        iT = 0;
    for(i = 1; i < 90000; i++)
    {
        if((cdf[iT][i-1] <= rand_num)&&(cdf[iT][i] >= rand_num))
        {
            j = i;
            break;
        }
    }
    v = 0.005 * (1 + j);
    angle = (((double) rand() + 1.0)/((double) RAND_MAX + 2.0) - 1.0) * M_PI; // random angle in range (-pi,0)
    p->vx = v * cos(angle);
    p->vy = v * sin(angle);
    p->y -= eps;
}

double calculate_internal_energy(struct Particle* p)
{
    static int i;
    static double U;
    U = 0.0;
    for(i = 0; i < N; i++)
    {
        U += mass * ((p[i].vx * p[i].vx) + (p[i].vy * p[i].vy)) / 2.0 + mass * g * (p[i].y + size_y/2);
    }
    return U;
}

int main(int argc, char *argv[])
{
    // 1. Initialization
    printf("Initialization...\n");

    if(argc == 4)
    {
        T_star = atoi(argv[1]);
        number_of_columns = atoi(argv[2]);
        number_of_rows = atoi(argv[3]);
    }
    else
    {
        printf("Incorrect number of parameters!");
    }

    // parameters of simulation
    unsigned int number_of_collisions; // number of collisions in simulation
    const double T_top = T0; // temperature of the top wall
    double T_bottom = T0; // temperature of the bottom wall
    double U_init, U, U0, U1, U2, U_sum, deltaU, deltaU1, deltaU2; // internal energies of gas
    double J, Q; // heat flux into the system [joules per second]
    double t; // time of simulation
    double dt;
    const double time_conv = 1000.0;
    const double time_end = 1500.0; // whole simulation time

    // auxiliary variables
    int i, j, k, l, m; // variables for loops iterations
    unsigned int aver_count;
    double dist_sq, dx, dy;
    int partneri, partnerj;
    double tij;
    double Ttemp, vtemp;
    double t_old;
    char c_T_star[3];
    char c_col[3];
    char c_row[3];
    sprintf(c_T_star, "%d", T_star);
    sprintf(c_col, "%d", number_of_columns);
    sprintf(c_row, "%d", number_of_rows);

    // table of particles
    struct Particle* Particles = (struct Particle*) malloc(N * sizeof(struct Particle));

    // tables for histograms - vx, vy, angle, T
    hist_tab = (double***) malloc(number_of_histograms * sizeof(double**));
    for(i = 0; i < number_of_histograms; i++)
    {
        hist_tab[i] = (double**) malloc(number_of_columns * sizeof(double*));
        for(j = 0; j < number_of_columns; j++)
        {
            hist_tab[i][j] = (double*) malloc(number_of_rows * sizeof(double));
        }
    }
    count = (unsigned int**) malloc(number_of_columns * sizeof(unsigned int*));
    for(i = 0; i < number_of_columns; i++)
    {
        count[i] = (unsigned int*) malloc(number_of_rows * sizeof(unsigned int));
    }

    // cumulation distribution function
    cdf = (double**) malloc(2 * sizeof(double*));
    cdf[0] = (double*) malloc(90000 * sizeof(double));
    cdf[1] = (double*) malloc(90000 * sizeof(double));
    for(i = 0; i < 2; i++)
    {
        if(i == 0)
            Ttemp = T0;
        else
            Ttemp = T0 * T_star;
        for(j = 0; j < 90000; j++)
        {
            vtemp = 0.005 * (1.0 + (double) j);
            cdf[i][j] = erf(vtemp * sqrt(mass / (2.0 * Ttemp))) - sqrt(2.0 * mass / (M_PI * Ttemp)) * vtemp * exp(-mass * vtemp * vtemp / (2.0 * Ttemp));
        }
    }

    // random seed initialization
    srand (time(NULL));

    // drawing of particles positions and velocities
    for(i = 0; i < N; i++)
    {
        draw_pos(&Particles[i]);
        draw_vel(&Particles[i], T0);

        // if particles overlap
        for(j = 0; j < i; j++)
        {
            dx = Particles[i].x - Particles[j].x;
            dy = Particles[i].y - Particles[j].y;
            dist_sq = dx*dx + dy*dy;
            if(dist_sq < diameter*diameter)
            {
                draw_pos(&Particles[i]);
                j = -1;
            }
        }
    }

    // file variables
    FILE* hist1;
    FILE* hist2;
    FILE* hist3;
    FILE* plots;
    FILE* res;
    char fname1[50] = "hist1_";
    char fname2[50] = "hist2_";
    char fname3[50] = "hist3_";
    char fname4[50] = "plots_";
    char fname5[50] = "res_";

    strcat(fname1, c_T_star);
    strcat(fname1, "_");
    strcat(fname1, c_col);
    strcat(fname1, "_");
    strcat(fname1, c_row);
    strcat(fname1, ".txt");

    strcat(fname2, c_T_star);
    strcat(fname2, "_");
    strcat(fname2, c_col);
    strcat(fname2, "_");
    strcat(fname2, c_row);
    strcat(fname2, ".txt");

    strcat(fname3, c_T_star);
    strcat(fname3, "_");
    strcat(fname3, c_col);
    strcat(fname3, "_");
    strcat(fname3, c_row);
    strcat(fname3, ".txt");

    strcat(fname4, c_T_star);
    strcat(fname4, "_");
    strcat(fname4, c_col);
    strcat(fname4, "_");
    strcat(fname4, c_row);
    strcat(fname4, ".txt");

    strcat(fname5, c_T_star);
    strcat(fname5, "_");
    strcat(fname5, c_col);
    strcat(fname5, "_");
    strcat(fname5, c_row);
    strcat(fname5, ".txt");

    // 2. First collision search

    // collision times initialization
    for(i = 0; i < N; i++)
    {
        Particles[i].col_time = big_number;
        Particles[i].partner = -1;
    }

    for(i = 0; i < N; i++)
    {
        // check for collisions with walls
        search_collision_with_walls(&Particles[i]);

        // check for collisions with other particles
        for(j = i + 1; j < N; j++)
        {
            check_collision_of_particles(&Particles[i], &Particles[j], i, j);
        }
    }

    // 3. Main program

    // reset of variables
    t = 0.0;
    t_old = 0.0;
    dt = 0.0;
    dQ = 0.0;
    J = 0.0;
    Q = 0.0;
    U_sum = 0.0;
    number_of_collisions = 0;
    aver_count = 0;

    plots = fopen(fname4, "w");

    //while(number_of_collisions < 200000)
    while(t < time_end)
    {
        if((number_of_collisions % 10000) == 0)
        {
            U = calculate_internal_energy(Particles);
            dt = t - t_old;
            t_old = t;
            if(number_of_collisions != 0)
                J = dQ / dt;
            fprintf(plots, "%f\t%f\t%f\t%d\n", t, U, J, number_of_collisions);
            if(t >= time_conv)
            {
                Q += dQ;
                U_sum += U;
                aver_count++;
            }
            dQ = 0.0;
        }

        if(number_of_collisions == 60000000)
        {
            // turn heating on
            T_bottom = T0 * T_star;
            U0 = calculate_internal_energy(Particles);
            save_hist_to_file(Particles, hist1, fname1);
        }

        if(number_of_collisions == 800000000)
        {
            save_hist_to_file(Particles, hist2, fname2);
        }

        // a) Search for the first collision
        tij = big_number;
        partneri = -1; // first particle
        partnerj = -1; // second particle
        for(i = 0; i < N; i++)
        {
            if(Particles[i].col_time < tij)
            {
                tij = Particles[i].col_time;
                partneri = i;
            }
        }
        partnerj = Particles[partneri].partner;

        // b) Dynamics of the gas till the collision
        for(i = 0; i < N; i++)
        {
            Particles[i].col_time -= tij;
            if(Particles[i].col_time < 0.0)
                Particles[i].col_time = 0.0;
            Particles[i].x += (Particles[i].vx) * tij;
            Particles[i].y += (Particles[i].vy)*tij - g * tij * tij / 2.0;
            Particles[i].vy -= g * tij;
        }
        t += tij;

        // c) Collision

        if(partnerj == -2) // collision with bottom wall
            collision_with_bottom_wall(&Particles[partneri], T_bottom);
        else if(partnerj == -3) // collision with left wall
        {
            Particles[partneri].vx *= -1.0;
            Particles[partneri].x += eps;
        }
        else if(partnerj == -4) // collision with right wall
        {
            Particles[partneri].vx *= -1.0;
            Particles[partneri].x -= eps;
        }
        else if(partnerj == -5) // collision with top wall
            collision_with_top_wall(&Particles[partneri], T_top);
        else // collision of two particles
            collision_of_particles(&Particles[partneri], &Particles[partnerj]);

        number_of_collisions++;

        // d) Update of collision times
        for(i = 0; i < N; i++)
        {
            if((i == partneri)||(i == partnerj)||(Particles[i].partner == partneri)||((Particles[i].partner == partnerj)&&(partnerj >= 0)))
            {
                Particles[i].col_time = big_number;

                // check for collisions with walls
                search_collision_with_walls(&Particles[i]);

                // sprawdzenie kolizji z innymi czastkami
                for(j = 0; j < N; j++)
                {
                    if(j != i)
                        check_collision_of_particles(&Particles[i], &Particles[j], i, j);
                }
            }
        }
    }
    fclose(plots);

    save_hist_to_file(Particles, hist3, fname3);

    U1 = U_sum / aver_count;
    J = Q / (time_end - time_conv);
    res = fopen(fname5,"w");
    fprintf(res,"%f\n",(U1-U0)/J);
    fclose(res);

    // 4. End of program

    // freeing memory
    for(i = number_of_histograms - 1; i >= 0; i--)
    {
        for(j = number_of_columns - 1; j >= 0; j--)
        {
            free(hist_tab[i][j]);
        }
        free(hist_tab[i]);
    }
    for(i = number_of_columns - 1; i >= 0; i--)
    {
        free(count[i]);
    }
    free(cdf[1]);
    free(cdf[0]);
    free(hist_tab);
    free(count);
    free(Particles);
    free(cdf);

    return 0;
}
