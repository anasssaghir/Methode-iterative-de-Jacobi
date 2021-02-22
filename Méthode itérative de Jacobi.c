#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Les éléments de matrice d'entrée */
void getInput( int, double** mat );
/* Le calcul et l'affichage les réponses */
void jacobiCalcul( int, double** mat ,float,int);
double dotProd( int num, double* v1, double* v2 );
int checkFlag( int num, int flags[] );

int main() {
    double **mat;/* Matrice des equations a traite */
    int num;
	float EPS; /* Epsilon */
	int Max_Iterations;
        printf("Entrez la dimension du systeme : ");
        scanf("%d", &num); /* nombre d'inconnues */
		printf("\n Entrez le maximum des iterations a faire :\n");
		scanf("%d",&Max_Iterations);
		printf("\nEntrez la precision epsilon (exemple : 0.000001):\n");
		scanf("%f",&EPS);
		
        while( getchar() != '\n' ) ;
        mat = NULL;
        if(Max_Iterations>0 && EPS>=0 && num>0 && (mat = (double**) malloc(num*sizeof(double*))) ){
            getInput(num, mat);
			jacobiCalcul(num,mat,EPS,Max_Iterations);
        }else{
			puts("\nLe nombre de lignes et de colonnes et epsilon et nombre des iterations doivent etre strictement positif");
            if( mat != NULL ) free( mat );
        }
    return 0;
}
//fonction pour entree la matrice
void getInput( int numEntree, double** mat ){
    int i, j;

    printf(
		"\nEntrez les valeurs pour des lignes et des colonnes \n"
        "(La derniere valeur de chaque ligne est le second membre de chaque equation)\n"
    );
    for( i = 0 ; i < numEntree ; i++ )
    {
        mat[i] = (double*) malloc( (numEntree+1)*sizeof(double) );

        puts("");
        for( j = 0 ; j < numEntree+1 ; j++ )
        {
            printf("entrez coefficient matrice[%d][%d] : ", i, j);
            if( scanf("%lf", &mat[i][j]) != 1 )
            {
                --j;
                puts("choix faux ... essayez a nouveau avec un <<vrai>> nombre.");
            }
            while( getchar() != '\n' ) ;
        }
    }
    printf("\nLa matrice entree :\n\n");

    for( i = 0 ; i < numEntree ; i++ )
	{
        for( j = 0 ; j < numEntree+1 ; j++ )
            printf("%+9f ", mat[i][j]);
			puts("");
    }
	printf("\n Cliquer <<Entrer>> pour commencer les iterations ");
    getchar();
}

/* Traitement ; methode de Jacobi */
void jacobiCalcul( int numEntree, double** mat ,float EPS,int Max_Iter)
{
    int* flag;
    int i, j, counter = 0;
    double* res;
    double* var = (double*) malloc( numEntree*sizeof(double) );
    res = (double*) malloc( numEntree*sizeof(double) );
    flag = (int*) malloc( numEntree*sizeof(int) );

    for(i = 0 ; i < numEntree ; i++ )
        var[i] = res[i] = flag[i] = 0;
    printf("La valeur initiale de chaque element du tableau a ete fixee a zero\n\n");
    printf( "*******************************************************\n");
    do
    {
        counter++;
        /* Pour chaque itération on conserve une copie des anciens résultats */
        for(i = 0 ; i < numEntree ; i++ ){
			var[i] = res[i];
		}
        printf("\n Iteration numero : %d \n", counter);
        for(i = 0 ; i < numEntree ; i++ ) /* Le calcul */
        {
            res[i] = mat[i][numEntree];
            for(j = 0 ; j < numEntree ; j++ )
                res[i] = res[i] - mat[i][j]*var[j] ;
				res[i] = res[i] + mat[i][i]*var[i] ;
				res[i] = res[i] / mat[i][i] ;
				printf("%c = %f\n", 'a'+i, res[i]);
            if( fabs(res[i] - var[i]) < EPS ) /* Condition d'arrêt */
                flag[i]++;
		}
    }while( !checkFlag( numEntree, flag ) && counter<Max_Iter);
printf("*********************************\n");
    printf( "Le resultat de %d iterations \n", counter);
    for( i = 0 ; i < numEntree ; i++){
        var[i] = dotProd( numEntree, mat[i], res );
	}
    printf("\nLa solution est :\n");
    for( i = 0 ; i < numEntree ; i++){
        printf("%c = %+f\n", 'a'+i, res[i]);
        free(mat[i]);
    }
    free( mat );
    free( flag );
    free( res );
    free( var );
}
int checkFlag( int num, int flags[] ){
    int i;
    for( i=0; i<num; ++ i)
        if( flags[i] == 0 ) return 0;
    return 1;
}
double dotProd( int num, double* v1, double* v2 ){
    int i;
    double somme =0;
    for( i=0; i<num; ++i ) somme += v1[i]*v2[i];
    return somme;
}