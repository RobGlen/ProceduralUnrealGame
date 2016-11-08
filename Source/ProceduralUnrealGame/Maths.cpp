// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralUnrealGame.h"
#include "Maths.h"
#include <stdio.h>
#include <time.h>

void Maths::ResetSeed( void )
{
	srand( time( NULL ) );
}

int Maths::RandomGen( int min, int max )
{
	return rand() % ( max - min ) + min;
}

float Maths::RandomGen( float min, float max )
{
	return min + static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / ( max - min ) ) );
}