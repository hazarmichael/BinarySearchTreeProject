/*
Name: Hazar Michael 
ID: 1201838
section: 1 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    struct Student { //  a structure to represent a student node in the BST
        int student_id;
        char name[50];
        char city[50];
        int class_id;
        char enrollment_date[20];
        struct Student* left; // Pointer to the left child node
        struct Student* right; // Pointer to the right child node
    };

typedef struct Student StudentNode;

// Define the structure for holding student information.
struct StudentInfo {
    int student_id;
    char name[50];
    char city[50];
    int class_id;
    char enrollment_date[20];
};

// allocates memory for a new student node and initializes its fields.
StudentNode* createNode(int student_id, char* name, char* city, int class_id, char* enrollment_date) { 
    StudentNode* newNode = (StudentNode*)malloc(sizeof(StudentNode)); // Allocate memory for a new node
    newNode->student_id = student_id; 
    strcpy(newNode->name, name);  
    strcpy(newNode->city, city);
    newNode->class_id = class_id;
    strcpy(newNode->enrollment_date, enrollment_date);
    newNode->left = newNode->right = NULL; // Initialize left and right child pointers to NULL
    return newNode;
}



// Function to insert a new student node into the BST based on the student's ID.
StudentNode* insertStudent(StudentNode* root, int student_id, char* name, char* city, int class_id, char* enrollment_date) {
    if (root == NULL) {  // If the tree or subtree is empty, create a new node and return it as the root

        return createNode(student_id, name, city, class_id, enrollment_date);
    }


    if (student_id < root->student_id) {
        // If the given student ID is less than the root node's student ID, recursively insert into the left subtree

        root->left = insertStudent(root->left, student_id, name, city, class_id, enrollment_date);
    } else if (student_id > root->student_id) {
         // If the given student ID is greater than the root node's student ID, recursively insert into the right subtree
        root->right = insertStudent(root->right, student_id, name, city, class_id, enrollment_date);
    } else {
        // Duplicate student ID, do not insert
        printf("Error: Student with ID %d already exists.\n", student_id);
    }
    return root;
}

//searches for a student node with a given ID in the BST.
StudentNode* findStudent(StudentNode* root, int student_id) {
    if (root == NULL || root->student_id == student_id) {
        return root;
    }

    if (student_id < root->student_id) { // If the given student ID is less than the root node's student ID, recursively search in the left subtree

        return findStudent(root->left, student_id);
    }

    // If the given student ID is greater than the root node's student ID, recursively search in the right subtree
    return findStudent(root->right, student_id);
}

// finds the node with the minimum student ID in a given subtree, i used it in the delete student func. only 
StudentNode* findMinStudent(StudentNode* root) { 
    if (root == NULL) {        // If the tree or subtree is empty, return NULL

        return NULL;
    }

    while (root->left != NULL) { // Traverse to the leftmost node to find the minimum student ID

        root = root->left;
    }
    return root;
}

// Function to delete a student node with a given ID from the BST.
StudentNode* deleteStudent(StudentNode* root, int student_id) {
    if (root == NULL) {
        return root;
    }

    if (student_id < root->student_id) {
 // If the given student ID is less than the root node's student ID, recursively delete from the left subtree
        root->left = deleteStudent(root->left, student_id);
    } else if (student_id > root->student_id) {
    // If the given student ID is greater than the root node's student ID, recursively delete from the right subtree

        root->right = deleteStudent(root->right, student_id);
    } else {
        if (root->left == NULL) {
         // If the node to be deleted has no left child, replace it with its right child

            StudentNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
        // If the node to be deleted has no right child, replace it with its left child

            StudentNode* temp = root->left;
            free(root);
            return temp;
        }

        // If the node to be deleted has both left and right children
        StudentNode* temp = findMinStudent(root->right);  // Find the node with the minimum student ID in the right subtree
        root->student_id = temp->student_id;  // Copy the data of the minimum node to the current node
        strcpy(root->name, temp->name);
        strcpy(root->city, temp->city);
        root->class_id = temp->class_id;
        strcpy(root->enrollment_date, temp->enrollment_date);
        root->right = deleteStudent(root->right, temp->student_id);
    }
    return root;
}

// Function to perform an inorder traversal of the BST and populate an array with student information.
void inorderTraversal(StudentNode* root, struct StudentInfo* studentArray, int* index) {
    if (root != NULL) {
        inorderTraversal(root->left, studentArray, index);
        
        // Copy student information to the studentArray
        studentArray[*index].student_id = root->student_id;
        strcpy(studentArray[*index].name, root->name);
        strcpy(studentArray[*index].city, root->city);
        studentArray[*index].class_id = root->class_id;
        strcpy(studentArray[*index].enrollment_date, root->enrollment_date);
        (*index)++;
        
        inorderTraversal(root->right, studentArray, index);
    }
}

// Function to compare student names for sorting purposes.
int compareNames(const void* a, const void* b) {
    struct StudentInfo* studentA = (struct StudentInfo*) a;
    struct StudentInfo* studentB = (struct StudentInfo*) b;

    return strcmp(studentA->name, studentB->name);
}

// Function to count the number of students in the BST.
int countStudents(StudentNode* root) {
    if (root == NULL) {
        return 0;
    } else {
        return countStudents(root->left) + countStudents(root->right) + 1;
    }
}

void printStudentsInLexicographicOrder(StudentNode* root) {
    // Count the number of students
    int numStudents = countStudents(root);

    // Create an array to hold student information
    struct StudentInfo* studentArray = (struct StudentInfo*) malloc(numStudents * sizeof(struct StudentInfo));
    int index = 0;

    // Perform inorder traversal and populate the student array
    inorderTraversal(root, studentArray, &index);

    // Sort the student array based on names
    qsort(studentArray, numStudents, sizeof(struct StudentInfo), compareNames);

    // Print the sorted student records
    for (int i = 0; i < numStudents; i++) {
        printf("Student ID: %d\n", studentArray[i].student_id);
        printf("Name: %s\n", studentArray[i].name);
        printf("City: %s\n", studentArray[i].city);
        printf("Class ID: %d\n", studentArray[i].class_id);
        printf("Enrollment Date: %s\n", studentArray[i].enrollment_date);
        printf("---------------------------------\n");
    }

    // Free the memory allocated for the student array
    free(studentArray);
}

void printIDs(StudentNode* root) {  // this function is only for making sure that the data is inserted correctly
                                   // in in order traversal
    if (root != NULL) {
        printIDs(root->left);
        printf("%d ", root->student_id);
        printIDs(root->right);
    }
}


// Function to populate an array with student information based on a specific city.
void populateStudentArray(StudentNode* node, char* city, struct StudentInfo* studentArray, int* index) {
    if (node != NULL) {
        populateStudentArray(node->left, city, studentArray, index);

        
         // Check if the current student's city matches the specified city
        if (strcmp(node->city, city) == 0) {
        
            studentArray[*index].student_id = node->student_id;
            strcpy(studentArray[*index].name, node->name);
            strcpy(studentArray[*index].city, node->city);
            studentArray[*index].class_id = node->class_id;
            strcpy(studentArray[*index].enrollment_date, node->enrollment_date);
            (*index)++; // Increment the index to store the next student information

        }
        populateStudentArray(node->right, city, studentArray, index);
    }
}

// Function to search and display student records by a specific city.
void searchByCity(StudentNode* root, char* city) {
    int studentCount = countStudents(root);
    struct StudentInfo* studentArray = (struct StudentInfo*)malloc(studentCount * sizeof(struct StudentInfo));

    int index = 0;
    populateStudentArray(root, city, studentArray, &index);

    qsort(studentArray, index, sizeof(struct StudentInfo), compareNames);

    // Iterate over the studentArray and display each student's information
    for (int i = 0; i < index; i++) {
        printf("Student ID: %d\n", studentArray[i].student_id);
        printf("Name: %s\n", studentArray[i].name);
        printf("City: %s\n", studentArray[i].city);
        printf("Class ID: %d\n", studentArray[i].class_id);
        printf("Enrollment Date: %s\n", studentArray[i].enrollment_date);
        printf("---------------------------------\n");
    }

    free(studentArray); // Free the memory allocated
}

void populateStudentArrayByClass(StudentNode* node, int class_id, struct StudentInfo* studentArray, int* index) {
    if (node != NULL) {
        populateStudentArrayByClass(node->left, class_id, studentArray, index);
        if (node->class_id == class_id) {
            studentArray[*index].student_id = node->student_id;
            strcpy(studentArray[*index].name, node->name);
            strcpy(studentArray[*index].city, node->city);
            studentArray[*index].class_id = node->class_id;
            strcpy(studentArray[*index].enrollment_date, node->enrollment_date);
            (*index)++;
        }
        populateStudentArrayByClass(node->right, class_id, studentArray, index);
    }
}

// Function to display student records by class ID.
void displayByClass(StudentNode* root, int class_id) {
    int studentCount = countStudents(root);
    struct StudentInfo* studentArray = (struct StudentInfo*)malloc(studentCount * sizeof(struct StudentInfo));

    int index = 0;
    populateStudentArrayByClass(root, class_id, studentArray, &index);

    qsort(studentArray, index, sizeof(struct StudentInfo), compareNames);

    for (int i = 0; i < index; i++) {
        printf("Student ID: %d\n", studentArray[i].student_id);
        printf("Name: %s\n", studentArray[i].name);
        printf("City: %s\n", studentArray[i].city);
        printf("Class ID: %d\n", studentArray[i].class_id);
        printf("Enrollment Date: %s\n", studentArray[i].enrollment_date);
        printf("---------------------------------\n");
    }

    free(studentArray);
}


// Function to save student records to a file in a inorder traversal manner.
void saveToFile(StudentNode* root, FILE* fp) {
    if (root != NULL) {
        saveToFile(root->left, fp);

        // Write student information to the file in the specified format
        fprintf(fp, "%d,%s,%s,%d,%s\n", root->student_id, root->name, root->city, root->class_id, root->enrollment_date);
        saveToFile(root->right, fp);  // Recursively traverse the right subtree
    }
}

// Function to load student records from a file 
StudentNode* loadFromFile(StudentNode* root, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s. Starting with an empty tree.\n", filename);
        return root;
    }
    int student_id, class_id;
    char name[50], city[50], enrollment_date[20];

    while (fscanf(fp, "%d,%[^,],%[^,],%d,%[^\n]\n", &student_id, name, city, &class_id, enrollment_date) != EOF) {
        root = insertStudent(root, student_id, name, city, class_id, enrollment_date);
    }

    fclose(fp);
    return root;
}

//Function to print the menu to the user with each iteration 
void printMenu() {
    printf("\n\n1. Insert a student\n");
    printf("2. Find/update a student\n");
    printf("3.List all students in lexicographic order of their names \n");
    printf("4. Search students by city\n");
    printf("5. List students by class\n");
    printf("6. Delete a student\n");
    printf("7. Save student records to file\n");
    printf("8. Exit\n");
    printf("\nEnter your choice: \n");
}

int main() {
    StudentNode* root = NULL;
   root = loadFromFile(root, "students_input.txt");
    struct StudentInfo studentArray[100];
    int count = 0;
    int choice;
    int student_id, class_id;
    char name[50], city[50], enrollment_date[20];
    int update = 0;


    while (1) {
        printMenu();
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                printf("Enter student ID: ");
                scanf("%d", &student_id);
                 while  (student_id < 0 ){
                    printf("ID number should be positive. Please try again.\n");
                    printf("Enter student ID: ");
                    scanf("%d", &student_id);

                 }
                 getchar(); // Consume the newline character left in the input buffer


                 printf("Enter name: ");
                 fgets(name, sizeof(name), stdin);
                 name[strcspn(name, "\n")] = '\0'; // Remove the newline character at the end


                 printf("Enter city: ");
                 fgets(city, sizeof(city), stdin);
                 city[strcspn(city, "\n")] = '\0'; // Remove the newline character at the end


                 printf("Enter class ID: ");
                 scanf("%d", &class_id);
                 getchar(); // Consume the newline character left in the input buffer


                 printf("Enter enrollment date: ");
                 fgets(enrollment_date, sizeof(enrollment_date), stdin);
                 enrollment_date[strcspn(enrollment_date, "\n")] = '\0'; // Remove the newline character at the end


                 root = insertStudent(root, student_id, name, city, class_id, enrollment_date);
                 printIDs(root);


                break;
            case 2:
                printf("Enter student ID to find: ");
                scanf("%d", &student_id);
                StudentNode* student = findStudent(root, student_id);
                if (student != NULL) {
                    printf("Student ID: %d\n", student->student_id);
                    printf("Name: %s\n", student->name);
                    printf("City: %s\n", student->city);
                    printf("Class ID: %d\n", student->class_id);
                    printf("Enrollment Date: %s\n", student->enrollment_date);

                    printf("Would you like to update this student's info? 1: YES, 0: NO\n");
                    scanf("%d", &update);
                    getchar();

                    if (update == 1) {
                        printf("Enter name: ");
                        fgets(name, sizeof(name), stdin);
                        name[strcspn(name, "\n")] = '\0';

                        printf("Enter city: ");
                        fgets(city, sizeof(city), stdin);
                        city[strcspn(city, "\n")] = '\0';

                        printf("Enter class ID: ");
                        scanf("%d", &class_id);
                        getchar();

                        printf("Enter enrollment date: ");
                        fgets(enrollment_date, sizeof(enrollment_date), stdin);
                        enrollment_date[strcspn(enrollment_date, "\n")] = '\0';

                        // Update the student information in the BST
                        strcpy(student->name, name);
                        strcpy(student->city, city);
                        student->class_id = class_id;
                        strcpy(student->enrollment_date, enrollment_date);

                        printf("Student record updated.\n");
                    }
                } else {
                    printf("There is no student with this ID number.\n");
                }
                break;

            case 3:
                printStudentsInLexicographicOrder(root);
                break;
            case 4:

                getchar();
                printf("Enter city to search: ");
                fgets(city, sizeof(city), stdin);
                city[strcspn(city, "\n")] = '\0';
                searchByCity(root, city);
                break;

            case 5:
                printf("Enter class ID to list: ");
                scanf("%d", &class_id);
                displayByClass(root, class_id);
                break;
            case 6:
                printf("Enter student ID to delete: ");
                scanf("%d", &student_id);
                root = deleteStudent(root, student_id);
                printf("Student record deleted.\n");
                printIDs(root);


                break;
            case 7:
                FILE* fp = fopen("students.data", "w");
                if (fp == NULL) {
                    printf("Error opening file for saving.\n");
                } else {
                    saveToFile(root, fp);
                    fclose(fp);


                    printf("Student records saved to file.\n");
                }
                break;
            case 8:
                printf("Exiting program. Thank you for using :) \n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}