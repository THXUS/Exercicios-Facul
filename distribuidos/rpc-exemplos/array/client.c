/* RPC client for simple addition example */

#include <stdio.h>
#include "simp.h"  /* Created for us by rpcgen - has everything we need ! */

/* Wrapper function takes care of calling the RPC procedure */

void mult( CLIENT *clnt, int x, int y) {
  operands ops;
  int *result;

  matrix teste;

  teste.matrix_len = 2;
  teste.matrix_val = malloc(2 * sizeof(int));

  *(teste.matrix_val) = 1;
  *(teste.matrix_val + 1) = 8;


  /* Gather everything into a single data structure to send to the server */
  ops.cols = x;
  ops.rows = y;
  ops.data = teste;

  /* Call the client stub created by rpcgen */
  mult_1(&ops,clnt);
}



int main( int argc, char *argv[]) {
  CLIENT *clnt;
  int x,y;
  if (argc!=2) {
    fprintf(stderr,"Usage: %s hostname \n",argv[0]);
    exit(0);
  }

  /* Create a CLIENT data structure that reference the RPC
     procedure SIMP_PROG, version SIMP_VERSION running on the
     host specified by the 1st command line arg. */

  clnt = clnt_create(argv[1], SIMP_PROG, SIMP_VERSION, "udp");

  /* Make sure the create worked */
  if (clnt == (CLIENT *) NULL) {
    clnt_pcreateerror(argv[1]);
    exit(1);
  }

  mult(clnt,2,2);

  return(0);
}