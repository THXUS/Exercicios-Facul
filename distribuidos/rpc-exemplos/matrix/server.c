/* Definition of the remote add and subtract procedure used by 
   simple RPC example 
   rpcgen will create a template for you that contains much of the code
   needed in this file is you give it the "-Ss" command line arg.
*/
#include <stdio.h>
#include "matrix.h"

/* Here is the actual remote procedure */
/* The return value of this procedure must be a pointer to int! */
/* we declare the variable result as static so we can return a 
   pointer to it */

matrix *
mult_1_svc(operands *argp, struct svc_req *rqstp)
{
	
  static matrix result;

  result.rows = argp->a.rows;
  result.cols = argp->b.cols;

  result.value.data_len  = result.rows * result.cols;
  result.value.data_val = malloc( result.value.data_len * sizeof(int));

    for (int i = 0; i <  argp->a.rows; i++) {
        for (int j = 0; j < argp->b.cols; j++) {
            *(result.value.data_val + i * argp->b.cols + j) = 0;
            for (int k = 0; k < argp->a.cols; k++) {
                *(result.value.data_val + i * argp->b.cols + j) += 
                *(argp->a.value.data_val + i * argp->a.cols + k) * *(argp->b.value.data_val + k * argp->b.cols + j);
            }
        }
    }

  printf("Multiplying Matrices A(%d,%d) and B(%d,%d)... returning Matrix C(%d,%d)\n",
   argp->a.rows,argp->a.cols,argp->b.rows, argp->b.cols,argp->a.rows,argp->b.cols);


    return (&result);

}