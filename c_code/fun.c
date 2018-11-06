#include <stdio.h>
#include <string.h>

char pdb[] = "%d->%d %c";
int cache[32];

int fib(int n) {
  int ret;
  ret = cache[n];
  char db[] = "spawned a new thread for fib(%d) -> %d %c";
  printf(db, n, ret, 10);
  if (ret == 0) {
    if (n < 2)
      ret = 1;
    else {
      int a;
      int b;
      a = spawn fib(n - 1);
      b = spawn fib(n - 2);
      sync;
      ret = a + b;
    }
  }
  cache[n] = ret;
  return ret;
}


int main() {
  int i = 0;
  printf(pdb, 31, fib(31), 10);
  for (i = 0; i<32; i+=1)
    printf(pdb, i, cache[i], 10);
  return 0;
}
