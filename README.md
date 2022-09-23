# Introduction
The goal of this project is to implement some of the data structures and algorithms I have learned about in theoretical CS courses. I have found that implementing an algorithm in code often gives a deeper understanding because it is more difficult to gloss over seemlying unimportant but subtle details.

So far I've only implemented Splay Trees.

## Usage
Tests are run using the GoogleTest C++ test framework which is installed with
```
    brew install googletest
```
Tests are run with
```
    make test && bin/test
```

Main file which allows you to input simple operations to do on the splay tree and display the out is run with 
```
    make && bin/main
```

# Splay Trees
Splay trees are a type of binary search where recently used elements are kept near the root of the tree. While the amortized cost of their operations is the same as other binary search trees $O(\log n)$, the temporal locality of non random access sequences often allows them to improve their performance.

Additionally, suppose the access frequencies of each key were static and known, e.g. key $x$ is accessed with probability $p_x$. Surprisingly Splay Trees match the optimal performance of any self adjusting binary search tree on this access pattern without even knowing the access frequencies or keeping any auxillary augmentations!

It is conjectured that Splay Trees are within a constant factor of the best dynamic binary search on any access sequence even one specifically designed to be good for another type of tree. This is known as the Dynamic Optimality Conjecture.

# TODO
    - expand README
    - Splay Trees
        - allow for duplicate keys
        - add more tests
    - add Fibonacci heap
    - add VEB queue

