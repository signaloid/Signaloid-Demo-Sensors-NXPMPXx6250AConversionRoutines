[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-latest.png#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/signaloid/Signaloid-Demo-Sensors-NXPMPXx6250AConversionRoutines#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-latest.png#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/signaloid/Signaloid-Demo-Sensors-NXPMPXx6250AConversionRoutines#gh-light-mode-only)

# NXP MPXx6250A Sensor Calibration Use Case
Example demonstrating real-time output uncertainty estimation for calibrated ADC values from the MPXx6250A sensor[^1].

## Introduction
The MPXx6250A is a 20 to 250 kPa range integrated pressure sensor.

## Getting started

The correct way to clone this repository to get the submodules is:
```sh
	git clone --recursive git@github.com:signaloid/Signaloid-Demo-Sensors-NXPMPXx6250AConversionRoutines.git
```

If you forgot to clone with `--recursive` and end up with empty submodule directories, you can remedy this with:
```sh
	git submodule update --init
```

## Running the application locally
Apart from using Signaloid's Cloud Compute Platform, you can compile and run this application
locally. Local execution is essentially a native Monte Carlo implementation,
that uses GNU Scientific Library (GSL)[^2] to generate samples for the different input distributions.
In this mode the application stores the generated output samples, in a file called `data.out`.
The first line of `data.out` contains the execution time of the Monte Carlo implementation
in microseconds (μs), and each
next line contains a floating-point value corresponding to an output sample value.
Please note, that for the Monte Carlo output mode, you need to select a single output
to calculate, using (`-S`) command-line option.

In order to compile and run this application in the native Monte Carlo mode:

0. Install dependencies (e.g., on Linux):
```
sudo apt-get install libgsl-dev libgslcblas0
```
1. Compile natively (e.g., on Linux):
```
cd src/
gcc -I. -I/opt/local/include main.c utilities.c common.c uxhw.c -L/opt/local/lib -o native-exe -lgsl -lgslcblas -lm
```
2. Run the application in the MonteCarlo mode, using (`-M`) command-line option:
```
./native-exe -M 10000
```
The above program runs 10000 Monte Carlo iterations.

3. See the output samples generated by the local Monte Carlo execution:
```
cat data.out
```

## Inputs
The inputs to the MPXx6250A sensor conversion algorithms are the raw ADC taken from the voltage output of the sensor ($V_{out}$)
as well as the supply voltage of the sensor ($V_{s}$). The algorithm models the ADC quantization error as well as the uncertainty
in the supply voltage using uniform distributions.

The uncertainty in $V_{out}$ is modeled as a (`UniformDist(2.3, 2.7)`) Volts.

The uncertainty in $V_{s}$ is modeled as a (`UniformDist(4.8, 5.4)`) Volts.



## Outputs
The output is the calibrated pressure:
```math
\mathrm{Calibrated Sensor Output} = \frac{(V_{out}/V_{s} + 0.040)}{0.004}
```

Following is an example output, using Signaloid's C0Pro-S core.

![Example output plot](./docs/plots/output-C0-S.png)

## Usage
```
Example: MPXx6250 sensor conversion routines - Signaloid version

Usage: Valid command-line arguments are:
        [-o, --output <Path to output CSV file : str>] (Specify the output file.)
        [-S, --select-output <output : int>] (Compute 0-indexed output, by default 0.)
        [-M, --multiple-executions <Number of executions : int (Default: 1)>] (Repeated execute kernel for benchmarking.)
        [-T, --time] (Timing mode: Times and prints the timing of the kernel execution.)
        [-v, --verbose] (Verbose mode: Prints extra information about demo execution.)
        [-j, --json] (Print output in JSON format.)
        [-h, --help] (Display this help message.)
```



---

[^1]: [NXP MPXH6250A, 20 to 250 kPa, Absolute, Integrated Pressure Sensor Datasheet](https://www.nxp.com/docs/en/data-sheet/MPXH6250A.pdf).

[^2]: [GNU Scientific Library](https://www.gnu.org/software/gsl/).
