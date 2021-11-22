#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 41
#define ID_LEN 11
#define EMAIL_LEN 41

struct student  // struct for each node
{
    char name[NAME_LEN];
    char ID[ID_LEN];
    char email[EMAIL_LEN];
    int presentation;
    int essay;
    int project;
    struct student *next;
};

void search(struct student *list);           // prototype
struct student *add(struct student *list);   // prototype
void edit(struct student *list);             // prototype
int read_line(char str[], int n);            // prototype
void printList(struct student *list);        // prototype
void deleteNode(struct student **head_ref);  // prototype

int main() {
    int input;
    struct student *student_list = NULL;  // Head Node
    struct student *temp;
    for (;;) {
        printf("\nMenu: \n");
        printf("1. Search For Student \n");
        printf("2. Add Student \n");
        printf("3. Delete Student \n");
        printf("4. Edit Student \n");
        printf("5. Exit Program  \n\n");
        printf("Input: ");
        scanf("%d", &input);

        switch (input) {
            case 1:
                search(student_list);
                break;
            case 2:
                //if head is equal to null then if not then stu_list->next
                if(student_list == NULL){
                    student_list = add(student_list);
                }
                else{
                    temp = student_list;
                    while(temp->next != NULL){
                        temp = temp->next;
                    }
                    temp->next = add(student_list);
                }
                break;
            case 3:
                deleteNode(&student_list);
                break;
            case 4:
                edit(student_list);
                break;
            case 5:
                return 0;
                break;
            default:
                printf("Invalid input, Enter a valid Number: \n\n");
                break;
        }
    }
    return 0;
}

void search(struct student *list)  // look for specific student using ID
{
    struct student* temp = list;
    struct student* prev;
    char ID[ID_LEN];
    printf("Enter Student ID: ");
    read_line(ID, ID_LEN);
    bool flag = 0;
    
    while(temp != NULL && flag != 1)  // loops through linked list
    {
        if (strcmp(temp->ID, ID) == 0)  // checks for match
        {
            printList(temp);
            flag = 1;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    if (flag == 0) printf("\nID Not Found \n");
}

struct student *add(struct student *list) {
    int flag =0;
    char name[NAME_LEN];
    char ID[ID_LEN];
    char email[EMAIL_LEN];
    int presentation = 100;
    int essay = 100;
    int project = 100;
    struct student *new_node;  // for the newest node
    struct student *p;  // a structured pointer for looping through the list

    if(!(new_node = (struct student*) malloc(sizeof(struct student)))){//frees up memory
        printf("malloc failed in ADD");
        return list;
    }

    /* Grabs User Info */
    printf("Enter Student Name: ");
    //read_line(name, NAME_LEN);
    read_line(name, NAME_LEN);
    strcpy(new_node->name, name);
    printf("Enter The ID: ");
    read_line(ID, ID_LEN);
    strcpy(new_node->ID, ID);
    for (p = list; p != NULL; p = p->next)  // checks to see if student already exists
    {
        if (strcmp(p->name, name) == 0 && strcmp(p->ID, ID) == 0) {
            printf(
                    "Update the student list instead of a new entry, student already "
                    "exists. \n");
            return list;
        }
    }

    /* grabs inputs */
    printf("Enter An Email: ");
    read_line(email, EMAIL_LEN);
    strcpy(new_node->email, email);
    while (presentation < 0 || presentation > 4) {
        printf("Enter Presentation Grade (0-4): ");
        scanf("%d", &presentation);
        new_node->presentation = presentation;
    }
    while (essay < 0 || essay > 4) {
        printf("Enter Essay Grade (0-4): ");
        scanf("%d", &essay);
        new_node->essay = essay;
    }
    while (project < 0 || project > 4) {
        printf("Enter Project Grade (0-4): ");
        scanf("%d", &project);
        new_node->project = project;
       // flag = 1;
    }

    /* Copies over input data into new node */    
    new_node->next = NULL;

    // printf("New node \n");
    // printList(new_node);
    return new_node;
}

void deleteNode(struct student **head_ref) {
    char key[ID_LEN];
    printf("Enter Student ID to delete: ");
    read_line(key, ID_LEN);
    // Store head node
    struct student *temp = *head_ref, *prev;
    
    // If head node itself holds the key to be deleted
    if (temp != NULL && strcmp(temp->ID, key) == 0) {
        *head_ref = temp->next;  // Changed head
        free(temp);              // free old head
        printf("Delete Complete");
    }

        // Search for the key to be deleted, keep track of the
        // previous node as we need to change 'prev->next'

    else {
        //for (p = list; p != NULL; p = p->next)
        while (temp != NULL && strcmp(temp->ID, key) != 0){
            prev = temp;
            temp = temp->next;
        }
            // if you find the id then store target in temp and store its previous
            

        // If key was not present in linked list
        if (temp == NULL) {
            printf("ID Not Found");
        } else {
            // Unlink the node from linked list
            prev->next = temp->next;

            free(temp);  // Free memory

            printf("Deleted \n");
        }
    }
}

/***
 * This function was created to edit the student grade.
 ***/
void edit(struct student *list) {
    char name[NAME_LEN];
    char studentID[ID_LEN];
    int pres;
    int ess;
    int proj;

    /*asks user for student information*/
    printf("Enter student NAME: ");
    read_line(name, NAME_LEN);

    printf("Enter student U ID: ");
    read_line(studentID, ID_LEN);

    /*searching for student to edit*/
    int flag = 0;
    struct student *edit_student;
    for (edit_student = list; edit_student != NULL;
         edit_student = edit_student->next) {
        if ((strcmp(edit_student->name, name) == 0) &&
            ((strcmp(edit_student->ID, studentID) == 0))) {
            flag = 1;

            /*info that needs to be edited*/
            printf("Enter new PRESENTATION grade: ");
            scanf("%d", &pres);
            printf("Enter new ESSAY grade: ");
            scanf("%d", &ess);
            printf("Enter new PROJECT grade: ");
            scanf("%d", &proj);

            edit_student->presentation = pres;
            edit_student->essay = ess;
            edit_student->project = proj;
        }
    }

    if (!flag) {
        printf("Student not found!");
    }
}

void printList(struct student *list) { //prints out student nodes
    printf("Name: %s \n", list->name);
    printf("ID: %s \n", list->ID);
    printf("Email: %s \n", list->email);
    printf("Presentation Grade: %d \n", list->presentation);
    printf("Essay Grade: %d \n", list->essay);
    printf("Project Grade: %d \n", list->project);
}

int read_line(char str[], int n)  // reads user input
{
    int ch, i = 0;

    while (isspace(ch = getchar()))
        ;  // gets rid of spaces
        
    str[i++] = ch;
    while ((ch = getchar()) != '\n') {  // loops while getchar isnt an enter key
        if (i < n) str[i++] = ch;
    }
    str[i] = '\0';
    return i;  // returns counter
}
