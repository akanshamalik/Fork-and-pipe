/* 

 * File:   assign1.c

 * Author: Akansha

 *

 * Parent sends the offset to the children and children process the file

 */



#include <stdio.h>

#include <stdlib.h>

#include<time.h>

#include<errno.h>

#include<unistd.h>

#define MAXVALUES 1000



void error(const char *msg)

{
   perror(msg);

    exit(1);

}



int main(int argc, char** argv) {

    

    FILE *fp;   // file pointer to the main porcess.

    
   static const char FILENAME[] = "medium.txt";

    

    //integer pointer that will act as an array to hod every number in 
the text file.

    

    int *data = malloc(sizeof(int)* MAXVALUES);

    

//Integers variable that will be used to point to various loops.

    int* i = malloc(sizeof(int));

    


    // Used to track the elapsed time

    struct timespec begin, end;

    

    int status = 0;     // variable used to return the status of an 
exiting child process

    

    int userInput;     // variable use to store the user input for the 
number of process.(1, 2, or 4);

    

    int* arraySplit = malloc(sizeof(int));  // integer pointer that will 
act as the max number of times each process may read from its file.


    // various files descriptors used to send the offsets to the 
children and receive the children's calculated values.

    

    int fd5_SEND[2];

    int fd5_RECEIVE[2];

    int fd6_SEND[2];

    int fd6_RECEIVE[2];

    int fd7_SEND[2];

    int fd7_RECEIVE[2];

  int fd8_SEND[2];

    int fd8_RECEIVE[2];

    

    pipe(fd5_SEND);

    pipe(fd5_RECEIVE);

    pipe(fd6_SEND);

    pipe(fd6_RECEIVE);

    pipe(fd7_SEND);


 pipe(fd8_SEND);

    pipe(fd8_RECEIVE);

    

    //long integers pinter that will store the offset to be sent to the 
children through the pipe.

    

    unsigned long int *offsetCalc1 = malloc(sizeof(unsigned long int));

    unsigned long int *offsetCalc2 = malloc(sizeof(unsigned long int));

    unsigned long int *offsetCalc3 = malloc(sizeof(unsigned long int));


  unsigned long int *offsetCalc4 = malloc(sizeof(unsigned long int));

    

    // long intergers pointer that will store the offset value of each 
of the process.

    unsigned long int* processValue1 = malloc(sizeof(unsigned long 
int));

    unsigned long int* processValue2 = malloc(sizeof(unsigned long 
int));

    unsigned long int* processValue3 = malloc(sizeof(unsigned long 
int));

    unsigned long int* processValue4 = malloc(sizeof(unsigned long 
int));

    


//integers used to store the values from the test vile in each child 
process.

    int valueGet1 = 0;

    int valueGet2 = 0;

    int valueGet3 = 0;

    int valueGet4 = 0;

    

    // long integer pointer that will store the final calculated result

    

    unsigned long int* combinedFinalValue2 = malloc(sizeof(unsigned long 
int));


    fp = fopen(FILENAME, "r");

    

    if(fp == NULL)

    {

        error("Unable to read the file. Exiting system now");

    }

 //scan each line and store the value inside the data pointer

    // continue till it reach the end of the file. the formate 
specifier.



   

    

    printf("\n Starting the processus");

    /**

     *  R. this read from a file pointed by the file pointer fp

  * @param fp : the file pointer

     * @param "%d": the format the date in the file is in

     * @param &data[*i] : the memory address where we want to save that 
value read.

     * @return 

     */

    while(fscanf(fp, "%d", &data[*i])==1)

        *i = *i + 1;

    

 printf("\nThe array has been filled");

    printf("\nThe size of the file :%ld\n", ftell(fp));

    char buffer[100];

    do{

        printf("how many process would you like to create? (1, 2, or 
4)\n\n ");

        fgets(buffer, 99,stdin);

        sscanf(buffer,"%d", &userInput);

    }while(!((userInput ==1)||(userInput ==2)||(userInput ==4)));

    

 clock_gettime(CLOCK_REALTIME, &begin);

    *arraySplit = *i/userInput;     // now the arraySplit value is  used 
for child process reading. Whatever i was

    

    // write to all the pipe depending on the entered user value

    if(userInput ==1)

    {

        //that single child process will start to read form the very 
beginning, so its offset should be 0 bytes

        *offsetCalc1 = 0;

  printf("\n1st offset: %ld\n", *offsetCalc1);



        //The 1stPipe is then written to with the offset value

        write(fd5_SEND[1], offsetCalc1, sizeof(offsetCalc1));



    }

    else if (userInput ==2)

    {

        *offsetCalc1 = 0;

   printf("\nThis is OFFSETCALC1: %lx\n", *offsetCalc1);



        *offsetCalc2 = (sizeof(int) * (MAXVALUES/2));

        printf("\n offsetcalc2: %ld\n", *offsetCalc2);



        // The pipes are then written to with the offset values



        write(fd5_SEND[1], offsetCalc1, sizeof(offsetCalc1));


        write(fd6_SEND[1], offsetCalc2, sizeof(offsetCalc2));

    }

    

    else if(userInput == 4)

    {

        *offsetCalc1 = 0;

        printf("\n offsetcalc1: %ld\n", *offsetCalc1);

        // offset value should be 1/4 of the bytes of the total bytes 
size of the file.

        *offsetCalc2 = (sizeof(int) *(MAXVALUES/4));

  printf("offsetcalc2: %ld\n", *offsetCalc2);



        //The third offset value need to be 2 times the bytes of the 
offsetCacl2

        *offsetCalc3 = (*offsetCalc2 * 2);

        printf("\this is offsetc3: %ld\n", *offsetCalc3);



        // the fourth offset value need to be 3 time the bytes of 
offsetcalc2.

        *offsetCalc4 = (*offsetCalc2 * 3);

  printf("offsetcalc4: %ld\n", *offsetCalc4);



        //the pipes are then written to with the offset values

        write(fd5_SEND[1], offsetCalc1, sizeof(offsetCalc1));

        write(fd6_SEND[1], offsetCalc2, sizeof(offsetCalc2));

        write(fd7_SEND[1], offsetCalc3, sizeof(offsetCalc3));

        write(fd8_SEND[1], offsetCalc4, sizeof(offsetCalc4));



    }

fseek(fp, 0, SEEK_SET);     // set the file pointer back to the 
beginning

    pid_t pids2[userInput +1];

    pid_t wpid;

    

    //set i back to 0

    *i = 0;

    printf("\n Program continues \n\n");

     if(userInput ==1)

{

        // the parent will never enter this if statement; it will 
continue in

        //Creates a child process, store to id , and if the id == 
0,(meaning its a child process) then enter the if condition is 
satisfied.

        if(pids2[0] = fork() == 0)

        {

            // read the offsetcalc1 value from the pipe read end.

            read(fd5_SEND[0], offsetCalc1, sizeof(offsetCalc1));

            //the file pointer will move to the beginning of the file. 
R. offsetCalc1 is 0

            fseek(fp, *offsetCalc1, SEEK_SET);

  //offsetCalck1 value is no longer needed so free the memory

            free(offsetCalc1);



            //if the file is empty

            if (fp == NULL) {

                error("File Empty or non-exiting. Exiting system now");

            }

            while(fscanf(fp, "%d", &valueGet1) == 1) {



   if (*i >= *arraySplit) {

                    // i is no longer need free

                    free(i);

                    free(arraySplit);

                    break;

                }

                *processValue1 += valueGet1;

                //increment i each loop

                *i = *i +1;

    }

            write(fd5_RECEIVE[1], processValue1, sizeof(processValue1));

            printf("Child 1 sent value: %ld\n,", processValue1);

            free(processValue1);

            printf("Child 1 exited\nChild 1 process Finish\n\n");

            exit(0);



       
        }

     }

    if(userInput ==2)

    {

        // the parent will never enter this if statement; it will 
continue in

        //Creates a child process, store to id , and if the id == 
0,(meaning its a child process) then enter the if condition is 
satisfied.

        if(pids2[0] = fork() == 0)

        {

            FILE *fp1 = fopen(FILENAME, "r");

            read(fd5_SEND[0], offsetCalc1, sizeof(offsetCalc1));

  //the file pointer will move to the beginning of the file.

            fseek(fp1, 0, SEEK_SET);                                    
// <---

            //offsetCalck1 value is no longer needed so free the memory

            free(offsetCalc1);



            //if the file is empty

            if (fp1 == NULL) {


                error("File Empty or non-exiting. Exiting system now");

            }

            while(fscanf(fp1, "%d", &valueGet1) == 1) {

                if (*i >= *arraySplit) {

                    // i is no longer need free

                    free(i);

                    free(arraySplit);

                    break;

                }

   *processValue1 += valueGet1;

                //increment i each loop

                *i = *i +1;

            }

            write(fd5_RECEIVE[1], processValue1, sizeof(processValue1));

            printf("Child 1 sent value: %ld\n,", processValue1);

            free(processValue1);

            printf("Child 1 exited\nChild 1 process Finish\n\n");


  fclose(fp1);

            exit(0);



        }

        if(pids2[1] = fork() == 0)

        {

            FILE *fp2;

            fp2 = fopen(FILENAME, "r");

            read(fd6_SEND[0], offsetCalc2, sizeof(offsetCalc2));


 //the file pointer will move to the beginning of the file.

            fseek(fp2, *offsetCalc2, SEEK_SET);

            //offsetCalck1 value is no longer needed so free the memory

            free(offsetCalc2);



            //if the file is empty

            if (fp2 == NULL) {

                error("File Empty or non-exiting. Exiting system now");



 }

            while(fscanf(fp2, "%d", &valueGet2) == 1) {

                if (*i >= *arraySplit) {

                    // i is no longer need free

                    free(i);

                    free(arraySplit);

                    break;

                }

                *processValue2 += valueGet2;                    // <---R 
to improve on


       //increment i each loop

                *i = *i +1;

            }

            write(fd6_RECEIVE[1], processValue2, sizeof(processValue2));

            printf("Child 2 sent value: %ld\n,", processValue2);

            free(processValue2);

            printf("Child 2 exited\nChild 2 process Finish\n\n");

            fclose(fp2);



      exit(0);



        }

   }

    if(userInput ==4)

    {

         // the parent will never enter this if statement; it will 
continue in

        //Creates a child process, store to id , and if the id == 
0,(meaning its a child process) then enter the if condition is 
satisfied.

        if(pids2[0] = fork() == 0)


  {

            FILE *fp1;

            fp1 = fopen(FILENAME, "r");     // take mem loc

            read(fd5_SEND[0], offsetCalc1, sizeof(offsetCalc1));

            //the file pointer will move to the beginning of the file.

            fseek(fp1, 0, SEEK_SET);

            //offsetCalck1 value is no longer needed so free the memory

            free(offsetCalc1);


            //if the file is empty

            if (fp1 == NULL) {

                error("File Empty or non-exiting. Exiting system now");

            }

            while(fscanf(fp1, "%d", &valueGet1) == 1) {

                if (*i >= *arraySplit) {

                    // i is no longer need free

                    free(i);

  free(arraySplit);

                    break;

                }

                *processValue1 += valueGet1;

                //increment i each loop

                *i = *i +1;

            }

            write(fd5_RECEIVE[1], processValue1, sizeof(processValue1));



 printf("Child 1 sent value: %ld\n,", processValue1);

            free(processValue1);

            printf("Child 1 exited\nChild 1 process Finish\n\n");

            fclose(fp1);

            exit(0);



        }

        if(pids2[1] = fork() == 0)

        {

            FILE *fp2;

            fp2 = fopen(FILENAME, "r");

            read(fd6_SEND[0], offsetCalc2, sizeof(offsetCalc2));

            //the file pointer will move to the beginning of the file.

            fseek(fp2, *offsetCalc2, SEEK_SET);

            //offsetCalck1 value is no longer needed so free the memory

            free(offsetCalc2);


    //if the file is empty

            if (fp2 == NULL) {

                error("File Empty or non-exiting. Exiting system now");

            }

            while(fscanf(fp2, "%d", &valueGet2) == 1) {

                if (*i >= *arraySplit) {

                    // i is no longer need free

                    free(i);

                    free(arraySplit);


                    break;

                }

                *processValue2 += valueGet2;

                //increment i each loop

                *i = *i +1;

            }

            write(fd6_RECEIVE[1], processValue2, sizeof(processValue2));

            printf("Child 2 sent value: %ld\n,", processValue2);


            free(processValue2);

            printf("Child 2 exited\nChild 2 process Finish\n\n");

            fclose(fp2);

            exit(0);



        }

        if(pids2[2] = fork() == 0)

        {

            FILE *fp3;

            fp3 = fopen(FILENAME, "r");

            read(fd7_SEND[0], offsetCalc3, sizeof(offsetCalc3));

            //the file pointer will move to the beginning of the file.

            fseek(fp3, *offsetCalc3, SEEK_SET);

            //offsetCalck1 value is no longer needed so free the memory

            free(offsetCalc3);



            //if the file is empty


      if (fp3 == NULL) {

                error("File Empty or non-exiting. Exiting system now");

            }

            while(fscanf(fp3, "%d", &valueGet3) == 1) {

                if (*i >= *arraySplit) {

                    // i is no longer need free

                    free(i);

                    free(arraySplit);

                    break;

                }

                *processValue3 += valueGet3;

                //increment i each loop

                *i = *i +1;

            }

            write(fd7_RECEIVE[1], processValue3, sizeof(processValue3));

            printf("Child 3 sent value: %ld\n,", processValue3);

            free(processValue3);


            printf("Child 3 exited\nChild 3 process Finish\n\n");

            fclose(fp3);

            exit(0);



        }

        if(pids2[3] = fork() == 0)

        {

            FILE *fp4;

            fp4 = fopen(FILENAME, "r");


    read(fd8_SEND[0], offsetCalc4, sizeof(offsetCalc4));

            //the file pointer will move to the beginning of the file.

            fseek(fp4, *offsetCalc4, SEEK_SET);

            //offsetCalck1 value is no longer needed so free the memory

            free(offsetCalc4);



            //if the file is empty

            if (fp4 == NULL) {



     error("File Empty or non-exiting. Exiting system now");

            }

            while(fscanf(fp4, "%d", &valueGet4) == 1) {

                if (*i >= *arraySplit) {

                    // i is no longer need free

                    free(i);

                    free(arraySplit);

                    break;

                }


           *processValue4 += valueGet4;

                //increment i each loop

                *i = *i +1;

            }

            // write the final process value to a new pipe that will 
send the value back to the parent

            write(fd8_RECEIVE[1], processValue4, sizeof(processValue4));

            printf("Child 4 sent value: %ld\n,", processValue4);

            free(processValue4);



            printf("Child 4 exited\nChild 3 process Finish\n\n");

            fclose(fp4);

            exit(0);



        }

    }

    

    

    // -------------------------------Parents now read values and output 
final sum -------------------------------------

    if(userInput ==1)

    {

        //the parent reads the value from the pipe

        read(fd5_RECEIVE[0], processValue1, sizeof(processValue1));

    }

    

    else if(userInput ==2)

   
    {

        read(fd5_RECEIVE[0], processValue1, sizeof(processValue1));

        read(fd6_RECEIVE[0], processValue2, sizeof(processValue2));

    }

    else if(userInput ==4)

    {

        read(fd5_RECEIVE[0], processValue1, sizeof(processValue1));

        read(fd6_RECEIVE[0], processValue2, sizeof(processValue2));

        read(fd7_RECEIVE[0], processValue3, sizeof(processValue3));

        read(fd8_RECEIVE[0], processValue4, sizeof(processValue4));

  }

    

    if(userInput ==1)

        *combinedFinalValue2 = *processValue1;

    else if(userInput ==2)

        *combinedFinalValue2= *processValue1 + *processValue2;

    else if (userInput ==4)

        *combinedFinalValue2= *processValue1 + *processValue2 + 
*processValue3 + *processValue4;


 free(processValue1);

    free(processValue2);

    free(processValue3);

    free(processValue4);

    

    printf("Combined final Value: %ld\n\n", *combinedFinalValue2);

    free(combinedFinalValue2);


    if(end.tv_nsec < begin.tv_nsec)

    {

        end.tv_nsec += 1000000000;

        end.tv_sec--;

    }

    clock_gettime(CLOCK_REALTIME,&end);

    printf("This is the elapsed time: %ld.%09ld\n\n",(long)(end.tv_sec - 
begin.tv_sec),end.tv_nsec - begin.tv_nsec);

    return (EXIT_SUCCESS);

}

