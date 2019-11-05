/******************************************************************************
 * rng.h
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
 * This code is a standardized API for generating random numbers from uniform
 * and Gaussian distributions.  The basic API was developed in the 1990's in 
 * support of neural network and evolutionary algorithm programs.  Later it
 * was extended to allow for "multiple independent" pseudo-random number 
 * generators by moving all RNG state into a struct, multiples of which could
 * be allocated and used as one might require.  Later, in 2017, additional 
 * code was added to allow one to continue to use the same API in legacy 
 * code, but derive the random numbers from the system provided /dev/urandom
 * device.  These later additions were, admittedly, something of a hack.
 * They do, however, allow one to employ a more modern entropy-driven RNG
 * while making only minor changes to the huge amount of legacy code that 
 * depends on this library of routines.
 *
 * Currently the library contains TWO separate random number generators.
 *
 * The first is the ran1() generators from the book "Numerical Recipes in C"
 * which is based on a shuffling algorithm from Bays and Durham as described
 * by Knuth in:
 *
 * Knuth, D.E. 1981, Semi numerical Algorithms, 2nd ed., vol. 2 of
 * The Art of Computer Programming (Reading, MA: Addison-Wesley)
 *
 * Naturally the above is pretty old and in many ways has been supplanted 
 * with more modern offerings.  However, use of the "ran1()" generator
 * at least gives identical operation (for the same RNG seed) across multiple
 * architectures and is not horribly taxing to resources.  These were both
 * important concerns early on.
 *
 * The second is the /dev/urandom device which is present on most modern 
 * Unix-like operating systems.  Using the variants of the library that use
 * /dev/urandom remove the ability for the code to work identically on all 
 * architectures / OSes AND removes the ability for the user to retain the
 * RNG seed so that sequences can be repeated later.  Also note that 
 * differences between /dev/random and /dev/urandom on specific machines
 * and specific OSes are NOT universally the same.  We chose to link to 
 * /dev/urandom on the assumption that generally it is the one that is 
 * non-blocking (doesn't wait on generation of "sufficient hardware entropy"
 * when it feels it hasn't collected enough).  The choice of /dev/urandom
 * is "correct" in most cases.  It's your responsibility, however, to change
 * the binding to /dev/random if the semantics of the devices are different
 * for you.
 *
 *****************************************************************************/

#ifndef RNG_H
#define RNG_H

/******************************************************************************
 * Forward declaration of the RNG struct. The member variables of the
 * RNG struct are private and should never be accessed directly.
 *****************************************************************************/

//struct RNG;
typedef struct RNG RNG;


/******************************************************************************
 * DESCRIPTION:  struct RNG *rng_create() and struct RNG *rng_create_system()
 *
 * The rng_create() function creates a new random number generator which is
 * seeded to the current system time and returns a pointer to its RNG struct.
 * If you use rng_create() you'll be specifying the use of rng1() from 
 * "Numerical Recipes in C" (see notes at beginning of this file).  This 
 * call will automatically seed the RNG using the system clock, but you may
 * set your own seed (or reseed at any time) with any value you like with other
 * routines in this API.
 *
 * The rng_create_system() function creates a new random number generator 
 * which gets random bytes from the /dev/urandom system device.  Naturally, 
 * you do not need to "seed" this device.  Further, any calls in this library
 * that attempt to seed or reseed the RNG when it's getting it randomness
 * from /dev/urandom will simply do nothing.  The RNG based on /dev/urandom
 * will seed and reseed itself automatically.  The "do nothing" behavior for
 * seeding routines when /dev/urandom is employed is intended to allow
 * legacy code to run without modification.  The "needless calls" that are 
 * still there just "do nothing".  There is no need to rewrite or recompile
 * code.
 *
 * EXCEPT FOR THE USE OF rng1() vs. /dev/urandom and the differences in 
 * seeding calls noted above, random number generators using EITHER method 
 * are accessed using exactly the same API routines using exactly the same
 * bindings.  Converting "legacy" code to use the /dev/urandom generator 
 * requires ONLY that all instances of rng_create() be changed to 
 * rng_create_system().  Literally everything else in the code being updated
 * can stay the same.
 *
 * NOTE: When no longer needed, all RNG structs should be destroyed via the 
 *       rng_destroy() function to return their memory to the system.  We 
 *       wouldn't want to create memory leaks, would we?
 *
 * RETURN VALUE
 *
 * On success, the both functions return a pointer to an initialized RNG struct.
 * Otherwise, NULL is returned and an error message is printed to stderr
 * indicating the nature of the error.
 *
 *****************************************************************************/

