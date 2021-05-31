#include <stdio.h>
#include <math.h>

double valor_absoluto(double num)
{
  if (num < 0) {
    return num * -1;
  }

  return num;
}

double raizCuadrada(int num)
{
  double margen = 0.000001;
  double estimacion = 1.0;

  while (valor_absoluto((estimacion * estimacion) - num) >= margen)
    {
      double cociente = num / estimacion;
      double promedio = (cociente + estimacion) / 2.0;
      estimacion = promedio;
    }

  return estimacion;
}

int main(void)
{
  int num_fib = 9;
  double res = 0.0;

  res = ((1/raizCuadrada(5))*pow(((1+raizCuadrada(5))/2), num_fib)) - ((1/raizCuadrada(5))*pow(((1 - raizCuadrada(5))/2), num_fib));
  printf("%f", res);
  
  return res;
}
