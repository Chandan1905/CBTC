#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    char **subjects;
    float *marks;
    float total;
    char **grades;
    char total_grade[3];
} Student;

typedef struct {
    float min;
    float max;
    char grade[3];
} GradeRange;

void assign_grade(float mark, GradeRange *ranges, int num_ranges, char *grade) {
    for (int i = 0; i < num_ranges; i++) {
        if (mark >= ranges[i].min && mark <= ranges[i].max) {
            strcpy(grade, ranges[i].grade);
            return;
        }
    }
    strcpy(grade, "NA"); // If no range matches
}

int main() {
    int num_students, num_subjects, num_ranges;
    float pass_marks;

    printf("Enter the number of students: ");
    scanf("%d", &num_students);

    printf("Enter the number of subjects: ");
    scanf("%d", &num_subjects);

    printf("Enter the pass marks: ");
    scanf("%f", &pass_marks);

    Student *students = (Student *)malloc(num_students * sizeof(Student));
    char **subject_names = (char **)malloc(num_subjects * sizeof(char *));
    for (int i = 0; i < num_subjects; i++) {
        subject_names[i] = (char *)malloc(20 * sizeof(char));
        printf("Enter the name of subject %d: ", i + 1);
        scanf("%s", subject_names[i]);
    }

    printf("Enter the number of grade ranges: ");
    scanf("%d", &num_ranges);

    GradeRange *ranges = (GradeRange *)malloc(num_ranges * sizeof(GradeRange));
    for (int i = 0; i < num_ranges; i++) {
        printf("Enter the minimum marks for grade %d: ", i + 1);
        scanf("%f", &ranges[i].min);
        printf("Enter the maximum marks for grade %d: ", i + 1);
        scanf("%f", &ranges[i].max);
        printf("Enter the grade for range %.2f - %.2f: ", ranges[i].min, ranges[i].max);
        scanf("%s", ranges[i].grade);
    }

    for (int i = 0; i < num_students; i++) {
        printf("Enter the name of student %d: ", i + 1);
        scanf("%s", students[i].name);
        students[i].subjects = (char **)malloc(num_subjects * sizeof(char *));
        students[i].marks = (float *)malloc(num_subjects * sizeof(float));
        students[i].grades = (char **)malloc(num_subjects * sizeof(char *));
        students[i].total = 0;

        for (int j = 0; j < num_subjects; j++) {
            students[i].subjects[j] = (char *)malloc(20 * sizeof(char));
            strcpy(students[i].subjects[j], subject_names[j]);
            students[i].grades[j] = (char *)malloc(3 * sizeof(char));
            printf("Enter the marks for %s: ", students[i].subjects[j]);
            scanf("%f", &students[i].marks[j]);
            students[i].total += students[i].marks[j];
            assign_grade(students[i].marks[j], ranges, num_ranges, students[i].grades[j]);
        }
        assign_grade(students[i].total / num_subjects, ranges, num_ranges, students[i].total_grade);
    }

    // Initialize variables for highest and lowest marks
    float *highest_marks = (float *)malloc(num_subjects * sizeof(float));
    float *lowest_marks = (float *)malloc(num_subjects * sizeof(float));
    float *total_marks_per_subject = (float *)calloc(num_subjects, sizeof(float));
    char **highest_scorers = (char **)malloc(num_subjects * sizeof(char *));
    char **lowest_scorers = (char **)malloc(num_subjects * sizeof(char *));
    for (int i = 0; i < num_subjects; i++) {
        highest_marks[i] = -1;
        lowest_marks[i] = 101;
        highest_scorers[i] = (char *)malloc(20 * sizeof(char));
        lowest_scorers[i] = (char *)malloc(20 * sizeof(char));
    }

    // Find highest and lowest marks in each subject and calculate total marks per subject
    for (int j = 0; j < num_subjects; j++) {
        for (int i = 0; i < num_students; i++) {
            total_marks_per_subject[j] += students[i].marks[j];
            if (students[i].marks[j] > highest_marks[j]) {
                highest_marks[j] = students[i].marks[j];
                strcpy(highest_scorers[j], students[i].name);
            }
            if (students[i].marks[j] < lowest_marks[j]) {
                lowest_marks[j] = students[i].marks[j];
                strcpy(lowest_scorers[j], students[i].name);
            }
        }
    }

    // Find highest and lowest total scores
    float highest_total = -1;
    float lowest_total = 101 * num_subjects;
    char highest_total_scorer[20];
    char lowest_total_scorer[20];
    float total_marks_all_students = 0;
    for (int i = 0; i < num_students; i++) {
        total_marks_all_students += students[i].total;
        if (students[i].total > highest_total) {
            highest_total = students[i].total;
            strcpy(highest_total_scorer, students[i].name);
        }
        if (students[i].total < lowest_total) {
            lowest_total = students[i].total;
            strcpy(lowest_total_scorer, students[i].name);
        }
    }

    // Count the number of students who passed all subjects and who failed
    int pass_count = 0;
    printf("\nStudents who failed:\n");
    for (int i = 0; i < num_students; i++) {
        int passed_all = 1;
        for (int j = 0; j < num_subjects; j++) {
            if (students[i].marks[j] < pass_marks) {
                passed_all = 0;
                break;
            }
        }
        if (passed_all) {
            pass_count++;
        } else {
            printf("%s\n", students[i].name);
        }
    }

    // Display the given information
    printf("\nYour given information is as follows:\n");
    for (int i = 0; i < num_students; i++) {
        printf("Name: %s\n", students[i].name);
        for (int j = 0; j < num_subjects; j++) {
            printf("Subject: %s\t", students[i].subjects[j]);
            printf("Marks: %.2f\t", students[i].marks[j]);
            printf("Grade: %s\n", students[i].grades[j]);
        }
        printf("Total: %.2f\n", students[i].total);
        printf("Total Grade: %s\n", students[i].total_grade);
        printf("\n");
    }

    // Display highest and lowest marks in each subject
    printf("Highest and lowest marks in each subject:\n");
    for (int j = 0; j < num_subjects; j++) {
        printf("Subject: %s\n", subject_names[j]);
        printf("Highest Marks: %.2f by %s\n", highest_marks[j], highest_scorers[j]);
        printf("Lowest Marks: %.2f by %s\n\n", lowest_marks[j], lowest_scorers[j]);
    }

    // Display highest and lowest total scores
    printf("Highest Total Score: %.2f by %s\n", highest_total, highest_total_scorer);
    printf("Lowest Total Score: %.2f by %s\n", lowest_total, lowest_total_scorer);

    // Display average marks in each subject
    printf("Average marks in each subject:\n");
    for (int j = 0; j < num_subjects; j++) {
        printf("Subject: %s, Average Marks: %.2f\n", subject_names[j], total_marks_per_subject[j] / num_students);
    }

    // Display average total marks
    printf("Average Total Marks: %.2f\n", total_marks_all_students / num_students);

    // Display the number of students who passed all subjects
    printf("Number of students who passed all subjects: %d\n", pass_count);

    // Free allocated memory
    for (int i = 0; i < num_students; i++) {
        for (int j = 0; j < num_subjects; j++) {
            free(students[i].subjects[j]);
            free(students[i].grades[j]);
        }
        free(students[i].subjects);
        free(students[i].marks);
        free(students[i].grades);
    }
    for (int i = 0; i < num_subjects; i++) {
        free(subject_names[i]);
        free(highest_scorers[i]);
        free(lowest_scorers[i]);
    }
    free(subject_names);
    free(highest_marks);
    free(lowest_marks);
    free(highest_scorers);
    free(lowest_scorers);
    free(total_marks_per_subject);
    free(students);
    free(ranges);

    return 0;
}
