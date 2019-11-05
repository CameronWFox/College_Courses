/******************************************************************************
 * rng.c
 *
 * Assorted routines for multiple, independent pseudo-random number
 * generation.
 *
 * John C. Gallagher
 * Department of Computer Science and Engineering
 * Wright State University
 * john.gallagher@wright.edu (Primary maintainer)
 *
 * Gregory R. Kramer
 * Department of Computer Science and Engineering
 * Wright State University
 * gkramer@cs.wright.edu  (Address no longer active)
 *
 * Last Revised on 08/21/2017
 *
 * SPECIAL NOTES
 * -------------
 * This is the code for jcg's random number generator library.  The API 
 * all of the user callable routines is provided in "rnd.h", which should
 * also be #included in any user code that is linking to this library.
 * Those API definitions will not be repeated here.
 *
 * Note that most people will never need to mess with the contents of this
 * file.  Rather, they should compile it, link it, and access user-level
 * routines via the API defined in rng.h.
 *
 * Note that this code DOSE contain a few simple examples of using the RNG
 * in various ways.  If you uncomment the line defining RNG_TEST_BLOC 
 * right after this comment header, you can compile rng.c not as a library,
 * but rather as a stand-alone test program.  Assuming that rng.h is in 
 * the same directory, the following will compile this in test mode:
 *
 * cc rng.c -lm -o rng_test
 *
 * It will put the executable in "rng_test"
 *
 *****************************************************************************/


// The next line should remain commented unless you want to compile this
// library in "test mode".  Test mode compile the library as an executable with
// a main() routine that exercises many of the features of the API.
// Normally you'll leave the next line commented and compile this as a object
// file you'd link with your own code.

//#define RNG_TEST_BLOC

 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "rng.h"

/******************************************************************************
 *                  PRIVATE DATA AND PROTOTYPE DECLARATIONS
 *
 *  As a user of the library, you'll NEVER need to directly modify any of the 
 *  declarations in this "private" block unless you want to change the very 
 *  nature of the RNGs.  Don't do that unless you know what you're doing.
 *****************************************************************************/

/******************************************************************************
 * Constants needed by the random number generation algorithm.  These are for
 * the ran1() function defined in Numerical Recipes in C.  An explanation 
 * for what they are and how they are used can be found there.
 *****************************************************************************/

#define RNG_IA 16807
#define RNG_IM 2147483647
#define RNG_AM (1.0/RNG_IM)
#define RNG_IQ 127773
#define RNG_IR 2836
#define RNG_NTAB 32
#define RNG_NDIV (1+(RNG_IM-1)/RNG_NTAB)
#define RNG_EPS  1.2e-7
#define RNG_RNMX (1.0-RNG_EPS)

/******************************************************************************
 * The RNG struct which stores the data needed for a single random
 * number generator. These fields should only be accessed through the
 * random number generation API functions.  As a user, never directly
 * access any of it.
 *****************************************************************************/

struct RNG
{
  int  use_dev_random;
  long idum;
  long iv[RNG_NTAB];
  long iy;
};

/******************************************************************************
 * Forward declaration of a private function that returns the next value from 
 * the specified random number generator. Used only internally by specific 
 * random number generation functions that ARE callable by the user.  As a 
 * private function, this prototype is NOT exposed in rng.h
 *****************************************************************************/

double _rng_next_val(struct RNG *rng);



/******************************************************************************
 * Another forward declaration of a private function.  This one is a utility 
 * function used by rng_gaussian. For more info see 'Numerical Recipes in C',
 * specifically the chapter on random number generation.
 *****************************************************************************/

void _rng_generate_normals(struct RNG *rng, double *gX1, double *gX2, double
                          *gSX);



