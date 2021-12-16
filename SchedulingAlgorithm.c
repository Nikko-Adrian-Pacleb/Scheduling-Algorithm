#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Constant variables
const int MIN_JOBS = 3;
const int MAX_JOBS = 10;
const int INTMAX = 2147483647;

void SJN();
void PP();
int getJobNumber();
void getAlgoInput();
void showTable();
int getMinimum();
int getTotal();
int getProcessNumberPP();
int getProcessNumberSJN();
void printGanttChart();

/**
    MAIN FUNCTION
*/
int main(){
    //Variables
    int jobNumber;
    bool loopEnd = false;
    char choice;
    //Creating Menu
    do {
        printf("- - -Scheduling Algorithm- - -\n");
        printf("A: Shortest Job Next\n");
        printf("B: Preemptive Priority\n");
        printf("C: Exit\n\n");
        printf("Enter Choice: ");
        scanf("%c", &choice);
        fflush(stdin);
        //Input Checker
        switch(toupper(choice)){
        case 'A': //Shortest Job Next
            printf("\n");
            SJN();
            break;
        case 'B': //Preemptive Priority
            printf("\n");
            PP();
            break;
        case 'C': //Exit loop and end code
            loopEnd = true;
            break;
        default: //Input Error
            printf("Input Unavailable\n");
        }
    } while (!loopEnd);
    //Exit Message
    printf("Thank You For Using The Program!\n");
    return 0;
}

/**
    Function Name: SJN
    Parameter: none
    Return Type: void
    Function:
        Do the Shortest Job Next algorithm for the data
        Display the output
*/
void SJN(){
    //variables
    int jobNumber = getJobNumber();
    int arrivalTime[jobNumber];
    int burstTime[jobNumber];
    getAlgoInput(jobNumber, arrivalTime, burstTime, NULL);
    int burstTimeCopy[jobNumber];
    for(int i = 0; i < jobNumber; ++i){
        burstTimeCopy[i] = burstTime[i];
    }

    //Algorithm
    int minArrivalTime = getMinimum(arrivalTime, jobNumber);
    int totalBurstTime = getTotal(burstTime, jobNumber);
    int index[totalBurstTime];
    memset(index, -1, totalBurstTime*sizeof(index[0]));
    for(int i = minArrivalTime; i < totalBurstTime + minArrivalTime; ++i){
        int processNumber = getProcessNumberSJN(i, jobNumber, arrivalTime, burstTime);
        index[i - minArrivalTime] = processNumber;
        burstTime[processNumber]--;
    }



    //@Show Data Table
    showTable(jobNumber, arrivalTime, burstTimeCopy, NULL);
    //Print Gantt Chart
    printGanttChart(index, totalBurstTime, minArrivalTime);
}

/**
    Function Name: PP
    Parameter: none
    Return Type: none
    Function:
        Do the Preemptive Priority algorithm for the data
        Display the output
*/
void PP(){
    //variables
    int jobNumber = getJobNumber();
    int arrivalTime[jobNumber];
    int burstTime[jobNumber];
    int priority[jobNumber];
    getAlgoInput(jobNumber, arrivalTime, burstTime, priority);
    int burstTimeCopy[jobNumber];
    for(int i = 0; i < jobNumber; ++i){
        burstTimeCopy[i] = burstTime[i];
    }
    //Algorithm
    int minArrivalTime = getMinimum(arrivalTime);
    int totalBurstTime = getTotal(burstTime);
    int index[totalBurstTime];
    memset(index, -1, totalBurstTime*sizeof(index[0]));
    for(int i = minArrivalTime; i < totalBurstTime + minArrivalTime; ++i){
        int processNumber = getProcessNumberPP(i, jobNumber, arrivalTime, burstTime, priority);
        index[i - minArrivalTime] = processNumber;
        burstTime[processNumber]--;
    }

    //@Show Data Table
    showTable(jobNumber, arrivalTime, burstTimeCopy, priority);
    //Print Gantt Chart
    printGanttChart(index, totalBurstTime, minArrivalTime);
}

/**
    Function Name: getJobNumber
    Parameter: none
    Return Type: int
        return the number of jobs the algorithm will have
    Function:
        Let the user input the number of jobs the algorithm will use
*/
int getJobNumber(){
    int jobNumber;
    printf("(min: 3|max: 10)\n");
    do{
        printf("Enter number of Jobs: ");
        scanf("%d", &jobNumber);
        fflush(stdin);
        if(jobNumber < MIN_JOBS || jobNumber > MAX_JOBS){
            printf("Limit Error!\n");
        }
    } while(jobNumber < MIN_JOBS || jobNumber > MAX_JOBS);
    printf("\n");
    return jobNumber;
}

