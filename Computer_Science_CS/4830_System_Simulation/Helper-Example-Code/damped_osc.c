#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{  double t       = 0.0; 	  // time in seconds
   double delta_t = 0.01;	  // time step in seconds

   double m       = 0.1;	  // mass of bob weight (kg)
   double c	  = 0.1; 	  // no damping
   double k	  = 1.0;	  // 1.0 N/m

   double	  x_pos = 10.0;   // Position in meters
   double	  x_vel =  0.0;   // Velocity
   double	  x_acc =  0.0;   // Acceleration 

   while (t < 10.0)
     { printf("%lf %lf %lf %lf\n", t, x_acc, x_vel, x_pos);
       x_acc = -((c * x_vel) + (k * x_pos)) / m;
       x_vel = x_vel + delta_t * x_acc;
       x_pos = x_pos + delta_t * x_vel;
       t     = t + delta_t;
     }
}
