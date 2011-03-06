/*
------------------------------------------------------------------------------
main.c: code to generate code for a hash for perfect hashing.
(c) Bob Jenkins, September 1996, December 1999
You may use this code in any way you wish, and it is free.  No warranty.
I hereby place this in the public domain.

NOTE: (CY)
Broke driver, main and usage_error out of perfect.c to allow building a library

------------------------------------------------------------------------------
*/

#include <string.h>
#include <stdlib.h>

#ifndef STANDARD
#include "standard.h"
#endif
#ifndef LOOKUPA
#include "lookupa.h"
#endif
#ifndef RECYCLE
#include "recycle.h"
#endif
#ifndef PERFECT
#include "perfect.h"
#endif

/*
------------------------------------------------------------------------------
Input/output type routines
------------------------------------------------------------------------------
*/

/* get the list of keys */
static void getkeys(keys, nkeys, textroot, keyroot, form)
key      **keys;                                         /* list of all keys */
ub4       *nkeys;                                          /* number of keys */
reroot    *textroot;                          /* get space to store key text */
reroot    *keyroot;                                    /* get space for keys */
hashform  *form;                                          /* user directives */
{
  key  *mykey;
  char *mytext;
  mytext = (char *)renew(textroot);
  *keys = 0;
  *nkeys = 0;
  while (fgets(mytext, MAXKEYLEN, stdin))
  {
    mykey = (key *)renew(keyroot);
    if (form->mode == AB_HM)
    {
      sscanf(mytext, "%lx %lx ", &mykey->a_k, &mykey->b_k);
    }
    else if (form->mode == ABDEC_HM)
    {
      sscanf(mytext, "%ld %ld ", &mykey->a_k, &mykey->b_k);
    }
    else if (form->mode == HEX_HM)
    {
      sscanf(mytext, "%lx ", &mykey->hash_k);
    }
    else if (form->mode == DECIMAL_HM)
    {
      sscanf(mytext, "%ld ", &mykey->hash_k);
    }
    else
    {
      mykey->name_k = (ub1 *)mytext;
      mytext = (char *)renew(textroot);
      mykey->len_k  = (ub4)(strlen((char *)mykey->name_k)-1);
    }
    mykey->next_k = *keys;
    *keys = mykey;
    ++*nkeys;
  }
  redel(textroot, mytext);
}

/* make the .h file */
static void make_h(blen, smax, nkeys, salt)
ub4  blen;
ub4  smax;
ub4  nkeys;
ub4  salt;
{
  FILE *f;
  f = fopen("phash.h", "w");
  fprintf(f, "/* Perfect hash definitions */\n");
  fprintf(f, "#ifndef STANDARD\n");
  fprintf(f, "#include \"standard.h\"\n");
  fprintf(f, "#endif /* STANDARD */\n");
  fprintf(f, "#ifndef PHASH\n");
  fprintf(f, "#define PHASH\n");
  fprintf(f, "\n");
  if (blen > 0)
  {
    if (smax <= UB1MAXVAL+1 || blen >= USE_SCRAMBLE)
      fprintf(f, "extern ub1 tab[];\n");
    else
    {
      fprintf(f, "extern ub2 tab[];\n");
      if (blen >= USE_SCRAMBLE)
      {
	if (smax <= UB2MAXVAL+1)
	  fprintf(f, "extern ub2 scramble[];\n");
	else
	  fprintf(f, "extern ub4 scramble[];\n");
      }
    }
    fprintf(f, "#define PHASHLEN 0x%lx  /* length of hash mapping table */\n",
	    blen);
  }
  fprintf(f, "#define PHASHNKEYS %ld  /* How many keys were hashed */\n",
          nkeys);
  fprintf(f, "#define PHASHRANGE %ld  /* Range any input might map to */\n",
          smax);
  fprintf(f, "#define PHASHSALT 0x%.8lx /* internal, initialize normal hash */\n",
          salt*0x9e3779b9);
  fprintf(f, "\n");
  fprintf(f, "ub4 phash();\n");
  fprintf(f, "\n");
  fprintf(f, "#endif  /* PHASH */\n");
  fprintf(f, "\n");
  fclose(f);
}

