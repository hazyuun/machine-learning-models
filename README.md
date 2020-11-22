# perceptron_algorithms

Perceptron learning algorithm, Pocket, and ADALINE, implemented in C
<br />
![C/C++ CI](https://github.com/A-Rain-Lover/perceptron_algorithms/workflows/C/C++%20CI/badge.svg?branch=master)

# Plots

|PLA|POCKET|ADALINE|
|----|----|----|
|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/PLA.png" />|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/pocket.png" />|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/ADALINE.png" />|
|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/PLA_loss.png" />|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/pocket_loss.png" />|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/ADALINE_loss.png" />|

# No dependencies
No dependencies unless you wanna see the plot, then you will need `gnuplot`
You can easily install that with your package manager.

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
$ ./bin/perceptron_test_noise
```
Then, run the `plot.sh` bash script
* Reminder : you will need gnuplot for that

```bash
$ ./plot.sh
```


