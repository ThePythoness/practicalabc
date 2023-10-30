#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 512

float Mat[N][N];
float MatDD[N][N];
float V1[N];
float V2[N];
float V3[N];

void InitData(){
    int i,j;
    srand(8824553);
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

    if (numel <= 0 || from + numel > N) {
        printf("Valor invàlid\n");
        return;
    }

    printf("Vector elements from position %d: ", from);
    for (int i = from; i < from + numel; i++) {
        printf("%.2f ", vect[i]);
    }
    printf("\n");

}

void PrintRow( float mat[N][N], int row, int from, int numel ){
    if (from < 0 || from >= N) {
        printf("Posició invàlida\n");
        return;
    }

    if ( numel <= 0 || from + numel >N){
        return;
    }

    printf("Elements de la fila %d de la matriu: ",row);
    
    for (int i = from; i<from + numel; i++){
        printf("%.2f", mat[row][i]);
    }
    printf("\n");
}

void MultEscalar( float vect[N], float vectres[N], float alfa){
    int pos;
    for (int i = 0;N;i++){
        pos = i;
        vectres[pos] = vect[i] * alfa;
    }
}

float Scalar( float vect1[N], float vect2[N] ){
    float res;
    for (int i = 0;N;i++){
        res = res + ( vect1[i] * vect2[i] );
    }
    return res; 
}

float Magnitude( float vect[N] ){
    return sqrtf(Scalar(vect,vect));
    }
    


int main(){
        InitData();
        float resultat; 
    // Example usage of PrintVect
    PrintVect(V1, 2, 5);  // Display 5 elements starting from position 2 in V1
        PrintRow(Mat, 6, 1, 7);
        resultat = Magnitude(V1);
        printf("%f",res);
    return 0;
}
