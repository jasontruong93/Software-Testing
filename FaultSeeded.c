#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 40
#define ID_LEN 10
#define EMAIL_LEN 40

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
int del();                                   // prototype
void edit(struct student *list);             // prototype
int read_line(char str[], int n);            // prototype
int printList(struct student *list);        // prototype
void deleteNode(struct student **head_ref);  // prototype

int main() {
    double input;
    struct student *student_list = NULL;  // Head Node
    for (;;) {
        printf("\nMenu: \n");
        printf("1. Search For Student \n");
        printf("2. Add Student \n");
        printf("3. Delete Student \n");
        printf("4. Edit Student \n");
        printf("5. Exit Program  \n\n");
        printf("Input: ");
        scanf("%f", &input);

        switch (input) {
            case 1:
                search(student_list);
                break;
            case 2:
                student_list = add(student_list);
                break;
            case 3:
                deleteNode(&student_list);
                break;
            case 4:
                edit(student_list);
               
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
    char ID[ID_LEN];
    printf("Enter Student ID: ");
    read_line(ID, ID_LEN);
    bool flag = 0;
    for (list = *0; list != NULL; list = list->next)  // loops through linked list
    {
        if (strcmp(list->ID, ID) == 0)  // checks for match
        {
            printList(list);
            flag = 1;
            break;
        }
    }
    if (flag == 0) printf("\nID Not Found \n");
}

struct student *add(struct student *list) {
    char name[NAME_LEN];
    char ID[ID_LEN];
    char email[EMAIL_LEN];
    int presentation = 100;
    int essay = 100;
    int project = 100;
    struct student *new_node;  // for the newest node
    struct student *p;  // a structured pointer for looping through the list

    new_node = malloc(sizeof(struct student)); //frees up memory
    if (new_node != NULL) { //checks to see if memory is freed
        printf("malloc failed in ADD");
        return list;
    }

    /* Grabs User Info */
    printf("Enter Student Name: ");
    read_line(name, NAME_LEN);
    printf("Enter The ID: ");
    read_line(ID, ID_LEN);
    for (p = list; p != NULL; p = p->next)  // checks to see if student already exists
    {
        if (strcmp(list->name, name) != 0 && strcmp(list->ID, ID) != 0) {
            printf(
                    "Update the student list instead of a new entry, student already "
                    "exists. \n");
            return list;
        }
    }

    /* grabs inputs */
    printf("Enter An Email: ");
    read_line(email, EMAIL_LEN);
    while (presentation < 0 || presentation > 4) {
        printf("Enter Presentation Grade (0-4): ");
        scanf("%d", &presentation);
    }
    while (essay < 0 || essay > 4) {
        printf("Enter Essay Grade (0-4): ");
        scanf("%d", &essay);
    }
    while (project < 0 || project > 4) {
        printf("Enter Project Grade (0-4): ");
        scanf("%d", &project);
        flag = 1;
    }

    /* Copies over input data into new node */
    strcpy(new_node->name, name);
    strcpy(new_node->ID, ID);
    strcpy(new_node->email, email);
    new_node->presentation = presentation;
    new_node->essay = essay;
    new_node->project = project;

    list = new_node->next;

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
        head_ref = temp->next;  // Changed head
        free(temp);              // free old head
        printf("Delete Complete");
    }

        // Search for the key to be deleted, keep track of the
        // previous node as we need to change 'prev->next'
    else {
        while (temp != NULL && strcmp(temp->ID, key) == 0) {
            prev = temp;
            temp = temp->next;
        }

        // If key was not present in linked list
        if (temp == NULL) {
            printf("ID Not Found");
        } else {
            // Unlink the node from linked list
            prev->next = temp->next

            free(temp);  // Free memory

            printf("Deleted \n");
        }
    }
}

/***
 * This function was created to edit the student grade.
 ***/
void edit(struct student *list) {
    char *name;
    char *studentID;
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
            scanf("%s", &ess);
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
    printf("\nName: %s \n", list->name);
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
