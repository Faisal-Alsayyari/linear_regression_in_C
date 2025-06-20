This is the code I wrote in my video ["Machine learning in C was a mistake"](https://youtu.be/gqSbWMiOuFk) where I implemented simple and multiple linear regression in C without any math or machine learning libraries.

This version includes significant improvements based on feedback and my own debugging efforts:

1) Proper memory management, most notably 'free()'ing dynamic allocations.
2) corrected gradient calculations. 
3) Simplified design by removing the 3 original functions for simple linear regression, as the 'multiple' linear regression functions can now support the case of 1 input feature.
4) Simplified parameter representation -- instead of being represented by structs, parameters are represented by a float pointer, where the last float is the bias.
5) Improved data layout by representing the input features with a normal pointer ('int *x') of size 'FEATURE_COUNT * DATA_POINTS * sizeof(int)'. There is also a macro, 'IDX', that allows for accessing the j-th x-value from the i-th feature.
6) Better comments & documentation, especially for function headers.

### Learning
If you are usig this to learn linear regression, please know that the code currently sets the same weight to all input features and doesn't incorporate any noise. I highly recommend:
a) defining different slopes for different variables, even programmatically with for loops
b) introducing noise to the data, such as by adding or subtracting a float from [0, 'MAX_NOISE']
c) changing the:
	i) learning rate 'alpha',
	ii) number of epochs 'EPOCHS',
	etc.

### Restrictions (under the original video):
- No Math/ML libraries
- Only 'assert.h', 'stdio.h', 'stdlib.h' for assert statements, printing, and memory allocation
- No googling syntax/errors during implementation (1 exception)

Please know that I am still quite new to C development, so I may have made a few mistakes even with the above improvements. That being said, I am very open to comments and criticism, so feel free to let me know :)
