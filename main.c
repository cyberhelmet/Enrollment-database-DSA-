
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "bst.h"

#define _CRT_SECURE_NO_WARNINGS
long id;

long id_entry()
{
    long student_id;
    printf("\nEnter the student id :\t\t");
    scanf("%ld", &student_id);
    return student_id;
}
String unit_entry()
{
    char buffer[100];
    printf("Enter unit code:\t\t");
    scanf("%s", buffer);
    char * name = malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(name, buffer);
    return name;
}
BSTNodePtr track(StudentBST *record)
{
    id = id_entry();
    return find_bst(record, id);
}

/*
void print_summary(StudentBST *record)
{

    BSTNodePtr search = track(record);
    ListNodePtr s = search->units.head;
    print_list(&search->units);

    //current = current->next;
}*/
typedef struct courseNode
{
    String unit_code;
    int enrollments_id;
    struct courseNode *next;
} * CourseNodePtr;

/**
 * Structure used for the 'count_total_enrollments' function below
 *
 * Represents a list of courses
 */
typedef struct courseList
{
    CourseNodePtr head;
} CourseList;

/**
 * Build a list of courses including the number of students enrolled in each course
 * @param student binary search tree node
 * @param course_list
 */
void count_total_enrollments(BSTNodePtr student, CourseList *course_list)
{

    /* if called on an empty student node, return */
    if (student == NULL)
    {
        return;
    }

    char *course_code;

    /* traverse the list of courses this student is enrolled in */
    ListNodePtr current_enrollment = student->units.head;

    while (current_enrollment != NULL)
    {
        course_code = current_enrollment->unit_code;

        /* if there are, we need to determine whether this course is part of the list already */
        CourseNodePtr current = course_list->head;
        CourseNodePtr prev = NULL;

        /* traverse the course list until we find a match or reach the end of possibilities */
        while (current != NULL && strcmp(current->unit_code, course_code) < 0)
        {
            prev = current;
            current = current->next;
        }

        /* if the course code already exists, increment the number of enrollments */
        if (current != NULL && strcmp(current->unit_code, course_code) == 0)
        {
            current->enrollments_id++;
        }
        else
        {
            /* otherwise, create a new node  */
            CourseNodePtr node = malloc(sizeof(*node));

            node->next = NULL;
            node->enrollments_id = 1;
            node->unit_code = course_code;

            /* add the new course in the correct position */
            if (prev == NULL)  
            {
                node->next = current;
                course_list->head = node;
            }
            else
            {
                node->next = current;
                prev->next = node;
            }
        }

        /* this enrollment has been processed; progress to the next one */
        current_enrollment = current_enrollment->next;
    }

    /* traverse down the tree for each child */
    count_total_enrollments(student->left, course_list);
    count_total_enrollments(student->right, course_list);
}
/**
 * Print a summary of courses and the number of students enrolled in each course
 * @param self
 */
void option_print_summary(StudentBST *self)
{

    /* create a new course list */
    CourseList course_list;
    course_list.head = NULL;

    /* build the list of enrolments */
    count_total_enrollments(self->root, &course_list);

    /* traverse the list and print its contents */
    CourseNodePtr current = course_list.head;

    printf("Current enrolments:\n");

    while (current != NULL)
    {
        printf("%s\t%d\n", current->unit_code, current->enrollments_id);
        current = current->next;
    }
}
void bst_print_matching_records(BSTNodePtr self, char *needle)
{

    /* exit function if called on a non-existent node */
    if (self == NULL)
    {
        return;
    }

    /* process left children first, as they are ordered first */
    bst_print_matching_records(self->left, needle);

    /* traverse through course list beginning at the head, until end of list or match found */
    ListNodePtr current = self->units.head;
    while (current != NULL && strcmp(current->unit_code, needle) != 0)
    {
        current = current->next;
    }

    /* if a match was found, print the data */
    if (current != NULL)
    {

        printf("%ld\n", self->student_id);
    }

    /* finish off by processing left children */
    bst_print_matching_records(self->right, needle);
}

/**
 * Print an ordered list of students enrolled in a course
 * @param self
 */
void option_print_course_enrollments(StudentBST *self)
{
    char *course = unit_entry();

    printf("Students enrolled in %s:\n", course);
    printf("\n");
    bst_print_matching_records(self->root, course);

    printf("\n");
}