/**
    Function Name: getAlgoNumber
    Parameter: int, int[], int[], int[]
        - jobNumber - Number of Jobs
        - AT[] - Array for Arrival Time
        - BT[] - Array for Burst Time
        - Priority[] - Array for Priority of Job
    Return Type: int
        return the total of burst time for all jobs
    Function:
        Let the user input the data for the algorithm
        Return the sum of time of the jobs
*/
void getAlgoInput(int jobNumber, int AT[], int BT[], int priority[]){
    //Enter Data for Arrival Time Array
    printf("Arrival Time:\n");
    for(int i = 0; i < jobNumber; ++i){
        printf("Enter Arrival Time for J%d: ", (i + 1));
        scanf("%d", &AT[i]);
        fflush(stdin);
    }
    printf("\n");

    //Enter Data for Burst Time Array
    printf("Burst Time:\n");
    for(int j = 0; j < jobNumber; ++j){
        printf("Enter Burst Time for J%d: ", (j + 1));
        scanf("%d", &BT[j]);
        fflush(stdin);
    }
    printf("\n");

    //Enter Data for Priority Array
    if(priority != NULL){
        printf("(1 - Highest Priority)\n");
        printf("Priority:\n");
        for(int i = 0; i < jobNumber; ++i){
            printf("Enter Priority for J%d: ", (i + 1));
            scanf("%d", &priority[i]);
            fflush(stdin);
        }
        printf("\n");
    }
}

/**
    Function Name: showTable
    Parameter: int, int[], int[], int[]
        - jobNumber - Number of Jobs
        - AT[] - Array for Arrival Time
        - BT[] - Array for Burst Time
    Return Type: void
    Function:
        Show the Table:
            JOB     AT      BT      Priority(optional)
*/
void showTable(int jobNumber, int AT[], int BT[], int priority[]){
    if(priority == NULL){
        printf("Jobs\tArrival Time\tBurst Time\n");
        for(int i = 0; i < jobNumber; ++i){
            printf("J%d\t%d\t\t%d\t\t\n", (i + 1), AT[i], BT[i]);
        }
    }
    else{
        printf("Jobs\tArrival Time\tBurst Time\tPriority\n");
        for(int i = 0; i < jobNumber; ++i){
            printf("%d\t%d\t\t%d\t\t%d\n", (i + 1), AT[i], BT[i], priority[i]);
        }
    }
}

/**
*/
int getProcessNumberPP(int currentTime, int jobNumber, int arrivalTime[], int burstTime[], int priority[]){
    int processNumber;
    int minPriority = INTMAX;
    for(int i = 0; i < jobNumber; ++i){
        if(arrivalTime[i] <= currentTime && minPriority > priority[i] && burstTime[i] != 0){
            minPriority = priority[i];
            processNumber = i;
        }
    }
    return processNumber;
}

/**
*/
int getProcessNumberSJN(int currentTime, int jobNumber, int arrivalTime[], int burstTime[]){
    int processNumber;
    int minBurstTime = INTMAX;
    for(int i = 0; i < jobNumber; ++i){
        if(arrivalTime[i] <= currentTime && burstTime[i] <= minBurstTime && burstTime[i] != 0){
            minBurstTime = burstTime[i];
            processNumber = i;
        }
    }
    return processNumber;
}

/**
*/
void printGanttChart(int index[], int totalBurstTime, int minArrivalTime){
    printf("Gantt Chart\n");
    for(int i = 0; i < totalBurstTime; ++i){
        printf("- ");
    }
    printf("\n");
    int prevValue = -1;
    for(int i = 0; i < totalBurstTime; ++i){
        if(index[i] != prevValue){
            printf("| ");
            prevValue = index[i];
        }
        else{
            printf("  ");
        }
    }
    printf("|");
    printf("\n");
    prevValue = -1;
    for(int i = 0; i < totalBurstTime; ++i){
        if(index[i] != prevValue){
            printf("J%d", (index[i] + 1));
            prevValue = index[i];
        }
        else{
            printf("  ");
        }
    }
    printf("\n");
    prevValue = -1;
    for(int i = minArrivalTime; i < totalBurstTime + minArrivalTime; ++i){
        if(index[i - minArrivalTime] != prevValue){
            printf("%02d", i);
            prevValue = index[i - minArrivalTime];
        }
        else{
            printf("  ");
        }
    }
    printf("%02d", totalBurstTime);
    printf("\n\n");
}

/**
*/
int getMinimum(int array[], int num){
    int min = INTMAX;
    for(int i = 0; i < num; ++i){
        if(min > array[i]) min = array[i];
    }
    return min;
}

/**
*/
int getTotal(int array[], int num){
    int sum = 0;
    for(int i = 0; i <num; ++i){
        sum += array[i];
    }
    return sum;
}
