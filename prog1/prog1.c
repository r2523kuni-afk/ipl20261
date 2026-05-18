#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[30];
    int id;
    float marks;
} record;

void writeToFile(record r[], int n, const char *filename);
int countRecord(const char *filename);
void readFile(const char *filename);
void getmthfile(int m, const char *filename);
void deleteRecord(int m, const char *filename);

int main() {
    int n;

    printf("Enter number of records: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number.\n");
        return 0;
    }

    record r[n];

    for (int i = 0; i < n; i++) {

        printf("\nEnter details of student %d\n", i + 1);

        printf("Enter name : ");
        scanf("%29s", r[i].name);

        printf("Enter ID : ");
        scanf("%d", &r[i].id);

        printf("Enter marks : ");
        scanf("%f", &r[i].marks);
    }

    writeToFile(r, n, "sample.bin");

    int m;

    printf("\nEnter mth record to display: ");
    scanf("%d", &m);

    getmthfile(m, "sample.bin");

    printf("\nEnter record number to delete: ");
    scanf("%d", &m);

    deleteRecord(m, "sample.bin");

    printf("\n----- FILE CONTENT AFTER DELETION -----\n");

    readFile("sample.bin");

    return 0;
}

void writeToFile(record r[], int n, const char *filename) {

    FILE *fp = fopen(filename, "wb");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fwrite(r, sizeof(record), n, fp);

    fclose(fp);
}

int countRecord(const char *filename) {

    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        return 0;
    }

    fseek(fp, 0, SEEK_END);

    long filesize = ftell(fp);

    fclose(fp);

    return filesize / sizeof(record);
}

void readFile(const char *filename) {

    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    int total = countRecord(filename);

    if (total == 0) {
        printf("No records found.\n");
        fclose(fp);
        return;
    }

    printf("\n%-5s %-15s %-10s %-10s\n",
           "Rec", "Name", "ID", "Marks");

    printf("------------------------------------------------\n");

    record rec;

    int i = 1;

    while (fread(&rec, sizeof(record), 1, fp) == 1) {

        printf("%-5d %-15s %-10d %-10.2f\n",
               i++,
               rec.name,
               rec.id,
               rec.marks);
    }

    fclose(fp);
}

void getmthfile(int m, const char *filename) {

    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int total = countRecord(filename);

    if (m < 1 || m > total) {
        printf("Invalid record number.\n");
        fclose(fp);
        return;
    }

    fseek(fp, (m - 1) * sizeof(record), SEEK_SET);

    record r;

    fread(&r, sizeof(record), 1, fp);

    printf("\n--- Record %d ---\n", m);

    printf("Name  : %s\n", r.name);
    printf("ID    : %d\n", r.id);
    printf("Marks : %.2f\n", r.marks);

    fclose(fp);
}

void deleteRecord(int m, const char *filename) {

    int total = countRecord(filename);

    if (m < 1 || m > total) {

        printf("Invalid record number.\n");
        return;
    }

    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    record *temp = malloc(total * sizeof(record));

    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return;
    }

    fread(temp, sizeof(record), total, fp);

    fclose(fp);

    fp = fopen(filename, "wb");

    if (fp == NULL) {

        printf("Cannot open file for writing.\n");

        free(temp);
        return;
    }

    for (int i = 0; i < total; i++) {

        if (i == m - 1)
            continue;

        fwrite(&temp[i], sizeof(record), 1, fp);
    }

    fclose(fp);

    free(temp);

    printf("Record %d deleted successfully.\n", m);
}