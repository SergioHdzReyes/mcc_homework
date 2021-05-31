#include <stdio.h>

int main() {
   int last, current, new, i, n;
   n = 9;

   last = 0;
   current = 1;
   
   printf("%d %d ", last, current);

   for(i = 1; i <= n-2; i++) {
      new = last + current;
      printf("%d ", new);
      
      last = current;
      current = new;
   }
   
   return 0;
}
