
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

UnitList new_list()
{
    UnitList temp;
    return temp;
}
void insert_at_front(UnitList *self, String data)
{
    ListNodePtr new_node = malloc(sizeof *new_node);

    new_node->unit_code = malloc((strlen(data) + 1) * sizeof(char));
    strcpy(new_node->unit_code, data);

    new_node->next = self->head;
    self->head = new_node;
}

/**
 * @brief deletes a given integer from the list
 * 
 * @param my_list 
 * @param data 
 */
void delete_list(UnitList *my_list, String data)
{

    ListNodePtr temp, prev;
    temp = my_list->head;

    // First, locate the node that contains the item.
    for (temp; temp->next != NULL; temp = temp->next)
    {
        if (strcmp(data, temp->unit_code) == 0)
        {
            break;
        }
        prev = temp;
    }

    // Now take care of deleting it.
    if (temp != NULL)
    {
        if (temp == my_list->head)
        {
            my_list->head = temp->next;
        }
        else
        {
            prev->next = temp->next;
        }
        free(temp->unit_code);
        free(temp);
    }
}

/**
   * @brief prints the contents of the list
   *
   * @param my_list
   */
void print_list(UnitList *my_list)
{
    String check = "\0";

    ListNodePtr current = malloc(sizeof *current);
    current = my_list->head;

    while (strlen(current->unit_code) > -1)
    {
        printf("%s \n", current->unit_code);

        current = current->next;

        if (current == NULL)
        {

            printf("\n");
        }
    }
}
/**
 * @brief destroys the entire list freeing memory space
 * 
 * @param my_list 
 */
void destroy_list(UnitList *my_list)
{
    ListNodePtr current = my_list->head;

    while (current != NULL)
    {
        ListNodePtr to_free = current;
        current = current->next;
        free(to_free);
    }
    my_list->head = NULL;
    printf("Memory is freed...");
}

UnitList copy_list(UnitList* self)
{
	UnitList temp = new_list();

	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	while (prev != self->head)
	{
		if (current->next == NULL || current->next == prev)
		{
			insert_in_order(&temp, current->unit_code);
			prev = current;
			current = self->head;
		}
		else
		{
			current = current->next;
		}
	}

	return temp;
}
void merge_list(UnitList* self, UnitList* other)
{
	if (other->head != NULL)
	{
		ListNodePtr current = other->head;
        ListNodePtr prev = current;
        insert_in_order(self, current->unit_code);
        while (current != NULL)
		{
			if (current != prev->next)
			{
				current = current->next;
			}
			else
			{
				insert_in_order(self, current->unit_code);
				prev = current;
				current = other->head;
			}
		}
	}
}
void insert_in_order(UnitList* self, String data)
{
	if (find_list(self, data) == NULL)
	{
		ListNodePtr current = self->head;
		ListNodePtr prev = NULL;
        ListNodePtr new_node = malloc(sizeof * new_node);
        new_node->unit_code = malloc(strlen(data) + 1);
		strcpy(new_node->unit_code, data);
		new_node->next = NULL;
        while (current != NULL && strcmp(current->unit_code, data) < 0)
		{
			prev = current;
			current = current->next;
		}
        if (current == self->head)
		{
			new_node->next = current;
			self->head = new_node;
		}
        else
        {
            new_node->next = current;
            prev->next = new_node;
        }
	}
}
ListNodePtr find_list_node(ListNodePtr self, String data)
{
	if (self != NULL)
	{
		if (strcmp(self->unit_code, data) == 0)
		{
			return self;
		}
		else if (strcmp(self->unit_code, data) > 0)
		{
			return NULL;
		}
		else
		{
			return find_list_node(self->next, data);
		}
	}
	else
	{
		return NULL;
	}
}

ListNodePtr find_list(UnitList* self, String data)
{
	return find_list_node(self->head, data);
}

