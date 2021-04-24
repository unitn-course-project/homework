#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

double get_input(int *n )
{
    printf("Please give a number : ");
    scanf("%d", n);
}
int main(void)
{
    int my_rank;
    int comm_sz;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int n;
    if (my_rank == 0)
    {
        get_input(&n);
    }
    if (my_rank == 0)
        MPI_Send(&n, 1, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD);
    if (my_rank < comm_sz - 1)
    {
        MPI_Recv(&n, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&n, 1, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&n, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    printf("process %d, the data is %d \n",my_rank,n);
    MPI_Finalize();
    return 0;
}