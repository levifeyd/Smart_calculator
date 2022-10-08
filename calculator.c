#include "calculator.h"

// int main() {
//    Node* head = NULL; //стек;
//    Node* output_str = NULL; // выходная строка
//    char str[256] = "1/2+(2+3";
//    double a = 0;
//    int b = validator(str);
//    if (b == ERROR) {
//         a = ERROR;
//         printf("ERROR");
//     } else {
//         a = parser(str, &head, &output_str);
//         print(output_str);
//         calculate(&head, &output_str, &a);
//         printf("%f",a);
//     }
//    return a;
// }
int startuem(char* str, double* result) {
    Node* head = NULL;
    Node* output_str = NULL;
    int a = 0;
    int b = validator(str);
    if (b == ERROR) {
        a = ERROR;
    } else {
        a = parser(str, &head, &output_str);
        calculate(&head, &output_str, result);
    }
    free_nodes(&head);
    free_nodes(&output_str);
    return a;
}

void pop(Node** plist) {
    if (*plist != NULL) {
        Node * p = *plist;
        *plist = p->next;
        free(p);
    }
}

Node* getLast(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}
void push_back(Node* head, double operand, int operation) {
    Node *last = getLast(head);
    Node *tmp = (Node*)malloc(sizeof(Node));
    tmp->operand = operand;
    tmp->operation = operation;
    tmp->next = NULL;
    last->next = tmp;
}

Node* push(Node* head, double operand, int operation) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->operation = operation;
    tmp->operand = operand;
    if (head == NULL) {
         head = tmp;
         tmp->next = NULL;
    } else {
         tmp->next = head;
         head = tmp;
    }
     return head;
}

int parser(char* str, Node** head, Node** output_str) {
    int res = 0;
    if (str) {
        int point_counter = 0;
        char* temp = malloc(sizeof(char) * 256);
            for (int i = 0; str[i] != '\0'; i++) {
                memset(temp, '\0', 256);
                double operand = 0;
                int operation = 0;
                if ((str[i] >= 48 && str[i] <= 57)) {
                    operation = NUM;
                    point_counter = 0;
                    get_variable(str, &i, &point_counter, temp);
                    if (point_counter > 1) {
                        res = 1;
                        break;
                    }
                    operand = atof(temp);
                    get_num(head, output_str, operand, operation);
                    i--;
                } else if (str[i] == '(') {
                    operation = OPEN;
                    get_num(head, output_str, operand, operation);
                } else if (str[i] == ')') {
                    operation = CLOSE;
                    get_num(head, output_str, operand, operation);
                } else if (str[i] == '+') {
                    operation = SUM;
                    get_num(head, output_str, operand, operation);
                } else if (str[i] == '-') {
                    operation = SUB;
                    get_num(head, output_str, operand, operation);
                } else if (str[i] == '*') {
                    operation = MUL;
                    get_num(head, output_str, operand, operation);
                } else if (str[i] == '/') {
                    operation = DIV;
                    get_num(head, output_str, operand, operation);
                } else if (str[i] == '%') {
                    operation = MOD;
                    get_num(head, output_str, operand, operation);
                } else if (str[i] == '^') {
                    operation = POW;
                    get_num(head, output_str, operand, operation);
                } else if (str[i] >= 'a' && str[i] <= 'z') {
                    get_function(str, &i, temp);
                    operation = define_function(temp);
                    get_num(head, output_str, operand, operation);
                    i--;
                    if (operation == 18) {
                        res = 1;
                        break;
                    }
                } else {
                    res = 1;
                    break;
                }
            }
            if (*head != NULL && point_counter <= 1) {
                out_stack(output_str, head);
            }
            free(temp);
    }
    return res;
}

void out_stack(Node** output_str, Node** head) {
    if (*head != NULL) {
        while (*head != NULL) {
            if (*output_str == NULL) {
                *output_str = push((*output_str), (*head)->operand, (*head)->operation);
            } else {
                push_back((*output_str), (*head)->operand, (*head)->operation);
            }
            pop(head);
        }
    }
}
void get_variable(const char* str, int* j, int* point_counter, char* digits) {
        int i = 0;
        while ((str[*j] >= 48  && str[*j] <= 57) || (str[*j] == '.')) {
            if (str[*j] == '.') *point_counter += 1;
            digits[i] = str[*j];
            *j = *j + 1;
            i++;
        }
}

