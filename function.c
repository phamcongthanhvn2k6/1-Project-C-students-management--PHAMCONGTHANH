// noi trien khai cac ham 
#include "function.h"
#include "datatype.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const char *filestudents = "C:\\Users\\LEGION\\OneDrive\\Documents\\C\\1 Project C students management\\students.bin";
const char *fileteachers = "C:\\Users\\LEGION\\OneDrive\\Documents\\C\\1 Project C students management\\teachers.bin";
const char *fileclass = "C:\\Users\\LEGION\\OneDrive\\Documents\\C\\1 Project C students management\\class.bin";
const char *fileadmin = "C:\\Users\\LEGION\\OneDrive\\Documents\\C\\1 Project C students management\\admin.bin";
const char *filescore = "C:\\Users\\LEGION\\OneDrive\\Documents\\C\\1 Project C students management\\score.bin";

#define MAX_ADMINS 100 // Maximum number of admin accounts
#define MAX_LENGTH 100  // Maximum length of email and password
struct score scores[100];
int numScores = 0;

void writeAdminsToFile(const char* filename, struct admin admins[], int numAdmins) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file!\n");
        return;
    }
    int i=0; 
	for (i; i < numAdmins; i++) {
        fprintf(file, "%s %s\n", admins[i].email, admins[i].password);
    }
    fclose(file);
}

void readAdminsFromFile(const char* filename, struct admin admins[], int* count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    char line[2 * MAX_LENGTH];
    *count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%s %s", admins[*count].email, admins[*count].password);
        (*count)++;
    }
    fclose(file);
}

// Ham dang nhap

void getPassword(char password[], int maxLength) {
    int index = 0;
    char ch;

    while (1) {//vong lap vo han , vong lap se tiep tuc khi nguoi dung an phim enter 
        ch = getch();
        if (ch == '\r') {  // Enter key
            password[index] = '\0';
            break;
        } else if (ch == '\b') {  
		// nhan phim Backspace (\b), ky tu cuoi cung trong mang password se bi xaa (neu co). Ðong thoi, ky tu hien thi tren man hinh cung bi xoa bang cach su dung chuoi "\b \b".
            if (index > 0) {
                index--;
                printf("\b \b");  // Xoa ki tu da hien thi 
            }
        } else if (index < maxLength - 1) {
            password[index++] = ch;
            printf("*");  // Hien thi dau sao thay cho ki tu mat khau ngay lap tuc
        }
    }
    printf("\n");
}

void manageTeacherLogin(const char* filename) {
    struct Teacher teachers[100];
    int count;
    
    readTeachersFromFile(filename, teachers, &count);// doc file teacher de lay thong tin cua giao vien 

    char email[MAX_LENGTH];
    char password[MAX_LENGTH];
    int loginSuccessful = 0;

    do {
        printf("+------------------------------------------+\n");
        printf("%-8s %-33s %s\n","|","SCHOOL MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-17s %-24s %s\n","|","TEACHER LOGIN", "|");
        printf("+------------------------------------------+\n");

        // Nhap email giao vien
        printf("Email: ");
        scanf("%s", email);

        // Nhap mat khau 
        printf("Password: ");
        getPassword(password, MAX_LENGTH);

        // xac minh thong tin dang nhap co khop voi email va mat khau dc cap khong
        int i=0; 
		for (i; i < count; i++) {
            if (strcmp(email, teachers[i].email) == 0 && strcmp(password, teachers[i].password) == 0) {
                printf("Teacher Login successful!\n");
                printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
    			printf("| %-10s | %-10s | %-20s | %-10s | %-6s | %-27s | %-13s |\n","Teacher ID", "Classroom ID", "Name", "DOB", "Gender", "Email", "Phone");
    			printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");

                printf("| %-10s | %-12s | %-20s | %02d/%02d/%04d | %-6s | %-27s | %-13s |\n",
                   teachers[i].teacherId,
                   teachers[i].classroomId,
                   teachers[i].name,
                   teachers[i].dateOfBirth.day,
                   teachers[i].dateOfBirth.month,
                   teachers[i].dateOfBirth.year,
                   teachers[i].gender ? "Male" : "Female",// neu gender la 1 thi la male con nguoc lai se la female
                   teachers[i].email,
                   teachers[i].phone);
            	printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
                loginSuccessful = 1;// dang nhap thanh cong 
                break;
            }
        }

        if (!loginSuccessful) {// neu khong dang nhap thanh cong thi se hien thong bao khong dang nhap thanh cong va yeu cau nhap lai email va mat khau 
            printf("Invalid email or password. Please try again.\n");
        }
    } while (!loginSuccessful);// vong lapm chay den khi nao dang nhap thanh cong 
}

void manageStudentLogin(const char* filename) {
    struct student students[100];
    struct score scores[100];
    int count, numScores;
    
    readStudentsFromFile(filename, students, &count);

    char email[MAX_LENGTH];
    char password[MAX_LENGTH];
    int loginSuccessful = 0;

    do {
        printf("+------------------------------------------+\n");
        printf("%-8s %-33s %s\n","|","SCHOOL MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-17s %-24s %s\n","|","STUDENT LOGIN", "|");
        printf("+------------------------------------------+\n");

		//nhap email
        printf("Email: ");
        scanf("%s", email);

        // nhap mat khau
        printf("Password: ");
        getPassword(password, MAX_LENGTH);

        // dung ham so sanh chuoi de biet email, mat khau nhap vao la dung hay sai
        int i=0; 
		for (i; i < count; i++) {
            if (strcmp(email, students[i].email) == 0 && strcmp(password, students[i].password) == 0) {
                printf("Student Login successful!\n");
                printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
                printf("| %-10s | %-10s | %-20s | %-10s | %-6s | %-27s | %-13s |\n","Student ID", "Classroom ID", "Name", "DOB", "Gender", "Email", "Phone");
                printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
                printf("| %-10s | %-12s | %-20s | %02d/%02d/%04d | %-6s | %-27s | %-13s |\n",
                students[i].studentId,
                students[i].classroomId,
                students[i].name,
                students[i].dateOfBirth.day,
                students[i].dateOfBirth.month,
                students[i].dateOfBirth.year,
                students[i].gender ? "Male" : "Female",
                students[i].email,
                students[i].phone);
                printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
                loginSuccessful = 1;
                
                // doc file diem  
                readScoresFromFile(filescore, scores, &numScores);

                // hien thi thong tin diem cua sinh vien 
                printf("+------------+--------------+------+------+------+------+------------------+---------------+------------+\n");
                printf("| Student ID | Student Name | RP1  | RP2  | RP3  | RP4  | Midterm Exam     | Final Exam    | Total      |\n");
                printf("+------------+--------------+------+------+------+------+------------------+---------------+------------+\n");
                int j=0; 
				for (j; j < numScores; j++) {
                    if (strcmp(scores[j].studentId, students[i].studentId) == 0) {// so sanh xem Id cua diem voi Id sinh vien neu dung thi hien thong tin ra  
                        double totalScore = ((scores[j].regularPoints1 + scores[j].regularPoints2 + scores[j].regularPoints3 + scores[j].regularPoints4) + scores[j].midtermExamScore * 2 + scores[j].finalExamScore * 3) / 9;
                        printf("| %10s | %-12s | %4.1f | %4.1f | %4.1f | %4.1f | %16.1f | %13.1f | %10.1f |\n",               
                        scores[j].studentId,
                        scores[j].studentName,
                        scores[j].regularPoints1,
                        scores[j].regularPoints2,
                        scores[j].regularPoints3,
                        scores[j].regularPoints4,
                        scores[j].midtermExamScore,
                        scores[j].finalExamScore,
                        totalScore);
                        printf("+------------+--------------+------+------+------+------+------------------+---------------+------------+\n");
                    }
                }
                break;
            }
        }

        if (!loginSuccessful) {// neu sai thi hien thong bao loi 
            printf("Invalid email or password. Please try again.\n");
        }
    } while (!loginSuccessful);
}



