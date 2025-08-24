#pragma once
#include<random>
#include<iostream>

float randposf()
{
	srand(static_cast<unsigned int>(time(NULL)));

	int randomNumber = rand() % 3;

	return (float)randomNumber;
}