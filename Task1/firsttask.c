#include<stdio.h>
#define print_var(x) printf(#x " is %d", x )

int main()
{
    int n1 = 10;
    print_var(n1);
    print_var(42);
    const n2 = 20;
    print_var(n2);
    return 0;
}