/******************************************************************************
 * THIS IS EVIL -- look away unless you're JCG
 * The end of rng.h gives some prototypes for some REALLY ancient backwards
 * compatibility routines.  Those routines used to use a single "global" RNG
 * state.  This variable will contain that state for those really old routines.
 * As stated in rng.h.  Unless you actually are JCG, you never need to concern
 * yourself with this.  Really... just back away slowly and pretend that this
 * particular global variable isn't even here.
 ******************************************************************************/

struct RNG _ran1_rng;

/******************************************************************************
 * THIS IS EVIL
 * Basically I'm defining a file handle variable that is global to all the 
 * code in this source code file / compilation unit.  This file handle will 
 * be bound to /dev/urandom and used whenever one of the private routines
 * needs to generate random bytes from /dev/urandom instead of from a seeded
 * pseudo-number generator [ran1].  Since all routines in THAT usage model
 * would draw from the same source (/dev/urandom), there is no need to have
 * more than one handle that is global to all routines.
 ******************************************************************************/

FILE *fp;

/******************************************************************************
 *                        PUBLIC AND PRIVATE FUNCTIONS
 *
 * Following are is all the code for public (user callable) and private 
 * (called only internally to this source code segment).  The commenting here
 * gets a little sparse.  Private functions begin with '_'.  Public functions
 * begin with 'rng_'.  OLD compatibility functions begin with 'RAN1_'
 * All but the private functions have prototypes in rng.h
 *****************************************************************************/


struct RNG *rng_create(void)
{
    struct RNG *rng = NULL;

    rng = malloc(sizeof(struct RNG));
    if (rng == NULL)
    {
        fprintf(stderr, "Error in rng_create: unable to allocate memory for rng struct\n");
        return NULL;
    }
    rng_set_seed(rng, time(NULL));
    rng->use_dev_random = 0;
    return rng;
}

struct RNG *rng_create_system(void)
{
    struct RNG *rng = NULL;

    rng = malloc(sizeof(struct RNG));
    if (rng == NULL)
    {
        fprintf(stderr, "Error in rng_create: unable to allocate memory for rng struct\n");
        return NULL;
    }
    rng_set_seed(rng, time(NULL));
    rng->use_dev_random = 1;
    fp = fopen("/dev/urandom", "r");
    return rng;
}


void rng_destroy(struct RNG *rng)
{
  if (rng != NULL)
    { if (rng->use_dev_random == 1) fclose(fp);
      free(rng);
    }
  rng = NULL;
}

double rng_gaussian(struct RNG *rng, double mean, double variance)
{
  double gX1, gX2, gSX;
  void _rng_generate_normals();
  _rng_generate_normals(rng, &gX1, &gX2, &gSX);
  return(sqrt(variance) * gX1 + mean);
}

double _rng_next_val(struct RNG *rng)
{
  int i,j;
  long k;
  float temp;

  unsigned long int random_value = 0;
  
  if (rng == NULL)
    return 0.0;

  // Check to see if we're using the OLD behavior, if so... do it...
  if (rng->use_dev_random == 0)
     {  /* Do random number magic */
       if (rng->idum <= 0 || !rng->iy)
         {
           if (-(rng->idum) < 1)
	     rng->idum = 1;	/* Initialize */
           else rng->idum = -(rng->idum);
           for (j=RNG_NTAB+7;j>=0;j--)
	     {
	       k=rng->idum/RNG_IQ;
	       rng->idum=RNG_IA*(rng->idum-k*RNG_IQ)-RNG_IR*k;
	       if (rng->idum < 0)
	         rng->idum += RNG_IM;
	       if (j < RNG_NTAB)
	         rng->iv[j] = rng->idum;
	     }
           rng->iy=rng->iv[0];
         }
       k=rng->idum/RNG_IQ;
       rng->idum=RNG_IA*(rng->idum-k*RNG_IQ)-RNG_IR*k;
       if (rng->idum < 0)
         rng->idum += RNG_IM;
       j=rng->iy/RNG_NDIV;
       rng->iy=rng->iv[j];
       rng->iv[j] = rng->idum;
       if ((temp=RNG_AM*rng->iy) > RNG_RNMX)
         return RNG_RNMX;
       else return temp;
      }
    
  // Check to see if we're using the NEW behavior, if so... do it...
  if (rng->use_dev_random == 1)
    { for (i=0; i < sizeof(random_value); i++)
       { random_value <<= 8;
         random_value |= fgetc(fp);
       }
     return ((double)random_value/(double)ULONG_MAX);
    
    }

  return(0.0);
}