/* make the .c file */
static void make_c(tab, smax, blen, scramble, final, form)
bstuff   *tab;                                         /* table indexed by b */
ub4       smax;                                       /* range of scramble[] */
ub4       blen;                                /* b in 0..blen-1, power of 2 */
ub4      *scramble;                                    /* used in final hash */
gencode  *final;                                  /* code for the final hash */
hashform *form;                                           /* user directives */
{
  ub4   i;
  FILE *f;
  f = fopen("phash.c", "w");
  fprintf(f, "/* table for the mapping for the perfect hash */\n");
  fprintf(f, "#ifndef STANDARD\n");
  fprintf(f, "#include \"standard.h\"\n");
  fprintf(f, "#endif /* STANDARD */\n");
  fprintf(f, "#ifndef PHASH\n");
  fprintf(f, "#include \"phash.h\"\n");
  fprintf(f, "#endif /* PHASH */\n");
  fprintf(f, "#ifndef LOOKUPA\n");
  fprintf(f, "#include \"lookupa.h\"\n");
  fprintf(f, "#endif /* LOOKUPA */\n");
  fprintf(f, "\n");
  if (blen >= USE_SCRAMBLE)
  {
    fprintf(f, "/* A way to make the 1-byte values in tab bigger */\n");
    if (smax > UB2MAXVAL+1)
    {
      fprintf(f, "ub4 scramble[] = {\n");
      for (i=0; i<=UB1MAXVAL; i+=4)
        fprintf(f, "0x%.8lx, 0x%.8lx, 0x%.8lx, 0x%.8lx,\n",
                scramble[i+0], scramble[i+1], scramble[i+2], scramble[i+3]);
    }
    else
    {
      fprintf(f, "ub2 scramble[] = {\n");
      for (i=0; i<=UB1MAXVAL; i+=8)
        fprintf(f, 
"0x%.4lx, 0x%.4lx, 0x%.4lx, 0x%.4lx, 0x%.4lx, 0x%.4lx, 0x%.4lx, 0x%.4lx,\n",
                scramble[i+0], scramble[i+1], scramble[i+2], scramble[i+3],
                scramble[i+4], scramble[i+5], scramble[i+6], scramble[i+7]);
    }
    fprintf(f, "};\n");
    fprintf(f, "\n");
  }
  if (blen > 0)
  {
    fprintf(f, "/* small adjustments to _a_ to make values distinct */\n");

    if (smax <= UB1MAXVAL+1 || blen >= USE_SCRAMBLE)
      fprintf(f, "ub1 tab[] = {\n");
    else
      fprintf(f, "ub2 tab[] = {\n");

    if (blen < 16)
    {
      for (i=0; i<blen; ++i) fprintf(f, "%3d,", scramble[tab[i].val_b]);
    }
    else if (blen <= 1024)
    {
      for (i=0; i<blen; i+=16)
	fprintf(f, "%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,\n",
		scramble[tab[i+0].val_b], scramble[tab[i+1].val_b], 
		scramble[tab[i+2].val_b], scramble[tab[i+3].val_b], 
		scramble[tab[i+4].val_b], scramble[tab[i+5].val_b], 
		scramble[tab[i+6].val_b], scramble[tab[i+7].val_b], 
		scramble[tab[i+8].val_b], scramble[tab[i+9].val_b], 
		scramble[tab[i+10].val_b], scramble[tab[i+11].val_b], 
		scramble[tab[i+12].val_b], scramble[tab[i+13].val_b], 
		scramble[tab[i+14].val_b], scramble[tab[i+15].val_b]); 
    }
    else if (blen < USE_SCRAMBLE)
    {
      for (i=0; i<blen; i+=8)
	fprintf(f, "%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,\n",
		scramble[tab[i+0].val_b], scramble[tab[i+1].val_b], 
		scramble[tab[i+2].val_b], scramble[tab[i+3].val_b], 
		scramble[tab[i+4].val_b], scramble[tab[i+5].val_b], 
		scramble[tab[i+6].val_b], scramble[tab[i+7].val_b]); 
    }
    else 
    {
      for (i=0; i<blen; i+=16)
	fprintf(f, "%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,\n",
		tab[i+0].val_b, tab[i+1].val_b, 
		tab[i+2].val_b, tab[i+3].val_b, 
		tab[i+4].val_b, tab[i+5].val_b, 
		tab[i+6].val_b, tab[i+7].val_b, 
		tab[i+8].val_b, tab[i+9].val_b, 
		tab[i+10].val_b, tab[i+11].val_b, 
		tab[i+12].val_b, tab[i+13].val_b, 
		tab[i+14].val_b, tab[i+15].val_b); 
    }
    fprintf(f, "};\n");
    fprintf(f, "\n");
  }
  fprintf(f, "/* The hash function */\n");
  switch(form->mode)
  {
  case NORMAL_HM:
    fprintf(f, "ub4 phash(key, len)\n");
    fprintf(f, "char *key;\n");
    fprintf(f, "int   len;\n");
    break;
  case INLINE_HM:
  case HEX_HM:
  case DECIMAL_HM:
    fprintf(f, "ub4 phash(val)\n");
    fprintf(f, "ub4 val;\n");
    break;
  case AB_HM:
  case ABDEC_HM:
    fprintf(f, "ub4 phash(a,b)\n");
    fprintf(f, "ub4 a;\n");
    fprintf(f, "ub4 b;\n");
    break;
  }
  fprintf(f, "{\n");
  for (i=0; i<final->used; ++i)
    fprintf(f, final->line[i]);
  fprintf(f, "  return rsl;\n");
  fprintf(f, "}\n");
  fprintf(f, "\n");
  fclose(f);
}


