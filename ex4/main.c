#include "ex4.h"
#include <stdio.h>

int main() {
    Collatz(7);
    Collatz(6);
    ProofCollatzUntill(6);
    Fermat(2, 20);
    Fermat(3, 100);
    printf("%d\n", IsDividedBy3Rec(123232323231));
    printf("%d\n", IsDividedBy3Rec(123232323232));
    printf("%d\n", IsDividedBy3Iter(123232323231));
    printf("%d\n", IsDividedBy3Iter(123232323232));
    printf("%d\n", FindCommonDigit(1113355579999, 22222444466668888));
    printf("%d\n", FindCommonDigit(1113555777777, 22222344446666899));
    printf("%d\n", FindCommonDigit(111222333444555, 111222333444555));
    printf("%d\n", CountDigit(125827620123, 2));
    printf("%d\n", CountDigit(123432123432, 7));
    PrintReverse(123456789);
    PrintReverse(111222333);
    return 0;
}
