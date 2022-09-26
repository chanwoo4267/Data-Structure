#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;
char expr[1111];
static int isp[] = {0,19,12,12,13,13,13,0};
static int icp[] = {20,19,12,12,13,13,13,0};

int stack[1111];
char expr_p[1111];
int top = -1;

precedence get_token(char*,int*);
void postfix(void);
char PrintToken(precedence);
void push(int *, int);
int pop(int *);
void stack_f(void);
void stack_e(void);

int main()
{
    scanf("%s",expr);
    postfix();
    printf("%s\n",expr_p);
    return 0;
}

void push(int *top, int item)
{
    if(*top>=1110)
    {
        stack_f();
        return;
    }
    stack[++(*top)] = item;
}

int pop(int *top)
{
    if (*top == -1)
        stack_e();
    return stack[(*top)--];
}

void stack_f()
{
    printf("Stack Is Full!");
    exit(1);
}

void stack_e()
{
    printf("Stack Is Empty!");
    exit(1);
}

precedence get_Token(char *symbol, int *n)
{
    *symbol = expr[(*n)++];
    switch(*symbol) {
        case '(' : return lparen;
        case ')' : return rparen;
        case '+' : return plus;
        case '-' : return minus;
        case '*' : return times;
        case '/' : return divide;
        case '%' : return mod;
        case '\0' : return eos;
        default : return operand;
    }
}

void postfix(void)
{
    precedence token;
    char symbol;
    int i=0;
    int n=0;
    stack[++top] = eos;
    for(token = get_Token(&symbol, &n); token != eos; token = get_Token(&symbol, &n))
    {
        if (token == operand)
            expr_p[i++] = symbol;
        else if (token == rparen)
        {
            while(stack[top] != lparen)
                expr_p[i++] = PrintToken(pop(&top));
            pop(&top);
        }
        else
        {
            while(isp[stack[top]] >= icp[token])
                expr_p[i++] = PrintToken(pop(&top));
            push(&top,token);
        }
    }
    while((token=pop(&top)) != eos)
        expr_p[i++] = PrintToken(token);
}

char PrintToken(precedence token)
{
    switch(token) {
        case plus : return '+'; break;
        case minus : return '-'; break;
        case divide : return '/'; break;
        case times : return '*'; break;
        case mod : return '%'; break;
        case eos : return '\0'; break;
    }
    return '\0';
}
