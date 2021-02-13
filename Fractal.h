#pragma once

#include "Complex.h"
#include "Vector.h"
#include <iostream>
#include <fstream>
#include <mutex>
#include <random>

#define GRADIENT_DESCENT true

class Fractal
{
public:
	//amount of poles
	static constexpr int N = 10;
	//amount of pixels
	static constexpr int p = 200, pixels_size = p * p;
	static constexpr int thread_count = 100;
	//pixels per thread
	static constexpr int ppt = pixels_size / thread_count;

	//bounds in the complex plane
	struct Box
	{
		double x0, y0, x1, y1;
		Box(double x0, double y0, double x1, double y1) : x0(x0), y0(y0), x1(x1), y1(y1)
		{
		}
		inline double Width()
		{
			return x1 - x0;
		}
		inline double Height()
		{
			return y1 - y0;
		}
	};

	//distributions used to randomize poles
	struct Dist
	{

		double mx, Mx;
		std::uniform_real_distribution<double> Distx;
		double my, My;
		std::uniform_real_distribution<double> Disty;
#if INTEGER_EXPONENT
		int mm, Mm;
		std::uniform_int_distribution<int> Distm;
#else
		double mm, Mm;
		std::uniform_real_distribution<double> Distm;
#endif


		Dist(double mx, double Mx, double my, double My, EXPONENT_TYPE mm, EXPONENT_TYPE Mm) : Distx(mx, Mx), Disty(my, My), Distm(mm, Mm)
		{
			this->mx = mx;
			this->Mx = Mx;
			this->my = my;
			this->My = My;
			this->mm = mm;
			this->Mm = Mm;
		}
		Dist(const Dist& dist) : Distx(dist.mx, dist.Mx), Disty(dist.my, dist.My), Distm(dist.mm, dist.Mm)
		{
			mx = dist.mx;
			Mx = dist.Mx;
			my = dist.my;
			My = dist.My;
			mm = dist.mm;
			Mm = dist.Mm;
		}
	};

	Fractal(int it, int bail, Dist dist, Box box);
	/* Functions */
	//randomize poles and return the minimal cost after given attempts
	double Randomize(int attempts);
	//the fractal function
	inline double Func(Complex c) const;
	//iterates over all the pixels and assigns their value
	void Iterate();
	//returns the total normalised energy of the current pixels
	double Cost();
	//returns the complex derivative of the position of the i'th' pole
	Vector PosDerivative(int i);
	//returns the real derivative of the exponent of the i'th' pole
	double PowerDerivative(int i);
	//does one training cycle for the position of the i'th' pole
	//returns the new_cost after the cycle: 
	//	new_cost < cost: the step was downhill
	//	new_cost >= cost: the step was not downhill and ForceDownhill was false (poles have changed)
	//	new_cost == -1.0f:  the step was not downhill and ForceDownhill was set true (poles haven't changed)
	double PosMinimize(int i, double cost, bool ForceDownhill);
	//does one training cycle for the exponent of the i'th' pole
	//returns true if the step was downhill (New_Cost < Prev_Cost)
	//if ForceDownhill is set to true it will always take a step so that: New_Cost <= Prev_Cost
	double PowerMinimize(int i, double cost, bool ForceDownhill);
	//print pixels and parameters to csv files
	void Print();
	/* Getters & Setters */
	Pole* GetPoles() { return poles; }
private:

	/* Variables */

	//constant used in the fractal function as e^C
	const double C = 0;
	//amount of increasingly smaller steps taken to find an efficient step (lower cost)
	int cost_steps = 5;
	//stepsize to determine the positional derivative of the poles
	double pos_step = 0.01;
	//stepsize to determine the exponent derivative of the poles
	double power_step = 0.01;
	//randomizer
	std::mt19937 rng;
	//double distributions for poles
	Dist dist;
	//thread lock
	std::mutex mtx;
	//threads
	std::thread threads[thread_count];
	//fractal properties
	int iterations, bailout;
	//distance per pixel
	double dx, dy;
	//area where the fractal is generated
	Box bounds;
	//array of all the coordinates inside the bounds
	Complex coordinates[pixels_size];

	//array of all values inside the bounds
	double pixels[pixels_size];

	//array of all desired values
	double desired[pixels_size];

	//poles, both numerator and denominator
	Pole poles[N];

	/* Functions */
	//Iterates over a portion of the total pixels
	void SubIterate(int start, int end);
};

