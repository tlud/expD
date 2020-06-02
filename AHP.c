#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define N 6
#define rep(i,n) for(int i = 0; i < (n); i++)


void init(double *vec);
double dot(double *vec1, double *vec2);
double norm(double *vec);
double max(double *vec);

//norm(arr)で呼べる.配列arrの先頭アドレスはarrで代用可能(arr == &arr[0])

int main(void){

///////////////////////////////////////////////////////////////
  double A[N][N] = {{1.0, 3.0, 9.0, 3.0, 5.0, 7.0},
                     {0.0, 1.0, 3.0, 1.0, 5.0, 3.0},
                     {0.0, 0.0, 1.0, 1.0/3.0, 1.0, 5.0},
                     {0.0, 0.0, 0.0, 1.0, 3.0, 5.0},
                     {0.0, 0.0, 0.0, 0.0, 1.0, 3.0},
                     {0.0, 0.0, 0.0, 0.0, 0.0, 1.0}};
  double x[N] = {0};
  double x_new[N] = {0};
  double u[N] = {0};

  double x_norm = 0;
  double epsilon = 0.0001;
  int max_itr = 100;
  double d = 0;
  int k = 0;

  double eignvec[N] = {0};
  double eignvalue = 0;
////////////////////////////////////////////////////////////////

  init(x);
  k = 0;



  rep(i, max_itr){

    // u = x / x_norm
    rep(j, N) u[j] = x[j] / norm(x);


    // x_new = Au
    rep(j, N) x_new[j] = dot(A[j], u);


    // d = max{ abs(x(i) - x_new(i)) }

    double dif[N];
    rep(j, N) dif[j] = abs(x[j] - x[j]);

    d = max(dif);

///////////////////////

    if(d < epsilon) break; //収束判定
    else if(k == max_itr - 1){ //最大反復との比較
      init(x); k = 0;
    }
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




  return 0;
}


void init(double *vec){
  rep(i, N) vec[i] = 1.0;
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
