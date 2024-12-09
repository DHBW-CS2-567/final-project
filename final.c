#include "final.h"

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
	fprintf(stderr, "invalidDateString");
	return datum;
}

int checkDate(Datum date)
{
	if(date.monat > 12){
		printf("INVALID DATE\nTRY AGAIN\n");
		return -1;
	}
	if(date.jahr%4 == 0){
		if(date.monat == 2){
			if(date.tag > 29){
				printf("INVALID DATE\nTRY AGAIN\n");
				return -1;
			}
		}
	}else if(date.monat == 4 || date.monat == 6 || date.monat == 9 || date.monat == 11){
		if(date.tag > 30){
			printf("INVALID DATE\nTRY AGAIN\n");
			return -1;
		}
	} else if(date.monat == 1 || date.monat == 3 || date.monat == 5 || date.monat == 7 || date.monat == 8 || date.monat == 10 || date.monat == 12){
		if(date.tag > 31){
			printf("INVALID DATE\nTRY AGAIN\n");
			return -1;
		}
	}
	return 0;
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

void addingWizard()
{
	printf("Nachname:\n");
	char nachname[51];
	scanf("%50s", nachname);
	printf("Vorname:\n");
	char vorname[51];
	scanf("%50s", vorname);
	printf("Studiengang:\n");
	char studiengang[51];
	scanf("%50s", studiengang);
	printf("Matrikelnummer:\n");
	char matrikelnummer[9];
	scanf("%8s", matrikelnummer);

	printf("Geburtstag (dd.mm.yyyy):\n");
	Datum geburtstag = {};
	scanf("%d.%d.%d", &geburtstag.tag, &geburtstag.monat, &geburtstag.jahr);
	while(checkDate(geburtstag) != 0){
		printf("Geburtstag (dd.mm.yyyy):\n");
		scanf("%d.%d.%d", &geburtstag.tag, &geburtstag.monat, &geburtstag.jahr);
	}

	printf("Startdatum (dd.mm.yyyy):\n");
	Datum startdatum = {};
	scanf("%d.%d.%d", &startdatum.tag, &startdatum.monat, &startdatum.jahr);
	while(checkDate(startdatum) != 0){
		printf("Startdatum (dd.mm.yyyy):\n");
		scanf("%d.%d.%d", &startdatum.tag, &startdatum.monat, &startdatum.jahr);
	}

	printf("Enddatum (dd.mm.yyyy):\n");
	Datum enddatum = {};
	scanf("%d.%d.%d", &enddatum.tag, &enddatum.monat, &enddatum.jahr);
	while(checkDate(enddatum) != 0){
		printf("Enddatum (dd.mm.yyyy):\n");
		scanf("%d.%d.%d", &enddatum.tag, &enddatum.monat, &enddatum.jahr);
	}

	Student student_tmp;
	strcpy(student_tmp.nachname, nachname);
    strcpy(student_tmp.vorname, vorname);
    strcpy(student_tmp.studiengang, studiengang);
    strcpy(student_tmp.matrikelnummer, matrikelnummer);
    student_tmp.geburtstag = geburtstag;
    student_tmp.startdatum = startdatum;
    student_tmp.enddatum = enddatum;
    student_tmp.nextStudent = NULL;

	addStudent(&student_tmp);
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

int count_student(Student *student, int counter)
{
	if(student->nextStudent == NULL)
		return counter;
	return count_student(student->nextStudent, counter++);
}

void print_student_info(Student *student)
{
	printf("nachname: %s\n", student->nachname);
	printf("vorname: %s\n", student->vorname);
	printf("studiengang: %s\n", student->studiengang);
	printf("matrikelnummer: %s\n", student->matrikelnummer);
	Datum date = student->geburtstag;
	printf("geburtstag: %02d. %02d. %d\n", date.tag, date.monat, date.jahr);
	date = student->startdatum;
	printf("startdatum: %02d. %02d. %d\n", date.tag, date.monat, date.jahr);
	date = student->enddatum;
	printf("enddatum: %02d. %02d. %d\n", date.tag, date.monat, date.jahr);
}

void print_student(Student *student, char matrikelnummer[9])
{
	if(strcmp(matrikelnummer, student->matrikelnummer) == 0)
		print_student_info(student);
	else if(student->nextStudent == NULL)
		printf("student not found");
	else
		print_student(student->nextStudent, matrikelnummer);
}

void print_all_student(Student *student)
{
	if(student->nextStudent != NULL){
		print_student_info(student);
		print_all_student(student->nextStudent);
	}
}

void delete_student(Student *student, char matrikelnummer[9])
{
	if(strcmp(matrikelnummer, student->matrikelnummer) == 0){
		Student *nextnext = student->nextStudent->nextStudent;
		free(student->nextStudent);
		student->nextStudent = nextnext;
	}
	else if(student->nextStudent == NULL)
		printf("student not found");
	else
		print_student(student->nextStudent, matrikelnummer);
}

void print_help(const char *program_name)
{
	printf("%s --help\t\t\tprint the help\n", program_name);
	printf("%s add\t\t\tstart the adding wizard\n", program_name);
	printf("%s amount\t\t\tget the student amount\n", program_name);
	printf("%s get {matrikelnummer}\t\t\tget the student with matrikelnummer\n", program_name);
	printf("%s getAll \t\t\tget all students\n", program_name);
	printf("%s delete {matrikelnummer} \t\t\tdelete student with matrikelnummer\n", program_name);
}

int main(int argc, char *argv[]) {
	Student *root = NULL;
	if(argc == 1)
		print_help(argv[0]);
	if(argc>=2){
		if(strcmp(argv[1], "--help") == 0)
			print_help(argv[0]);
		else if(strcmp(argv[1], "add") == 0)
			addingWizard();
		else if(strcmp(argv[1], "amount") == 0){
			if(root == NULL)
				printf("0\n");
			else count_student(root, 0);
		}
		else if(root == NULL)
				printf("Add a student first\n");
		else{
			if(strcmp(argv[1], "get") == 0){
				if(argc>=3)
					print_student(root, argv[2]);
				else printf("you need to do %s get {matrikelnummer}\n", argv[0]);
				//TODO: ; matrikelnummer has to be a number
			}
			else if(strcmp(argv[1], "getAll") == 0)
				print_all_student(root);
			else if(strcmp(argv[1], "delete") == 0){
				if(argc>=3)
					delete_student(root, argv[2]);
				else printf("you need to do %s delete {matrikelnummer}\n", argv[0]);
			}
		}
	}

	// Specify the path to your CSV file here
	// const char *csvFilePath = "students.csv"; // Path to CSV file -> Paste the Path where the CSV File is

	// Read CSV and add students at the start
	// readCSVAndAddStudents(csvFilePath);

	// Now, you can proceed with the rest of your program (e.g., interacting with students)
	// Your existing code can be executed here
	return 0;
}
