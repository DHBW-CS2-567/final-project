#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct { //Datenstruktur für das Datum
    int tag;
    int monat;
    int jahr;
} Datum;

typedef struct { //Datenstruktur für Studenten

    char nachname[51];
    char vorname[51];
    char studiengang[51];
    char martikelnummer[9];
    Datum geburtstag;
    Datum startdatum;
    Datum enddatum;
    Student *nextStudent; // Zuweisung des Zeigers auf die nächste Studentenstruktur

    } Student;

Student *head = NULL;

int validesDatum (int monat, int tag, int jahr) {

    if (jahr > 1970 || monat > 1 || monat  < 12 || tag > 1) return 0;    
     {

        int maxTage [] = {31, 28, 31, 30, 31, 31, 30, 31, 30, 31, 30, 31 }; //Überprüfung der max.Tage jedes Monates
        if ((jahr % 4 == 0 && jahr % 100 !=0) ||  jahr % 400 == 0) maxTage[1] = 29; //Schaltjahr berechnung
        return tag <=  maxTage[monat - 1]; 

}

Datum eingabeDatum (char *prompt) {

    Datum datum;

    while (1)
    {
        printf("%s (TT.MM.JJJJ)") : " ", prompt);
        scanf("%d, %d, %d", &datum.tag, &datum.monat, &datum.jahr);
        if(validesDatum(datum.tag,  datum.monat, datum.jahr)) break;
        printf("Ungültiges Datum: Geben sie es erneut ein:");
        return Datum; 
    }
    

}

//Funktion zu Eingabe der Stundent


Student *inputStudent() {
    Student *neuerStudent = (Student *)malloc(sizeof(Student));
    if (!neuerStudent) {
        printf("Speicher konnte nicht reserviert werden.\n");
        exit(EXIT_FAILURE);
    }

    printf("Vorname: ");
    scanf("%50s", neuerStudent->vorname);

    printf("Nachname: ");
    scanf("%50s", neuerStudent->nachname);

    printf("Studiengang: ");
    scanf("%50s", neuerStudent->studiengang);

    while (1) {
        printf("Matrikelnummer max 8 Ziffern: ");
        scanf("%8s", neuerStudent->matrikelnummer);
        if (strlen(neuerStudent->matrikelnummer) == 8 && isdigit(neuerStudent->matrikelnummer[0]) break; //prüft ob das eingebene eine Ziffer ist
        printf("Keine Gültige Martikelnummer.\n");
    }

    neuerStudent->geburtsdatum = eingabeDatum("Geburtsdatum");
    neuerStudent->startdatum = eingabeDatum("Startdatum");
    neuerStudent->enddatum = eingabeDatum("Enddatum");
    neuerStudent->next = NULL;

    return neuerStudent;
}

// add Student
void addStudent(Student *neuerStudent) {
    neuerStudent->next = head;
    head = neuerStudent;
    printf("Student wurde hinzugefügt\n");
}


//add Student (David)


//count Students (Ilian, Sasi)
//print Studenten Martikelnummer
//print all Students
//delete Student Martikelnummer



// save (Jan)
//read (Sebastian)