void _rng_generate_normals(struct RNG *rng, double *gX1, double *gX2, double *gSX)
{
  double v1,v2,s,d;
  double rng_uniform();

  /* This is a private function that should never be called by
     a user */
  do
   {
     v1 = rng_uniform(rng, -1.0,1.0);
     v2 = rng_uniform(rng, -1.0,1.0);
     s = v1 * v1 + v2 * v2;
   }
  while (s >= 1.0);
  *gSX = -2 * log(s);
  d = sqrt(*gSX/s);
  *gX1 = v1 * d;
  *gX2 = v2 * d;
}

int rng_set_seed(struct RNG *rng, long seed)
{
    if (seed <= 0)
    {
        fprintf(stderr, "Error in rng_set_seed: seed argument is %ld\n", seed);
        return 1;
    }
    rng->idum = -1 * seed;
    rng->iy = 0;
    return 0;
}

double rng_uniform(struct RNG *rng, double min, double max)
{
    if (min >= max)
    {
        fprintf(stderr, "Error in rng_uniform: the argument min is >= argument max\n");
        return 0.0;
    }
    return min + ((max - min) * _rng_next_val(rng));
}

double rng_uniform01(struct RNG *rng)
{
  return rng_uniform(rng, 0.0, 1.0);
}

/*****************************************
 * Old RAN1 Style Compatibility Functions
 * (depreciated, not for use in new code)
 *****************************************/

void RAN1_SeedRandom(long seed)
{ rng_set_seed(&_ran1_rng, seed);}

double RAN1_SimpleRandom()
{ return rng_uniform01(&_ran1_rng);}

double RAN1_UniformRandom(double l, double u)
{ return rng_uniform(&_ran1_rng, l, u);}

double RAN1_GaussianRandom(double m, double v)
{ return rng_gaussian(&_ran1_rng, m, v); }


#ifdef RNG_TEST_BLOC

/**************
 * TEST BLOC
 **************/

int main()
{ RNG *foo_ran1;    // This will point to a RNG that uses the ran1 algorithm
  RNG *foo_system;  // This will point to a RNG that uses /dev/urandom
  int i;
  

  // Create two separate RNGs.  One uses the ran1 algorithm, the other uses
  // /dev/urandom to construct desired values from random bytes sourced
  // from that device.
  
  foo_ran1   = rng_create();
  foo_system = rng_create_system();

  printf("\n\n");
  printf("Generate numbers using the RAN1 number generator\n");
  printf("------------------------------------------------\n");
  printf("Five uniform random numbers in the range [0.0 .. 1.0]\n");
  for (i=0; i < 5; i++)
      printf("%f ", rng_uniform01(foo_ran1));
  printf("\n");
  printf("Five Gaussian random numbers\n");
  for (i=0; i < 5; i++)
      printf("%f ", rng_gaussian(foo_ran1, 0.0, 1.0));
  printf("\n\n");

  printf("Generate numbers using /dev/urandom generator\n");
  printf("------------------------------------------------\n");
  printf("Five uniform random numbers in the range [0.0 .. 1.0]\n");
  for (i=0; i < 5; i++)
      printf("%f ", rng_uniform01(foo_system));
  printf("\n");
  printf("Five Gaussian random numbers\n");
  for (i=0; i < 5; i++)
      printf("%f ", rng_gaussian(foo_system, 0.0, 1.0));
  printf("\n\n");


  return(0);
}

#endif

/* EOF */
  

