#include <stdio.h>
#include "matrix.h" 

void fill_matrix(matrix* mat) {

  mat->value.data_len = mat->cols * mat->rows;
  mat->value.data_val = malloc((mat->cols * mat->rows) * sizeof(int));

  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < mat->cols; j++) {
      *(mat->value.data_val + i * mat->cols + j) = i * mat->cols + j;  // Valor a ser atribuído
    }
  }
}

void print_matrix(matrix* mat) {
  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < mat->cols; j++) {
        printf("%d ", *(mat->value.data_val + i * mat->cols + j));
      }
      printf("\n");
    }
}

matrix mult( CLIENT *clnt, int rows_a, int cols_a, int rows_b, int cols_b) {
  operands ops;
  matrix *result;

  matrix teste;
  matrix teste2;
  
  teste.rows = rows_a;
  teste.cols = cols_a;

  teste2.rows = rows_b;
  teste2.cols = cols_b;

  fill_matrix(&teste);
  printf("Matrix A\n");
  print_matrix(&teste);


  fill_matrix(&teste2);
  printf("Matrix B\n");
  print_matrix(&teste2);

  ops.a = teste;
  ops.b = teste2;

  result = mult_1(&ops,clnt);

  if(result == NULL) {
    fprintf(stderr,"Trouble calling remote procedure\n");
    exit(0);
  }
  return (*result);
}

int main( int argc, char *argv[]) {
  CLIENT *clnt;
  int rows_a,rows_b,cols_a,cols_b, check;
  matrix result;
  if (argc!=2) {
    fprintf(stderr,"Usage: %s hostname \n",argv[0]);
    exit(0);
  }

  clnt = clnt_create(argv[1], SIMP_PROG, SIMP_VERSION, "udp");

  /* Make sure the create worked */
  if (clnt == (CLIENT *) NULL) {
    clnt_pcreateerror(argv[1]);
    exit(1);
  }

  scanf("%d%d%n", &rows_a, &cols_a, &check);
  scanf("%d%d%n", &rows_b, &cols_b, &check);

  if(cols_a != rows_b) {
    fprintf(stderr," incompatible matrices\n");
    exit(0);
  }
  
  result = mult(clnt,rows_a,cols_a, rows_b, cols_b);

  printf("Matrix C\n");
  print_matrix(&result);

  return(0);
}