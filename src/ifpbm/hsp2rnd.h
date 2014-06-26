/**
 * HSP2 RNG Simulator (LCG)
 * written by gocha, feel free to redistribute
 */


#ifndef HSP2RND_H
#define HSP2RND_H


#include <stdlib.h>


/* RNG variables */
typedef struct TagHsp2Rnd
{
  unsigned int x;
  unsigned int a;
  unsigned int c;
} Hsp2Rnd;

Hsp2Rnd* hsp2RndCreate(unsigned int seed);
void hsp2RndDelete(Hsp2Rnd* rnd);
unsigned int hsp2RndSeed(Hsp2Rnd* rnd, unsigned int seed);
unsigned int hsp2Rnd(Hsp2Rnd* rnd, unsigned int max);

/* create new RNG */
Hsp2Rnd* hsp2RndCreate(unsigned int seed)
{
  Hsp2Rnd* rnd = NULL;

  rnd = (Hsp2Rnd*) malloc(sizeof(Hsp2Rnd));
  if(rnd)
  {
    rnd->x = seed;
    rnd->a = 0x000343fd;
    rnd->c = 0x00269ec3;
  }
  return rnd;
}

/* delete RNG */
void hsp2RndDelete(Hsp2Rnd* rnd)
{
  if(rnd)
  {
    free(rnd);
  }
}

/* set RNG seed (randomize) */
unsigned int hsp2RndSeed(Hsp2Rnd* rnd, unsigned int seed)
{
  unsigned int oldSeed = 0;

  if(rnd)
  {
    oldSeed = rnd->x;
    rnd->x = seed;
  }
  return oldSeed;
}

/* generate randomness (rnd) */
unsigned int hsp2Rnd(Hsp2Rnd* rnd, unsigned int max)
{
  unsigned int ret = 0;

  if(rnd)
  {
    rnd->x = (rnd->x * rnd->a) + rnd->c;
    ret = ((rnd->x >> 16) & 0x7fff) % max;
  }
  return ret;
}


#endif
