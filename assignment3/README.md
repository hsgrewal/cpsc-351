# Assignment 3

## Goals
1. To appreciate the benefits and challenges of the pipe IPC mechanism
2. To experiment with POSIX pipes
3. To use pipe(), read(), and write() system calls in order to implement
    parent-child process IPC
4. Employ the pipe IPC mechanism to solve a real-world problem
5. To implement a program for computing the hashes of files using multiple
    hash algorithms

### Hash
*Hash algorithms* map large data sets of variable length to data sets of a
fixed length. For example, the contents of a 1GB file may be hashed into a
single 128-bit integer. Many hash algorithms exhibit an important property
called an avalanche effect – slight changes in the input data trigger
significant changes in the hash value.

Hash algorithms are often used for verifying the integrity of files downloaded
from the web. For example, the website hosting the file posts the hash of the
file computed using the MD5 hash algorithm. The user then verifies the
integrity of the downloaded file, by computing its hash using the MD5 algorithm
and comparing the hash against the hash posted on the website. The download is
successful only if the two values match.

In this assignment, a program for computing a hash of the file using MD5,
SHA1, SHA224, SHA256, SHA384, and SHA512 hashing algorithms is implemented.
The program takes the name of the target file as a command line argument, and
then does the following:
1. Check to make sure the file exists
2. Create two pipes
3. Create a child process
4. The parent transmits the name of the file to the child (over the first pipe)
5. The child receives the name of the file and computes the hash of the file
    using the MD5 algorithm (using Linux program md5sum)
6. The child transmits the computed hash to the parent (over the second pipe),
    and terminates
7. The parent receives the hash, prints it, and calls wait()
8. Repeat the same process starting with step 3, but using algorithms
    SHA1...SHA512
9. The parent terminates after all hashes have been computed

#### Build & Execute
Use `make` to build
Run `./multihash <TARGET FILE NAME>`

**NOTE:** Target file whose the hash value is to be calculated must
be in same the directory as the code
