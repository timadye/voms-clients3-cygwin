#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
  char sh[1024];
  const char* arg[1024]= {"C:\\cygwin\\bin\\bash.exe", sh};
  int i;
  strncpy (sh, getenv("FAKEBIN"), sizeof(sh));
  strncat (sh, "\\", sizeof(sh));
  strncat (sh, argv[0], sizeof(sh));
  strncat (sh, ".sh", sizeof(sh));
  for (i=1; i<argc; i++) arg[i+1]= argv[i];
  fprintf (stderr, "+ ");
  for (i=0; i<argc+1; i++) fprintf (stderr, "%s%c", arg[i], i<argc?' ':'\n');
  fflush(stderr);
  int ret= execv (arg[0], (char* const*)arg);
  perror(arg[0]);
  return ret;
}
