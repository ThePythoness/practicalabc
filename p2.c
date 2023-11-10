#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 512
float Mat[N][N];
float MatDD[N][N];
float V1[N];
float V2[N];
float V3[N];
float V4[N];
void InitData(){
        int i,j;
        srand(4422543);
        for( i = 0; i < N; i++ )
                for( j = 0; j < N; j++ ){
                        Mat[i][j]=(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
                        if ( (abs(i - j) <= 3) && (i != j))
                                MatDD[i][j] = (((i*j)%3) ? -1 : 1)*(rand()/(1.0*RAND_MAX));
                        else if ( i == j )
                                MatDD[i][j]=(((i*j)%3)?-1:1)*(10000.0*(rand()/(1.0*RAND_MAX)));
                        else MatDD[i][j] = 0.0;
                }
        for( i = 0; i < N; i++ ){
                V1[i]=(i<N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
                V2[i]=(i>=N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
                V3[i]=(((i*j)%5)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
        }
}
void PrintVect( float vect[N], int from, int numel ){
    if (from < 0 || from >= N) {
        printf("Posició invàlida\n");
        return;
    }

    if (numel <= 0 ||numel > N) {
        printf("Valor invàlid\n");
        return;
    }

    printf("Elements del vector desde %d: ", from);
    for (int i = from; i < from + numel; i++) {
        printf("%f ", vect[i]);
    }
    printf("\n");
}

void PrintRow( float mat[N][N], int row, int from, int numel ){
        if (from < 0 || from >= N){
                printf("Posició invàlida\n");
                return;
        }
        if (numel <= 0 ||numel > N){
                printf("Valor invàlid\n");
                return;
        }
        printf("Elements de la fila %d de la matriu: ",row);
        for (int i = from; i< from + numel; i++){
                printf("%f ", mat[row][i]);
        }
        printf("\n");
}
void MultEscalar( float vect[N], float vectres[N], float alfa ){
        int pos;
        for (int i = 0;i<N;i++){
                pos = i;
                vectres[pos] = vect[i] * alfa;
        }
}
float Scalar( float vect1[N], float vect2[N] ){
        float res;
        for (int i = 0;i<N;i++){
                res = res + (vect1[i] * vect2[i]);
        }
        return res;
}
float Magnitude( float vect[N] ){
        return sqrtf(Scalar(vect,vect));
}
int Ortogonal( float vect1[N], float vect2[N] ){
        float resp;
        resp = Scalar(vect1,vect2);
        if (resp == 0){
                return 1;
        }
        else{
                return 0;
        }
}
void Projection( float vect1[N], float vect2[N], float vectres[N] ){
        float res1, res2, res3;
        res1 = Scalar(vect1,vect2);
        res2 = Magnitude(vect2);
        res3 = res1/res2;
        MultEscalar(vect2, vect1, res3);
}
float Infininorm( float M[N][N] ){
        float max_sum = 0;

    for (int i = 0; i < N; i++) {
        float suma_fila= 0;

        for (int j = 0; j < N; j++) {
            suma_fila += fabs(M[i][j]);
        }

        if (suma_fila > max_sum) {
            max_sum = suma_fila;
        }
    }
    return max_sum;
}
float Onenorm( float M[N][N] ){
         float max_sum = 0;

    for (int j = 0; j < N; j++) {
        float col_sum = 0;

        for (int i = 0; i < N; i++) {
            col_sum += fabs(M[i][j]);
        }

        if (col_sum > max_sum) {
            max_sum = col_sum;
        }
    }
    return max_sum;
}
float NormFrobenius( float M[N][N] ){
        float suma_tot = 0;
        for (int j = 0; j < N; j++) {
                float col_sum = 0;
        for (int i = 0; i < N; i++) {
            col_sum += (fabs(M[i][j])*fabs(M[i][j]));
        }
        suma_tot += col_sum;
        }
        float res;
        res = sqrt(suma_tot);
        return res;
}
int DiagonalDom( float M[N][N] ){
        for (int i = 0; i < N; i++) {
                float val_diagonal = fabs(M[i][i]);
                float suma_fila = 0;

        for (int j = 0; j < N; j++) {
            if (j != i) {
                suma_fila += fabs(M[i][j]);
            }
        }

        if (val_diagonal < suma_fila) {
            return 0;
        }
    }    return 1;
}
int Jacobi( float M[N][N] , float vect[N], float vectres[N], unsigned iter ){
        if (!DiagonalDom(M)) {
                printf("La matriu no és diagonal dominant, per tant, no es pot aplicar la funció Jacobi");
                return 0;
        }
        float temp[N];
        unsigned int l;
        for (l=0; l< iter;l++){
                for (int i = 0; i < N; i++) {
                        temp[i]=vect[i];
                        for (int j=0; j < N; j++) {
                                if (j!=i){
                                        temp[i]=M[i][j]*vectres[j];
                                }
                        }
                        temp[i] /= M[i][i];
                }
                for (int i=0; i<N; i++){
                        vectres[i]=temp[i];
                }
        }
        return 1;
}
int main(){
}
