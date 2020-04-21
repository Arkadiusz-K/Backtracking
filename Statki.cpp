#define _DEBUG_
#define _CRT_SECURE_NO_WARNINGS

#include "StatkiH.h"
#include <stdio.h>

void SetTab( char* sFile, int** pTab, int nRow, int nCol );
void PrintTab( int** pTab, int nRow, int nCol );

int main( int argc, char** argv )
{
	if ( argc != 2 )		// Sprawdzenie popranwoœci iloœci podanych argumentów
	{
		printf( "main: Bledna liczba argumentow!! \n\n" );
		return 1;
	}

	int** pTab = NULL;			// do tablicy okreœlajacej g³êbokoœæ w ka¿dym kwadracie
	if ( !CreateMatrix( &pTab, N, M ) )	// Tablica i podane przez sta³e wymiary planszy
	{
		printf( "main: Blad kreacji macierzy \n\n" );
		return 1;
	}
	int** pRoot = NULL;			// Tablica pamiêtaj¹ca ruchy o rozmiarze nRow, nCol
	if ( ! CreateMatrix( &pRoot, N, M ) )
	{
		printf( "main: Blad kreacji macierzy \n\n" );
		return 1;
	}

	SetTab( argv[1], pTab, N, M );

	if ( root(pTab, N, M, DEPTH_MIN, 0, 0, pRoot, N - 1, M - 1 ) )
	{
		printf( "\n\nStatek dotar³ do celu (portu) !! \n\n" );
#ifdef _DEBUG_
		PrintTab( pRoot, N, M );
#endif // _DEBUG_
	}
	else
		printf( "Nie ma mozliwosci, ¿eby statek dop³yn¹³ do celu (portu) !!\n\n" );

	DeleteMatrix(&pTab, N);
	DeleteMatrix(&pRoot, N);


	return 0;
}


void SetTab( char* sFile, int** pTab, int nRow, int nCol )
{
	FILE* f = NULL;
	if ( ( f = (fopen(sFile, "rt" ) ) ) == NULL )	// r - otwiera plik do odczytu, t - otwiera plik w trybie tekstowym
	{
		perror( "ERROR: Nie udalo sie otworzyc pliku!\n\n" );
		return;
	}

	// Wczytuje dane z pliku
	for ( int i = 0; i < nRow; i++ )
	{
		int* p = *pTab++;
		for ( int j = 0; j < nCol; j++ )
			fscanf( f, "%d", p++ );			// pobór z pliku
	}
	fclose( f );
}


#ifdef _DEBUG_
void PrintTab( int** pTab, int nRow, int nCol )
{
	printf( "\n\n" );
	for ( int i = 0; i < nRow; i++ )
	{
		int* pTemp = *pTab++;
		for ( int j = 0; j < nCol; j++ )
			printf( "%d ", *pTemp++ );
		printf( "\n" );
	}
	printf( "\n" );
}
#endif // _DEBUG_