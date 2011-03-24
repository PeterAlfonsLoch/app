/* 
 * libepp-nicbr 1.10 on 2010-14-10 2009 Registro.br
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 1. Redistribution of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY REGISTRO.BR ``AS IS AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIE OF FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL REGISTRO.BR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
/* $Id: shepp.cpp 1009 2009-03-04 20:23:23Z rafael $ */
/** @file shepp.cpp
 *  @brief EPP command-line shell client
 */
#include <cstdio>
#include <csignal>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "DomainFunctions.H"
#include "ContactFunctions.H"
#include "BrOrgFunctions.H"
#include "PollFunctions.H"
#include "AsnFunctions.H"
#include "IpNetworkFunctions.H"

/// SIGINT signal handler
static void sig_int(int signo)
{
  printf("Aborted\n");
  exit(0);
}

/// Prints info when program starts
void welcome_message()
{
  printf("Welcome to ");
  about();
  printf("Type 'help' for available commands.\n");
}

/// Calls command-comparable_array init function and customize readline if necessary
void init_readline()
{
  init_commands();
  // Workaround: Limiting input on iterative sessions due to
  // obscure readline/terminal limitations
#ifndef LIMITED_READLINE
  if (isatty(STDIN_FILENO)) {
    rl_num_chars_to_read = MAX_TERM_DEV_LINE_SIZE;
  }
#endif //LIMITED_READLINE
}

/// Run a command line
/**
   @param line   command line to be run
   @return zero on success, non-zero on failure
 */
int execute(char *line)
{
  // get the first word (command name)
  stringa args = SheppStrUtil::parse_line(line);

  // args will be is_empty() if any word exceed MAX_WORD_LENGTH
  if (args.is_empty()) {
    return 1;
  }

  const command* cmd = find_command(args[0]);

  if (cmd == NULL) {
    fprintf(stderr, "Unknown command: %s\n", args[0]);
    return 1;
  }

  // commands that require raw command-line input
  if (args[0] == "runxml") {
    string rawcmd(line);
    rawcmd = rawcmd.substr(args[0].get_length());
    while (whitespace(rawcmd[0])) {
      rawcmd = rawcmd.substr(1);
    }

    if (rawcmd == "") {
      // read input
      printf("Enter XML code. Escape character is '^]'.\n");
      string unit;
      getline(cin, unit, (char)29);
      rawcmd += unit;
    }

   args.clear();
    args.add(rawcmd);
  } else {
    args.remove_at(args.begin());
  }

  return ((*(cmd->function))(args));
}

/// prints usage instructions
int usage()
{
  printf("usage: shepp [server[:port]] [-p passphrase]\n");
  printf("       shepp -f inputFile\n");
  printf("       shepp -help\n");
  return 0;
}

/// main
int main(int argc, char **argv)
{
  //SIGINT signal handler
  signal(SIGINT, sig_int);

  //SIGALRM signal handler
  signal(SIGALRM, sig_alrm);

  //ignoring SIGPIPE for write (W. Richard Stevens - Unix Network
  //Programming v1 - pages 132 and 133)
  signal(SIGPIPE, SIG_IGN);

  //input
  if (argc > 1) {
    stringa args;
    for (int i = 1; i < argc; i++) {
      args.add((string) argv[i]);
    }

    if (args[0] == "-f") {
      if (args.size() == 1) {
	printf("no input file given.\n");
	return usage();
      }

      if (executeInputFile(args[1]) == -1) {
	return usage();
      }

      args.remove_at(args.begin());
      args.remove_at(args.begin());
    } else if (args[0].substr(0,1) != "-") {
      cmd_server(args);
      args.remove_at(args.begin());
    } else {
      return usage();
    }
    
    while (!args.is_empty()) {
      if (args[0] == "-p") {
	//passphrase
	args.remove_at(args.begin());
	if (args.is_empty()) {
	  return usage();
	}
	_passphrase = args[0];
	args.remove_at(args.begin());
      } else {
	return usage();
      }
    }
  }

  init_readline();
  welcome_message();

  char *input_line;
  char *last_line = (char *) malloc(1 * sizeof(char));
  last_line[0] = '\0';

  while (true) {
    input_line = readline("shepp> ");

    //exit on Ctrl-D
    if (input_line == NULL) {
      break;
    }

    char *trimmed_input = SheppStrUtil::trim(input_line);

    if (*trimmed_input != '\0') {
      // adds current line to history if different from the previous one
      int biggest_len = strlen(trimmed_input) > strlen(last_line) ? 
	strlen(trimmed_input) : strlen(last_line);

      if (strncmp(last_line, trimmed_input, biggest_len) != 0) {
	add_history(trimmed_input);

	// copy current trimmed line to last executed line
	free(last_line);
	last_line = (char *) malloc(sizeof(char) * strlen(trimmed_input) + 1);
	strncpy(last_line, trimmed_input, strlen(trimmed_input) + 1);
      }

      execute(trimmed_input);
    }

    free(input_line);
  }

  stringa dummy;
  cmd_quit(dummy);

  return 0;
}
