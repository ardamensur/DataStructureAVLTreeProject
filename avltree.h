#ifndef INC_213_AS3_AVLTREE_H
#define INC_213_AS3_AVLTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 40
#define TRUE 1
#define FALSE 0

typedef struct node *Node;
typedef struct tree *AVLTree;


struct node{
    char name[MAX];
    int weight;
    float length;
    int day;
    int month;
    int year;
    char city[MAX];
    Node next;
};

struct tree{

    Node fish_data;
    int height;
    AVLTree right;
    AVLTree left;
};

AVLTree MakeEmptyTree(AVLTree Tree);
int Height(AVLTree Tree);
int Find_Max(int val1, int val2);
AVLTree SingleRotateWithLeft(AVLTree Tree);
AVLTree SingleRotateWithRight(AVLTree Tree);
AVLTree DoubleRotateWithLeft(AVLTree Tree);
AVLTree DoubleRotateWithRight(AVLTree Tree);
AVLTree insertFish(char name[MAX], int weight, float length, int day, int month, int year, char city[MAX], AVLTree Tree);
AVLTree readData(char filename[MAX]);
void displayIndex(AVLTree Tree);
void heaviestFish(AVLTree Tree);
Node longestFish(AVLTree Tree);


AVLTree MakeEmptyTree(AVLTree Tree){

    if (Tree != NULL){
        MakeEmptyTree(Tree->left);
        MakeEmptyTree(Tree->right);
        free(Tree);
    }
    return NULL;
}


int Height(AVLTree Tree){

    if (Tree == NULL)
        return -1;
    else
        return Tree->height;
}


int Find_Max(int val1, int val2){

    if (val1 >= val2)
        return val1;
    else
        return val2;
}


AVLTree SingleRotateWithLeft(AVLTree Tree){// left rotation

    AVLTree tmp = Tree->left;

    Tree->left;
    Tree->left = tmp->right;
    tmp->right = Tree;

    Tree->height = (Find_Max(Height(Tree->left), Height(Tree->right)) + 1);
    tmp->height = (Find_Max(Height(tmp->left), Tree->height) + 1);

    return tmp;
}


AVLTree SingleRotateWithRight(AVLTree Tree){// right rotation

    AVLTree tmp = Tree->right;

    Tree->right = tmp->left;
    tmp->left = Tree;

    Tree->height = (Find_Max(Height(Tree->left), Height(Tree->right)) + 1);
    Tree->height = (Find_Max(Height(tmp->right), Tree->height) + 1);

    return tmp;
}


AVLTree DoubleRotateWithLeft(AVLTree Tree){// if double rotation needs

    Tree->left = SingleRotateWithRight(Tree->left);
    return SingleRotateWithLeft(Tree);
}


AVLTree DoubleRotateWithRight(AVLTree Tree){// if double rotation needs

    Tree->right = SingleRotateWithLeft(Tree->right);
    return SingleRotateWithRight(Tree);
}

