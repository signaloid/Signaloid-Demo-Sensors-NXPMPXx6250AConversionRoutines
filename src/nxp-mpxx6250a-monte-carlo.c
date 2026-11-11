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

#include <stddef.h>
#include "kernel.h"
#include "nxp-mpxx6250a-monte-carlo.h"

double
NXPMPXx6250AMonteCarlo(
	size_t      numberOfMonteCarloIterations,
	double *    inputVariables,
	double *    outputVariables,
	double *    monteCarloOutputSamples)
{
	double calibratedSensorOutput = 0.0;

	for (size_t ii = 0; ii < numberOfMonteCarloIterations; ii++)
	{
		/*
		 *	Set input distribution values inside the Monte Carlo loop, so that
		 *	each iteration draws a fresh sample, exactly as the pre-refactor
		 *	loop in `main.c` did.
		 */
		NXPMPXx6250ASetInputVariablesViaUxHwCall(inputVariables);

		calibratedSensorOutput = NXPMPXx6250A_calculateOutput(inputVariables, outputVariables);

		monteCarloOutputSamples[ii] = calibratedSensorOutput;
	}

	return calibratedSensorOutput;
}