void option_print_student_enrolments(StudentBST *self)
{
    long student = id_entry();

    BSTNodePtr student_node = malloc(sizeof *student_node);
    student_node = find_bst(self, student);
    printf("Enrolments for %ld:\n", student_node->student_id);
    print_list(&student_node->units);
}
int count_enrolments_bst(BSTNodePtr self, String unit)
{
	int count = 0;
	if (self != NULL)
	{
		count += count_enrolments_bst(self->left, unit);
		count += count_enrolments_bst(self->right, unit);
		if (find_list(&(self->units), unit) != NULL)
		{
			count += 1;
		}
	}
	return count;
}
void build_temp_unit_list_node_bst(BSTNodePtr self, UnitList* list)
{
	if (self != NULL)
	{
		merge_list(list, &(self->units));
		build_temp_unit_list_node_bst(self->left, list);
		build_temp_unit_list_node_bst(self->right, list);
	}
}
void option_print_ordered_summary_bst(StudentBST* tree)
{
	printf("Unit\tEnrolments\n");
    UnitList tempUnitList = new_list();
    build_temp_unit_list_node_bst(tree->root, &tempUnitList);
    ListNodePtr currentUnit = (&tempUnitList)->head;
    while (currentUnit != NULL)
	{
		int count = count_enrolments_bst(tree->root, currentUnit->unit_code);
		printf("%s\t%d\n", currentUnit->unit_code, count);
		currentUnit = currentUnit->next;
	}
    destroy_list(&tempUnitList);
}
void option_print_ordered_list_units_bst(StudentBST* tree)
{
	long id;
    printf("= Print A Students Enrolled Units =\n");
	printf("Enter student ID (-1 to return): ");
	scanf("%ld", &id);

	if (id != -1)
	{
		printf("%ld enrolled units:\n", id);
		print_list(&(find_bst(tree, id)->units));
		printf("\n");
	}
}
int main(int argc, char *argv[])
{
    StudentBST record = new_bst(); //tree for storing student id's
    UnitList newlist = new_list(); //UnitList unit;
    long search_id;
    String unit_name;
    int q;
    char *one, *two, *three;
    int menu;     //choices for the program
    int quit = 1; //terminating condition
    printf("\nStudent record system  :\t\n\n");
    printf("1.Add student\n2.Remove student\n3.Enrol student in a unit\n4.Un-enrol student from a unit\n5.Print an ordered summary of units and the number of students enrolled in each unit\n6.Print an ordered list of students enrolled in a specific unit\n7.Print an ordered list of units that a specific student is enrolled in\n0.Terminate the program\n");

    while (quit != 0)
    {
        printf("\nEnter the option:\t\t");
        scanf("%d", &menu);
        switch (menu)
        {
        case 0:
            printf("Terminating the program.\n");
            quit = 0;
            break;

        case 1: //Add student
            id = id_entry();
            insert_bst(&record, id);
            printf("Successfully added student:\t");
            print_in_order_bst(&record);
            printf("\n");
            break;

        case 2: //Remove student
            id = id_entry();
            delete_bst(&record, id);
            printf("Successfully removed student:\t \n");
            print_in_order_bst(&record);
            printf("\n");
            break;

        case 3:
            printf("To enroll,");
            unit_name = unit_entry();
            BSTNodePtr tracker = track(&record);
            insert_at_front(&tracker->units, unit_name);
            printf("Working");
            printf("\n");
            break;

        case 4: //Un-enrol student from a unit
            printf("To un-enroll,");
            unit_name = unit_entry();
            BSTNodePtr spotter = track(&record);
            delete_list(&spotter->units, unit_name);
            printf("Working ");
            printf("\n");
            break;

        case 5: //Print an ordered summary of units and the number of students enrolled in each unit

            option_print_ordered_summary_bst(&record);

            break;
        case 6: //Print an ordered list of students enrolled in a specific unit
            option_print_student_enrolments(&record);
            break;
        case 7: //Print an ordered list of units that a specific student is enrolled in
            option_print_ordered_list_units_bst(&record);
            break;
        default:
            printf("Option not available.\n");
            quit = 0;
            break;
        }
    }
}
