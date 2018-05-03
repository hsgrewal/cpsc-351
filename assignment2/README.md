# Assignment 2

## Goals
1. To demonstrate IPC principles in action
2. To develop greater appreciation of shared memory, message passing, and
    signal IPC mechanisms
3. To implement a multi-process application
4. To use message passing, shared memory, and signals IPC mechanisms in order
    to implement cooperation between processes
5. To develop a practical application where the sender process transfers
    files to receiver process

## Sender
This program implements the process that sends files to the receiver process.
The sender is invoked using `./sender <FILE NAME>`, where `sender` is the
name of the executable and `<FILE NAME>` is the name of the file to be
transferred. When invoked, the sender performs the following sequence of steps:

1. Attach to the shared memory segment and connect to the message queue both
    previously set up by the receiver process
2. Send the name of the file specified at the command line to the receiver
    process using the message queue. The message shall contain a field called
    fileName specifying the name of the file to to be sent
3. Read a predefined number of bytes from the specified file, and store these
    bytes in the shared memory segment
4. Send a message to the receiver (using the message queue). The message shall
    contain a field called size indicating how many bytes were read from the
    file and are currently stored in the shared memory segment
5. Wait on the message queue to receive a message from the receiver confirming
    successful retrieval of data from shared memory and saving of data to the
    file
6. Go back to step 3. Repeat until the whole file has been transferred
7. When the end of the file is reached, send a message to the receiver with
    the size field set to 0. This will tell the receiver that the sender has
    nothing more to send
8. Close the file, detach the shared memory segment, print the number of
    bytes sent, and exit.

## Receiver
This program implements the process that receives files from the sender
process. The program is invoked using `./recv` where `recv` is the name
of the executable. When invoked, the receiver program performs the following
sequence of steps:

1. Setup a shared memory segment and a message queue
2. Wait on the message queue to receive a message containing the name of
    the file about to be transferred. The received message shall contain a
    field called fileName specifying the name of the file to be transferred
3. The program shall wait on the message queue to receive a message from the
    sender program. The received message shall contain a field called size
    specifying the number of bytes the sender has saved in the shared memory
    segment that are ready to be read by the receiver.
4. If size is not 0, then read size number of bytes from shared memory and
    save them to the file with the same name as the file received in step 2
    with recv appended to the end of the file name. For example, if the sender
    sent a file named song.mp3, the receiver saves the received file as
    song.mp3 recv. Finally, send a message to the sender acknowledging
    successful reception and saving of data and go back to step 3
5. Otherwise, if size is 0, then close the file, deallocate the shared memory
    segment, deallocate the message queue, print the number of bytes received,
    and exit

#### Build & Execution
Use `make` command to build the code

Execute in this order:
1. `./recv`
2. `./sender <FILE NAME>` where `<FILE NAME>` is the name of the file to be
    transferred. Note: the file to be transferred must be in same the
    directory as the code.
