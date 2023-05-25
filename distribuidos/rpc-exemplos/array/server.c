/* Definition of the remote add and subtract procedure used by 
   simple RPC example 
   rpcgen will create a template for you that contains much of the code
   needed in this file is you give it the "-Ss" command line arg.
*/
#include <stdio.h>
#include "simp.h"

/* Here is the actual remote procedure */
/* The return value of this procedure must be a pointer to int! */
/* we declare the variable result as static so we can return a 
   pointer to it */

void *
mult_1_svc(operands *argp, struct svc_req *rqstp)
{
	
    matrix result = argp->data;

    printf("%d\n", *(result.matrix_val+1));
}