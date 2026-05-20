#include<stdio.h>
#include<stdlib.h>

/*
    Structure definition
*/

typedef struct{
    char name[30];
    int id;
    float marks;
}record;

/* Function declarations */

void writeToFile(record r[], int n, const char *filename);

void createSeekPositions(const char *filename, long pos[], int *count);

void displayRecord(long position, const char *filename);

int main(){

    int n;

    printf("Enter number of records: ");
    scanf("%d", &n);

    if(n <= 0){
        printf("Invalid number\n");
        return 0;
    }

    /* Array of structures */

    record r[n];

    /* Read records */

    for(int i=0; i<n; i++){

        printf("\nEnter details of student %d\n", i+1);

        printf("Enter name: ");
        scanf("%s", r[i].name);

        printf("Enter ID: ");
        scanf("%d", &r[i].id);

        printf("Enter marks: ");
        scanf("%f", &r[i].marks);
    }

    /* Store records in ASCII format */

    writeToFile(r, n, "records.txt");

    /*
        Array to store seek positions

        pos[0] -> beginning of record 1
        pos[1] -> beginning of record 2
        etc.
    */

    long pos[100];

    int count = 0;

    /* Create array of positions */

    createSeekPositions("records.txt", pos, &count);

    /* Display all positions */

    printf("\n--- Seek Positions ---\n");

    for(int i=0; i<count; i++){

        printf("Record %d starts at byte %ld\n",
               i+1, pos[i]);
    }

    int m;

    printf("\nEnter record number to display: ");
    scanf("%d", &m);

    if(m < 1 || m > count){

        printf("Invalid record number\n");

        return 0;
    }

   

    displayRecord(pos[m-1], "records.txt");

    return 0;
}



void writeToFile(record r[], int n, const char *filename){

    FILE *fp = fopen(filename, "w");

    if(fp == NULL){

        printf("Error opening file\n");

        return;
    }

    /*
        Store records line by line

        Example:
        Rohith 101 95.50
    */

    for(int i=0; i<n; i++){

        fprintf(fp, "%s %d %.2f\n",
                r[i].name,
                r[i].id,
                r[i].marks);
    }

    fclose(fp);
}

/*
    Function:
    Create array of seek positions

    Logic:
    Store the byte position
    where each line begins
*/

void createSeekPositions(const char *filename,
                         long pos[],
                         int *count){

    FILE *fp = fopen(filename, "r");

    if(fp == NULL){

        printf("Error opening file\n");

        return;
    }

    char line[100];

    int index = 0;

    while(1){

        /*
            Store current position
            before reading line
        */

        long currentPos = ftell(fp);

        /*
            Read one line
        */

        if(fgets(line, sizeof(line), fp) == NULL){

            break;
        }

        /*
            Save beginning position
            of this record
        */

        pos[index++] = currentPos;
    }

    *count = index;

    fclose(fp);
}

/*
    Function:
    Display record given
    the seek position
*/

void displayRecord(long position,
                   const char *filename){

    FILE *fp = fopen(filename, "r");

    if(fp == NULL){

        printf("Error opening file\n");

        return;
    }

    /*
        Move pointer directly
        to stored position
    */

    fseek(fp, position, SEEK_SET);

    char line[100];

    /*
        Read that line
    */

    fgets(line, sizeof(line), fp);

    printf("\n--- Record Found ---\n");

    printf("%s", line);

    fclose(fp);
}