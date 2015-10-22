/*
Rishabh Jangir
130121028
Engineering Physics
4/08/2015
*/

#include <iostream>
#include <cmath>


double current;
double crudeGuess = 2.0;
int iterations = 0;

double function(float Xi){
	return 2*pow(Xi, 3) - 11.7*pow(Xi, 2) + 17.7*Xi -5;
}

double slopeAt(float Xi){
	return 6*pow(Xi, 2) -23.4*Xi + 17.7;
}

double drawTangentFindNext(float Xi){
	return Xi - (function(Xi)/slopeAt(Xi));
}

double error(float Xi){
	return std::abs(100*(1-(Xi/drawTangentFindNext(Xi))));
}

int main(){
    current = crudeGuess;
    while (error(current) >= 0.01){
        iterations++;
    	current = drawTangentFindNext(current);

    }

    std::cout<<"Root of the given function is:"<<current<<std::endl;
    std::cout<<"Numver of iterations performed:"<<iterations<<std::endl;

    
    return 0;
}