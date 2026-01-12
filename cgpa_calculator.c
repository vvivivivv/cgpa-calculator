#include <stdio.h>
#include <string.h>

typedef struct {
    int au;
    char grade[3];
    float grade_pt;
    int included;
} Course;

float get_grade_pt(char grade[]);
float calculate_cgpa(Course courses[], int num_of_courses);
float is_excluded(char grade[]);
void su(Course courses[], int count);
void grade_predictor(Course courses[], int count);
void add_retaken_courses(Course courses[], int *count);

#define MAX_COURSES 70

int main(void){
    Course courses[MAX_COURSES];
    int num_of_courses = 0;
    int choice;

    printf("cGPA Calculator and Planner\n");
    printf("1. Input courses and AUs\n");
    printf("2. Calculate cGPA\n");
    printf("3. SU and recalculate cGPA\n");
    printf("4. Average cGPA required for remaining courses to attain target cGPA\n");
    printf("5. Add retaken 'F' courses and recalculate cGPA\n");
    printf("6. Exit\n");

    do{
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Enter number of courses: ");
                scanf("%d", &num_of_courses);

                for (int i=0; i<num_of_courses; i++){
                    printf("Enter Course AU: ");
                    scanf("%d", &courses[i].au);
                    printf("Enter Course Grade: ");
                    scanf("%s", courses[i].grade);

                    if (is_excluded(courses[i].grade) == 0.0){
                        printf("Note: Grade %s will be excluded from CGPA calculation.\n", courses[i].grade);
                        courses[i].included = 0;
                        courses[i].grade_pt = 0.0;
                    }
                    else {
                        courses[i].included = 1;
                        courses[i].grade_pt = get_grade_pt(courses[i].grade);
                    }

                    if (courses[i].grade_pt == -1.0){
                        printf("Invalid grade entered. Please restart the program and enter a valid grade.\n");
                    }
                }
                break;

            case 2: 
                printf("cGPA: %.2f\n", calculate_cgpa(courses, num_of_courses));
                break;

            case 3:
                su(courses, num_of_courses);
                break;
        
            case 4:
                grade_predictor(courses, num_of_courses);
                break;
        
            case 5:
                add_retaken_courses(courses, &num_of_courses);
                break;
        
            case 6:
                printf("Exiting.\n");
                break;
        }
    } while(choice!=6);
    return 0;
}


float get_grade_pt(char grade[]){
    if (strcmp(grade, "A+")==0 || strcmp(grade, "A")==0){
        return 5.0;
    }
    else if (strcmp(grade, "A-")==0){
        return 4.5;
    }
    else if (strcmp(grade, "B+")==0){
        return 4.0;
    }
    else if (strcmp(grade, "B")==0){
        return 3.5;
    }
    else if (strcmp(grade, "B-")==0){
        return 3.0;
    }
    else if (strcmp(grade, "C+")==0){
        return 2.5;
    }
    else if (strcmp(grade, "C")==0){
        return 2.0;
    }
    else if (strcmp(grade, "D+")==0){
        return 1.5;
    }
    else if (strcmp(grade, "D")==0){
        return 1.0;
    }
    else if (strcmp(grade, "F")==0){
        return 0.0;
    }
    else
    {
        return -1.0;  
    }
}


float is_excluded(char grade[]){
    if (strcmp(grade, "S")==0 || strcmp(grade, "U")==0 || strcmp(grade, "IP")==0 || strcmp(grade, "P")==0 || strcmp(grade, "EX")==0){
        return 0.0;
    }
    return -1.0;
}


float calculate_cgpa(Course courses[], int num_of_courses){
    float total_grade_pts = 0;
    int total_au = 0;
    
    for (int i=0; i<num_of_courses; i++){
        if (courses[i].included){
            total_grade_pts += courses[i].grade_pt * courses[i].au;
            total_au += courses[i].au;
        }
    }

    if (total_au == 0) {
        return 0.0;
    }

    return total_grade_pts / total_au;
}


void su(Course courses[], int count){
    int idx;
    printf("Enter course number (1 to %d) to SU: ", count);
    scanf("%d", &idx);
    if (idx<1 || idx>count) {
        printf("Invalid index.\n");
        return;

    }
    if (!courses[idx-1].included){
        printf("Course at index %d is already excluded.\n", idx);
        return;
    }
    courses[idx-1].included = 0;
    printf("Course at index %d has been marked as SU.\n", idx);
    printf("Updated CGPA: %.2f\n", calculate_cgpa(courses, count));
}


void grade_predictor(Course courses[], int count){
    float target_cgpa = 0.0;
    int total_au_required = 0;
    int total_au_completed = 0;

    float current_cgpa = calculate_cgpa(courses, count);

    printf("Current cGPA: %.2f\n", current_cgpa);
    for (int i=0; i<count; i++){
        if (courses[i].included){
            total_au_completed += courses[i].au;
        }
    }
    printf("Total AUs completed: %d\n", total_au_completed);

    printf("Enter target cGPA: ");
    scanf("%f", &target_cgpa);
    if (target_cgpa<0.0 || target_cgpa>5.0){
        printf("Invalid target cGPA. Please enter a value between 0.0 and 5.0\n");
        return;
    }

    printf("Enter total AUs required to complete your degree: ");
    scanf("%d", &total_au_required);

    int remaining_au = total_au_required - total_au_completed;
    if (remaining_au<=0) {
        printf("You have already completed all required AUs. No cGPA to predict.\n");
        return;
    }

    float required_avg = (target_cgpa * total_au_required - current_cgpa * total_au_completed) / remaining_au;
    if (required_avg<0.0){
        printf("Target cGPA already achieved.\n");
    } 
    else if (required_avg>5.0) {
        printf("Target cGPA is not achievable.\n");
    }
    else {
        printf("Required cGPA for remaining AUs: %.2f\n", required_avg);
    }
}


void add_retaken_courses(Course courses[], int *count){
    int retake_count;
    printf("Enter number of retaken 'F' courses: ");
    scanf("%d", &retake_count);

    if (*count >= MAX_COURSES) {
        printf("Course limit reached.\n");
        return;
    }

    for (int i=0; i<retake_count; i++){
        printf("Enter AU for retaken course %d: ", i+1);
        scanf("%d", &courses[*count].au);
        printf("Enter new grade for retaken course %d: ", i+1);
        scanf("%s", courses[*count].grade);

        courses[*count].grade_pt = get_grade_pt(courses[*count].grade);
        if (courses[*count].grade_pt == -1.0){
            printf("Invalid grade entered. Skipping this course.\n");
            continue;
        }
        courses[*count].included = 1;
        (*count)++;
    }
    printf("Updated CGPA after adding retaken courses: %.2f\n", calculate_cgpa(courses, *count));
}

