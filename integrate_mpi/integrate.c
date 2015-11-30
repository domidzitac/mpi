#include <stdio.h>
#include <math.h>

#include "mpi.h"

#define PI 3.1415926535
int main(int argc, char **argv) {

  long long i, num_intervals;
  double rect_width, area, sum, x_middle; 

  int size;
  int rank;
  long long workload;
  long long local_l, local_r;
  double local_sum = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    sscanf(argv[1],"%llu",&num_intervals);
  }

  /* int MPI_Bcast(               */
  /*        void *message,        */
  /*        int count,             */
  /*        MPI_Datatype datatype, */
  /*        int root,              */
  /*        MPI_Comm comm)         */
  MPI_Bcast(&num_intervals, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

  rect_width = PI / num_intervals;
  workload = num_intervals / size;  
  local_l = 1 + workload * rank;
  local_r = 1 + workload * (rank + 1);

  if (rank == size - 1) {
    local_r = num_intervals + 1; 
  }


  /* printf("rank = %d workload = %llu local_l = %llu local_r = %llu\n", rank, workload, local_l, local_r); */

  sum = 0;
  for(i = local_l; i < local_r; i++) {
    /* find the middle of the interval on the X-axis. */ 
    x_middle = (i - 0.5) * rect_width;
    area = sin(x_middle) * rect_width; 
    local_sum = local_sum + area;
  }

  /* int MPI_Reduce(               */
  /*        void *operand,         */
  /*        void *result,          */
  /*        int count,             */
  /*        MPI_Datatype datatype, */
  /*        MPI_Op operator,       */
  /*        int root,              */
  /*        MPI_Comm comm)         */
  MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    printf("The total area is: %f\n", (float)sum);
  }
  MPI_Finalize();
  return 0;
}   