void manageAdminLogin(const char* filename) {
    struct admin admins[MAX_ADMINS];
    int count;
    readAdminsFromFile(filename, admins, &count);

    char email[MAX_LENGTH];
    char password[MAX_LENGTH];
    int loginSuccessful = 0;

    do {
        printf("+------------------------------------------+\n");
        printf("%-8s %-33s %s\n","|","STUDENT MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-17s %-24s %s\n","|","LOGIN", "|");
        printf("+------------------------------------------+\n");

        printf("Email: ");
        scanf("%s", email);

        printf("Password: ");
        getPassword(password, MAX_LENGTH);

        int i=0; 
		for (i; i < count; i++) {
            if (strcmp(email, admins[i].email) == 0 && strcmp(password, admins[i].password) == 0) {
                printf("Login successful!\n");
                loginSuccessful = 1;
                break;
            }
        }

        if (!loginSuccessful) {
            printf("Invalid email or password. Please try again.\n");
        }
    } while (!loginSuccessful);
}

void menu(){
	struct score scores[100];
	int numScores = 0;
    int choice;
    do {
        // Hien thi menu chính
        printf("+------------------------------------------+\n");
		printf("%-8s %-33s %s\n","|","STUDENT MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-13s %-28s %s\n","|","Choose Your Role", "|");
        printf("+------------------------------------------+\n");
        printf("| %-3s | %-34s |\n", "[1]", "Admin");
        printf("| %-3s | %-34s |\n", "[2]", "Student");
        printf("| %-3s | %-34s |\n", "[3]", "Teacher");
        printf("| %-3s | %-34s |\n", "[0]", "Exit the Program");
        printf("+------------------------------------------+\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
 				manageAdminLogin(fileadmin);// ham dang nhap admin 
                adminMenu();// menu admin 
                break;
            case 2:
 				manageStudentLogin(filestudents);// ham dang nhap sinh vien co tich hop cac tinh nang  
                break;
            case 3:
 				manageTeacherLogin(fileteachers);//ham dang nhap giao vien 
				teacherMenu();// menu giao vien 
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");// thoat chuong trinh 
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");// neu nhap khong dung so thi se cho nhap lai va hien thong bao 
                break;
        }
    } while (choice != 0);
}



void displayUsageInstructions() {// hien thi bang huong dan su dung 
    printf("==============================================================================================\n");
	printf("|                  INSTRUCTIONS FOR USING THE SCHOOL MANAGEMENT SYSTEM                       |\n");
	printf("==============================================================================================\n");
	printf("| Step 1: Preparation                                                                        |\n");
	printf("----------------------------------------------------------------------------------------------\n");
	printf("| - Make sure the information file is formatted correctly.                                   |\n");
	printf("| - The file must contain the required fields                                                |\n"); 
	printf("==============================================================================================\n");
	printf("| Step 2: Log in                                                                             |\n");
	printf("----------------------------------------------------------------------------------------------\n");
	printf("| - Open the program and enter your email address provided.                                  |\n");
	printf("| - Enter the corresponding password for the registered email.                               |\n");
	printf("| - If the email and password are correct, your information will be displayed.               |\n");
	printf("| - If the email or password is incorrect, please try again.                                 |\n");
	printf("==============================================================================================\n");
	printf("| Step 3: View information                                                                   |\n");
	printf("----------------------------------------------------------------------------------------------\n");
	printf("| - After successfully logging in, your information will be displayed as a table.            |\n");
	printf("| - Information fields include: Your ID, Class ID, Name, Date of Birth, Gender, Email, Phone.|\n");
	printf("==============================================================================================\n");
}