/*
------------------------------------------------------------------------------
Read in the keys, find the hash, and write the .c and .h files
------------------------------------------------------------------------------
*/
static void driver(form)
hashform *form;                                           /* user directives */
{
  ub4       nkeys;                                         /* number of keys */
  key      *keys;                                    /* head of list of keys */
  bstuff   *tab;                                       /* table indexed by b */
  ub4       smax;            /* scramble[] values in 0..smax-1, a power of 2 */
  ub4       alen;                            /* a in 0..alen-1, a power of 2 */
  ub4       blen;                            /* b in 0..blen-1, a power of 2 */
  ub4       salt;                       /* a parameter to the hash function */
  reroot   *textroot;                      /* MAXKEYLEN-character text lines */
  reroot   *keyroot;                                       /* source of keys */
  gencode   final;                                    /* code for final hash */
  ub4       i;
  ub4       scramble[SCRAMBLE_LEN];           /* used in final hash function */
  char      buf[10][80];                        /* buffer for generated code */
  char     *buf2[10];                             /* also for generated code */

  /* set up memory sources */
  textroot = remkroot((size_t)MAXKEYLEN);
  keyroot  = remkroot(sizeof(key));

  /* set up code for final hash */
  final.line = buf2;
  final.used = 0;
  final.len  = 10;
  for (i=0; i<10; ++i) final.line[i] = buf[i];

  /* read in the list of keywords */
  getkeys(&keys, &nkeys, textroot, keyroot, form);
  printf("Read in %ld keys\n",nkeys);

  /* find the hash */
  findhash(&tab, &alen, &blen, &salt, &final, 
	   scramble, &smax, keys, nkeys, form);

  /* generate the phash.h file */
  make_h(blen, smax, nkeys, salt);
  printf("Wrote phash.h\n");

  /* generate the phash.c file */
  make_c(tab, smax, blen, scramble, &final, form);
  printf("Wrote phash.c\n");

  /* clean up memory sources */
  refree(textroot);
  refree(keyroot);
  free((void *)tab);
  printf("Cleaned up\n");
}


