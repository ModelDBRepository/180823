README
======

About this program
------------------

This is the source code of our simulation program used in the following article:

> Yamazaki T, Nagao S, Lennon W, Tanaka S.
> Modeling memory consolidation during posttraining periods in cerebellovestibular learning.
> Proc Nat Acad Sci USA, 2015, doi: 10.1073/pnas.1413798112

Contents
--------

* `Makefile`: Makefile
* `main.c`: Main program
* `func.c`: Functions for OKR(t), w(t), and v(t)
* `param.h.dist`: Parameters
* `param.h`: Identical to `param.h.dist`

Basic usage
-----------

0. You might clean the directory first by `make distclean`
1. `make`
2. Done.

Generated files
---------------

* `normal.dat`: Normal condition as in Fig. 1
* `normal4.dat`: Normal condition for 4 days
* `shutdown4.dat`: Shutdown after the 4th day training
* `muscimol[n].dat`: Muscimol injection [n]min after training
* `mass.dat`: Massed 1-hour training
* `space[n].dat`: Spaced trainig with various conditions

File usage
----------

Each data follow the following format:

    time(min) okr(t) w(t) v(t)

For instance, if you use gnuplot and type `plot 'normal.dat' with line`, you will see the same plot as in Fig. 1C.

Similarly, if you type `plot 'normal.dat' using 1:3 with line, 'normal.dat' using 1:4 with line`, you will see the same plot as in Fig. 1D.

Advanced usage
--------------

To obtain results for the gene-manipulated animals as in Fig. 4, you need to rewrite `main()` in `main.c` by commenting in/out correctly, and set parameters appropriately in `param.h`. That's why `param.h.dist` exists. Once you succeed, you will obtain one of the following files:

* `ltd.dat`: LTD-deficient result as in Fig. 4B
* `wulff.dat`: GABA receptor depletion result as in Fig. 4C

Note that the code does not generate data for Fig. 4A, because from Eqs.(S27--29), the result is obvious.

License
-------

CC-BY

Contact
-------

If you have questions and/or comments, please let me know:

> YAMAZAKI, Tadashi
> Graduate School of Informatics and Engineering
> The University of Electro-Communications
> pnas14@neuralgorithm.org

History
-------

* 20150225: Initial version
