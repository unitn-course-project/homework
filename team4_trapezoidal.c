#include <mpi.h>
#include <stdio.h>
#include <string.h>
//const int MAX_STRING = 100;
const double A=0.0;
const double B=100.0;
double dest_func(double x){
    return x;
}
int main(int argc, char **argv)
{
    //char greeting[MAX_STRING];
    int comm_sz;
    int my_rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    // Get the number of processes
    double h =(A+B)/comm_sz;
    if (my_rank != 0)
    {
        double fx=dest_func(A+my_rank*h);
        MPI_Send(&fx, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        printf("Sending from process %d piece %f\n", my_rank, fx);
    }
    else
    {
        int q;
        double tr_all=0;
        for (q = 1; q < comm_sz; q++)
        {
            double tr_piece=0;
            MPI_Recv(&tr_piece, 1, MPI_DOUBLE, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%f\n", tr_piece);
            tr_all=tr_all+tr_piece;
            printf("Collect from process %d piece %f\n", q, tr_piece);
        }
        printf("Collect all trapezoid areas is %f", tr_all*h);
    }
    MPI_Finalize();
    return 0;
}