void get_function(const char* str, int* j, char* function) {
    int i = 0;
    while (str[*j] >= 97 && str[*j] <= 122) {
        function[i] = str[*j];
        *j = *j + 1;
        i++;
    }
}

int define_function(char* str) {
    int func_res = 0;
    if (!strcmp(str, "sin")) {
        func_res = SIN;
    } else if (!strcmp(str, "cos")) {
        func_res = COS;
    } else if (!strcmp(str, "tan")) {
        func_res = TAN;
    } else if (!strcmp(str, "acos")) {
        func_res = ACOS;
    } else if (!strcmp(str, "asin")) {
        func_res = ASIN;
    } else if (!strcmp(str, "atan")) {
        func_res = ATAN;
    } else if (!strcmp(str, "sqrt")) {
        func_res = SQRT;
    } else if (!strcmp(str, "ln")) {
        func_res = LN;
    } else if (!strcmp(str, "log")) {
         func_res = LOG;
    } else {
        func_res = ERROR;
    }
    return func_res;
}

int get_brackets(Node** head, Node** output_str, int operation, double operand) {
    int res = 0;
    if (operation == OPEN) {
        *head = push(*head, operand, operation);  // в стек
        res = 1;
    } else if (operation == CLOSE) {
        while (((*head) != NULL) && ((*head)->operation != OPEN)) {
            push_back(*output_str, (*head)->operand, (*head)->operation);
            pop(head);
        }
        pop(head);
        res = 1;
    }
    return res;
}

void get_num(Node** head, Node** output_str, double operand, int operation) {
    if (operation == NUM) {
        if (*output_str == NULL) {
            *output_str = push(*output_str, operand, operation);
        } else {
            push_back(*output_str, operand, operation);
        }
    } else {
       if (*head == NULL) {
            *head = push(*head, operand, operation);
        } else {
            if (!get_brackets(head, output_str, operation, operand)) {
                prioritet_functions(head, output_str, operand, operation);
            }
        }
    }
}

void prioritet_functions(Node** head, Node** output_str, double operand, int operation) {
    if (get_prioritet(operation) > (get_prioritet((*head) -> operation))) {
       *head = push(*head, operand, operation);
    } else if ((get_prioritet(operation)) < (get_prioritet((*head) -> operation))) {
        while ((*head != NULL) && (get_prioritet(operation)) < (get_prioritet((*head) -> operation))) {
            if (*output_str == NULL) {
                *output_str = push(*output_str, (*head)->operand, (*head)->operation);
                } else {
                    if ((*head)->operation != OPEN) {
                        push_back(*output_str, (*head)->operand, (*head)->operation);
                    }
                }
                pop(head);
        }
        *head = push(*head, operand, operation);
    } else {
        if (operation == MOD) {
            *head = push(*head, operand, operation);
        } else {
            if (*output_str == NULL) {
                *output_str = push(*output_str, operand, (*head)->operation);
            } else {
                push_back(*output_str, operand, (*head)->operation);
            }
        pop(head);
        *head = push(*head, operand, operation);
        }
    }
}

int get_prioritet(int operation) {
     int res = 0;
     if (operation >= 8 && operation <= 15) {
         res = 5;
     } else if (operation == 6 || operation == 7) {
         res = 4;
     } else if (operation == 5) {
         res = 3;
     } else if (operation == 3 || operation == 4) {
         res = 2;
     } else if (operation == 1 || operation == 2) {
         res = 1;
     }
     return res;
}

