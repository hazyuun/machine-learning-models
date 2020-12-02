# perceptron_algorithms

Some perceptron classification and regression algorithms, implemented in C
<br />
![C/C++ CI](https://github.com/A-Rain-Lover/perceptron_algorithms/workflows/C/C++%20CI/badge.svg?branch=master)

# Plots
## Classification
|PLA|POCKET|ADALINE|
|----|----|----|
|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/PLA.png" />|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/pocket.png" />|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/ADALINE.png" />|
|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/PLA_loss.png" />|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/pocket_loss.png" />|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/ADALINE_loss.png" />|
## Regression
|Linear regression ( Least squares with gradient decent )| Evolution of loss |
|----|----|
|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/lin_reg.png" />|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/lin_reg_loss.png" />|

# Getting started
## Dependencies (Optionnal)
* `gnuplot` (optionnal) This is just for the `plot.sh` script, you can compile and use the library without this
* `rainy-csv` (optionnal) This is my library, I used it just for the tests, so you can skip it too, it is used as git submodule so it will be automatically downloaded when you clone using the command below
## Cloning
If you wanna run the tests, please clone with
```bash
$ git clone --recurse-submodules https://github.com/A-Rain-Lover/perceptron_algorithms
```
to automatically get `rainy-csv` used in the tests.
If you won't run the tests, then clone as usual.

# Compiling and using
## Compiling
Just use the Makefile
### Compile everthing
```bash
$ make all
```
Output will be in `lib` for the library, and in `bin` for the tests
### Only compile the library
```bash
$ make lib
```
Output will be in `lib` directory
### Compile the test (supposing you already compiled the library
```bash
$ make test
```
Output will be in `bin` directory
## Running the test

First of all, after compiling, run the test of your choice, 
eg.
```bash
$ ./bin/noisy_input_test
```
Some output files will be generated, those files are used by the gnuplot scripts to show the result 

Run the `plot.sh` bash script to see the plots 
* Reminder : you will need gnuplot for that

For the classification tests run :
```bash
$ ./plot.sh
```

For the regression ones run :
```bash
$ ./plot.sh --lin-reg
```