// Ham menu cho Admin
void adminMenu(){
	int choice;
    do {
        // Hien thi menu chính
        printf("+------------------------------------------+\n");
		printf("%-8s %-33s %s\n","|","STUDENT MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-19s %-22s %s\n","|","MENU", "|");
        printf("+------------------------------------------+\n");
        printf("| %-3s | %-34s |\n", "[1]", "Students Management.");// quan ly hoc sinh 
        printf("| %-3s | %-34s |\n", "[2]", "Classrooms Management.");// quan ly lop hoc 
        printf("| %-3s | %-34s |\n", "[3]", "teacher Management.");//quan ly giao vien 
        printf("| %-3s | %-34s |\n", "[4]", "User Guideline.");// huong dan su dung 
		printf("| %-3s | %-34s |\n", "[5]", "About Us.");// ve chung toi 
		printf("| %-3s | %-34s |\n", "[0]", "Exit the Program");//thoat 
        printf("+------------------------------------------+\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            	studentManagementMenu();
                break;
                
            case 2:
            	ClassroomsManagement() ;
                break;
                
            case 3:
            	teacherManagementMenu();
                break;
            
            case 4:
            	displayUsageInstructions();
            	break;
            	
            case 5:
            	printAboutUs();
            	break;
        
            case 0:
                printf("Exiting the program. Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

}

// ham menu sinh vien
void studentManagementMenu() {
	struct student students[MAX_STUDENTS];
    int numStudents = 0;
	int choice;
	char studentId[10];
    do {
        // Hien thi menu chinh
        printf("+------------------------------------------+\n");
		printf("%-8s %-33s %s\n","|","STUDENT MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-15s %-26s %s\n","|","STUDENT MENU", "|");
        printf("+------------------------------------------+\n");
        printf("| %-3s | %-34s |\n", "[1]", "Add A New Student.");// them mot hoc sinh 
        printf("| %-3s | %-34s |\n", "[2]", "Show All Students.");// hien thi hoc sinh 
        printf("| %-3s | %-34s |\n", "[3]", "Seach A Students");// tim kiem hoc sinh 
        printf("| %-3s | %-34s |\n", "[4]", "Edit A students");// chinh sua hoc sinh 
		printf("| %-3s | %-34s |\n", "[5]", "Delete A Students.");// xoa hoc sinh 
		printf("| %-3s | %-34s |\n", "[6]", "Sort student list.");// sap xep  hoc sinh 
		printf("| %-3s | %-34s |\n", "[0]", "Exit the Program");//thoat 
        printf("+------------------------------------------+\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            	addStudent(students, &numStudents);// ham them sinh vien 
                break;
                
            case 2:
    			readStudentsFromFile(filestudents, students, &numStudents);
				printStudents(students, numStudents);// in thong tin sinh vien                
				break;
                
            case 3:            	
            	readStudentsFromFile(filestudents, students, &numStudents);
            	printStudents(students, numStudents);// in thong tin ra truoc 
            	
				char searchName[20];

    			printf("Enter the name of the student you want to search: ");// nhap thong tin tim kiem 
                scanf(" %[^\n]s", searchName);
                searchStudentByName(students, numStudents, searchName);// ham tim kiem sinh vien 

    			writeStudentsToFile(filestudents, students, numStudents);// ghi file vao 
                break;
            
            case 4:
    			readStudentsFromFile(filestudents, students, &numStudents);
            	editStudent(students, numStudents);// ham sua thong tin sinh vien 
    			writeStudentsToFile(filestudents, students, numStudents);
                break;
            	
            case 5:
    			readStudentsFromFile(filestudents, students, &numStudents);
			    printStudents(students, numStudents);
			    
			    studentId[20];
			    printf("Enter the student ID to delete: ");
			    scanf("%s", studentId);
			
			    deleteStudentById(students, &numStudents, studentId);// ham xoa  
    			writeStudentsToFile(filestudents, students, numStudents);
                break;
        	case 6:
        		readStudentsFromFile(filestudents, students, &numStudents);
			    printStudents(students, numStudents);	
				sortMenu(students, numStudents);// menu sap xep 
				writeStudentsToFile(filestudents, students, numStudents);
                break;		 
            case 0:
                printf("Exiting the program. Goodbye!\n");
                return; 
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);
}


// Ham menu cho Teacher
void teacherMenu() {
	struct Teacher teachers[MAX_TEACHERS]; 
    struct Classroom classes[MAX_CLASSES];
	struct student students[100];
    char teacherId[10];
    int choice;
    int numTeachers = 0;
    int numClasses = 0;
    int numStudents =0;
    do {
        printf("+------------------------------------------+\n");
        printf("%-8s %-33s %s\n","|","STUDENT MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-15s %-26s %s\n","|","TEACHER MENU", "|");
        printf("+------------------------------------------+\n");
        printf("| %-3s | %-34s |\n", "[1]", "View Class List."); // Xem danh sach lop 
        printf("| %-3s | %-34s |\n", "[2]", "fix scores.");      // sua diem 
        printf("| %-3s | %-34s |\n", "[0]", "Back to Main Menu");
        printf("+------------------------------------------+\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            	readStudentsFromFile(filestudents, students, &numStudents);
            	viewClassList(students, numStudents);
                break;
                
            case 2:
				readScoresFromFile(filescore, scores, &numScores);
				viewScoresAsTable(scores, numScores);
				editScore(scores, numScores);
				viewScoresAsTable(scores, numScores);
				writeScoresToFile(filescore, scores, numScores);
                break;
            
            case 0:
                printf("Exiting the program. Goodbye!\n");
                return;
                
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);
}

void writeStudentsToFile(const char* filename, struct student students[], int numStudents) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file!\n");
        return;
    }
    int i;
    for (i = 0; i < numStudents; i++) {
        fprintf(file, "%s %s %s %02d/%02d/%04d %d %s %s %s\n",// dung fprintf den ghi thong tin tu mang students vao trong file 
                students[i].studentId,
                students[i].classroomId,
                students[i].name,
                students[i].dateOfBirth.day,
                students[i].dateOfBirth.month,
                students[i].dateOfBirth.year,
                students[i].gender,
                students[i].email,
                students[i].phone,
                students[i].password);
    }
    fclose(file);
}


void readStudentsFromFile(const char* filename, struct student students[], int *numStudents) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file!\n");
        return;
    }
    int i = 0;
    while (fscanf(file, "%s %s %s %d/%d/%d %d %s %s %s",// dung vong lap de ghi thong tin vao mang students  
                  students[i].studentId,
                  students[i].classroomId,
                  students[i].name,
                  &students[i].dateOfBirth.day,
                  &students[i].dateOfBirth.month,
                  &students[i].dateOfBirth.year,
                  &students[i].gender,
                  students[i].email,
                  students[i].phone,
                  students[i].password) != EOF) {
        i++;
    }
    *numStudents = i;
    if (ferror(file)) {
        perror("Error reading from file");
    }
    fclose(file);
}


int isValidEmail(char email[]) {
    return strchr(email, '@') != NULL;//ham tim kiem ky tu @ neu co se tra ve toi vi tri cua con tro con neu khong se tra ve NULL 
}

int isUniqueID(struct student students[], int numStudents, char id[]) { 
	int i=0;
	for (i; i < numStudents; i++) {
        if (strcmp(students[i].studentId, id) == 0) {
            return 0;
        }
    }
    return 1;
}

int isUniqueEmail(struct student students[], int numStudents, char email[]) {
    int i=0; 
	for (i; i < numStudents; i++) {// dung vong lap for chay den het 
        if (strcmp(students[i].email, email) == 0) {// neu trung voi email nao thi se tra ve 0(sai) 
            return 0;
        }
    }
    return 1;// con neu khong khop voi ai se tra ve la 1(dung) 
}

int isUniquePhone(struct student students[], int numStudents, char phone[]) {
	int i=0;
	for (i; i < numStudents; i++) {
        if (strcmp(students[i].phone, phone) == 0) {
            return 0;
        }
    }
    return 1;
}

int isNotEmpty(char str[]) {
    return strlen(str) > 0;
}

void addStudent(struct student students[], int *numStudents) {
    FILE *file;
    file = fopen(filestudents, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct student newStudent;

    while (1) {
        printf("Enter Student ID: ");
        scanf("%s", newStudent.studentId);

        if (!isNotEmpty(newStudent.studentId)) {
            printf("Student ID cannot be empty. Please enter a valid ID.\n");
            continue;
        }

        if (!isUniqueID(students, *numStudents, newStudent.studentId)) {
            printf("Student ID already exists. Please enter a unique ID.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter Classroom ID: ");
        scanf("%s", newStudent.classroomId);

        if (!isNotEmpty(newStudent.classroomId)) {
            printf("Classroom ID cannot be empty. Please enter a valid Classroom ID.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter Name: ");
        scanf(" %[^\n]s", newStudent.name);

        if (!isNotEmpty(newStudent.name)) {
            printf("Name cannot be empty. Please enter a valid Name.\n");
            continue;
        }

        break;
    }

    printf("Enter Date of Birth (dd mm yyyy): ");
    scanf("%d %d %d", &newStudent.dateOfBirth.day, &newStudent.dateOfBirth.month, &newStudent.dateOfBirth.year);

    printf("Enter Gender (1 for Male, 0 for Female): ");
    scanf("%d", &newStudent.gender);

    while (1) {
        printf("Enter Email: ");
        scanf("%s", newStudent.email);

        if (!isNotEmpty(newStudent.email)) {
            printf("Email cannot be empty. Please enter a valid email.\n");
            continue;
        }

        if (!isValidEmail(newStudent.email)) {
            printf("Invalid email format. Please enter a valid email.\n");
            continue;
        }

        if (!isUniqueEmail(students, *numStudents, newStudent.email)) {
            printf("Email already exists. Please enter a unique email.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter Phone: ");
        scanf("%s", newStudent.phone);

        if (!isNotEmpty(newStudent.phone)) {
            printf("Phone number cannot be empty. Please enter a valid phone number.\n");
            continue;
        }

        if (!isUniquePhone(students, *numStudents, newStudent.phone)) {
            printf("Phone number already exists. Please enter a unique phone number.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter Password: ");
        scanf("%s", newStudent.password);

        if (!isNotEmpty(newStudent.password)) {
            printf("Password cannot be empty. Please enter a valid Password.\n");
            continue;
        }

        break;
    }

    // Write student information to file
    if(fprintf(file, "%s %s %s %d/%d/%d %d %s %s %s\n", newStudent.studentId, 
                                                     newStudent.classroomId, 
                                                     newStudent.name, 
                                                     newStudent.dateOfBirth.day, 
                                                     newStudent.dateOfBirth.month, 
                                                     newStudent.dateOfBirth.year, 
                                                     newStudent.gender, 
                                                     newStudent.email, 
                                                     newStudent.phone, 
                                                     newStudent.password)<0){
													 

	
    	perror("Error writing to file");
        fclose(file);
        return;
    }

    fclose(file);

    students[*numStudents] = newStudent; 
    (*numStudents)++;  
    printf("Added Student Successfully!\n");
}

void printStudents(struct student students[], int numStudents){

    printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
    printf("| %-10s | %-12s | %-20s | %-10s | %-6s | %-27s | %-13s |\n",
           "Student ID", "Classroom ID", "Name", "DOB", "Gender", "Email", "Phone");
    printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");

    int i;
    for (i = 0; i < numStudents; i++) {
        printf("| %-10s | %-12s | %-20s | %02d/%02d/%04d | %-6s | %-27s | %-13s |\n",
               students[i].studentId,
               students[i].classroomId,
               students[i].name,
               students[i].dateOfBirth.day,
               students[i].dateOfBirth.month,
               students[i].dateOfBirth.year,
               students[i].gender ? "Male" : "Female",
               students[i].email,
               students[i].phone);
        printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
    }
}
    

void searchStudentByName(struct student students[], int numStudents, const char* name){

    int i;
    bool found = false;
    printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
    printf("| %-10s | %-10s | %-20s | %-10s | %-6s | %-27s | %-13s |\n",
           "Student ID", "Classroom ID", "Name", "DOB", "Gender", "Email", "Phone");
    printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");

    for (i = 0; i < numStudents; ++i) {
        if (strcmp(students[i].name, name) == 0) {
            printf("| %-10s | %-12s | %-20s | %02d/%02d/%04d | %-6s | %-27s | %-13s |\n",
                   students[i].studentId,
                   students[i].classroomId,
                   students[i].name,
                   students[i].dateOfBirth.day,
                   students[i].dateOfBirth.month,
                   students[i].dateOfBirth.year,
                   students[i].gender ? "Male" : "Female",
                   students[i].email,
                   students[i].phone);
            printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
            found = true;
        }
    }

    if (!found) {
        printf("Teacher with name '%s' not found.\n", name);
    }
}

int findStudentIndex(struct student students[], int numStudents, const char* studentId) {
    int i=0;
	for (i; i < numStudents; ++i) {
        if (strcmp(students[i].studentId, studentId) == 0) {
            return i;
        }
    }
    return -1;
}

// Ham chinh sua thông tin sinh viên
void editStudent(struct student students[], int numStudents) {
    char studentId[20];
    int index;

    printf("Enter Student ID to edit: ");
    scanf("%s", studentId);

    // Tim kiem thong tin sinh vien theo ma sinh vien 
    index = findStudentIndex(students, numStudents, studentId);
    if (index == -1) {
        printf("Student not found!\n");
        return;
    }

    // Nhap cac thong tin sinh vien 
    printf("Enter new Classroom ID: ");
    scanf("%s", students[index].classroomId);

    printf("Enter new Name: ");
    scanf(" %[^\n]s", students[index].name);

    printf("Enter new Date of Birth (dd mm yyyy): ");
    scanf("%d %d %d", &students[index].dateOfBirth.day,
                      &students[index].dateOfBirth.month,
                      &students[index].dateOfBirth.year);

    printf("Enter new Gender (1 for Male, 0 for Female): ");
    scanf("%d", (int*)&students[index].gender);

    printf("Enter new Email: ");
    scanf("%s", students[index].email);

    printf("Enter new Phone: ");
    scanf("%s", students[index].phone);

    printf("Enter new Password: ");
    scanf("%s", students[index].password);

    printf("Student information updated successfully!\n");
}


void deleteStudentById(struct student students[], int *numStudents, const char* studentId) {
    int i = 0;
    for (i; i < *numStudents; ++i) {
        if (strcmp(students[i].studentId, studentId) == 0) {
            printf("Deleting student with ID %s\n", studentId);

            // Xac nhan xoa sinh viên
            char confirmation;
            printf("Are you sure you want to delete student with ID %s? (y/n): ", studentId);
            scanf(" %c", &confirmation);
            if (confirmation != 'y' && confirmation != 'Y') {
                printf("Deletion cancelled.\n");
                return;
            }

            // Di chuyen tat ca các phan tu sau sinh viên bi xoa lên mot vi tri 
            int j = i;
            for (j; j < *numStudents - 1; ++j) {
                students[j] = students[j + 1];
            }
            (*numStudents)--;
            printf("Student with ID %s has been deleted.\n", studentId);
            return;
        }
    }
    printf("Student with ID %s not found.\n", studentId);
}



void sortStudents(struct student students[], int numStudents, int sortOrder) {
    int i, j;
    struct student temp;

    for (i = 0; i < numStudents - 1; ++i) {
        for (j = 0; j < numStudents - 1 - i; ++j) {
            int compareResult = strcmp(students[j].name, students[j + 1].name);
            //neu lua chon la 1 va ten 1 lon hon ten 2 thi doi cho 
            if ((sortOrder == 1 && compareResult > 0) || (sortOrder == 2 && compareResult < 0)) {
                // Hoan doi hai sinh viên
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    if (sortOrder == 1) {
        printf("Students sorted by name in ascending order:\n");// tang dan 
    } else if (sortOrder == 2) {
        printf("Students sorted by name in descending order:\n");// giam dan 
    }
    printStudents(students, numStudents);
}


void sortMenu(struct student students[], int numStudents) {
    int sortOrder;
    printf("1. Sort Ascending\n");
    printf("2. Sort Descending\n");
    printf("Enter your choice: ");
    scanf("%d", &sortOrder);

    switch (sortOrder) {
        case 1:
            sortStudents(students, numStudents, 1);// tang dan 
            break;
        case 2:
            sortStudents(students, numStudents, 2);// giam dan 
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            sortMenu(students, numStudents); 
    }
}


void printAboutUs() {
	printf("+------------------------------------+------------------------------------+\n");
    printf("| %40s %32s \n","ABOUT US","|");
    printf("+------------------------------------+------------------------------------+\n");
    printf("| %50s %22s \n","STUDENT MANAGEMENT SYSTEM","|");
	printf("+------------------------------------+------------------------------------+\n");
    printf("| %-71s |\n", "This project is a simple Student Management System");
    printf("| %-71s |\n", "developed to demonstrate basic file handling,");
    printf("| %-71s |\n", "data structures, and user interaction in C programming.");
    printf("+------------------------------------+------------------------------------+\n");
    printf("| %-34s | %-34s |\n", "Project Developer:", "Contact Information:");
    printf("+------------------------------------+------------------------------------+\n");
    printf("| %-34s | %-34s |\n", "Name: Pham Cong Thanh", "Email: phamcongt56@gmail.com");
    printf("| %-34s | %-34s |\n", "Role: Software Developer", "");
    printf("+------------------------------------+------------------------------------+\n");
    printf("| %-71s |\n", "If you have any questions or need further assistance,");
    printf("| %-71s |\n", "please feel free to contact the developer.");
    printf("| %-71s |\n", "Thank you for using the Student Management System!");
    printf("+------------------------------------+------------------------------------+\n");
}

// phan nay cua giao vien
void teacherManagementMenu() {
    struct Teacher teachers[MAX_TEACHERS]; // Khai bao mang voi kich thuoc xac dinh 
    int numTeachers = 0;
    int choice;
    char teacherId[10];
    do {
        printf("+------------------------------------------+\n");
        printf("%-8s %-33s %s\n","|","TEACHER MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-15s %-26s %s\n","|","TEACHER MENU", "|");

        printf("+------------------------------------------+\n");
        printf("| %-3s | %-34s |\n", "[1]", "Add A New Teacher.");  
        printf("| %-3s | %-34s |\n", "[2]", "Show All Teachers.");  
        printf("| %-3s | %-34s |\n", "[3]", "Search A Teacher.");  
        printf("| %-3s | %-34s |\n", "[4]", "Edit A Teacher.");  
        printf("| %-3s | %-34s |\n", "[5]", "Delete A Teacher."); 
		printf("| %-3s | %-34s |\n", "[6]", "Sort A Teacher."); 
        printf("| %-3s | %-34s |\n", "[0]", "Exit the Program.");  
        printf("+------------------------------------------+\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTeacher(teachers, &numTeachers);
                break;

            case 2:
                readTeachersFromFile(fileteachers, teachers, &numTeachers);
                printTeachers(teachers, numTeachers);                
                break;

            case 3:
                readTeachersFromFile(fileteachers, teachers, &numTeachers);
                printTeachers(teachers, numTeachers);
                
                {
                char searchName[50];
                printf("Enter the name of the teacher you want to search: ");
                scanf(" %[^\n]s", searchName);
                searchTeacherByName(teachers, numTeachers, searchName);
                }

                writeTeachersToFile(fileteachers, teachers, numTeachers);
                break;

            case 4:
                readTeachersFromFile(fileteachers, teachers, &numTeachers);
                editTeacher(teachers, numTeachers);
                writeTeachersToFile(fileteachers, teachers, numTeachers);
                break;

            case 5:
                readTeachersFromFile(fileteachers, teachers, &numTeachers);
                printTeachers(teachers, numTeachers);
                
                {
                char teacherId[10];
                printf("Enter the teacher ID to delete: ");
                scanf("%s", teacherId);
                deleteTeacherById(teachers, &numTeachers, teacherId);
                }

                writeTeachersToFile(fileteachers, teachers, numTeachers);
                break;
			
			case 6:
				readTeachersFromFile(fileteachers, teachers, &numTeachers);
			    printTeachers(teachers, numTeachers);	
				sortTeacherMenu(teachers, numTeachers);
				writeTeachersToFile(fileteachers, teachers, numTeachers);
				break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                return; 
                
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);
}


void writeTeachersToFile(const char* filename, struct Teacher teachers[], int numTeachers) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file!\n");
        return;
    }
    int i=0;
	for (i; i < numTeachers; i++) {
        fprintf(file, "%s %s %s %02d/%02d/%04d %d %s %s %s\n",
                teachers[i].teacherId,
                teachers[i].classroomId,
                teachers[i].name,
                teachers[i].dateOfBirth.day,
                teachers[i].dateOfBirth.month,
                teachers[i].dateOfBirth.year,
                teachers[i].gender,
                teachers[i].email,
                teachers[i].phone,
                teachers[i].password);
    }
    fclose(file);
}

void readTeachersFromFile(const char* filename, struct Teacher teachers[], int *numTeachers) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file!\n");
        return;
    }
    int i = 0;
    while (fscanf(file, "%s %s %s %d/%d/%d %d %s %s %s",
                  teachers[i].teacherId,
                  teachers[i].classroomId,
                  teachers[i].name,
                  &teachers[i].dateOfBirth.day,
                  &teachers[i].dateOfBirth.month,
                  &teachers[i].dateOfBirth.year,
                  &teachers[i].gender,
                  teachers[i].email,
                  teachers[i].phone,
                  teachers[i].password) != EOF) {
        i++;
    }
    *numTeachers = i;
    if (ferror(file)) {
        perror("Error reading from file");
    }
    fclose(file);
}


int isUniqueTeacherID(struct Teacher teachers[], int numTeachers, char id[]) {
    int i=0; 
	for (i; i < numTeachers; i++) {
        if (strcmp(teachers[i].teacherId, id) == 0) {
            return 0;
        }
    }
    return 1;
}

int isUniqueTeacherEmail(struct Teacher teachers[], int numTeachers, char email[]) {
    int i=0; 
	for (i; i < numTeachers; i++) {
        if (strcmp(teachers[i].email, email) == 0) {
            return 0;
        }
    }
    return 1;
}

int isUniqueTeacherPhone(struct Teacher teachers[], int numTeachers, char phone[]) {
    int i=0; 
	for (i; i < numTeachers; i++) {
        if (strcmp(teachers[i].phone, phone) == 0) {
            return 0;
        }
    }
    return 1;
}

void addTeacher(struct Teacher teachers[], int *numTeachers) {
    FILE *file;
    file = fopen(fileteachers, "a"); 

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Teacher newTeacher;

    while (1) {
        printf("Enter Teacher ID: ");
        scanf("%s", newTeacher.teacherId);

        if (!isNotEmpty(newTeacher.teacherId)) {
            printf("Teacher ID cannot be empty. Please enter a valid ID.\n");
            continue;
        }

        if (!isUniqueTeacherID(teachers, *numTeachers, newTeacher.teacherId)) {
            printf("Teacher ID already exists. Please enter a unique ID.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter Classroom ID: ");
        scanf("%s", newTeacher.classroomId);

        if (!isNotEmpty(newTeacher.classroomId)) {
            printf("Classroom ID cannot be empty. Please enter a valid Classroom ID.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter Name: ");
        scanf(" %[^\n]s", newTeacher.name);

        if (!isNotEmpty(newTeacher.name)) {
            printf("Name cannot be empty. Please enter a valid Name.\n");
            continue;
        }

        break;
    }

    printf("Enter Date of Birth (dd mm yyyy): ");
    scanf("%d %d %d", &newTeacher.dateOfBirth.day, &newTeacher.dateOfBirth.month, &newTeacher.dateOfBirth.year);

    printf("Enter Gender (1 for Male, 0 for Female): ");
    scanf("%d", &newTeacher.gender);

    while (1) {
        printf("Enter Email: ");
        scanf("%s", newTeacher.email);

        if (!isNotEmpty(newTeacher.email)) {
            printf("Email cannot be empty. Please enter a valid email.\n");
            continue;
        }

        if (!isValidEmail(newTeacher.email)) {
            printf("Invalid email format. Please enter a valid email.\n");
            continue;
        }

        if (!isUniqueTeacherEmail(teachers, *numTeachers, newTeacher.email)) {
            printf("Email already exists. Please enter a unique email.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter Phone: ");
        scanf("%s", newTeacher.phone);

        if (!isNotEmpty(newTeacher.phone)) {
            printf("Phone number cannot be empty. Please enter a valid phone number.\n");
            continue;
        }

        if (!isUniqueTeacherPhone(teachers, *numTeachers, newTeacher.phone)) {
            printf("Phone number already exists. Please enter a unique phone number.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter Password: ");
        scanf("%s", newTeacher.password);

        if (!isNotEmpty(newTeacher.password)) {
            printf("Password cannot be empty. Please enter a valid Password.\n");
            continue;
        }

        break;
    }
   

      if (fprintf(file, "%s %s %s %d/%d/%d %d %s %s %s\n",
               newTeacher.teacherId,
               newTeacher.classroomId,
               newTeacher.name,
               newTeacher.dateOfBirth.day,
               newTeacher.dateOfBirth.month,
               newTeacher.dateOfBirth.year,
               newTeacher.gender,
               newTeacher.email,
               newTeacher.phone,
               newTeacher.password) < 0) {
        perror("Error writing to file");
        fclose(file);
        return;
    }

    fclose(file);

    teachers[*numTeachers] = newTeacher; 
    (*numTeachers)++;  
    printf("Added Teacher Successfully!\n");
}

void printTeachers(struct Teacher teachers[], int numTeachers) {
    printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
    printf("| %-10s | %-12s | %-20s | %-10s | %-6s | %-27s | %-13s |\n",
           "Student ID", "Classroom ID", "Name", "DOB", "Gender", "Email", "Phone");
    printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");

    int i;
    for (i = 0; i < numTeachers; i++) {
        printf("| %-10s | %-12s | %-20s | %02d/%02d/%04d | %-6s | %-27s | %-13s |\n",
               teachers[i].teacherId,
               teachers[i].classroomId,
               teachers[i].name,
               teachers[i].dateOfBirth.day,
               teachers[i].dateOfBirth.month,
               teachers[i].dateOfBirth.year,
               teachers[i].gender ? "Male" : "Female",
               teachers[i].email,
               teachers[i].phone);
        printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
    }
}
    

void searchTeacherByName(struct Teacher teachers[], int numTeachers, const char* name) {
    int i;
    bool found = false;
    printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
    printf("| %-10s | %-10s | %-20s | %-10s | %-6s | %-27s | %-13s |\n",
           "Teacher ID", "Classroom ID", "Name", "DOB", "Gender", "Email", "Phone");
    printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");

    for (i = 0; i < numTeachers; ++i) {
        if (strcmp(teachers[i].name, name) == 0) {
            printf("| %-10s | %-12s | %-20s | %02d/%02d/%04d | %-6s | %-27s | %-13s |\n",
                   teachers[i].teacherId,
                   teachers[i].classroomId,
                   teachers[i].name,
                   teachers[i].dateOfBirth.day,
                   teachers[i].dateOfBirth.month,
                   teachers[i].dateOfBirth.year,
                   teachers[i].gender ? "Male" : "Female",
                   teachers[i].email,
                   teachers[i].phone);
            printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
            found = true;
        }
    }

    if (!found) {
        printf("Teacher with name '%s' not found.\n", name);
    }
}

int findTeacherIndex(struct Teacher teachers[], int numTeachers, const char* teacherId) {
    int i=0;
	for (i; i < numTeachers; ++i) {
        if (strcmp(teachers[i].teacherId, teacherId) == 0) {
            return i;
        }
    }
    return -1;
}

// Ham chinh sua thông tin giao vien
void editTeacher(struct Teacher teachers[], int numTeachers) {
    char teacherId[20];
    int index;

    printf("Enter Student ID to edit: ");
    scanf("%s", &teacherId);

    index = findTeacherIndex(teachers, numTeachers, teacherId);
    if (index == -1) {
        printf("Student not found!\n");
        return;
    }

    printf("Enter new Classroom ID: ");
    scanf("%s", teachers[index].classroomId);

    printf("Enter new Name: ");
    scanf(" %[^\n]s", teachers[index].name);

    printf("Enter new Date of Birth (dd mm yyyy): ");
    scanf("%d %d %d", &teachers[index].dateOfBirth.day,
                      &teachers[index].dateOfBirth.month,
                      &teachers[index].dateOfBirth.year);

    printf("Enter new Gender (1 for Male, 0 for Female): ");
    scanf("%d", (int*)&teachers[index].gender);

    printf("Enter new Email: ");
    scanf("%s", teachers[index].email);

    printf("Enter new Phone: ");
    scanf("%s", teachers[index].phone);

    printf("Enter new Password: ");
    scanf("%s", teachers[index].password);

    printf("Teacher information updated successfully!\n");
}


void deleteTeacherById(struct Teacher teachers[], int *numTeachers, const char* teacherId) {
    int i = 0;
    for (i; i < *numTeachers; ++i) {
        if (strcmp(teachers[i].teacherId, teacherId) == 0) {
            printf("Deleting teacher with ID %s\n", teacherId);

            // Xac nhan xoa sinh viên
            char confirmation;
            printf("Are you sure you want to delete student with ID %s? (y/n): ", teacherId);
            scanf(" %c", &confirmation);
            if (confirmation != 'y' && confirmation != 'Y') {
                printf("Deletion cancelled.\n");
                return;
            }

            // Di chuyen tat ca các phan tu sau sinh viên bi xoa lên mot vi tri 
            int j = i;
            for (j; j < *numTeachers - 1; ++j) {
                teachers[j] = teachers[j + 1];
            }
            (*numTeachers)--;
            printf("Teacher with ID %s has been deleted.\n", teacherId);
            return;
        }
    }
    printf("Teacher with ID %s not found.\n", teacherId);
}



void sortTeachers(struct Teacher teachers[], int numTeachers, int sortOrder) {
    int i, j;
    struct Teacher temp;

    for (i = 0; i < numTeachers - 1; ++i) {
        for (j = 0; j < numTeachers - 1 - i; ++j) {
            int compareResult = strcmp(teachers[j].name, teachers[j + 1].name);
            //neu lua chon la 1 va ten 1 lon hon ten 2 thi doi cho 
            if ((sortOrder == 1 && compareResult > 0) || (sortOrder == 2 && compareResult < 0)) {
                // Hoan doi hai sinh viên
                temp = teachers[j];
                teachers[j] = teachers[j + 1];
                teachers[j + 1] = temp;
            }
        }
    }

    if (sortOrder == 1) {
        printf("Teacher sorted by name in ascending order:\n");// tang dan 
    } else if (sortOrder == 2) {
        printf("Teacher sorted by name in descending order:\n");// giam dan 
    }
    printTeachers(teachers, numTeachers);
}


void sortTeacherMenu(struct Teacher teachers[], int numTeachers) {
    int sortOrder;
    printf("1. Sort Ascending\n");
    printf("2. Sort Descending\n");
    printf("Enter your choice: ");
    scanf("%d", &sortOrder);

    switch (sortOrder) {
        case 1:
            sortTeachers(teachers, numTeachers, 1);// tang dan 
            break;
        case 2:
            sortTeachers(teachers, numTeachers, 2);// giam dan 
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            sortTeacherMenu(teachers, numTeachers); 
    }
}

// phan nay cua quan ly lop hoc 

int isUniqueClassID(struct Classroom classes[], int numClasses, char id[]) {
    int i=0;
	for (i; i < numClasses; i++) {
        if (strcmp(classes[i].classroomId, id) == 0) {
            return 0;
        }
    }
    return 1;
}

int isUniqueTeacherClassID(struct Classroom classes[], int numClasses, char teacherId[]) {
    int i=0;
	for (i; i < numClasses; i++) {
        if (strcmp(classes[i].teacherId, teacherId) == 0) {
            return 0;
        }
    }
    return 1;
}

void addClass(struct Classroom classes[], int *numClasses) {
    FILE *file = fopen(fileclass, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Classroom newClass;

    while (1) {
        printf("Enter Classroom ID: ");
        scanf("%s", newClass.classroomId);

        if (!isNotEmpty(newClass.classroomId)) {
            printf("Classroom ID cannot be empty. Please enter a valid ID.\n");
            continue;
        }

        if (!isUniqueClassID(classes, *numClasses, newClass.classroomId)) {
            printf("Classroom ID already exists. Please enter a unique ID.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter Teacher ID: ");
        scanf("%s", newClass.teacherId);

        if (!isNotEmpty(newClass.teacherId)) {
            printf("Teacher ID cannot be empty. Please enter a valid ID.\n");
            continue;
        }

        if (!isUniqueTeacherClassID(classes, *numClasses, newClass.teacherId)) {
            printf("Teacher ID already exists. Please enter a unique ID.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter Classroom Name: ");
        scanf(" %[^\n]s", newClass.classroomName);

        if (!isNotEmpty(newClass.classroomName)) {
            printf("Classroom Name cannot be empty. Please enter a valid name.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter Class Count: ");
        scanf("%d", &newClass.classCount);

        if (newClass.classCount < 0) {
            printf("Class Count cannot be negative. Please enter a valid number.\n");
            continue;
        }

        break;
    }
    
	while (1) {
        printf("Enter Student Count: ");
        scanf("%d", &newClass.studentCount);

        if (newClass.studentCount < 0) {
            printf("Class Count cannot be negative. Please enter a valid number.\n");
            continue;
        }

        break;
    }

    fprintf(file, "%s %d %s %s %d\n",
            newClass.classroomId,
            newClass.classCount,
            newClass.teacherId,
            newClass.classroomName,
            newClass.studentCount);

    fclose(file);

    classes[*numClasses] = newClass; 
    (*numClasses)++;  
    printf("Added Class Successfully!\n");
}

void printClasses(struct Classroom classes[], int numClasses) {
    printf("+--------------------------------------------------------------------+\n");
    printf("| %-10s | %-10s | %-10s | %-10s | %-12s |\n", "Class ID", "Class Count", "Teacher ID", "Class Name", "Student Count");
    printf("+--------------------------------------------------------------------+\n");
    int i=0;
	for (i; i < numClasses; i++) {
        printf("| %-10s | %-11d | %-10s | %-10s | %-13d |\n",
               classes[i].classroomId,
               classes[i].classCount,
               classes[i].teacherId,
               classes[i].classroomName,
               classes[i].studentCount);
    }
    printf("+--------------------------------------------------------------------+\n");
}

// doc file class.bin
void readClassesFromFile(const char* filename, struct Classroom classes[], int *numClasses) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    int i = 0;
    while (fscanf(file, "%s %d %s %s %d",
                  classes[i].classroomId,
                  &classes[i].classCount,
                  classes[i].teacherId,
                  classes[i].classroomName,
                  &classes[i].studentCount) != EOF) {
        i++;
    }
    *numClasses = i;
    fclose(file);
}

//ghi file class.bin
void writeClassesToFile(const char* filename, struct Classroom classes[], int numClasses) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    int i=0;
	for (i; i < numClasses; i++) {
        fprintf(file, "%s %d %s %s %d\n",
                classes[i].classroomId,
                classes[i].classCount,
                classes[i].teacherId,
                classes[i].classroomName,
                classes[i].studentCount);
    }
    fclose(file);
}

//ham tim kiem lop
void searchClassByName(struct Classroom classes[], int numClasses, char *searchName) {
    int found = 0;
    printf("+--------------------------------------------------------------------+\n");
    printf("| %-10s | %-10s | %-10s | %-10s | %-12s |\n", "Class ID", "Class Count", "Teacher ID", "Class Name", "Student Count");
    printf("+--------------------------------------------------------------------+\n");
    int i=0;
	for (i; i < numClasses; i++) {
        if (strstr(classes[i].classroomName, searchName) != NULL) {
        		printf("| %-10s | %-11d | %-10s | %-10s | %-13d |\n",
                   classes[i].classroomId,
                   classes[i].classCount,
                   classes[i].teacherId,
                   classes[i].classroomName,
                   classes[i].studentCount);
            found = 1;
        }
    }
    printf("+--------------------------------------------------------------------+\n");
    if (!found) {
        printf("No class found with the name: %s\n", searchName);
    }
}
//ham chinh sua
void editClass(struct Classroom classes[], int numClasses) {
    char classId[20];
    printf("Enter the Classroom ID to edit: ");
    scanf("%s", classId);
    int i=0;
	for (i; i < numClasses; i++) {
        if (strcmp(classes[i].classroomId, classId) == 0) {
            printf("Enter new Teacher ID: ");
            scanf("%s", classes[i].teacherId);
            printf("Enter new Class Count: ");
            scanf("%d", classes[i].classCount);
            printf("Enter new Classroom Name: ");
            scanf(" %[^\n]s", classes[i].classroomName);
            printf("Enter new Student Count: ");
            scanf("%d", classes[i].studentCount);
            printf("Classroom updated successfully!\n");
            return;
        }
    }
    printf("Classroom ID not found.\n");
}

//ham xoa 
void deleteClassById(struct Classroom classes[], int *numClasses, char *classId) {
    int i=0;
	for (i; i < *numClasses; i++) {
        if (strcmp(classes[i].classroomId, classId) == 0) {
            int j=i;
			for (j; j < *numClasses - 1; j++) {
                classes[j] = classes[j + 1];
            }
            (*numClasses)--;
            printf("Classroom deleted successfully!\n");
            return;
        }
    }
    printf("Classroom ID not found.\n");
}
void sortClasses(struct Classroom classes[], int numClasses, int sortOrder) {
    int i=0, j=0;
    struct Classroom temp;

    for (i; i < numClasses - 1; ++i) {
        for (j; j < numClasses - 1 - i; ++j) {
            int compareResult = strcmp(classes[j].classroomName, classes[j + 1].classroomName);
            if ((sortOrder == 1 && compareResult > 0) || (sortOrder == 2 && compareResult < 0)) {
                temp = classes[j];
                classes[j] = classes[j + 1];
                classes[j + 1] = temp;
            }
        }
    }

    if (sortOrder == 1) {
        printf("Classes sorted by name in ascending order:\n"); 
    } else if (sortOrder == 2) {
        printf("Classes sorted by name in descending order:\n"); 
    }
    printClasses(classes, numClasses);
}

void sortClassMenu(struct Classroom classes[], int numClasses) {
    int sortOrder;
    printf("1. Sort Ascending\n");
    printf("2. Sort Descending\n");
    printf("Enter your choice: ");
    scanf("%d", &sortOrder);

    switch (sortOrder) {
        case 1:
            sortClasses(classes, numClasses, 1); 
            break;
        case 2:
            sortClasses(classes, numClasses, 2); 
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            sortClassMenu(classes, numClasses); 
    }
}

void ClassroomsManagement() {
    struct Classroom classes[MAX_CLASSES];
    int numClasses = 0;
    int choice;
    char classId[20];

    do {
        printf("+------------------------------------------+\n");
        printf("%-8s %-33s %s\n", "|", "CLASSROOM MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-15s %-26s %s\n", "|", "CLASS MENU", "|");
        printf("+------------------------------------------+\n");
        printf("| %-3s | %-34s |\n", "[1]", "Add A New Class.");
        printf("| %-3s | %-34s |\n", "[2]", "Show All Classes.");
        printf("| %-3s | %-34s |\n", "[3]", "Search A Class.");
        printf("| %-3s | %-34s |\n", "[4]", "Edit A Class.");
        printf("| %-3s | %-34s |\n", "[5]", "Delete A Class.");
        printf("| %-3s | %-34s |\n", "[6]", "Sort class list.");
        printf("| %-3s | %-34s |\n", "[0]", "Exit the Program");
        printf("+------------------------------------------+\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addClass(classes, &numClasses);
                writeClassesToFile(fileclass, classes, numClasses);
                break;

            case 2:
                readClassesFromFile(fileclass, classes, &numClasses);
                printClasses(classes, numClasses);
                break;

            case 3:
                readClassesFromFile(fileclass, classes, &numClasses);
                char searchName[50];
                printf("Enter the name of the class you want to search: ");
                scanf(" %[^\n]s", searchName);
                searchClassByName(classes, numClasses, searchName);
                break;

            case 4:
                readClassesFromFile(fileclass, classes, &numClasses);
                editClass(classes, numClasses);
                writeClassesToFile(fileclass, classes, numClasses);
                break;

            case 5:
                readClassesFromFile(fileclass, classes, &numClasses);
                printClasses(classes, numClasses);
                printf("Enter the Class ID to delete: ");
                scanf("%s", classId);
                deleteClassById(classes, &numClasses, classId);
                writeClassesToFile(fileclass, classes, numClasses);
                break;
                
			case 6:
                readClassesFromFile(fileclass, classes, &numClasses);
                printClasses(classes, numClasses);
				sortClassMenu(classes, numClasses);
                writeClassesToFile(fileclass, classes, numClasses);
                break;
						
            case 0:
                printf("Exiting the program. Goodbye!\n");
                return;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);
}

void viewClassList(struct student students[], int numStudents) {
    char classId[20];
    
    printf("Enter the Class Id you want to see the list of: ");
    scanf("%s", classId);

    printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
    printf("| %-10s | %-12s | %-20s | %-10s | %-6s | %-27s | %-13s |\n",
           "Student ID", "Classroom ID", "Name", "DOB", "Gender", "Email", "Phone");
    printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
    
    int found = 0;
    int i;
    for (i = 0; i < numStudents; i++) {
        if (strcmp(students[i].classroomId, classId) == 0) {
            found = 1;
            printf("| %-10s | %-12s | %-20s | %02d/%02d/%04d | %-6s | %-27s | %-13s |\n",
                   students[i].studentId,
                   students[i].classroomId,
                   students[i].name,
                   students[i].dateOfBirth.day,
                   students[i].dateOfBirth.month,
                   students[i].dateOfBirth.year,
                   students[i].gender ? "Male" : "Female",
                   students[i].email,
                   students[i].phone);
            printf("+------------+--------------+----------------------+------------+--------+-----------------------------+---------------+\n");
        }
    }

    if (!found) {
        printf("Class with ID not found: %s\n", classId);
    }
}

void readScoresFromFile(const char* filename, struct score scores[], int *numScores) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file!\n");
        return;
    }
    int i = 0;
    while (fscanf(file, "%s %s %lf %lf %lf %lf %lf %lf",
                  scores[i].studentId,
                  scores[i].studentName,
                  &scores[i].regularPoints1,
                  &scores[i].regularPoints2,
                  &scores[i].regularPoints3,
                  &scores[i].regularPoints4,
                  &scores[i].midtermExamScore,
                  &scores[i].finalExamScore) != EOF) {
        i++;
    }
    *numScores = i;
    if (ferror(file)) {
        perror("Error reading from file");
    }
    fclose(file);
}

void writeScoresToFile(const char* filename, struct score scores[], int numScores) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file!\n");
        return;
    }
    int i=0; 
	for (i; i < numScores; i++) {
        fprintf(file, "%s %s %.1f %.1f %.1f %.1f %.1f %.1f\n",
                scores[i].studentId,
                scores[i].studentName,
                scores[i].regularPoints1,
                scores[i].regularPoints2,
                scores[i].regularPoints3,
                scores[i].regularPoints4,
                scores[i].midtermExamScore,
                scores[i].finalExamScore);
    }
    fclose(file);
}

void viewScoresAsTable(struct score scores[], int numScores) {

	printf("+------------+--------------+------+------+------+------+------------------+---------------+------------+\n");
	printf("| Student ID | Student Name | RP1  | RP2  | RP3  | RP4  | Midterm Exam     | Final Exam    | Total      |\n");
	printf("+------------+--------------+------+------+------+------+------------------+---------------+------------+\n");
	int i=0; 
    for (i; i < numScores; i++) {
        double totalScore = ((scores[i].regularPoints1+scores[i].regularPoints2+scores[i].regularPoints3+scores[i].regularPoints4)+scores[i].midtermExamScore*2 +scores[i].finalExamScore*3)/9; 
		printf("| %10s | %-12s | %4.1f | %4.1f | %4.1f | %4.1f | %16.1f | %13.1f | %10.1f |\n",               
			scores[i].studentId,
            scores[i].studentName,
            scores[i].regularPoints1,
 	    	scores[i].regularPoints2,
            scores[i].regularPoints3,
            scores[i].regularPoints4,
            scores[i].midtermExamScore,
            scores[i].finalExamScore,
            totalScore);
        printf("+------------+--------------+------+------+------+------+------------------+---------------+------------+\n");	}
}	

void editScore(struct score scores[], int numScores) {
    char studentId[20];
    double newRegularPoints1, newRegularPoints2, newRegularPoints3, newRegularPoints4, newMidtermExamScore, newFinalExamScore;

    printf("Enter Student ID to edit: ");
    scanf("%s", studentId);

    int found = 0;
    int i=0; 
	for (i; i < numScores; i++) {
        if (strcmp(scores[i].studentId, studentId) == 0) {
            printf("Enter new Regular Points 1: ");
            scanf("%lf", &newRegularPoints1);
            printf("Enter new Regular Points 2: ");
            scanf("%lf", &newRegularPoints2);
            printf("Enter new Regular Points 3: ");
            scanf("%lf", &newRegularPoints3);
            printf("Enter new Regular Points 4: ");
            scanf("%lf", &newRegularPoints4);
            printf("Enter new Midterm Exam Score: ");
            scanf("%lf", &newMidtermExamScore);
            printf("Enter new Final Exam Score: ");
            scanf("%lf", &newFinalExamScore);

            scores[i].regularPoints1 = newRegularPoints1;
            scores[i].regularPoints2 = newRegularPoints2;
            scores[i].regularPoints3 = newRegularPoints3;
            scores[i].regularPoints4 = newRegularPoints4;
            scores[i].midtermExamScore = newMidtermExamScore;
            scores[i].finalExamScore = newFinalExamScore;

            printf("Updated scores for student ID %s\n", studentId);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student ID %s not found!\n", studentId);
    }
}

