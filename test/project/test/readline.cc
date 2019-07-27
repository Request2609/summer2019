#include<iostream>
#include <readline/readline.h>
#include <readline/history.h>
using namespace std;
int main()
{
    while(true)
    {   
        const char* q = "myshell:" ;
        char * p =readline(q)  ;
        add_history(p);//加入历史列表
        p = readline(q);
    }
}
