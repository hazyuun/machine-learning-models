# perceptron_algorithms
Perceptron learning algorithm, Pocket, and ADALINE, implemented in C

# Plots
|PLA|POCKET (Not working)|ADALINE|
|----|----|----|
|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/PLA.png" />|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/pocket.png" />|<img src="https://github.com/A-Rain-Lover/perceptron_algorithms/blob/master/plots/adaline.png" />|


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
* Reminder : you will need gnuplot for that

First of all, after compiling, run the test of your choice, 
eg.
```bash
$ ./bin/perceptron_test_noise
```
Then, run the `plot.sh` bash script
```bash
$ ./plot
```


