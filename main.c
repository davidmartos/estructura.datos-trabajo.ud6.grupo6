#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#define MAX 10
#define A 0.6180339887

struct student
{
    int id;
    char name[50];
    char phone[9];
    char email[50];
    int enrolled;
    struct student *next;
}*arr_student[MAX];

int h(int k, int m)
{
    return floor(m * (k*A - floor(k*A)));
}

int main()
{
    struct student *temp, *temp2;
    int arrayIndex=0,key_roll=0;
    int flag = 1,search_flag =1;

    while(flag == 1)
    {

        temp = (struct student*)malloc(sizeof(struct student));

        printf("Introducir id de usuario: ");
        scanf("%d", &temp->id);

        printf("Introduce el nombre: ");
        scanf("%s", &temp->name);

        printf("Introduce el telefono: ");
        scanf("%s", &temp->phone);

        printf("Introduce el email: ");
        scanf("%s", &temp->email);

        printf("¿Está matriculado? (Si-> 1/No->0): ");
        scanf("%d", temp->enrolled);

        temp->next = NULL;

        //hash calculation using multiplication method
        arrayIndex = h(temp->roll_no,11);
        printf("%d \t : %d \n", temp->id, arrayIndex);

        // Checking for hash collision
        // default initial value of roll no is use senitel value
        // initial value for global array of poiniter is 0

        if (arr_student[arrayIndex] != 0)
        {
            printf("\n\nA hash collision detected\n");
            printf("New data will addedd to the chain.\n");
            temp2 = arr_student[arrayIndex];
            while(temp2->next != NULL)
            {
                temp2 = temp2->next;
            }
            temp2->next = temp;

        }
        else
        {
            // using hash value to store a student record
            arr_student[arrayIndex] = (struct student *)malloc(sizeof(struct student));
            arr_student[arrayIndex] = temp;
        }

        printf("Do you want to add more entry:(Yes-> 1/No->0)");
        scanf("%d",&flag);
    }

    printf("\n");

    while(search_flag == 1)
    {
        printf("\n");
        // searching a student information based on hash value
        printf("Enter Roll number so show the details: ");
        scanf("%d", &key_roll);
        //hash calculation using multiplication method
        arrayIndex = h(key_roll,11);
        //Need to compare the stored value with the search key (roll no)
        if(arr_student[arrayIndex])
        {
            if (arr_student[arrayIndex]->roll_no == key_roll)
            {
                printf("\n\t \t Name: %s \t Roll:%d \t Marks: %.2f\n\n",
                       arr_student[arrayIndex]->name, arr_student[arrayIndex]->roll_no, arr_student[arrayIndex]->marks);
            }

            else
            {
                if(arr_student[arrayIndex]->next)
                {
                    temp2 = arr_student[arrayIndex];
                    while(temp2->next != NULL)
                    {
                        temp2 = temp2->next;
                        if (temp2->roll_no == key_roll)
                        {
                            printf("\n\t \t Name: %s \t Roll:%d \t Marks: %.2f\n\n",temp2->name, temp2->roll_no,temp2->marks);
                            break;
                        }
                    }
                    printf("Record with Roll No:%d not found!\n",key_roll);
                }
            }
        }
        else
        {
            printf("Record with Roll No:%d not found!\n",key_roll);
        }

        printf("Do you want search more record:(Yes-> 1/No->0)");
        scanf("%d",&search_flag);
    }
    return 0;
}
