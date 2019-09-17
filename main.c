#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

double f1(double x);
double f2(double x);
double f3(double x);
double pf1(double x);
double pf2(double x);
double pf3(double x);

char *arg1 = "-help", *arg2 = "-intersect",
     *arg3 = "-count", *arg4 = "-rootTest", *arg5 = "-integralTest";

int iterations = 0;//кол-во итераций при нахождения корня

const double eps1 = 0.0001, eps2 = 0.0001;

bool type(double (*f)(double), double (*g)(double), double a, double b)//определения случая поиска корней
{
    double c = (a + b) / 2;
    double Fc = f(c) - g(c);
    double Fa = f(a) - g(a);
    double Fb = f(b) - g(b);

    bool x = Fa < 0;
    bool y = Fc > (Fa + Fb) / 2;

    return x ^ y;
}

double calculation(double (*f)(double), double border, double *c4, double *c2, int n, double a, double b)
{
    double h = b - a;
    h /= 2 * n;

    double I = *c2 + *c4 + border;
    *c2 += *c4;
    *c4 = 0;

    for (int i = 1; i < 2 * n; i += 2)
    {
        double _new = 2 * f(a + i * h);
        I += 2 * _new;
        *c4 += _new;
    }
    return I * h / 3;
}

double chord(double (*f)(double), double (*g)(double), double a, double b)//смещение границы методом хорд
{
    double Fa = f(a) - g(a);
    double Fb = f(b) - g(b);
    return (a * Fb - b * Fa) / (Fb - Fa);
}

double tangent(double (*f)(double), double (*g)(double), double (*pf)(double), double (*pg)(double), double a, double b, bool t)//смещение границы методом касательных
{
    double d = t ? b : a;
    double Fd = f(d) - g(d);
    double pFd = pf(d) - pg(d);
    return d - Fd / pFd;
}

double root(double (*f)(double), double (*g)(double), double (*pf)(double), double (*pg)(double), double a, double b, double eps)
{
    iterations = 0;
    bool t = type(f, g, a, b);
    while (b - a > eps)
    {
        double c1 = chord(f, g, a, b);
        double c2 = tangent(f, g, pf, pg, a, b, t);
        a = t ? c1 : c2;
        b = t ? c2 : c1;
        iterations++;
    }
    return a;
}

double integral(double (*f)(double), double a, double b, double eps)
{
    int n0 = 20;
    int n = n0;
    double h = (b - a);
    h /= n;

    double p = 1.0 / 15, c2 = 0, c4 = 0;
    double I1 = 0, I2 = 0;
    double border = f(a) + f(b);

    I1 += border;
    bool flag = 0;
    for (int i = 1; i < n; i++)
    {
        double _new = f(a + i * h);
        if (flag)
            c2 += 2 * _new;
        else
            c4 += 2 * _new;
        I1 += (flag ? 2 : 4) * _new;
        flag ^= 1;
    }
    I1 *= h / 3;
    I2 = I1;

    while (n == n0 || p * fabs(I2 - I1) > eps)
    {
        I1 = I2;
        I2 = calculation(f, border, &c4, &c2, n, a, b);
        n *= 2;
    }
    return I2;
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        double a12, a23, a13;
        a12 = root(f1, f2, pf1, pf2, 1.0, 2.0, eps1);
        a23 = root(f2, f3, pf2, pf3, 0.5, 1.0, eps1);
        a13 = root(f1, f3, pf1, pf3, -3.0, -2.0, eps1);

        double I1 = integral(f1, a13, a12, eps2);
        double I2 = integral(f2, a23, a12, eps2);
        double I3 = integral(f3, a13, a23, eps2);
        printf("Square: %f\n", I1 - I2 - I3);
        return 0;
    }

    if ( !strcmp(arg1, argv[1]) )
    {
        printf("-help\n");
        printf("-count\n");
        printf("-intersect\n");
        printf("-rootTest\n");
        printf("-integralTest\n");
    }

    if (!strcmp(arg2, argv[1]) )
    {
        printf("intersection f1 and f2: %f\n", root(f1, f2, pf1, pf2, 1.0, 2.0, eps1));
        printf("intersection f2 and f3: %f\n", root(f2, f3, pf2, pf3, 0.5, 1.0, eps1));
        printf("intersection f1 and f3: %f\n", root(f1, f3, pf1, pf3, -3.0, -2.0, eps1));
    }

    if ( !strcmp(arg3, argv[1]) )
    {
        root(f1, f2, pf1, pf2, 1.0, 2.0, eps1);
        printf("iterations for f1 and f2 %d\n", iterations);
        root(f2, f3, pf2, pf3, 0.5, 1.0, eps1);
        printf("iterations for f2 and f3 %d\n", iterations);
        root(f1, f3, pf1, pf3, -3.0, -2.0, eps1);
        printf("iterations for f1 and f3% d\n", iterations);
    }

    if ( !strcmp(arg4, argv[1]) )
    {
        int nf1, nf2;
        double a, b, eps;
        double(*f)(double);
        double(*pf)(double);
        double(*g)(double);
        double(*pg)(double);
        scanf("%d%d%f%f%f", &nf1, &nf2, &a, &b, &eps);

        switch(nf1) {
        case 1:
            f = f1;
            pf = pf1;
            break;
        case 2:
            f = f2;
            pf = pf2;
            break;
        case 3:
            f = f3;
            pf = pf3;
            break;
        }

        switch(nf2) {
        case 1:
            g = f1;
            pg = pf1;
            break;
        case 2:
            g = f2;
            pg = pf2;
            break;
        case 3:
            g = f3;
            pg = pf3;
            break;
        }
        printf("Intersection for functions %d and %d is %f", nf1, nf2, root(f, g, pf, pg, a, b, eps));
    }

    if (!strcmp(arg5, argv[1]) )
    {
        int num_funck;
        double a, b, eps;
        double(*f)(double);
        scanf("%d%lf%lf%lf", &num_funck, &a, &b, &eps);

        switch(num_funck) {
        case 1:
            f = f1;
            break;
        case 2:
            f = f2;
            break;
        case 3:
            f = f3;
            break;
        }
        printf("%Integral for function %d is %f\n", num_funck, integral(f, a, b, eps));
    }
}
