#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#if DBG
#include <stdio.h>
#endif

int main(int argc, char* argv[])
{
  char cmd[10240]= "C:\\cygwin\\bin\\bash.exe ";
  int i;
  const char* FAKEBIN= getenv("FAKEBIN");
  if (FAKEBIN) {
    strncat (cmd, FAKEBIN, sizeof(cmd));
    strncat (cmd, "\\", sizeof(cmd));
  }
  strncat (cmd, argv[0], sizeof(cmd));
  strncat (cmd, ".sh", sizeof(cmd));
  for (i=1; i<argc; i++) {
    strncat (cmd, " ", sizeof(cmd));
    strncat (cmd, argv[i], sizeof(cmd));
  }
#if DBG
  fprintf (stderr, "+ %s\n", cmd);
  fflush(stderr);
#endif
  int ret= system (cmd);
  if (ret) perror (argv[0]);
  return ret;
}
