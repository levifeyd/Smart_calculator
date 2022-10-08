#ifndef SRC_CALCULATOR_H_
#define SRC_CALCULATOR_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define NUM 0
#define SUM 1
#define SUB 2
#define MUL 3
#define DIV 4
#define MOD 5
#define POW 6
#define SQRT 7
#define COS 8
#define SIN 9
#define ACOS 10
#define ASIN 11
#define TAN 12
#define ATAN 13
#define LN 14
#define LOG 15
#define OPEN 16
#define CLOSE 17
#define ERROR 18

typedef struct Node {
    int operation;
    double operand;
    struct Node* next;
} Node;


Node* push(Node* head, double operand, int operation);

void push_back(Node* head, double operand, int operation);
int is_empty(Node* list);

void pop(Node** plist);

int parser(char* str, Node** head, Node** output_str);

void get_variable(const char* str, int* j, int* point_counter, char* digits);
void get_function(const char* str, int* j, char* function);
int define_function(char* str);

Node* getLast(Node *head);
void pushBack(Node *head, char value);

void get_num(Node** head, Node** output_str, double operand, int operation);
void get_presendence(Node** head, Node** output_str, int operand, int opearation);
void prioritet_functions(Node** head, Node** output_str, double operand, int operation);
int get_brackets(Node** head, Node** output_str, int operation, double operand);
int get_prioritet(int operation);
void free_nodes(Node ** head);
int calculate(Node** head, Node ** output_str, double* res);
void out_stack(Node** output_str, Node** head);

int validator(char*str);
int is_digit(char digit);
int startuem(char* str, double* result);

#ifdef __cplusplus
}

#endif
#endif  // SRC_CALCULATOR_H_
