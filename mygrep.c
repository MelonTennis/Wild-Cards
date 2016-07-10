#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE      (1024)
#define TRUE 1
#define FALSE 0 

int match(const char* regexp, const char* text);

/*
 * Fill out your functions here 
 */
/*-------------------------------------------------------------------*/
/* match: search for regexp anywhere in text. If a match is found,   */
/*   return TRUE and if not, return FALSE                            */
/*-------------------------------------------------------------------*/
int 
match(const char *regexp, const char *text)
{
  /* fill out this function */
  return FALSE;
}
/*-------------------------------------------------------------------*/
/* is_valid_regexp: check whether regexp is in the correct format    */
/*-------------------------------------------------------------------*/
int 
is_valid_regexp(const char* regexp)
{
  /* fill out this function */
  return FALSE;
}
/*-------------------------------------------------------------------*/
/* grep: searches for regexp in the file 'f', prints each line that  */
/* matches regexp, and returns the number of maching lines	     */
/*-------------------------------------------------------------------*/
/* complete this function */
int 
grep(const char* regexp, FILE* f, const char* filename)
{
  char buf[BUFSIZE];
  int nmatch = 0;
  int n;

  while (fgets(buf, sizeof(buf), f)) {
    n = strlen(buf);
    /* terminate the input string */
    if (n > 0 && buf[n-1] == '\n')
      buf[n-1] = '\0';
    if (match(regexp, buf)) {
      nmatch++;
      printf("%s:%s\n", filename, buf);
    }
  }
  return(nmatch);
}
/*-------------------------------------------------------------------*/
int 
main(int argc, char *argv[])
{
  int i;
  FILE *f;
  int nmatch = 0;

  if (argc < 2) {
    fprintf(stderr, "usage mygrep regexp [file ...]");
    return(EXIT_FAILURE);
  }
  
  /* if the regular expression in the wrong format, complain and stop
     here */
  if (!is_valid_regexp(argv[1])) {
    fprintf(stderr, "wrong regular expression format:%s", argv[1]);
    return(EXIT_FAILURE); 
  }

  /* main grep */
  if (argc == 2) {
    /* we're getting the text from the standard input. Note that we
       use 'stdin' as the second parameter(FILE*). 'stdin' is a vaild
       pointer that points to the standard input. It is automatically
       opened before main() is called.
    */
    nmatch = grep(argv[1], stdin, "stdin");
  } 
  else {
    /* reading one file at a time */
    for (i = 2; i < argc; i++) {
      f = fopen(argv[i], "r");
      if (f == NULL) {
	fprintf(stderr, "can't open %s:", argv[i]);
	continue;
      }
      nmatch += grep(argv[1], f, argv[i]);
      fclose(f);
    }
  }
  printf("Total # of matching lines: %d\n", nmatch);
  return(EXIT_SUCCESS);
}
