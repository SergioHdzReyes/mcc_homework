#include <stdio.h>

int main() {
   int last, current, new, i, n;
   n = 9;

   last = 0;
   current = 1;

   for(i = 0; i <= n-2; i++) {
      new = last + current;

      if ((i + 2) == n) {
	printf("%d", new);
      }
      
      last = current;
      current = new;
   }
   
   return 0;
}
