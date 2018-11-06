#include <stdio.h>
#include <string.h>

int factorial(int n) {
    char db[] = "%d%c";
    printf(db, n, 10);
    int ret;
    if (n < 2)
      ret = 1;
    else {
      ret = spawn factorial(n-1);
      sync;
      ret *= n;
    }
    return ret;
}

int main() {
    char result[] = "INPUT: %d%cRESULT: %d";
    int input = 16;
    auto a = factorial(input);
    printf(result, input, 10, a);
    return 0;
}
