#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mpi.h"

int isprime(int n) {
  int i,squareroot;
  if (n>10) {
    squareroot = (int) sqrt(n);
    for (i=3; i<=squareroot; i=i+2)
      if ((n%i)==0)
        return 0;
    return 1;
  }
  else
    return 0;
}

int main(int argc, char *argv[])
{
  int pc,       /* prime counter */
      foundone; /* most recent prime found */
  long long int n, limit;

  /* pc=4; */    /* Assume (2,3,5,7) are counted here */
  
  int local_pc = 0;
  int local_fundone;
  int size;
  int rank;
  long long int total;
  long long int local_limit;
  long long int local_n;
  long long int workload;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
  if (rank==0) {
    sscanf(argv[1],"%llu",&limit);	
    printf("Starting. Numbers to be scanned= %lld\n",limit);
  }

  /* int MPI_Bcast(               */
  /*        void *message,        */
  /*        int count,             */
  /*        MPI_Datatype datatype, */
  /*        int root,              */
  /*        MPI_Comm comm)         */

  MPI_Bcast(&limit, 1, MPI_LONG, 0, MPI_COMM_WORLD);

  total = limit - 11 + 1;
  workload = total / size;
  if ((workload % 2) != 0) {
      workload--;
  }
  local_n = workload * rank + 11;
  local_limit = local_n + workload - 1; 

  /* if (rank == 0) { */
    /* printf("workload = %llu\n", workload); */
  /* } */


  if (rank == size -1) {
    local_limit = limit;
  }
  
  for (n=local_n; n<=local_limit; n=n+2) {
    if (isprime(n) == 1) {
      local_pc++;
      local_fundone = n;  
    }
  }

  /* printf("rank = %d local_n %llu local_limit = %llu local_fundone = %d\n", rank, local_n, local_limit, local_fundone); */
  
  /* int MPI_Reduce(               */
  /*        void *operand,         */
  /*        void *result,          */
  /*        int count,             */
  /*        MPI_Datatype datatype, */
  /*        MPI_Op operator,       */
  /*        int root,              */
  /*        MPI_Comm comm)         */

  MPI_Reduce(&local_pc, &pc, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&local_fundone, &foundone, 1, MPI_LONG, MPI_MAX, 0, MPI_COMM_WORLD);

  /* for (n=11; n<=limit; n=n+2) { */
    /* if (isprime(n)) { */
      /* pc++; */
      /* foundone = n; */
    /* }			 */
  /* } */
  if (rank == 0) {
    printf("Done. Largest prime is %d Total primes %d\n",foundone,pc+4);
  }
  MPI_Finalize();
  return 0;
} 
