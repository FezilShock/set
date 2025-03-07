#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct n{
    double val;
    struct n* next;
}node;

typedef struct{
    node* first_node;
    node* now;
    int size;
}set;

node* create_node(double val){
    node* new_node = (node *)malloc(sizeof(node));
    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

set* createSet(void){
    set* new_set = (set*)malloc(sizeof(set));
    new_set->first_node = NULL;
    new_set->size = 0;
    return new_set;
}

bool setSearch(set* set, double var){
    if(set->size){
        node* curNode = set->first_node;
        while(curNode != NULL){
            if(curNode->val == var) return curNode;
            curNode = curNode->next;
        }
        return NULL;
    }else return NULL;
}

void setPush(set* set){
    double new_var;
    char ch;
    char res = 0;
    scanf("%lf", &new_var);
    node* tmp = create_node(new_var);
    set->first_node = tmp;
    set->now = tmp;
    ++set->size;
    do{
        res = scanf("%lf", &new_var);
        if (!setSearch(set, new_var)){
            node* tmp = create_node(new_var);
            set->now->next = tmp;
            set->now = tmp;
            ++set->size;
        }
        if (res == 0 && (ch = getchar()) == 'q') break;
    }while(true);
}

void setOutput(set* set){
    node* curNode = set->first_node;
    while(curNode != NULL){
        printf("%.4f ", curNode->val);
        curNode = curNode->next;
    }
}

int convert(int dv){
    int res = 0;
    long j = 1;
    while(dv > 0){
        res += (dv % 2) * j;
        dv /= 2;
        j *= 10;
    }
    return res;
}

void binconvert(set* main_set, set* bin_set){
    node* curNode = main_set->first_node;  
    node* tmp = create_node(convert(curNode->val));
    bin_set->first_node = tmp;
    bin_set->now = tmp;
    ++bin_set->size;
    curNode = curNode->next;
    while(curNode != NULL){
        node* tmp = create_node(convert(curNode->val));
        bin_set->now->next = tmp;
        bin_set->now = tmp;
        curNode = curNode->next;
        ++bin_set->size;
    }
}

void freeset(set* set){
    if(set->size){
        node* curNode = set->first_node;
        while(curNode != NULL){
            node* delNode = curNode;
            curNode = curNode->next;
            free(delNode);
        }
        free(curNode);
    }
    free(set);
}

double modulo(double a){
    if(a >= 0){
        int b = (int) a;
        return (a-b);
    }else{
        int b = (int) a;
        return (b-a);
    }
}

int main(void)
{
    set* main_set = createSet();
    set* bin_set = createSet();
    setPush(main_set);
    binconvert(main_set, bin_set);
    setOutput(main_set);
    putchar('\n');
    setOutput(bin_set);
    freeset(main_set);
    return 0;
}