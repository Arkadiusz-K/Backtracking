#include "StatkiH.h"

#include <stdio.h>

#include <stdlib.h>



int CreateMatrix( int*** pTab, int nRow, int nCol )

{
	
*pTab = ( int** )calloc( nRow, sizeof( int* ) );

if ( !*pTab )
	
{
		
	perror( "CreateMatrix: allocation error" );

	return 0;
	
}

	
int **p = *pTab;


for ( int i = 0; i < nRow; i++, p++ )
	
{
		
	*p = ( int* )calloc( nCol, sizeof( int ) );

	if ( !*p )
		
	{
			
		perror( "CreateMatrix: allocation error" );

		return 0;

	}

}

return 1;

}





int DeleteMatrix( int*** pTab, int nRow )

{
	
int** p = *pTab;
	
for ( int i = 0; i < nRow; i++, p++ )

free( *p );
	
free( *pTab );
	
*pTab = NULL;
	
return 1;

}






int move( int** pTab, int nRow, int nCol, int nDepth, int move_nr, int x, int y, int* px, int* py, int** pRoot )

{
	
	switch ( move_nr )
	
	{
	
	case UP:
		*px = x;

		*py = ++y;

		break;

	case RIGHT:

		*px = ++x;
		*py = y;

		break;
	
	case DOWN:
		
		*px = x;

		*py = --y;

		break;
	
	case LEFT:

		*px = --x;

		*py = y;

		break;
	
	}

	
	// Sprawdziæ cz ruchy (indeksy) mieszcz¹ siê w zakresie
	
if ( ( *px >= 0 ) && ( *px < N ) && ( *py >= 0 ) && ( *py < M ) )
	
{
		
	if ( ( pTab[ *px ][ *py ] > nDepth ) && ( pRoot[ *px ][ *py ] == 0 ) )	
	// Warunek odpowiedniej glêbokoœci i nieodwiedzenia danego pola
		
	{

		return 1;

	}

}
	
return 0;

}






int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest )

{
	
	pRoot[ x ][ y ] = 1;
	// pRoot[x][y] zosta³ odwiedzony


	if ( ( x == x_dest ) && ( y == y_dest ) )
	// Jeœli statek dotar³ do portu
	
	{
		
		printf( " (%d,%d) ", x, y );
		// Wypisz miejsce docelowe

		return 1;
	
	}

	
	// Zdefiniowane nowe wspó³rzêdne

	int new_x = x;
	int new_y = y;

	
	for ( int i = UP; i <= LEFT; i++ )
	// Sprawdzamy kolejno ruch w dó³, w prawo, w górê i w lewo (nazwa UP to tak z punktu widzenia statku)
		
	if ( move( pTab, nRow, nCol, nDepth, i, x, y, &new_x, &new_y, pRoot ) )
	// ==1 -> to poprawny ruch, ==0 -> trzeba rozpatrzyæ kolejny ruch

	if ( root( pTab, N, M, DEPTH_MIN, new_x, new_y, pRoot, x_dest, y_dest ) )
	// Jeœli dosz³o do tego miejsca, to znaczy, ¿e ruch okaza³ siê dobry

	{
				
		printf( "(%d,%d) ", y, x );
		// Wypis ruchów

		return 1;

	}

	
	pRoot[ x ][ y ] = -1;
	return 0;

}