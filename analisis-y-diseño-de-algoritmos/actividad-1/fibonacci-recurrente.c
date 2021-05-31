#include <stdio.h>

int fibonacci_item(int n)
{
    if (n <= 1)
        return n;
    
    return fibonacci_item(n - 1) + fibonacci_item(n - 2);
}

int main()
{
    int n = 9;
    printf("%d", fibonacci_item(n));
    getchar();

    return 0;
}
