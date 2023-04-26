/* runcmd - run command converting arguments to Cygwin paths
 * Copy runcmd.exe to ls.exe and then execute as ./ls -l C:\cygwin.
 * This gives ls -l /, ensuring that standard Cygwin permissions are displayed.
 * runcmd.cc should be compiled with mingw32, eg. x86_64-w64-mingw32-gcc.
 */
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#if DBG
#include <stdio.h>
#endif

int main(int argc, char* argv[])
{
  char cmd[102400], arg0[1024];
  const char *prog, *BASHEXE;
  int i;

  strncpy (arg0, argv[0], sizeof(arg0));
  prog= basename (arg0);

  BASHEXE= getenv ("BASHEXE");
  if (!BASHEXE) BASHEXE= "C:\\cygwin\\bin\\bash.exe";
  strncpy (cmd, BASHEXE, sizeof(cmd)-1);

  strncat (cmd, " -c \"arg=(", sizeof(cmd)-1);
  for (i=1; i<argc; i++) {
    if (i>1) strncat (cmd, " ", sizeof(cmd)-1);
    strncat (cmd, "'", sizeof(cmd)-1);
    strncat (cmd, argv[i], sizeof(cmd)-1);
    strncat (cmd, "'", sizeof(cmd)-1);
  }
  strncat (cmd, "); for ((i=0; i<${#arg[*]}; i++)); do case \\\"${arg[$i]}\\\" in [A-Z]:/*|*\\\\\\\\*) arg[$i]=$(/usr/bin/cygpath \\\"${arg[$i]}\\\");; esac; done; ", sizeof(cmd)-1);
#if DBG
  strncat (cmd, "set -x; ", sizeof(cmd)-1);
#endif

  strncat (cmd, "exec /usr/bin/", sizeof(cmd)-1);
  strncat (cmd, prog, sizeof(cmd)-1);
  strncat (cmd, " \\\"${arg[@]}\\\"\"", sizeof(cmd)-1);

#if DBG
  fprintf (stderr, "+ %s\n", cmd);
  fflush(stderr);
#endif
  int ret= system (cmd);
  if (ret==-1) perror (prog);
  return ret;
}
