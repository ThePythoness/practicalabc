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
        for (int i = 0;i<N;i++){
                vectres[i] = vect[i] * alfa;
        }
}
float Scalar( float vect1[N], float vect2[N] ){
        float res = 0;
        for (int i = 0;i<N;i++){
                res = res + (vect1[i] * vect2[i]);
        }
        return res;
}
float Magnitude( float vect[N] ){
        float res = 0;
	for(int i =0; i<N;i++){
		float suma = 0;
		suma = pow(vect[i],2);
		res +=suma;
	}
	float magnitude = sqrt(res);
	return magnitude;
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
        MultEscalar(vect2, vectres, res3);
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
        if (DiagonalDom(M)==0) {
                printf("La matriu no és diagonal dominant, per tant, no es pot aplicar la funció Jacobi");
                return 0;
	}
	for (unsigned k = 0; k < iter; k++) {
        float temp[N];

        for (int i = 0; i < N; i++) {
            temp[i] = vect[i];

            for (int j = 0; j < N; j++) {
                if (i != j) {
                    temp[i] -= M[i][j] * vect[j];
                }
            }

            temp[i] /= M[i][i];
        }

        // Actualizar el vector resultado con el resultado temporal
        for (int i = 0; i < N; i++) {
            vectres[i] = temp[i];
        }
    }

    return 1;
}
int main(){
        InitData();

    // Llama a todas las demás funciones aquí
    PrintVect(V1, 0, 10);
    printf("\n");
    PrintVect(V1,  256, 10);
    printf("\n");
    PrintVect(V2, 0, 10);
    printf("\n");
    PrintVect(V2, 256, 10);
    printf("\n");
    PrintVect(V3, 0, 10);
    printf("\n");
    PrintVect(V3, 256, 10);
    printf("\n");
    PrintRow(Mat, 0, 0, 10);
    printf("\n");
    PrintRow(Mat, 100, 0, 10);
    printf("\n");
    PrintRow(MatDD, 0, 0, 10);
    printf("\n");
    PrintRow(MatDD, 100, 90, 10);
    printf("\n");

    float inf, one, frob;
    inf=Infininorm(Mat);
    printf("Infininorm de Mat: %f\n", inf);
    printf("\n");
    one=Onenorm(Mat);
    printf("Onenorm de Mat: %f\n", one);
    printf("\n");
    frob=NormFrobenius(Mat);
    printf("Frobenius de Mat: %f\n", frob);
    printf("\n");
    int isDiagonalDom = DiagonalDom(Mat);
    if (isDiagonalDom) {
        printf("Mat és diagonal dominant.\n");
        printf("\n");
    } else {
        printf("Mat no és diagonal dominant.\n");
        printf("\n");
    }
    inf=Infininorm(MatDD);
    printf("Infininorm de MatDD: %f\n", inf);
    printf("\n");
    one=Onenorm(MatDD);
    printf("Onenorm de MatDD: %f\n", one);
    printf("\n");
    frob=NormFrobenius(MatDD);
    printf("Frobenius de MatDD %f\n", frob);
    printf("\n");
    int isDiagonalDomDD = DiagonalDom(MatDD);
    if (isDiagonalDomDD) {
        printf("MatDD és diagonal dominant.\n");
        printf("\n");
    } else {
        printf("MatDD no és diagonal dominant.\n");
        printf("\n");
    }

    float result = Scalar(V1, V2);
    printf("Ecalar V1 V2: %f\n", result);
    printf("\n");
    float result1 = Scalar(V1, V3);
    printf("Escalar V1 V3: %f\n", result1);
    printf("\n");
    float result2 = Scalar(V2, V3);
    printf("Escalar V2 V3: %f\n", result2);
    printf("\n");
    result = Magnitude(V1);
    printf("Magnitud de V1: %f\n", result);
    printf("\n");
    result = Magnitude(V2);
    printf("Magnitud de V2: %f\n", result);
    printf("\n");
    result = Magnitude(V3);
    printf("Magnitud de V3: %f\n", result);
    printf("\n");

    int isOrthogonal = Ortogonal(V1, V2);
    if (isOrthogonal) {
        printf("V1 y V2 són ortogonals.\n");
        printf("\n");
    } else {
        printf("V1 y V2 no són ortogonals.\n");
        printf("\n");
    }

    MultEscalar(V3, V3, 2.0);
    PrintVect(V3, 0, 10);
    printf("\n");
    PrintVect(V3, 256, 10);
    printf("\n");

    Projection(V2, V3, V4);
    PrintVect(V4, 0 ,10);
    printf("\n");
    Projection(V1, V2, V4);
    PrintVect(V4, 0, 10);
    printf("\n");
        // J Jacob
    Jacobi(MatDD,V3,V4,1);
    printf("ELs elements 0 a 9 de la solució (1 iter) del sistema d'equacions són: \n");
    for (int i = 0; i < 10; i++){
            printf("%f ", V4[i]);
                }
    printf("\n");
    Jacobi(MatDD,V3,V4,1000);
    printf("ELs elements 0 a 9 de la solució (1000 iter) del sistema d'equacions són: ");
            for (int i = 0; i < 10; i++){
            printf("%f ", V4[i]);
                }
    printf("\n");

    return 0;
}
