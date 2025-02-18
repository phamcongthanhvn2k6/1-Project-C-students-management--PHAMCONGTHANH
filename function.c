// noi trien khai cac ham 
#include "function.h"
#include "datatype.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxlop 100 

void menu(){
	
login(); // G?i hàm dang nh?p tru?c khi hi?n th? menu chính
    int choice;
    do {
        // Hi?n th? menu chính
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
                adminMenu();
                break;
            case 2:
                studentMenu();
                break;
            case 3:
                teacherMenu();
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);
}

// Hàm dang nh?p
void login() {
    char email[50];
    char password[50];
    
    printf("+------------------------------------------+\n");
	printf("%-8s %-33s %s\n","|","STUDENT MANAGEMENT SYSTEM", "|");
    printf("+------------------------------------------+\n");
    printf("%-17s %-24s %s\n","|","LOGIN", "|");

    printf("+------------------------------------------+\n");
    
    // Yêu c?u nh?p email
    printf("Email: ");
    scanf("%s", email);
    
    // Yêu c?u nh?p m?t kh?u
    printf("Password: ");
    scanf("%s", password);
    
    // Ki?m tra thông tin dang nh?p
    // Ðây là ví d? don gi?n, b?n có th? thay th? b?ng cách ki?m tra thông tin t? co s? d? li?u
    if (strcmp(email, "phamcongthanh") == 0 && strcmp(password, "123456789") == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password. Exiting the program.\n");
        exit(1);
    }
}

// Hàm menu cho Admin
void adminMenu(){
	int choice;
    do {
        // Hi?n th? menu chính
        printf("+------------------------------------------+\n");
		printf("%-8s %-33s %s\n","|","STUDENT MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-19s %-22s %s\n","|","MENU", "|");

        printf("+------------------------------------------+\n");
        printf("| %-3s | %-34s |\n", "[1]", "Students Management.");
        printf("| %-3s | %-34s |\n", "[2]", "Classrooms Management.");
        printf("| %-3s | %-34s |\n", "[3]", "teacher Management.");
        printf("| %-3s | %-34s |\n", "[4]", "User Guideline.");
		printf("| %-3s | %-34s |\n", "[5]", "About Us.");
		printf("| %-3s | %-34s |\n", "[0]", "Exit the Program");
        printf("+------------------------------------------+\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                break;
                
            case 2:
                break;
                
            case 3:
                break;
            
            case 4:
            	break;
            	
            case 5:
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
void studentMenu() {
	int choice;
    do {
        // Hien thi menu chính
        printf("+------------------------------------------+\n");
		printf("%-8s %-33s %s\n","|","STUDENT MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-15s %-26s %s\n","|","STUDENT MENU", "|");

        printf("+------------------------------------------+\n");
        printf("| %-3s | %-34s |\n", "[1]", "Add A New Student.");
        printf("| %-3s | %-34s |\n", "[2]", "Show All Students.");
        printf("| %-3s | %-34s |\n", "[3]", "Seach A Students");
        printf("| %-3s | %-34s |\n", "[4]", "Edit A students");
		printf("| %-3s | %-34s |\n", "[5]", "Delete A Students.");
		printf("| %-3s | %-34s |\n", "[0]", "Exit the Program");
        printf("+------------------------------------------+\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                break;
                
            case 2:
                break;
                
            case 3:
                break;
            
            case 4:
            	break;
            	
            case 5:
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


// Hàm menu cho Teacher
void teacherMenu() {
	int choice;
    do {
        // Hien thi menu chính
        printf("+------------------------------------------+\n");
		printf("%-8s %-33s %s\n","|","STUDENT MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-15s %-26s %s\n","|","TEACHER MENU", "|");

        printf("+------------------------------------------+\n");
        printf("| %-3s | %-34s |\n", "[1]", "View Class List.");
        printf("| %-3s | %-34s |\n", "[2]", "Add Grades.");
		printf("| %-3s | %-34s |\n", "[0]", "Back to Main Menu");
        printf("+------------------------------------------+\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                break;
                
            case 2:
                break;
                
            case 3:
                break;
            
            case 4:
            	break;
            	
            case 5:
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


