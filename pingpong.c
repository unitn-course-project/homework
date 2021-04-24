#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

int main(void)
{
    int my_rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    FILE *fptr;
    fptr = fopen("./output/ping_pong/result.csv", "w");
    // select message length
    for (long mess_len = 1; mess_len <= 1048576; mess_len = mess_len * 2)
    {
        char *mess = (char *)malloc(mess_len * sizeof(char));
        // init message with mess_len byte
        if (my_rank == 0)
        {
            for (int i = 0; i < mess_len; i++)
            {
                mess[i] = "a";
            }
        }
        printf("%.*s",,mess);
        //MPI_Bcast(&mess_len, 1, MPI_LONG, 0, MPI_COMM_WORLD);
        // compute time with message length
        if (my_rank == 0)
        {
            double estimated_time = 0;
            for (int i = 0; i < 10; i++)
            {
                double start = MPI_Wtime();
                MPI_Send(mess, mess_len, MPI_CHAR, 1, i, MPI_COMM_WORLD);
                MPI_Recv(mess, mess_len, MPI_CHAR, 1, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                double finish = MPI_Wtime();
                double elapsed_time = finish - start;
                estimated_time += elapsed_time;
            }
            printf("Estimated time %lf\n", estimated_time);
            fprintf(fptr, "%ld, %lf\n", mess_len, estimated_time / 20.0);
        }
        else
        {
            for (int i = 0; i < 10; i++)
            {
                MPI_Recv(mess, mess_len, MPI_CHAR, 0, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(mess, mess_len, MPI_CHAR, 0, i, MPI_COMM_WORLD);
            }
        }
        free(mess);
    }
    fclose(fptr);
    MPI_Finalize();
    return 0;
}