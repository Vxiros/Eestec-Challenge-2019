#include <iostream>
#include <math.h>

using namespace std;

int main() 
{


int i,j,M,N,r; //declarations
int counter = 0;
int counter2;
int k,l;



cin >> N >> M; //read dimensions
int grid[N][M]; //declare grid
int coodrinates[N*M][2]; //0 gia to x kai 1 gia to y


for (i=0; i<N; i++) { //reading grid
	for (j=0; j<M; j++) {
		cin >> grid[i][j];
	}
}


cin >> r; //reading radious 

// arxika tha paroume an exei corner cases
if ( grid[0][0] == 1 ) {
	coodrinates[counter][0] = r; //x 
	coodrinates[counter][1] = r; //y
	counter++;
} 

if ( grid[N-1][0] == 1 ) {
	coodrinates[counter][0] = N-1-r; //x
	coodrinates[counter][1] = r; //y
	counter++;
}

if ( grid[0][M-1] == 1 ) {
	coodrinates[counter][0] = r; //x
	coodrinates[counter][1] = M - 1 - r; //y
	counter++;
}

if ( grid[0][M-1] == 1 ) {
	coodrinates[counter][0] = N - 1 - r; //x
	coodrinates[counter][1] = M - 1 - r; //y
	counter++;
}


//testcases gia to an iparxei enas asos kai guro tou uparxoun mono midenika se range r
for (i = 0; i<N; i++) {
	for (j = 0; j<M; j++) {
		if ( i == 0 && j == 0) break;
		if ( i == N-1 && j == 0) break;
		if ( i == 0 && j == M-1) break;
		if ( i == N-1 && j == M-1) break;


		if ( grid[i][j] == 1 ) {
		counter2 = 0;

			for (k = r-i-1; k < r+i; k++) {
				for ( l = r-j-1; l<r+j; l++){
					if (k == i && l == j ) break;
					else counter2++;
				}
			}
		int apot = (pow((2*r+1),2) -1);
		if ( counter2 == apot ) {
			coodrinates[counter][0] = i;
			coodrinates[counter][1] = j;
			counter++;
		}
		apot = 0;
		}
	}
}




/*ektiposi apotelesmatwn */

cout << counter << endl;
for (i=0; i<counter; i++) {
	cout << "x " << coodrinates[i][0] << " y " << coodrinates[i][1] << endl;
}


return 0;
}

/* episimenoume oti exoume analisei ton pseudokwdika stin anafora mas */