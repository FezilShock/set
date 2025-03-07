#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

char* dynstring(char c){
    int l = 0;
    int size = 10;
    char *string = (char*) malloc(size * sizeof(char));
    char ch = getchar();
    while (ch != c){
        string[(l)++] = ch;
        if(l >= size){
            size *=2;
            string = (char *) realloc(string, size * sizeof(char));
        }
        ch = getchar();
    }
    string[l] = '\0';
    return string;
}

//start realization of stack
typedef struct n{
    char* val;
    struct n* next;
}node;

typedef struct{
    node* stack_pt;
    int size;
}stack;

node* create_node(char sym){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->val = dynstring(sym);
    new_node->next = NULL;
    return new_node;
}

stack* createStack(void){
    stack* new_stack = (stack*)malloc(sizeof(stack));
    new_stack->stack_pt = NULL;
    new_stack->size = 0;
    return new_stack;
}

void stackPush(char val, stack* stack){
    node* tmp = create_node(val);
    tmp->next = stack->stack_pt;
    stack->stack_pt = tmp;
    ++stack->size;
}

char* stackPop(stack* stack){
    if(!stack->size){
        printf("Error: stack is empty\n");
        return 0;
    }
    char* result = stack->stack_pt->val;
    node* tmp = stack->stack_pt;
    stack->stack_pt = stack->stack_pt->next;
    free(tmp);
    --stack->size;
    return result;
}

bool stackIsEmpty(stack* stack){
    if(stack->size){
        return false;
    }else{
        return true;
    }
}

bool stackSearch(stack* stack, char* str){
    if(stack->size){
        node* curNode = stack->stack_pt;
        while(curNode != NULL){
            if(!strcmp(str, curNode->val)) return curNode;
            curNode = curNode->next;
        }
        return NULL;
    }else return NULL;
}

int stackSize(stack* stack){
    return stack->size;
}

void freestack(stack* stack){
    if(stack->size){
        node* curNode = stack->stack_pt;
        while(curNode != NULL){
            node* delNode = curNode;
            curNode = curNode->next;
            free(delNode);
        }
        free(curNode);
    }
    free(stack);
}



void help(void){
    printf("Commands for work with stack:\n1 - push in stack string value.\n2 - pop from stack string value.\n4 - stack is empty.\n0 - exit from program.\n");

}


int main(void)
{
    stack* main_stack = createStack();
    help();
    int input = 1;
    while (input){
        printf("Input commands: ");
        scanf("%d", &input);
        switch(input){
            case 0: break;
            case 1:
                getchar();
                puts("Input string: ");
                stackPush('\n', main_stack);
                break;
            case 2:
                printf("Value from stack: %s\n", stackPop(main_stack));
                break;
            case 3:
                printf("Size of stack: %d\n", stackSize(main_stack));
                break;
            case 4:
                printf("stack is: ");
                if (stackIsEmpty(main_stack)){
                    puts("not empty");
                }else{
                    puts("empty");
                }
                break;
            default:
                help();
        }
    }
    return 0;
}