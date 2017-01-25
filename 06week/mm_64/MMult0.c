#include <stdio.h>


#define A(i,j) a[ (i)*n + (j) ]
#define B(i,j) b[ (i)*n + (j) ]
#define C(i,j) c[ (i)*n + (j) ]

/* Routine for computing C = A * B + C */

void MY_MMult( int n, double *a, double *b, double *c)
{
/*
	register i, j, k;
	register double r;
	for ( i=0; i<n; i++ ){
		for ( k=0; k<n;k++){
			r=A( i,k );
			for ( j=0; j<n; j++ ){
				C( i,j ) += r * B( k,j );
			}
		}
	}
*/
	register int i,j,k;
	register int p,m,o;
	register double G;
	double tmp_a[100][100], tmp_b[100][100];
	for(i=0; i<n; i=i+100)
	{
		for(j=0; j<n; j=j+100)
		{
			for(k=0; k<n; k=k+100)
			{
				for(p=0;p<100;p++)
				{
					for(m=0;m<100;m++)
					{
						tmp_a[p][m]=A(i+p,k+m);
						tmp_b[p][m]=B(k+p,j+m);
					}
				}
				for(o=0;o<100;o++)
				{
					for(m=0;m<100;m++)
					{
						G=tmp_a[o][m];
						for(p=0;p<100;p++)
						{
							C(i+o,j+p)+=G*tmp_b[m][p];
	
						}
					}
				}
			}
		}
	}

}