struct RNG *rng_create();
struct RNG *rng_create_system();


/******************************************************************************
 * DESCRIPTION:  void rng_destroy()
 *
 * The rng_destroy function frees the memory used by the random number
 * generator <rng> and sets <rng> to NULL.  It works on any pointer to a RNG
 * struct regardless of which create routine [rng_create() or 
 * rng_create_system()] had been used to allocate it.
 *
 * The <rng> argument must point to an RNG struct obtained by a previous call
 * to rng_create() or rng_create_system()  Passing it a pointer to some other 
 * block of memory will likely result in bad things.
 *
 *****************************************************************************/

void rng_destroy(struct RNG *rng);



/******************************************************************************
 * DESCRIPTION: rng_gaussian(struct RNG *rng, double mean, double variance)
 *
 * The rng_gaussian function returns a random value from a Gaussian
 * distribution with mean <mean> and variance <variance> from the random
 * number generator <rng>.
 *
 * The <rng> argument must point to an RNG struct obtained by a previous
 * call to rng_create.
 *
 * RETURN VALUE
 *
 * The function returns a random value from a Gaussian distribution with 
 * mean <mean> and variance <variance> from the random number generator <rng>.
 *
 * HISTORY
 *
 *****************************************************************************/

double rng_gaussian(struct RNG *rng, double mean, double variance);



/******************************************************************************
 * DESCRIPTION  int rng_set_seed(struct RNG *rng, long seed)
 *
 * The rng_set_seed function seeds the random number generator <rng> to the
 * specified seed value <seed>.
 *
 * The <rng> argument must point to an RNG structure obtained by a previous
 * call to rng_create() or rng_create_system().  Note that if the RNG structure
 * was created by rng_create_system(), "setting the seed" will essentially 
 * do nothing, as one doesn't seed /dev/urandom.  Calling this function is
 * causes no harm if the RNG object was created with rng_create_system(), but
 * it doesn't accomplish anything either ;)
 *
 * The <seed> argument must be > 0
 *
 * RETURN VALUE
 *
 * On success, the function returns 0. Otherwise, 1 is returned and an error
 * message is printed to stderr indicating the nature of the error.
 *
 * HISTORY
 *
 * [03/03/2004] Changed the return type from void to int so that the
 * function can return a value indicating error or success. Also, modified
 * the function to detect error conditions and print error messages to
 * stderr. - Greg Kramer
 *****************************************************************************/

int rng_set_seed(struct RNG *rng, long seed);



/******************************************************************************
 * DESCRIPTION: double rng_uniform(struct RNG *rng, double min, double max)
 *
 * The rng_uniform function returns a uniformly distributed random value in
 * the range <min> to <max> exclusive of the end points from the random number
 * generator <rng>.
 *
 * The <rng> argument must point to an RNG struct that was obtained from a
 * previous call to rng_create.
 *
 * The <min> argument must be less than the <max> argument.
 *
 * RETURN VALUE
 *
 * On success, the function returns a uniformly distributed random value in
 * the specified range. On error, the function returns 0.0 and prints an
 * error message to stderr indicating the nature of the error.
 *
 * HISTORY
 *
 * [03/03/2004] Modified the function to error check the values of min and
 * max and to print an error message if the values are illegal. - Greg Kramer
 *
 *****************************************************************************/

double rng_uniform(struct RNG *rng, double min, double max);



/******************************************************************************
 * DESCRIPTION: double rng_uniform01(struct RNG *rng)
 *
 * The rng_uniform01 function returns a uniformly distributed random value
 * in the range (0,1) exclusive of the endpoints from the random number
 * generator <rng>.
 *
 * The <rng> argument must point to an RNG struct that was obtained by a
 * previous call to rng_create.
 *
 * RETURN VALUE
 *
 * The function returns a uniformly distributed value in the range (0,1) from
 * <rng>
 *
 * HISTORY
 *
 *****************************************************************************/

double rng_uniform01(struct RNG *rng);


/******************************************************************************
 * There was an even OLDER version of this library used by JCG in the distant 
 * past.  For compatibility with this truly ancient code, prototypes for those
 * long ago deprecated functions are here.  Unless you're actually JCG, you'll
 * never need these.  So feel free to ignore them, but please don't delete them
 * either ;)                                         
 *****************************************************************************/
void   RAN1_SeedRandom(long seed);
double RAN1_SimpleRandom();
double RAN1_UniformRandom(double l, double u);
double RAN1_GaussianRandom(double m, double v);

#endif
/* EOF */

