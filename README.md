# Machine Learning Models
Some ML models for classification and regression implemented from scratch in C.
<br />

![C/C++ CI](https://github.com/computer-spectre/machine-learning-models/workflows/C/C++%20CI/badge.svg?branch=master)

# Plots
## Classification
|PLA|POCKET|ADALINE|
|----|----|----|
|<img src="https://github.com/computer-spectre/machine-learning-models/blob/master/plots/PLA.png" />|<img src="https://github.com/computer-spectre/machine-learning-models/blob/master/plots/pocket.png" />|<img src="https://github.com/computer-spectre/machine-learning-models/blob/master/plots/ADALINE.png" />|
|<img src="https://github.com/computer-spectre/machine-learning-models/blob/master/plots/PLA_loss.png" />|<img src="https://github.com/computer-spectre/machine-learning-models/blob/master/plots/pocket_loss.png" />|<img src="https://github.com/computer-spectre/machine-learning-models/blob/master/plots/ADALINE_loss.png" />|
## Regression
|Simple linear regression (Least squares with gradient decent)| Evolution of loss |
|----|----|
|<img src="https://github.com/computer-spectre/machine-learning-models/blob/master/plots/lin_reg.png" />|<img src="https://github.com/computer-spectre/machine-learning-models/blob/master/plots/lin_reg_loss.png" />|

# Getting started
## Dependencies (Optionnal)
* `gnuplot` (optionnal) This is just for the `plot.sh` script, you can compile and use the library without this
* `rainy-csv` (optionnal) This is my library, I used it just for the tests, so you can skip it too, it is used as git submodule so it will be automatically downloaded when you clone with `--recurse-submodules`
## Cloning
If you are planning to run the tests, please clone with
```bash
$ git clone --recurse-submodules https://github.com/computer-spectre/machine-learning-models
```
to automatically get `rainy-csv`. <br />
If you won't run the tests, then clone as usual :
```bash
$ git clone https://github.com/computer-spectre/machine-learning-models
```
# Compiling and using
## Compiling
Just use the Makefile
### Compile everthing
```bash
$ make USE_RAINY_CSV=1 all
```
Output will be in `lib` for the library, and in `bin` for the tests, note that `USE_RAINY_CSV` macro needs to be defined to compile the tests.
### Only compile the library
if you want to compile the library without `rainy-csv` support, run :
```bash
$ make lib
```
otherwise, run
```bash
$ make USE_RAINY_CSV=1 lib
```
Output will be in `lib` directory
### Compile the test (supposing you already compiled the library
```bash
$ make test
```
Output will be in `bin` directory
## Usage example
```C
#include <helpers/model.h>
#include <helpers/csv2dataset.h>
#include <utils/export.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

   /* Load data */
  labeled_dataset_t *data;
  data = csv_to_labeled_dataset("./test-data/noisy01.csv");

  /* Make and train the model */
  single_layer_model_t *model;
  model = make_single_layer_model(LOG_REG_MODEL, 2, &sigmoid);
  history_t *history = model->train(model, data);

  /* Generate the output files for plotting */
  gp_export_labeled_dataset(data, "data.in");
  gp_export_single_layer_model(model, history);
}
```

## Running the tests

First of all, after compiling, run the test of your choice, 
eg.
```bash
$ ./bin/rg_simple_linreg_test
```
Some output files will be generated, those files are used by the gnuplot scripts to show the result 

Run the `plot.sh` bash script to see the plots 
* Reminder : you will need gnuplot for that

For the classification tests run :
```bash
$ ./plot.sh
```

For the linear regression ones run :
```bash
$ ./plot.sh --lin-reg
```
### Notes about the tests
* Test files prefixed with `cl_` are for classification, and ones prefixed with `rg_` are for regression.
