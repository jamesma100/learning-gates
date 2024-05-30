# learning-gates
Machine learning for logic gates.
Basically just a dumb linear classifier and hence cannot predict something like XOR.

In essence, we calculate partial derivatives for a cost function `sqrt((f(x) - y)^2)`, where `f(x) = w*x + b`, which we use for our step function.
As long as the learning rate is reasonably small and number of iterations is reasonably large, we can drive the cost to zero.

## Setup
To build:
```
$ make gates
```

Then run `./gates <num iterations>`. Program defaults to NAND gate prediction:
```
$ ./gates 500000
i = 0: w = [0.015327, 0.231793], b = 0.346607, cost = 0.940311
i = 1: w = [0.014813, 0.231102], b = 0.348040, cost = 0.940032
i = 2: w = [0.014297, 0.230410], b = 0.349471, cost = 0.939753
...
i = 499997: w = [-12.365129, -12.365138], b = 18.630379, cost = 0.003494
i = 499998: w = [-12.365132, -12.365142], b = 18.630384, cost = 0.003494
i = 499999: w = [-12.365136, -12.365146], b = 18.630390, cost = 0.003494
=========================================================================
0 | 0 => 1.000000
0 | 1 => 0.998102
1 | 0 => 0.998102
1 | 1 => 0.002238
```
To predict a different gate, just change the `y` values in `gates.c`.
For instance, an OR gate would be:
```
const float x[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
// const float y[4] = {1, 1, 1, 0}; // NAND
const float y[4] = {0, 1, 1, 1};    // OR
```
Voila:
```
$ make gates && ./gates 500000
...
i = 499997: w = [13.642645, 13.642620], b = -6.595342, cost = 0.001837
i = 499998: w = [13.642649, 13.642624], b = -6.595344, cost = 0.001837
i = 499999: w = [13.642653, 13.642628], b = -6.595345, cost = 0.001837
=========================================================================
0 | 0 => 0.001365
0 | 1 => 0.999131
1 | 0 => 0.999131
1 | 1 => 1.000000
```
