#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{
  // The command buffer
  string cmdBuff;

  // The ID of the child process
  pid_t pid;

  // Loop to keep running until the user types "exit"
  do
  {
    // Prompt the user to enter the command
    cerr << "cmd>";

    // Load command to buffer
    cin >> cmdBuff;

    // Proceed if user does not want to exit
    if(cmdBuff != "exit")
    {
      // Create a child
      pid = fork();

      // Error check to make sure child was successfully forked
      if (pid < 0)
      {
        perror("fork");
        exit(-1);
      }

      // Code of child
      if(pid == 0)
      {
        // Call execlp() and give it the command typed by user as argument
        // execlp takes an array of character so change string to characters
        // Error check the execlp() system call
        if(execlp(cmdBuff.c_str(), cmdBuff.c_str(), NULL)<0)
        {
          perror("execlp");
          exit(-1);
        }
      }

      // Parent code
      // Wait for child to finish executing
      else
      {
        // Error check the wait() system call
        if(wait(NULL)<0)
        {
          perror("wait");
          exit(-1);
        }
      }
    }
  }

  // Loop again since user did not type in "exit"
  while(cmdBuff != "exit");

  return 0;	
}
