/*
 *	Copyright (c) 2024-2026, Signaloid.
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 */

#pragma once

#include <stddef.h>

/**
 *	@brief	Runs `numberOfMonteCarloIterations` independent evaluations of the sensor
 *		conversion routine, one per iteration, and fills `monteCarloOutputSamples`.
 *		Each iteration re-samples the input variables via
 *		`NXPMPXx6250ASetInputVariablesViaUxHwCall()` (the same `UxHwDoubleUniformDist()`
 *		calls used by the UxHw path) and evaluates `NXPMPXx6250A_calculateOutput()`,
 *		exactly as the pre-refactor Monte Carlo loop in `main.c` did.
 *
 *	@param	numberOfMonteCarloIterations	: Number of Monte Carlo iterations to run.
 *	@param	inputVariables			: Scratch array sized to hold the sensor's input variables.
 *	@param	outputVariables			: An array of output variables, holding the last
 *						  iteration's result on return.
 *	@param	monteCarloOutputSamples		: Array of `numberOfMonteCarloIterations` doubles,
 *						  filled with one calibrated sensor output per iteration.
 *	@return	double				: Returns the calibrated sensor output of the last iteration.
 */
double
NXPMPXx6250AMonteCarlo(
	size_t      numberOfMonteCarloIterations,
	double *    inputVariables,
	double *    outputVariables,
	double *    monteCarloOutputSamples);
