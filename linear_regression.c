#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define EPOCHS (1000)
#define FEATURE_COUNT (1)
#define DATA_POINTS (100)

// This can be changed around -- but do note that the slope is consistent across
// ALL input features.

#define SLOPE (2)
#define Y_INTERCEPT (1)

// access element of the i-th row and j-th column of a 1-D array.

#define IDX(arr, i, j) (arr[(i) * FEATURE_COUNT + (j)])

// Linear regression: FEATURE_COUNT input variables to predict 1 output variable.
void weights_gradient(const int *x, const int *y, const float *weights, const float bias, float *weights_gradient);
float bias_gradient(const int *x, const int *y, const float *weights, const float bias);
float *gradient_descent(int *x, int *y, float alpha);

// Utilities
float predict(const int *x, const float *weight, const float bias);
void print_data(int *x, int *y);

int main() {

    // Initializes the array of input features of whole numbers from 0 to DATA_POINTS
    // FEATURE_COUNT times. 

    int *x = malloc(FEATURE_COUNT * DATA_POINTS * sizeof(int));
    assert(x != NULL);
    for (int i = 0; i < DATA_POINTS; i++) {
        for (int j = 0; j < FEATURE_COUNT; j++) {
            IDX(x, i, j) = i;
        }
    }


    // initializes y (output) values of the form wx+b, where w (weight) is the slope and b (bias) is the y-intercept
    // Like the x-values, there is no noise.

    int *y = malloc(DATA_POINTS * sizeof(int));
    assert(y != NULL);
    for (int i = 0; i < DATA_POINTS; i++) {
        y[i] = SLOPE * i + Y_INTERCEPT;
    } 

    // learning rate alpha. Feel free to tweak this and observe how it effects model convergence speed / divergence !
    float alpha = 0.0001f;

    float *params = gradient_descent(x, y, alpha);
    
    for (int i = 0; i < FEATURE_COUNT; i++) {
        printf("Weight #%d: %f, ", i, params[i]);
    }
    printf("bias: %f\n", params[FEATURE_COUNT]);

    free(x);
    free(y);
    free(params);

    return 0;
}

/*
 * Given:
 * 1) arrays of input data (x),
 * 2) an array of output data (y), and
 * 3) a learning rate (alpha),
 *
 * Update the weights and bias by a factor of the gradient until convergence. 
 * Current implementation hard-codes a number of iterations, called 'EPOCHS'
 *
 * Note: there is a closed-form solution for linear regression, since it has a
 * convex cost function. However, gradient descent shows up in many other machine
 * learning algorithms, and seeing it in this context may be beneficial to learn :)
 *
 * returns float pointer of parameters, with the last one being the bias.
 */
float *gradient_descent(int *x, int *y, float alpha) {
    float *weights = calloc(FEATURE_COUNT, sizeof(float));
    assert(weights != NULL);
    float bias = 0.0f;
    float *weight_g = calloc(FEATURE_COUNT, sizeof(float));
    assert(weight_g != NULL);
    for (int i = 0; i < EPOCHS; i++) {

        for (int j = 0; j < FEATURE_COUNT; j++) {
            weight_g[j] = 0.0f;
        }

        weights_gradient(x, y, weights, bias, weight_g);
        float bias_g = bias_gradient(x, y, weights, bias);
        for (int j = 0; j < FEATURE_COUNT; j++) {
            weights[j] = weights[j] - alpha * weight_g[j];
        }
        bias = bias - alpha * bias_g;
    }

    float *params = malloc((FEATURE_COUNT + 1) * sizeof(float));
    for (int i = 0; i < FEATURE_COUNT; i++) {
        params[i] = weights[i];
    }
    params[FEATURE_COUNT] = bias;

    free(weight_g);
    weight_g = NULL;
    free(weights);
    weights = NULL;
    return params;
}

void weights_gradient(const int *x, const int *y, const float *weights, const float bias, float *weights_gradient) {
    for (int i = 0; i < DATA_POINTS; i++) {
        float prediction = predict(&IDX(x, i, 0), weights, bias);
        for (int j = 0; j < FEATURE_COUNT; j++) {
            weights_gradient[j] += (prediction - y[i]) * IDX(x, i, j);
        }
    }
    for (int i = 0; i < FEATURE_COUNT; i++) {
        weights_gradient[i] = weights_gradient[i] / DATA_POINTS;
    }
}

float bias_gradient(const int *x, const int *y, const float *weights, const float bias) {
    float bias_gradient = 0;
    for (int i = 0; i < DATA_POINTS; i++) {
        float prediction = predict((int *)&IDX(x, i, 0), weights, bias);
        bias_gradient += (prediction - y[i]);
    }
    return bias_gradient / DATA_POINTS;
}

float predict(const int *x, const float *weights, const float bias) {
    float dot = 0;
    for (int i = 0; i < FEATURE_COUNT; i++) {
        dot += x[i] * weights[i];
    }
    return dot + bias;
}

void print_data(int *x, int *y) {
    for (int i = 0; i < DATA_POINTS; i++) {
        printf("x values: (");
        for (int j = 0; j < FEATURE_COUNT; j++) {
            printf("%d,%d: %d, ", i, j, IDX(x, i, j));
        }
        printf(") y value: %d\n", y[i]);
    }
}
