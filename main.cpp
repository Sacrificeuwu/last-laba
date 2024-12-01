#include<stdio.h>
#include<math.h>

double sinPC(double x) {
	return sinl(x);
}
double cosPC(double x) {
	return cosl(x);
}
double expPC(double x) {
	return exp(x);
}
double tanPC(double x) {
	return tanl(x);
}
int Factorial(int a) {
	int fact = 1, i;
	for (i = 1; i <= a; i++) {
		fact *= i;
	}
	return fact;
}
double Sin(double x, double eps, int N) {
	double sum = 0.0;
	double term = x;
	int sign = 1;

	for (int n = 1; fabs(term) >= eps || n <= N; n++) {
		sum += sign * term;
		term *= x * x / ((2 * n) * (2 * n + 1));
		sign = -sign;
	}

	return sum;
}
double Cos(double x, double eps, int N) {
	double sum = 0.0;
	double term = x;
	int sign = 1;

	for (int n = 1; fabs(term) >= eps || n <= N; n++) {
		sum += term * sign;
		term = pow(x, 2 * n) / Factorial(2 * n);
		sign = -sign;
	}

	return sum;
}

double Tan(double x, double eps, int N)
{
	double sum = 0.0;
	double term = x;
	int sign = 1;
	int cnt = 0;
	for (int n = 1; fabs(term) >= eps || n <= N; ++n) {
		sum += sign * term;
		term *= x * x * (2 * n) * (2 * n - 1) / ((2 * n + 1) * (2 * n + 2));
		sign = -sign;
	}
	return sum;
}
double Exponential(double x, double eps, int N) {
	double sum = 0.0;
	double term = 0;
	for (int n = 0; fabs(term) >= eps || n <= N; n++) {
		term = pow(x, n) / Factorial(n);
		sum += term;
	}
	return sum;
}

int main() {
	while (true) {
		int N = 0;
		double (*functions[4])(double, double, int) = { Exponential, Sin, Cos, Tan };
		double (*functionsPC[4])(double) = { expPC, sinPC, cosPC , tanPC };
		int NMax = 0;
		double x;
		double ans;
		int mode = 0;
		int functionMode = 0;
		double eps;
		double raznica;
		printf("Select mode (1 or 2): ");
		scanf_s("%d", &mode);
		switch (mode)
		{
		case 1:
			printf("Select function:\n 1 - Exponent\n 2 - Sin\n 3 - Cos \n 4 - Tan\n");
			scanf_s("%d", &functionMode);
			printf("Enter fault size:");
			scanf_s("%lf", &eps);
			printf("from 1 to 1000:");
			scanf_s("%d", &N);
			printf("x: ");
			scanf_s("%lf", &x);
			switch (functionMode)
			{
			case 1:
				printf("%0.15lf\n", exp(x));
				printf("%0.15lf\n", Exponential(x, eps, N));
				raznica = fabs(Exponential(x, eps, N) - exp(x));
				printf("%0.15lf\n", raznica);
				break;
			case 2:
				printf("%0.15lf\n", sin(x));
				printf("%0.15lf\n", Sin(x, eps, N));
				raznica = fabs(Sin(x, eps, N) - sinl(x));
				printf("%0.15lf\n", raznica);
				break;
			case 3:
				printf("%0.15lf\n", cosl(x));
				printf("%0.15lf\n", Cos(x, eps, N));
				raznica = fabs(Cos(x, eps, N) - cosl(x));
				printf("%0.15lf\n", raznica);
				break;
			case 4:
				printf("%0.15lf\n", tanl(x));
				printf("%0.15lf\n", Tan(x, eps, N));
				raznica = fabs(Tan(x, eps, N) - tanl(x));
				printf("%0.15lf\n", raznica);
				break;
			
			}
			return 0;
		case 2:
			eps = 1;
			printf("x: ");
			scanf_s("%lf", &x);
			printf("Number of experiments(from 1 to 25): ");
			scanf_s("%d", &NMax);
			printf("Select function:\n 1 - Exponent\n 2 - Sin\n 3 - Cos \n 4 - Tan\n");
			scanf_s("%d", &functionMode);
			double result = functionsPC[functionMode - 1](x);
			printf("Reference value: %0.15lf\n", result);
			for (int i = 0; i < NMax; ++i) {
				double myResult = functions[functionMode - 1](x, eps, i);
				printf("Number of Teylor terms:%d    Calculated result:%0.15lf       ", i,myResult);
				raznica = fabs(myResult - result);
				printf("Difference:%0.15lf\n", raznica);
			}
		}

	}
}
