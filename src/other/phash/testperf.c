/*
----------------------------------------------------------------------------
Test a perfect hash.
By Bob Jenkins.  Public Domain.
----------------------------------------------------------------------------
*/
#ifndef STANDARD
#include "standard.h"
#endif
#ifndef RECYCLE
#include "recycle.h"
#endif
#ifndef PHASH
#include "phash.h"
#endif

/* user directives: perfect hash? minimal perfect hash? input is an int? */
struct hashform
{
  enum {
    NORMAL_HM,                                            /* key is a string */
    INLINE_HM,   /* user will do initial hash, we must choose salt for them */
    HEX_HM,              /* key to be hashed is a hexidecimal 4-byte integer */
    DECIMAL_HM,          /* key to be hashed is a hexidecimal 4-byte integer */
    AB_HM,      /* key to be hashed is "A B", where A and B are (A,B) in hex */
    ABDEC_HM                                /* same as AB_HM, but in decimal */
  } mode;
};
typedef  struct hashform  hashform;

#define MAXKEYLEN  30
struct key
{
  char *kname;
  ub4   klen;
  struct key *knext;
};
typedef  struct key  key;

/* get the list of keys */
static void getkeys(keys, nkeys, textroot, keyroot)
key    **keys;        /* list of all keys */
ub4     *nkeys;       /* number of keys */
reroot  *textroot;    /* get space to store key text */
reroot  *keyroot;     /* get space for keys */
{
  key  *mykey;
  char *mytext;
  mytext = (char *)renew(textroot);
  *keys  = (key *)0;
  *nkeys = (ub4)0;
  while (fgets(mytext, MAXKEYLEN, stdin))
  {
    ub4 i;
    mykey = (key *)renew(keyroot);
    mykey->kname = (ub1 *)mytext;
    mytext = (char *)renew(textroot);
    mykey->klen  = (ub4)(strlen((char *)mykey->kname)-1);
    mykey->knext = *keys;
    *keys = mykey;
    ++*nkeys;
  }
  redel(textroot, mytext);
}


/*
------------------------------------------------------------------------------
Read in the keys, find the hash, and write the .c and .h files
------------------------------------------------------------------------------
*/
void driver(form)
hashform *form;
{
  ub4     nkeys;      /* number of keys */
  key    *keys;       /* head of list of keys */
  key    *mykey;
  reroot *textroot;   /* MAXKEYLEN-character text lines */
  reroot *keyroot;    /* source of keys */

  /* set up memory sources */
  textroot = remkroot((size_t)MAXKEYLEN);
  keyroot  = remkroot(sizeof(key));

  /* read in the list of keywords */
  getkeys(&keys, &nkeys, textroot, keyroot);
  printf("Read in %ld keys\n",nkeys);

  for (mykey=keys; mykey; mykey=mykey->knext)
  {
    ub4 hash;
    ub4 i;
    ub4 a;
    ub4 b;
    switch(form->mode)
    {
    case NORMAL_HM:
      hash = phash(mykey->kname, mykey->klen);  
      break;
    case INLINE_HM:
      hash = PHASHSALT;
      for (i=0; i<mykey->klen; ++i)
      {
	hash = (mykey->kname[i] ^ hash) + ((hash<<26)+(hash>>6));
      }
      hash = phash(hash);
      break;
    case HEX_HM:
      sscanf(mykey->kname, "%lx ", &hash);
      hash = phash(hash);
      break;
    case DECIMAL_HM:
      sscanf(mykey->kname, "%ld ", &hash);
      hash = phash(hash);
      break;
    case AB_HM:
      sscanf(mykey->kname, "%lx %lx ", &a, &b);
      hash = phash(a,b);
      break;
    case ABDEC_HM:
      sscanf(mykey->kname, "%ld %ld ", &a, &b);
      hash = phash(a,b);
      break;
    }
    printf("%8d  %.*s\n", hash, mykey->klen, mykey->kname);
  }

  /* clean up memory sources */
  refree(textroot);
  refree(keyroot);
}


void usage_error()
{
  printf("usage is the same as perfect (which see)\n");
  exit(SUCCESS);
}

int main(argc, argv)
int    argc;
char **argv;
{
  hashform  form;
  char     *c;
  int       mode_given = 0;

  form.mode = NORMAL_HM;

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
	form.mode = NORMAL_HM; break;
      case 'i': case 'I':
	form.mode = INLINE_HM; break;
      case 'h': case 'H':
	form.mode = HEX_HM; break;
      case 'd': case 'D':
	form.mode = DECIMAL_HM; break;
      case 'a': case 'A':
	form.mode = AB_HM; break;
      case 'b': case 'B':
	form.mode = ABDEC_HM; break;
      }
      mode_given = TRUE;
      break;
    case 'm': case 'M':
    case 'p': case 'P':
    case 'f': case 'F':
    case 's': case 'S':
      break;
    default:
      usage_error();
    }
    break;
  default:
    usage_error();
  }

  driver(&form);
  return 1;
}
