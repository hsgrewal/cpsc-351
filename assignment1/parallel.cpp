#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
  /* Parallel downloader: The parent forks n children (where n
   * is the number of URLs in urls.txt). The children call run
   * the wget program to download from their respective urls.
   * The parent then calls wait n times (once for each child).
   */

  // Open the urls.txt file
  ifstream urlFile("urls.txt");

  // URL buffer
  string urlBuffer;

  // Process id
  pid_t pid;

  // Counter to keep track of the number of children forked
  int counter = 0;

  // Check for an error opening file
  if(!urlFile.is_open())
  {
    perror("Failed to open the file");
    exit(-1);
  }

  // Read the file
  while(!urlFile.eof())
  {
    // Read URL into the buffer
    urlFile >> urlBuffer;

    // If user does not want to exit, fork a child to begin download
    if(!urlFile.eof())
    {
      // Create a child
      pid = fork();

      // Increment the counter
      counter++;

      // Check for error
      if(pid < 0)
      {
        perror("fork");
        exit(-1);
      }

      // Child code
      if(pid == 0)
      {
        // Call execlp() system call and pass it arguments for wget program.
        // Pass the URL as a character array to execlp as well
        // Error check the execlp() system call
        if(execlp("/usr/bin/wget", "wget", urlBuffer.c_str(), NULL) < 0)
        {
          perror("execlp");
          exit(-1);
        }
      }
    }
  }

  // Close the file
  urlFile.close();

  // Loop to call wait for every child created
  for(int i = 0; i < counter; i++)
  {
    // Error check the wait() system call
    if(wait(NULL)<0)
    {
      perror("wait");
      exit(-1);
    }
  }

  return 0;
}
