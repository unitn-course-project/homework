#include <mpi.h>
#include <stdio.h>
#include <string.h>
const int MAX_STRING = 100;
int main(int argc, char **argv)
{
    //Initialize the MPI environment. The two arguments to MPI Init are not
    // currently used by MPI implementations, but are there in case future
    // implementations might need the arguments.
    char greeting[MAX_STRING];
    int comm_sz;
    int my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    // Get the number of processes
    if (my_rank != 0)
    {
        sprintf(greeting, "Greetins from process %d of %d!", my_rank, comm_sz);
        MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        printf("Greetings from process %d of %d! \n", my_rank, comm_sz);
        int q;
        for (q = 1; q < comm_sz; q++)
        {
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", greeting);
        }
    }
    MPI_Finalize();
    return 0;
}