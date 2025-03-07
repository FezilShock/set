#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct n{
    int val;
    struct n* next;
}node;

typedef struct{
    node* set_pt;
    int size;
}set;

node* create_node(){
    int val;
    node* new_node = (node *)malloc(sizeof(node));
    scanf("%d", &val);
    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

set* createSet(void){
    set* new_set = (set*)malloc(sizeof(set));
    new_set->set_pt = NULL;
    new_set->size = 0;
    return new_set;
}

void setPush(set* set){
    node* tmp = create_node();
    tmp->next = set->set_pt;
    set->set_pt = tmp;
    ++set->size;
}

void setOutput(set* set){
    node* curNode = set->set_pt;
    while(curNode != NULL){
        printf("%d ", curNode->val);
        curNode = curNode->next;
    }
}

void freeset(set* set){
    if(set->size){
        node* curNode = set->set_pt;
        while(curNode != NULL){
            node* delNode = curNode;
            curNode = curNode->next;
            free(delNode);
        }
        free(curNode);
    }
    free(set);
}

int main(void)
{
    set* main_set = createSet();
    setPush(main_set);
    setPush(main_set);
    setPush(main_set);
    setPush(main_set);
    setOutput(main_set);
    freeset(main_set);
    return 0;
}