int calculate(Node** head, Node ** output_str, double* res) {
    int result = 0;
    double a;
    double b;
    while (*output_str != NULL) {
        if ((*output_str) ->operation == NUM) {
            *head = push(*head, (*output_str)->operand, (*output_str)->operation);
            pop(output_str);
        } else {
            if (((*output_str))->operation == SUM) {
                a = (*head)->operand;
                pop(head);
                if (*head == NULL) {
                    b = 0;
                } else {
                    b = (*head)->operand;
                    pop(head);
                }
                *res = b + a;
            } else if ((*output_str)->operation == SUB) {
                a = (*head)->operand;
                pop(head);
                if (*head == NULL) {
                    b = 0;
                } else {
                    b = (*head)->operand;
                    pop(head);
                }
                *res = b - a;
            } else if ((*output_str)->operation == MUL) {
                a = (*head)->operand;
                pop(head);
                if (*head == NULL) {
                    b = 1;
                } else {
                    b = (*head)->operand;
                    pop(head);
                }
                *res = b * a;
            } else if ((*output_str)->operation == DIV) {
                a = (*head)->operand;
                pop(head);
                if (*head == NULL) {
                    b = 1;
                } else {
                    b = (*head)->operand;
                    pop(head);
                }
                *res = b / a;
            } else if ((*output_str)->operation == MOD) {
                a = (*head)->operand;
                pop(head);
                if (*head == NULL) {
                    b = 0;
                } else {
                    b = (*head)->operand;
                    pop(head);
                }
                *res = fmod(b, a);
            } else if ((*output_str)->operation == POW) {
                a = (*head)->operand;
                pop(head);
                if (*head == NULL) {
                    b = 1;
                } else {
                    b = (*head)->operand;
                    pop(head);
                }
                *res = pow(b, a);
            } else if ((*output_str)->operation == SQRT) {
                a = (*head)->operand;
                pop(head);
                *res = sqrt(a);
            } else if ((*output_str)->operation == SIN) {
                a = (*head)->operand;
                pop(head);
                *res = sin(a);
            } else if ((*output_str)->operation == COS) {
                a = (*head)->operand;
                pop(head);
                *res = cos(a);
            } else if ((*output_str)->operation == TAN) {
                a = (*head)->operand;
                pop(head);
                *res = tan(a);
            } else if ((*output_str)->operation == ATAN) {
                a = (*head)->operand;
                pop(head);
                *res = atan(a);
            } else if ((*output_str)->operation == ASIN) {
                a = (*head)->operand;
                pop(head);
                *res = asin(a);
            } else if ((*output_str)->operation == ACOS) {
                a = (*head)->operand;
                pop(head);
                *res = acos(a);
            } else if ((*output_str)->operation == LN) {
                a = (*head)->operand;
                pop(head);
                *res = log(a);
            } else if ((*output_str)->operation == LOG) {
                a = (*head)->operand;
                pop(head);
                *res = log10(a);
            }
            pop(output_str);
            *head = push(*head, *res, 0);
        }
    }
    *res = (*head)->operand;
    pop(head);
    return result;
}
int is_digit(char digit) {
    int res = 0;
    if ((digit >= 48 && digit <= 57)) {
        res = 1;
    }
    return res;
}

void free_nodes(Node ** head) {
    while (*head != NULL) {
        Node* prev = NULL;
        prev = *head;
        *head = prev->next;
        free(prev);
    }
}

int validator(char* str) {
    int res = 0;
    int cnt_bracket_open = 0;
    int cnt_bracket_close = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') cnt_bracket_open++;
        if (str[i] == ')') cnt_bracket_close++;
    }
    if (cnt_bracket_close != cnt_bracket_open) {
        res = ERROR;
    } else {
        int func_cnt = 0;
        int cnt_digit = 0;
        for (int i = 0; str[i] != '\0'; i++) {
                if (is_digit(str[i])) {
                    cnt_digit++;
                } else if (str[i] == '-' && str[i-1] == '(') {
                    continue;
                } else if (str[i] == 40 || str[i] == 41 || (str[i] >= 97 && str[i] <= 122) || str[i] == '.') {
                    continue;
                }
                if (!(is_digit(str[i]))) {
                    func_cnt++;
                }
            }
            if (cnt_digit <= func_cnt) {
                res = ERROR;
            }
    }
    return res;
}
