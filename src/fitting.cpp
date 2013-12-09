#include <stdio.h>
#include <gsl/gsl_fit.h>
#include <gsl/gsl_multifit.h>

#include <iostream>
#include <vector>

/*
 Compile with:
 ORDER IS IMPORTANT!
 g++ -o /tmp/fitting fitting.cpp -lgsl -lgslcblas -lm -std=c++0x
 */

void least_squares_straightline_fit(void) {
	int i, n = 4;
	double x[4] = { 1970, 1980, 1990, 2000 };
	double y[4] = { 12, 11, 14, 13 };
	double w[4] = { 0.1, 0.2, 0.3, 0.4 };

	double c0, c1, cov00, cov01, cov11, chisq;

	gsl_fit_wlinear(x, 1, w, 1, y, 1, n, &c0, &c1, &cov00, &cov01, &cov11,
			&chisq);

	printf("# best fit: Y = %g + %g X\n", c0, c1);
	printf("# covariance matrix:\n");
	printf("# [ %g, %g\n#   %g, %g]\n", cov00, cov01, cov01, cov11);
	printf("# chisq = %g\n", chisq);

	for (i = 0; i < n; i++)
		printf("data: %g %g %g\n", x[i], y[i], 1 / sqrt(w[i]));

	printf("\n");

	for (i = -30; i < 130; i++) {
		double xf = x[0] + (i / 100.0) * (x[n - 1] - x[0]);
		double yf, yf_err;

		gsl_fit_linear_est(xf, c0, c1, cov00, cov01, cov11, &yf, &yf_err);

		printf("fit: %g %g\n", xf, yf);
		printf("hi : %g %g\n", xf, yf + yf_err);
		printf("lo : %g %g\n", xf, yf - yf_err);
	}
}

void quadratic_fit(void) {

	int i, n;
	double xi, yi, ei, chisq;
	gsl_matrix *X, *cov;
	gsl_vector *y, *w, *c;

	n = 7;
	double x_vec[] = { 0, 100, 200, 300, 400, 500, 600 };
	double y_vec[] = { 0, 12.5, 50.0, 112.5, 200.0, 312.5, 450.0 };
	double e_vec[] = { 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 };

	X = gsl_matrix_alloc(n, 3);
	y = gsl_vector_alloc(n);
	w = gsl_vector_alloc(n);

	c = gsl_vector_alloc(3);
	cov = gsl_matrix_alloc(3, 3);

	for (i = 0; i < n; i++) {
		xi = x_vec[i];
		yi = y_vec[i];
		ei = e_vec[i];

		printf("%g %g +/- %g\n", xi, yi, ei);

		gsl_matrix_set(X, i, 0, 1.0);
		gsl_matrix_set(X, i, 1, xi);
		gsl_matrix_set(X, i, 2, xi * xi);

		gsl_vector_set(y, i, yi);
		gsl_vector_set(w, i, 1.0 / (ei * ei));
	}

	{
		gsl_multifit_linear_workspace * work = gsl_multifit_linear_alloc(n, 3);
		gsl_multifit_wlinear(X, w, y, c, cov, &chisq, work);
		gsl_multifit_linear_free(work);
	}

#define C(i) (gsl_vector_get(c,(i)))
#define COV(i,j) (gsl_matrix_get(cov,(i),(j)))

	{
		printf("# best fit: Y = %g + %g X + %g X^2\n", C(0), C(1), C(2));

		printf("# covariance matrix:\n");
		printf("[ %+.5e, %+.5e, %+.5e  \n", COV(0,0), COV(0,1), COV(0,2));
		printf("  %+.5e, %+.5e, %+.5e  \n", COV(1,0), COV(1,1), COV(1,2));
		printf("  %+.5e, %+.5e, %+.5e ]\n", COV(2,0), COV(2,1), COV(2,2));
		printf("# chisq = %g\n", chisq);
	}

	gsl_matrix_free(X);
	gsl_vector_free(y);
	gsl_vector_free(w);
	gsl_vector_free(c);
	gsl_matrix_free(cov);
}

/*
 * adapted from http://rosettacode.org/wiki/Polynomial_regression
 *
 * @return m_coeffs[0] + m_coeffs[1]*x + m_coeffs[2]*x^2 + ...
 *
 */
std::vector<double> polynomialfit(int degree, std::vector<double> dx,
		std::vector<double> dy) {

	std::vector<double> store(degree);
	gsl_multifit_linear_workspace *ws;
	gsl_matrix *cov, *X;
	gsl_vector *y, *c;
	double chisq;

	int i, j;

	if (dx.size() != dx.size())
		throw;

	int obs = dx.size(); // number of values

	X = gsl_matrix_alloc(obs, degree);
	y = gsl_vector_alloc(obs);
	c = gsl_vector_alloc(degree);
	cov = gsl_matrix_alloc(degree, degree);

	for (i = 0; i < obs; i++) {
		gsl_matrix_set(X, i, 0, 1.0);
		for (j = 0; j < degree; j++) {
			gsl_matrix_set(X, i, j, pow(dx[i], j));
		}
		gsl_vector_set(y, i, dy[i]);
	}

	ws = gsl_multifit_linear_alloc(obs, degree);
	gsl_multifit_linear(X, y, c, cov, &chisq, ws);

	/* store result ... */
	for (i = 0; i < degree; i++) {
		store[i] = gsl_vector_get(c, i);
	}

	gsl_multifit_linear_free(ws);
	gsl_matrix_free(X);
	gsl_matrix_free(cov);
	gsl_vector_free(y);
	gsl_vector_free(c);
	return store;
}

int main_fitting() {
	// 3 x^2 + 2 x + 1
	std::vector<double> x = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<double> y = { 1, 6, 17, 34, 57, 86, 121, 162, 209, 262, 321 };

	int degree = 3;

	// return m_coeffs[0] + m_coeffs[1]*x + m_coeffs[2]*x^2 + ...
	std::vector<double> coeffs = polynomialfit(degree, x, y);
	for (auto i : coeffs) {
		std::cout << i << std::endl;
	}
	return 0;
}

