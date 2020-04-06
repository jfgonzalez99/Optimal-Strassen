# Optimal Strassen

*Justin Gonzalez*

Strassen's divide and conquer algorithm for n by n matrix multiplication is asymptotically faster than the traditional O(n^3) algorithm. However, for small values of n, the traditional algorithm is actually faster. The goal of this project is to approximate the value of n for which Strassen's algorithm becomes faster and create an algorithm that optimally switches between the traditional O(n^3) algorithm and Strassen's algorithm.

## How to Run

To compile, simply run `make`. 

To run on a randomly generated matrix of size `n x n` whose elements are in `{0,1,2}`:

```./strassen 1 n none```

To run on a matrix of size `n x n` stored in a text file:

```./strassen 0 n path/to/file.txt```
