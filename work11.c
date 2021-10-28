#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 
#include <fcntl.h> // to open file
#include <unistd.h> // to read and write data w a file

// 
int rand_num(){
	
	// error is to see if open works
  int random = open("/dev/urandom", O_RDONLY);
  
  // if open fails (signified by -1)
  if(random == -1){
	  // print the error (strerror gives the string desc of the error)
    printf("%s\n", strerror(errno));
    return 0;
  }
  
  int num = 0;
  // reads bytes from file into num
  read(random, &num, sizeof(&num));
  return num;
}

int main() {
	
	// creates an array w a size of 10 
   int array0[10];
   int i;
   // to use to track errors
   int error;
	
	// to generate 10 randonm numbers
  printf("Generating random numbers:");
  // loop to print out our first 10 random numbers
  for(i=0; i<10; i++){
	  printf("\n\trandom %d: %u", i, array0[i]);
  }
  printf("\n");

	
  printf("\nWriting numbers to file ...");
  // puts the contents of the array into file.txt, (o_create and o_reader)
  int new = open("file.txt", O_CREAT | O_RDWR, 0644);
  // to print out error message (remember new will be -1 if theres an error)
  if(new == -1){
    printf("Error found: \n %s\n", strerror(errno));
    return 0;
  }
  
  // writes the data into file 'new'
  error = write(new, array0, sizeof(array0));
  // prints out error message
  if(error == -1){
    printf("Error found \n %s\n", strerror(errno));
    return 0;
  }
  printf("\n");

	// now we read from file 'new'
  printf("\nReading numbers from file...");
  // opens text
  new = open("file.txt", O_RDONLY);
  // to see if theres any problems opening our new file
  if(new == -1){
    printf("Error found: \n %s\n", strerror(errno));
    return 0;
  }
  
  // to initialize second array which we will then print to verify the random numbers
  int array1[10];
  // read file / put values into array 1
  
  error = read(new, array1, sizeof(array1));
  // print out error if it aint readable
  if(error == -1){
    printf("Error found : \n %s\n", strerror(errno));
    return 0;
  }

  printf("\n");
  printf("\nVerification that written values were the same\n");
  
  // for loop to print out the contents of the second array
  for(i=0; i<10; i++) {
	  printf("\n\trandom %d: %u", i , array1[i]);
  }
  printf("\n");
}