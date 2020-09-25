#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Employee{
    char name[20];
    char jobPos[15];
    int grade;
    int age;
    Employee *next;
}*head = NULL, *tail = NULL;

bool isValid(char *name, char *jobPos, int grade, int age){
    // [15%] (1) INSERT YOUR CODE HERE  (DONE)
    struct Employee *curr = (struct Employee *) malloc(sizeof(Employee));
    curr = head;
    
    while (curr != NULL){
        if(strcmp(curr->name, name) == 0 && strcmp(curr->jobPos, jobPos) == 0 && curr->grade == grade && curr->age == age){
            return false;
        }
        curr = curr -> next;
    }

    return true;
}

void push(char *name, char *jobPos, int grade, int age){
	if(isValid(name, jobPos, grade, age) == false) return;
	 
    struct Employee *curr = (struct Employee *) malloc(sizeof(Employee));
    curr->next = NULL;
    // [10%] (2) INSERT YOUR CODE HERE (Done)
    strcpy (curr->name, name);
    strcpy (curr->jobPos, jobPos);
    curr->age = age;
    curr->grade = grade;
    
    if(head == NULL){
        head = curr;
        tail = curr;
    }else{
        curr->next = head;
        head = curr;
    }
}


void pop(){
    struct Employee * curr = head;
    // [15%] (3) INSERT YOUR CODE HERE (Done)
    if (curr == NULL){
    	printf("the list is empty!");
        return;
    }
    else if (curr == tail){
     free(curr);
     head = tail = NULL;
	} else{
		while (curr -> next != tail){
			curr = curr -> next;
		}
			free (tail);
			tail = curr;
			tail -> next = NULL;
	}
}

void printAll(){
    printf("\n\n");
    struct Employee * curr = head;
    int empCtr = 0;
    int tmp=0;
    if(!curr){
        printf("the list is empty!");
    }else{
        // [10%] (4) INSERT YOUR CODE HERE
        
        curr = head;
        printf ("===============================================================================\n");
        printf("|     Name     |     Job Position     |     Grade     |     Age     \n");
        printf ("===============================================================================\n");
        while (curr != NULL){
        	printf("     %s     |", curr -> name);
        	printf("     %s     |", curr -> jobPos);
        	printf("     %d     |", curr -> age);
        	printf("      %d  \n| ", curr -> grade);
        	curr = curr -> next;
        	tmp++;
		}
		printf ("===============================================================================\n");
		printf ("Total Employee : %d\n", tmp);
		printf ("===============================================================================\n");
        
	}
}


int main(){
    pop();
    printAll();
    push("Hanry", "Supervisor", 12, 27);
    push("Yen", "Manager", 13, 40);
    pop();
    push("Derwin", "Manager", 15, 31);
    push("Andry", "Manager", 15, 30);
    pop();
    push("Saka", "Manager", 15, 32);
    pop();
    push("Afan", "Manager", 16, 35);
    push("Fredy", "Senior Manager", 18, 45);
    pop();
    printAll();
    return 0;

}

