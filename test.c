#include <stdio.h>
#pragma waring(disable:4996)

int main() {
    double a,b,c;
    double g;
    scanf("%lf %lf %lf", &a,&b,&c);
    g = (a + b + c) / 3;
    if (g >= 91.5) printf("A");
    else if (g >= 85.5) printf("B");
    else if (g >= 80.5) printf("C");
    else printf("F");

    if (a == 100)
}