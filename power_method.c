#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define N 3
#define rep(i,n) for(int i = 0; i < (n); i++)


void init(double *vec);
double dot(double *vec1, double *vec2);
double norm(double *vec);
double max(double *vec);

//norm(arr)で呼べる.配列arrの先頭アドレスはarrで代用可能(arr == &arr[0])

int main(void){

///////////////////////////////////////////////////////////////
  double A[N][N] = {{6.0, -1.0, -2.0},
                     {4.0, 1.0, -2.0},
                     {5.0, -1.0, -1.0}};
  double x[N] = {0};
  double x_new[N] = {0};
  double u[N] = {0};

  double x_norm = 0;
  double epsilon = 0.000001;
  int max_itr = 1000;
  double d = 0;

  double eignvec[N] = {0};
  double eignvalue = 0;
////////////////////////////////////////////////////////////////

  init(x);

  rep(i, max_itr){

    // u = x / x_norm
    rep(j, N) u[j] = x[j] / norm(x);


    // x_new = Au
    rep(j, N) x_new[j] = dot(A[j], u);


    // d = max{ abs(x(i) - x_new(i)) }

    double dif[N];
    rep(j, N) dif[j] = fabs(x[j] - x_new[j]);
    d = max(dif);

///////////////////////

    if(d < epsilon) break; //収束判定

    else if(i == max_itr - 1){ //最大反復との比較
      init(x); i = 0;
      printf("init\n");
    }


    rep(j, N) x[j] = x_new[j];


  }

///////////////////////

  // eignvec = u
  rep(j, N) eignvec[j] = u[j];

  // eignvalue = u'(Au)    (Au == x_new)
  eignvalue = dot(u, x_new);

///////////////////////

  printf("eign value: ");
  printf("%3lf, ", eignvalue);
  printf("\n");
  printf("eign vector: ");
  rep(j, N) printf("%3lf, ", eignvec[j]);

  ///////// Au = (lambda)u の確認 ///////////////////

  double Au[N];
  rep(i, N) Au[i] = dot(A[i] , u);

  printf("\n");
  printf("\n");
  printf("Au: ");
  rep(j, N) printf("%3lf, ", Au[j]);
  printf("\n");
  printf("(lambda)u: ");
  rep(j, N) printf("%3lf, ", eignvec[j] * eignvalue);




  return 0;
}


void init(double *vec){
  rep(i, N) vec[i] = (rand() % 11); // [0, 10]
}

double dot(double *vec1, double *vec2){
  double dot = 0;
  rep(i, N) dot += vec1[i] * vec2[i];
  return dot;
}

double norm(double *vec){
  double norm = dot(vec, vec);
  norm = sqrt(norm);
  return norm;
  //配列vecの先頭アドレスを受け取り、関数内でvecはその先頭アドレスを示す.
  //そのためdotに渡しているのはアドレス
}

double max(double *vec){
  double mx = 0;
  rep(i, N) if(mx < vec[i]) mx = vec[i];
  return mx;
}
