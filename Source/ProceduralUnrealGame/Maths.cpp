// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralUnrealGame.h"
#include "Maths.h"
#include <stdio.h>
#include <time.h>

//set the seed to the current time
void Maths::ResetSeed( void )
{
	srand( time( NULL ) );
}

//return a random integer between min and max
int Maths::RandomGen( int min, int max )
{
	return rand() % ( max - min ) + min;
}

//return a random float between min and max
float Maths::RandomGen( float min, float max )
{
	return min + static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / ( max - min ) ) );
}