/* Describe how to use this utility */
static void usage_error()
{
  printf("Usage: perfect [-{NnIiHhDdAaBb}{MmPp}{FfSs}] < key.txt \n");
  printf("The input is a list of keys, one key per line.\n");
  printf("Only one of NnIiHhDdAa and one of MmPp may be specified.\n");
  printf("  N,n: normal mode, key is any string string (default).\n");
  printf("  I,i: initial hash for ASCII char strings.\n");
  printf("The initial hash must be\n");
  printf("  hash = PHASHSALT;\n");
  printf("  for (i=0; i<keylength; ++i) {\n");
  printf("    hash = (hash ^ key[i]) + ((hash<<26)+(hash>>6));\n");
  printf("  }\n");
  printf("Note that this can be inlined in any user loop that walks\n");
  printf("through the key anyways, eliminating the loop overhead.\n");
  printf("  H,h: Keys are 4-byte integers in hex in this format:\n");
  printf("ffffffff\n");
  printf("This is good for optimizing switch statement compilation.\n");
  printf("  D,d: Same as H,h, except in decimal not hexidecimal\n");
  printf("  A,a: An (A,B) pair is supplied in hex in this format:\n");
  printf("aaa bbb\n");
  printf("  B,b: Same as A,a, except in decimal not hexidecimal\n");
  printf("This mode does nothing but find the values of tab[].\n");
  printf("*A* must be less than the total number of keys.\n");
  printf("  M,m: Minimal perfect hash.  Hash will be in 0..nkeys-1 (default)\n");
  printf("  P,p: Perfect hash.  Hash will be in 0..n-1, where n >= nkeys\n");
  printf("and n is a power of 2.  Will probably use a smaller tab[].");
  printf("  F,f: Fast mode.  Generate the perfect hash fast.\n");
  printf("  S,s: Slow mode.  Spend time finding a good perfect hash.\n");

  exit(SUCCESS);
}


/* Interpret arguments and call the driver */
/* See usage_error for the expected arguments */
int main(argc, argv)
int    argc;
char **argv;
{
  int      mode_given = FALSE;
  int      minimal_given = FALSE;
  int      speed_given = FALSE;
  hashform form;
  char    *c;

  /* default behavior */
  form.mode = NORMAL_HM;
  form.hashtype = STRING_HT;
  form.perfect = MINIMAL_HP;
  form.speed = SLOW_HS;

  /* let the user override the default behavior */
  switch (argc)
  {
  case 1:
    break;
  case 2:
    if (argv[1][0] != '-')
    {
      usage_error();
      break;
    }
    for (c = &argv[1][1]; *c != '\0'; ++c) switch(*c)
    {
    case 'n': case 'N':
    case 'i': case 'I':
    case 'h': case 'H':
    case 'd': case 'D':
    case 'a': case 'A':
    case 'b': case 'B':
      if (mode_given == TRUE) 
	usage_error();
      switch(*c)
      {
      case 'n': case 'N':
	form.mode = NORMAL_HM;  form.hashtype = STRING_HT; break;
      case 'i': case 'I':
	form.mode = INLINE_HM;  form.hashtype = STRING_HT; break;
      case 'h': case 'H':
	form.mode = HEX_HM;     form.hashtype = INT_HT; break;
      case 'd': case 'D':
	form.mode = DECIMAL_HM; form.hashtype = INT_HT; break;
      case 'a': case 'A':
	form.mode = AB_HM;      form.hashtype = AB_HT; break;
      case 'b': case 'B':
	form.mode = ABDEC_HM;   form.hashtype = AB_HT; break;
      }
      mode_given = TRUE;
      break;
    case 'm': case 'M':
    case 'p': case 'P':
      if (minimal_given == TRUE)
	usage_error();
      switch(*c)
      {
      case 'p': case 'P':
	form.perfect = NORMAL_HP; break;
      case 'm': case 'M':
	form.perfect = MINIMAL_HP; break;
      }
      minimal_given = TRUE;
      break;
    case 'f': case 'F':
    case 's': case 'S':
      if (speed_given == TRUE)
	usage_error();
      switch(*c)
      {
      case 'f': case 'F':
	form.speed = FAST_HS; break;
      case 's': case 'S':
	form.speed = SLOW_HS; break;
      }
      speed_given = TRUE;
      break;
    default:
      usage_error();
    }
    break;
  default:
    usage_error();
  }

  /* Generate the [minimal] perfect hash */
  driver(&form);

  return SUCCESS;
}
