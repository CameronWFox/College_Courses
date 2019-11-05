#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{  double t       = 0.0; 	// time in seconds
   double delta_t = 0.01;	// time step in seconds
   double k;			// drain constant
   double L       = 10.0;	// initial height of column
   double g	  = 9.8;	// Gravitational Constant in meters/sec^2
   double A	  = 10.0;   	// Bottom of tank area, 10 m^2
   double a	  = 0.01;       // Drain hole, 1 cm^2


  k = (a/A) * sqrt(2.0 * g);

   while (L > 0.01)
      { printf("%lf %lf\n", t, L);
        L = L - delta_t * k * sqrt(L);
        t = t + delta_t;
      }
}

