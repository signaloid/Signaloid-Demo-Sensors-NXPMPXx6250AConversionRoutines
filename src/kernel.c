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

#include <uxhw.h>
#include "kernel.h"
#include "nxp-mpxx6250a-uxhw.h"
#include "nxp-mpxx6250a-monte-carlo.h"


double
NXPMPXx6250A_calculateOutput(double * inputVariables, double *  outputVariables)
{
	double  vSupplyADC;
	double  vSensorADC;
	double  calibratedValue;

	vSupplyADC  = inputVariables[kNXPMPXx6250AInputVariableIndexVsupplyADC];
	vSensorADC  = inputVariables[kNXPMPXx6250AInputVariableIndexVsensorADC];

	calibratedValue = ((vSensorADC / vSupplyADC) + kNXPMPXx6250ASensorCalibrationConstant1) / kNXPMPXx6250ASensorCalibrationConstant2;
	outputVariables[kNXPMPXx6250AOutputVariableIndexCalibratedSensorOutput] = calibratedValue;

	return calibratedValue;
}

void
NXPMPXx6250ASetInputVariablesViaUxHwCall(double * inputVariables)
{
	inputVariables[kNXPMPXx6250AInputVariableIndexVsensorADC] = UxHwDoubleUniformDist(
		kNXPMPXx6250ADefaultInputDistributionVsensorUniformDistLow,
		kNXPMPXx6250ADefaultInputDistributionVsensorUniformDistHigh
	);
	inputVariables[kNXPMPXx6250AInputVariableIndexVsupplyADC] = UxHwDoubleUniformDist(
		kNXPMPXx6250ADefaultInputDistributionVsupplyUniformDistLow,
		kNXPMPXx6250ADefaultInputDistributionVsupplyUniformDistHigh
	);

	return;
}

double
NXPMPXx6250ACalculateOutputUxHw(
	double *    outputVariables,
	double *    monteCarloOutputSamples)
{
	double  inputVariables[kNXPMPXx6250AInputVariableIndexMax];
	double  calibratedSensorOutput;

	calibratedSensorOutput      = NXPMPXx6250AUxHw(inputVariables, outputVariables);
	monteCarloOutputSamples[0]  = calibratedSensorOutput;

	return calibratedSensorOutput;
}

double
NXPMPXx6250ACalculateOutputMonteCarlo(
	size_t      numberOfMonteCarloIterations,
	double *    outputVariables,
	double *    monteCarloOutputSamples)
{
	double inputVariables[kNXPMPXx6250AInputVariableIndexMax];

	return NXPMPXx6250AMonteCarlo(
		numberOfMonteCarloIterations,
		inputVariables,
		outputVariables,
		monteCarloOutputSamples
	);
}
