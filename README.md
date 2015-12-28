# MakeAndDoPolydivisible
Computing polydivisible numbers using all non-zero digits once for different base numbers, as mentioned in Matt Parker's ["Things to Make and Do in the Fourth Dimension"](http://makeanddo4d.com/).

## Overview
The numbers are computed using a depth-first-method and the program utilizes the [Open MP](http://openmp.org/wp/)-pragma to parallelize the computations.

Any polydivisible numbers found by the program are printed to the screen as a comma-separated list starting from the most significant digit. At termination, the total running time is recorded. If no polydivisible numbers exist in the given base, the program prints nothing but the running time. Of course, these times will depend on the specific system.

Although the algorithm terminates quickly for the first base numbers, the algorithm will scale poorly because of its apalling O(n!n) complexity. For more details, see Complexity.pdf.
