#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct { // Datenstruktur für das Datum
    int tag;
    int monat;
    int jahr;
} Datum;

typedef struct { // Datenstruktur für Studenten
    char nachname[51];
    char vorname[51];
    char studiengang[51];
    char matrikelnummer[9];
    Datum geburtstag;
    Datum startdatum;
    Datum enddatum;
    struct Student *nextStudent; // Zuweisung des Zeigers auf die nächste Studentenstruktur
} Student;

Student *head = NULL;

int validesDatum(int monat, int tag, int jahr) {
    if (jahr > 1970 || monat < 1 || monat > 12 || tag < 1 || tag > 31) return 0;

    int maxTage[] = {31, 28, 31, 30, 31, 31, 30, 31, 30, 31, 30, 31};
    if ((jahr % 4 == 0 && jahr % 100 != 0) || jahr % 400 == 0) maxTage[1] = 29; // Schaltjahrberechnung
    return tag <= maxTage[monat - 1];
}

Datum stringToDate(char *dateStr) {
    Datum datum;
    sscanf(dateStr, "%d.%d.%d", &datum.tag, &datum.monat, &datum.jahr);
    return datum;
}

Student* inputStudentFromCSV(FILE *file) {
    Student *neuerStudent = (Student *)malloc(sizeof(Student));
    if (!neuerStudent) {
        exit(EXIT_FAILURE);
    }

    char geburtsdatumStr[11], startdatumStr[11], enddatumStr[11];

    // Read data from the CSV line (assuming proper CSV format)
    if (fscanf(file, "%50[^,],%50[^,],%50[^,],%8s,%10s,%10s,%10s\n", 
               neuerStudent->vorname, neuerStudent->nachname, neuerStudent->studiengang, 
               neuerStudent->matrikelnummer, geburtsdatumStr, startdatumStr, enddatumStr) != 7) {
        free(neuerStudent);
        return NULL;
    }

    // Convert string dates to Datum structure
    neuerStudent->geburtstag = stringToDate(geburtsdatumStr);
    neuerStudent->startdatum = stringToDate(startdatumStr);
    neuerStudent->enddatum = stringToDate(enddatumStr);

    neuerStudent->nextStudent = NULL;

    return neuerStudent;
}

void addStudent(Student *neuerStudent) {
    neuerStudent->nextStudent = head;
    head = neuerStudent;
    printf("Student wurde hinzugefügt\n");
}

void readCSVAndAddStudents(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return;
    }

    char line[256]; // Buffer for the header line
    // Read header line, assuming it exists and is valid
    fgets(line, sizeof(line), file);

    while (1) {
        Student *neuerStudent = inputStudentFromCSV(file);
        if (neuerStudent == NULL) break; // Stop when no more students are found
        addStudent(neuerStudent);
    }

    fclose(file);
}

int main() {
    // Specify the path to your CSV file here
    const char *csvFilePath = "students.csv"; // Path to CSV file -> Paste the Path where the CSV File is

    // Read CSV and add students at the start
    readCSVAndAddStudents(csvFilePath);

    // Now, you can proceed with the rest of your program (e.g., interacting with students)
    // Your existing code can be executed here
    return 0;
}
