// noi goi ham 
#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h" // Bao g?m t?p datatype.h

// Khai báo nguyên m?u hàm
// cac ham kiem tra du lieu :
int isValidEmail(char email[]) ;
int isUniqueID(struct student students[], int numStudents, char id[]);
int isUniqueEmail(struct student students[], int numStudents, char email[]) ;
int isUniquePhone(struct student students[], int numStudents, char phone[]) ;
int isNotEmpty(char str[]) ;

int isUniqueTeacherID(struct Teacher teachers[], int numTeachers, char id[]) ;

int isUniqueTeacherEmail(struct Teacher teachers[], int numTeachers, char email[]) ;
int isUniqueTeacherPhone(struct Teacher teachers[], int numTeachers, char phone[]) ;

// phan menu 
void menu();

void login();

void adminMenu();

void studentManagementMenu();

void teacherMenu();

void teacherManagementMenu();
//phan ghi va doc file  
void writeStudentsToFile(const char* filename, struct student students[], int numStudents) ;

void readStudentsFromFile(const char* filename, struct student students[], int *numStudents) ;

void readTeachersFromFile(const char* filename, struct Teacher teachers[], int *numTeachers);

void writeTeachersToFile(const char* filename, struct Teacher teachers[], int numTeachers);
// phan cac chuc nang cua menu sinh vien 
void addStudent(struct student students[], int *numStudents) ;

void printStudents(struct student students[], int numStudents);

void searchStudentByName(struct student students[], int numStudents, const char* name);

int findStudentIndex(struct student students[], int numStudents, const char* studentId);
void editStudent(struct student students[], int numStudents);

void deleteStudentById(struct student students[], int *numStudents, const char* studentId) ;

void sortStudents(struct student students[], int numStudents, int sortOrder) ;

void sortMenu(struct student students[], int numStudents) ;


void printAboutUs();
// phan nay cua giao vien

void addTeacher(struct Teacher teachers[], int *numTeachers) ;

void printTeachers(struct Teacher teachers[], int numTeachers) ;

void searchTeacherByName(struct Teacher teachers[], int numTeachers, const char* name) ;

int findTeacherIndex(struct Teacher teachers[], int numTeachers, const char* teacherId) ;

void editTeacher(struct Teacher teachers[], int numTeachers) ;

void deleteTeacherById(struct Teacher teachers[], int *numTeachers, const char* teacherId);

void sortTeacherMenu(struct Teacher teachers[], int numTeachers) ;

// phan nay cua lop hoc  
void addClass(struct Classroom classes[], int *numClasses) ;

void printClasses(struct Classroom classes[], int numClasses) ;

void readClassesFromFile(const char* filename, struct Classroom classes[], int *numClasses) ;

void writeClassesToFile(const char* filename, struct Classroom classes[], int numClasses) ;

void searchClassByName(struct Classroom classes[], int numClasses, char *searchName);

void editClass(struct Classroom classes[], int numClasses);

void deleteClassById(struct Classroom classes[], int *numClasses, char *classId) ;

void ClassroomsManagement() ;

// phan nay cua phan diem
void viewClassList(struct student students[], int numStudents);

void editScore(struct score scores[], int numScores);

void viewScoresAsTable(struct score scores[], int numScores);

void writeScoresToFile(const char* filename, struct score scores[], int numScores);

void readScoresFromFile(const char* filename, struct score scores[], int *numScores);



#endif