AVLTree readData(char filename[MAX]){// reading data part
    char name[MAX],city[MAX];
    float length;
    int weight,day,month,year;


    FILE* inFile = fopen(filename, "r");//open the file
    if (inFile == NULL){
        printf("Error opening file");
        exit(1);
    }

    AVLTree tmp;
    while(!feof(inFile)){//it takes data from txt file
        fscanf(inFile, "%[^,],%d,%f,%d/%d/%d,%[^\n]", name, &weight, &length, &day, &month, &year, city);
        tmp = insertFish(name, weight, length, day, month, year, city, tmp);// it sends every loop insert function


    }
    fclose(inFile);
    return tmp;
}
AVLTree insertFish(char name[MAX], int weight, float length, int day, int month, int year, char city[MAX], AVLTree Tree){

    if(Tree == NULL){//if it is empty it generates new tree and loads.
        Tree = (AVLTree)malloc(sizeof(struct tree));


        Tree->fish_data=(Node) malloc(sizeof (struct node));
        Tree->fish_data->weight=weight;
        strcpy(Tree->fish_data->name, name);
        Tree->fish_data->length=length;
        Tree->fish_data->day=day;
        Tree->fish_data->month=month;
        Tree->fish_data->year=year;
        strcpy(Tree->fish_data->city,city);

        Tree->height = 0;
        Tree->left = Tree->right = NULL;
        Tree->fish_data->next = NULL;
    }

    else if(Tree->fish_data->weight>weight){//to go left
        Tree->left = insertFish(name, weight, length, day, month, year, city, Tree->left);

        if(Height(Tree->left) - Height(Tree->right) == 2){// to choose single or double rotation
            if(Tree->fish_data->weight>weight)
                Tree = SingleRotateWithLeft(Tree);
            else
                Tree = DoubleRotateWithLeft(Tree);
        }
    }
    else if(Tree->fish_data->weight<weight){//to go right
        Tree->right = insertFish(name, weight, length, day, month, year, city, Tree->right);

        if(Height(Tree->left) - Height(Tree->right) == 2){ // to choose single or double rotation
            if(Tree->fish_data->weight<weight)
                Tree = SingleRotateWithRight(Tree);
            else
                Tree = DoubleRotateWithRight(Tree);
        }
    }
    else {//if the fishes have same weight
        Tree->fish_data->next= (Node)malloc(sizeof (struct node));
        strcpy(Tree->fish_data->next->name,name);
        Tree->fish_data->next->weight=weight;
        Tree->fish_data->next->length=length;
        Tree->fish_data->next->day=day;
        Tree->fish_data->next->month=month;
        Tree->fish_data->next->year=year;
        strcpy(Tree->fish_data->next->city,city);
        Tree->fish_data->next->next=NULL;
    }

    Tree->height = (Find_Max(Height(Tree->left), Height(Tree->right)) + 1);

    return Tree;
}


void displayIndex(AVLTree Tree){//print function

    if(Tree != NULL){
        displayIndex(Tree->left);
        printf("%s  %03d  %.2f %02d/%02d/%-5d  %s\n", Tree->fish_data->name, Tree->fish_data->weight, Tree->fish_data->length, Tree->fish_data->day, Tree->fish_data->month, Tree->fish_data->year, Tree->fish_data->city);

        if(Tree->fish_data->next != NULL){

            Node tmp =Tree->fish_data->next;

            while(tmp != NULL){
                printf("%s  %03d  %.2f %02d/%02d/%-5d  %s\n", tmp->name, tmp->weight, tmp->length, tmp->day, tmp->month, tmp->year, tmp->city);
                tmp = tmp->next;
            }
        }
        displayIndex(Tree->right);
    }
}
void heaviestFish(AVLTree Tree) {//to find heaviest it will go the rightest node.
    AVLTree heaviest = Tree;
    while (heaviest->right != NULL)
        heaviest = heaviest->right;
    printf("%s  %03d  %.2f %02d/%02d/%-5d  %s\n", heaviest->fish_data->name, heaviest->fish_data->weight, heaviest->fish_data->length,
           heaviest->fish_data->day, heaviest->fish_data->month, heaviest->fish_data->year, heaviest->fish_data->city);


    if (heaviest->fish_data->next != NULL) {
        Node tmp = heaviest->fish_data->next;

        while (tmp != NULL) {
            printf("%s  %03d  %.2f %02d/%02d/%-5d  %s\n", tmp->name, heaviest->fish_data->weight, tmp->length, tmp->day, tmp->month, tmp->year, tmp->city);
            tmp = tmp->next;
        }
    }
}

Node longestFish(AVLTree Tree) {//recursively
    if (Tree == NULL) { //base case
        return NULL;
    }

    Node leftLongest = longestFish(Tree->left);// It will find the longest fish in the left and right subtrees
    Node rightLongest = longestFish(Tree->right);

    Node current = Tree->fish_data;// it will find the longest fish in the current node's data' linked list
    Node currentLongest = current;
    while (current != NULL) {
        if (current->length > currentLongest->length) {
            currentLongest = current;
        }
        current = current->next;
    }

    Node longest = currentLongest; // it will determine the longest fish among the current node, left subtree, and right subtree
    if (leftLongest != NULL && (longest == NULL || leftLongest->length > longest->length)) {
        longest = leftLongest;
    }
    if (rightLongest != NULL && (longest == NULL || rightLongest->length > longest->length)) {
        longest = rightLongest;
    }

    return longest;//not AVL tree, it will return NODE because of the finding longest in all fish data.
}


#endif //INC_213_AS3_AVLTREE_H
