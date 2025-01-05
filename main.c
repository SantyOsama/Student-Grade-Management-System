#include <stdio.h>
#include <windows.h>//menue
#include <conio.h> //getch()
#include <stdlib.h> // malloc
#include <string.h> // strcpy, strcat

struct subject
{
    char subjectName[30];
    float subjectScore;
};
struct student
{
    int studentId;
    char studentName[50];
    struct subject *subjects;
    int numSubjects;
    char grade;
    float totalScore;
    float average;
};
struct student students[100];
int studentNum = 0;
struct student *searchForStudent(int studentId)
{
    for (int i = 0; i < studentNum; i++)
    {
        if (students[i].studentId == studentId)
        {
            return &students[i];
        }
    }
    return NULL;
}
struct student* showStudentDetails()
{
    int studentId;
    printf("\nEnter Student ID to search: ");
    scanf("%d", &studentId);
    struct student *currentStudent = searchForStudent(studentId);
    if (currentStudent == NULL)
    {
        printf("Student with ID %d not found.\n", studentId);
        system("pause");
        return;
    }
    printf("\nCurrent Student Info:\n");
    printf("ID: %d\n", currentStudent->studentId);
    printf("Name: %s\n", currentStudent->studentName);
    printf("Number of Subjects: %d\n", currentStudent->numSubjects);
    for (int i = 0; i < currentStudent->numSubjects; i++)
    {
        printf("Subject %d: %s, Score: %.1f\n", i + 1, currentStudent->subjects[i].subjectName, currentStudent->subjects[i].subjectScore);
    }
    printf("Current Average: %.1f\n", currentStudent->average);
    printf("Current Grade: %c\n", currentStudent->grade);
    getchar();
    system("pause");
    return currentStudent;
}
void addStudent()
{
    struct student *newStudent = &students[studentNum];
    printf("\nEnter Student ID: ");
    scanf("%d", &newStudent->studentId);
    printf("Enter Student Name: ");
    getchar();
    scanf("%s", newStudent->studentName);
    printf("Enter number of subjects: ");
    scanf("%d", &newStudent->numSubjects);
    newStudent->subjects = (struct subject *)malloc(newStudent->numSubjects * sizeof(struct subject));
    newStudent->average = 0.0f;
    for (int i = 0; i < newStudent->numSubjects; i++)
    {
        printf("\nEnter Subject %d Name: ", i + 1);
        getchar();
        scanf("%s", newStudent->subjects[i].subjectName);
        printf("Enter Subject %d Score: ", i + 1);
        scanf("%f", &newStudent->subjects[i].subjectScore);
        while (newStudent->subjects[i].subjectScore < 0 || newStudent->subjects[i].subjectScore > 100)
        {
            printf("Invalid score!Please enter a score for %s between 0 and 100: ",newStudent->subjects[i].subjectName);
            scanf("%f", &newStudent->subjects[i].subjectScore);
        }
        newStudent->totalScore += newStudent->subjects[i].subjectScore;
    }
    calculateAverage(newStudent);
    /*newStudent->average = newStudent->totalScore / newStudent->numSubjects;*/

    /*  if (newStudent->average >= 90) {
          newStudent->grade = 'A';
      } else if (newStudent->average >= 80) {
          newStudent->grade = 'B';
      } else if (newStudent->average >= 70) {
          newStudent->grade = 'C';
      } else if (newStudent->average >= 60) {
          newStudent->grade = 'D';
      } else {
          newStudent->grade = 'F';
      }*/
    printf("\nStudent information added successfully!\n Average Grade: %c\n", newStudent->grade);
    studentNum++;
    system("pause");
}
void updateStudentScores()
{
    struct student *currentStudent = showStudentDetails();
    if (currentStudent == NULL)
    {
        printf("\Student Not Found");
        return;
    }
    currentStudent->totalScore=0;
    for (int i = 0; i < currentStudent->numSubjects; i++)
    {
        char flag;
        printf("\n Do you want to change %s Score ?(y/n) ",currentStudent->subjects[i].subjectName);
        scanf(" %c",&flag);
        if(flag=='Y'||flag=='y')
        {
            printf("\n Enter Score For Subject %s :",currentStudent->subjects[i].subjectName);
            scanf("%f", &currentStudent->subjects[i].subjectScore);
            while(currentStudent->subjects[i].subjectScore < 0 || currentStudent->subjects[i].subjectScore > 100)
            {
                printf("Invalid score!Please enter a score for %s between 0 and 100: ",currentStudent->subjects[i].subjectName);
                scanf(" %f", &currentStudent->subjects[i].subjectScore);
            }
        }
        currentStudent->totalScore += currentStudent->subjects[i].subjectScore;
    }
    calculateAverage(currentStudent);

    /*
    currentStudent->average = currentStudent->totalScore / currentStudent->numSubjects;
    if (currentStudent->average >= 90) {
        currentStudent->grade = 'A';
    } else if (currentStudent->average >= 80) {
        currentStudent->grade = 'B';
    } else if (currentStudent->average >= 70) {
        currentStudent->grade = 'C';
    } else if (currentStudent->average >= 60) {
        currentStudent->grade = 'D';
    } else {
        currentStudent->grade = 'F';
    }*/
    printf("\nStudent information updated successfully!\n");
    printf("Updated Average: %.1f\n", currentStudent->average);
    printf("Updated Grade: %c\n", currentStudent->grade);
    system("pause");
}
void showHighestAvgScore()
{
    if (studentNum == 0)
    {
        printf("\nNo students available.\n");
        system("pause");
        return;
    }
    float highestAvg = students[0].average;
    struct student *topStudent = &students[0];
    for (int i = 1; i < studentNum; i++)
    {
        if (students[i].average > highestAvg)
        {
            highestAvg = students[i].average;
            topStudent = &students[i];
        }
    }
    printf("\nStudent with highest average score:\n");
    printf("ID: %d\n", topStudent->studentId);
    printf("Name: %s\n", topStudent->studentName);
    printf("Average Score: %.1f\n", topStudent->average);
    printf("Grade: %c\n", topStudent->grade);
    printf("\n\n");
    system("pause");
}
void showStudentsRecord()
{
    if (studentNum == 0)
    {
        printf("\nNo students available.\n");
        system("pause");
        return;
    }
    for (int i = 0; i < studentNum; i++)
    {
        ;
        printf("ID: %d\n", students[i].studentId);
        printf("Name: %s\n", students[i].studentName);
        printf("Number of Subjects: %d\n", students[i].numSubjects);
        printf("Average: %.1f\n", students[i].average);
        printf("Grade: %c\n", students[i].grade);
        printf("\n\n");
        /**getchar();**/
    }
    system("pause");
}
void showAllAvg()
{
    if (studentNum == 0)
    {
        printf("\nNo students available.\n");
        system("pause");
        return;
    }
    for (int i = 0; i < studentNum; i++)
    {
        printf("ID: %d\n", students[i].studentId);
        printf("Name: %s\n", students[i].studentName);
        printf("%s Average is: %.1f\n", students[i].studentName,students[i].average);
        printf("\n\n");
    }
    system("pause");
}
void showFailed()
{
    if (studentNum == 0)
    {
        printf("\nNo students available.\n");
        system("pause");
        return;
    }
    for (int i = 0; i < studentNum; i++)
    {
        if (students[i].grade == 'F')
        {
            printf("ID: %d\n", students[i].studentId);
            printf("Name: %s\n", students[i].studentName);
            printf("Average: %.1f\n", students[i].average);
            printf("Grade: %c\n", students[i].grade);
            printf("\n");
        }
    }
    system("pause");
}
void showPassed()
{
    if (studentNum == 0)
    {
        printf("\nNo students available.\n");
        system("pause");
        return;
    }
    for (int i = 0; i < studentNum; i++)
    {
        if (students[i].grade != 'F')
        {
            printf("ID: %d\n", students[i].studentId);
            printf("Name: %s\n", students[i].studentName);
            printf("Average: %.1f\n", students[i].average);
            printf("Grade: %c\n", students[i].grade);
            printf("\n");
        }
    }
    system("pause");
}
COORD coord = {0, 0};
void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
void displayMenu(char menuItems[][30], int menuSize, int selectedIndex)
{
    for (int i = 0; i < menuSize; i++)
    {
        gotoxy(30, 5 + i+i);
        if (i == selectedIndex)
        {
            SetColor(13);
            printf("%s", menuItems[i]);
        }
        else
        {
            SetColor(7);
            printf("%s", menuItems[i]);
        }
    }
}
int main()
{
    char menuItems[9][30] =
    {
        "=> Add Student Info", // subjects and info
        "=> Search for Student",//one sudent details
        "=> Update Student Info", // search then update
        "=> Show Students Details", // calc avg and grade
        "=> Show Highest Average", // highest one
        "=> Show All Average only",
        "=> Show Failed Student only",
        "=> Show Passed Student only",
        "=> Exit"
    };
    int menuSize = 9;
    int selectedIndex = 0;
    char key;
    do
    {
        system("cls");
        displayMenu(menuItems, menuSize, selectedIndex);
        key = _getch();
        if (key == 72)
        {
            selectedIndex--;
            if (selectedIndex < 0)
                selectedIndex = menuSize - 1;
        }
        else if (key == 80)
        {
            selectedIndex++;
            if (selectedIndex >= menuSize)
                selectedIndex = 0;
        }
        else if (key == 13)
        {
            system("cls");
            switch (selectedIndex)
            {
            case 0:
                addStudent();
                break;
            case 1:
                showStudentDetails();
                break;
            case 2:
                updateStudentScores();
                break;
            case 3:
                showStudentsRecord();
                break;
            case 4:
                showHighestAvgScore();
                break;
            case 5:
                showAllAvg();
                break;
            case 6:
                showFailed();
                break;
            case 7:
                showPassed();
                break;
            case 8:
                printf("\nExiting the program...\n");
                break;
            default:
                printf("\nInvalid option!\n");
                break;
            }
        }
    }
    while (key != 13 || selectedIndex != menuSize - 1);
    gotoxy(30, 5 + menuSize);
    SetColor(7);
    printf("You Exit successfully: %s\n", menuItems[selectedIndex]);
    freeStudentMemory();
    freeAllMemory();
    return 0;
}
/*هجرب افصل حساب المتوسط لأنه بيتكرر معايا الكود*/
void calculateAverage(struct student *currentStudent)
{
    currentStudent->average = currentStudent->totalScore / currentStudent->numSubjects;

    if (currentStudent->average >= 90)
    {
        currentStudent->grade = 'A';
    }
    else if (currentStudent->average >= 80)
    {
        currentStudent->grade = 'B';
    }
    else if (currentStudent->average >= 70)
    {
        currentStudent->grade = 'C';
    }
    else if (currentStudent->average >= 60)
    {
        currentStudent->grade = 'D';
    }
    else
    {
        currentStudent->grade = 'F';
    }
}
void freeStudentMemory()
{
    for (int i = 0; i < studentNum; i++)
    {
        free(students[i].subjects);
        students[i].subjects = NULL;
    }
    studentNum = 0;
    printf("Memory for all students has been freed successfully!\n");
}
void freeAllMemory()
{
    for (int i = 0; i < studentNum; i++)
    {
        free(students[i].subjects);  // Free memory allocated for subjects
    }
    printf("\nAll memory has been freed.\n");
}
/* كنت عاملة دي وقسمتها عدلت عليها عشان استخدم الفانكشنز اكتر
كمان مكنتش ضيفة توتال سكور وكنت بزود في الافريدج وبعدين بقسمه علي عدد المواد
فقولت لية محطش خانة في الستركت اسميها توتال سكور
تعبت فيها ف خليتها الصراحة مهانش عليا امسح الكود
void updateStudentInfo() {
    int id;
    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);
    int found = 0;
    for (int i = 0; i < studentNum; i++) {
        if (students[i].studentId == id) {
            found = 1;
            struct student *currentStudent = &students[i];
            printf("\nStudent Found: %s\n", currentStudent->studentName);
            printf("Subjects and Scores:\n");
            for (int j = 0; j < currentStudent->numSubjects; j++) {
                printf("%s: %.1f\n", currentStudent->subjects[j].subjectName, currentStudent->subjects[j].subjectScore);
            }
            printf("\nEnter the number of the subject to update (1-%d): ", currentStudent->numSubjects);
            int subjectIndex;
            scanf("%d", &subjectIndex);
            subjectIndex--;
            if (subjectIndex >= 0 && subjectIndex < currentStudent->numSubjects) {
                printf("Enter new score for %s: ", currentStudent->subjects[subjectIndex].subjectName);
                scanf("%f", &currentStudent->subjects[subjectIndex].subjectScore);
                currentStudent->average = 0.0f;
                for (int j = 0; j < currentStudent->numSubjects; j++) {
                    currentStudent->average += currentStudent->subjects[j].subjectScore;
                }
                currentStudent->average = currentStudent->average / currentStudent->numSubjects;
            if (currentStudent->average >= 90) {
                currentStudent->grade = 'A';
            } else if (currentStudent->average >= 80) {
                currentStudent->grade = 'B';
            } else if (currentStudent->average >= 70) {
                currentStudent->grade = 'C';
            } else if (currentStudent->average >= 60) {
                currentStudent->grade = 'D';
            } else {
                currentStudent->grade = 'F';
            }
            printf("\nUpdated Student Information:\n");
            printf("Student Name: %s\n", currentStudent->studentName);
            printf("New Average: %.1f\n", currentStudent->average);
            printf("New Grade: %c\n", currentStudent->grade);
        } else {
            printf("Invalid subject number!\n");
        }
        break;}
    }
if (!found) {
        printf("Student with ID %d not found.\n", id);}
system("pause");
}*/
