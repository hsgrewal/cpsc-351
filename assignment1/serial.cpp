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
  /* Serial downloader: Fork a child for each URL. The child uses
   * the execlp() system call to replace its code with wget program.
   * The parent calls wait() and waits until the child exits.
   * The parent forks another child and repeats until all files
   * are downloaded.
   */

  // Open the urls.txt file
  ifstream urlFile("urls.txt");

  // URL buffer
  string urlBuffer;

  // Process id
  pid_t pid;

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

    // If not at the end of the file, download the file
    if(!urlFile.eof())
    {
      // Create a child
      pid = fork();

      // Error check the child creation
      if(pid < 0)
      {
        perror("fork");
        exit(-1);
      }

      // Child code
      if(pid == 0)
      {
        // Use execlp() system call to replace child code with wget program
        // Pass URL as array of characters as an argument
        // Error check the execlp() system call
        if(execlp("/usr/bin/wget", "wget", urlBuffer.c_str(), NULL) < 0)
        {
          perror("execlp");
          exit(-1);
        }
      }

      // Parent code
      else
      {
        // Call wait() and wait for child to finish
        // Error check the wait
        if(wait(NULL)<0)
        {
          perror("wait");
          exit(-1);
        }
      }
    }
  }

  // Close the file
  urlFile.close();

  return 0;
}
