#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

int is_valid_regexp(const char* regexp);
int match(const char *regexp, const char *text);
char tmp;           //用于存储当前待比对的字母或数字

enum Statetype
{
    normal,state1,state2,statestar,stateplus,statequestion,states,stated
};
enum Statetype state=normal;

int length,count,i,j;

int main()
{
    char * regexp = (char *)malloc(100);
    char * text = (char *)malloc(100);
    printf("先输入正则表达式，再输入需匹配的串：\n");
    scanf("%s",regexp);
    scanf("%s",text);
    if (is_valid_regexp(regexp))
        match(regexp,text);
    else
        printf("error!'\n");
    return 0;
}

int is_valid_regexp(const char* regexp)
{
    int length=strlen(regexp),i=0;
    if (length>1&&regexp[0]=='$')
        return FALSE;
    if (regexp[0]=='.'||regexp[0]=='?'||regexp[0]=='*'||regexp[0]=='+')
        return FALSE;
    return TRUE;
}

int isdigit(char c)
{
    if((c>='0')&&(c<='9'))
        return TRUE;
    else
        return FALSE;
}

int isspace(char c)
{
    if (c == ' ' && c == '\n' && c == '\f' && c == '\r' && c == '\t' && c == '\v')
        return TRUE;
    else
        return FALSE;
}

int judgechar(char c)       //判断当前字符的下一个是否有重复符号
{
    if  (c == '?')
        return 1;
    else if (c =='*')
        return 0;
    else if (c == '+')
        return -1;
    else
        return 100;
}

int isalnum(char c)             //检测是不是字母?
{
    if ((c >= 'a' && c<= 'z')||(c>='A' && c<='Z'))
        return TRUE;
    else
        return FALSE;
}
int match(const char *regexp, const char *text)
{
    length = strlen(regexp);
    count = strlen(text);
    i=0,j=0;
    int judge = 1;
    if (regexp[0]=='^')           //state1
    {
        i++;
        if (text[j]!=regexp[1])
        {
            return FALSE;
        }
        else
            state=state1;
    }
    /*if (regexp[length-1]=='$')
    {

    }*/
    while (j<count)
    {
        judge = statedecide(regexp,text);
        if (!judge)
        {
            printf("不接受\n");
            break;
        }
    }
    printf("%d,%d",i,j);
    printf("jieshu");
    return FALSE;
}

int statedecide(const char *regexp, const char *text)
{
    int flag=1,m=0;
    tmp = regexp[i];
    if (state == normal)
    {
        if (regexp[i]=='\\')
        {
            state = state2; //state2 根据\后字符判断是什么
            i++;
        }
        else if (regexp[i+1]=='*')
            state = statestar;
        else if (regexp[i+1]=='?')
            state = statequestion;
        else if (regexp[i+1]=='+')
            state = stateplus;
        else
        {
            for (; j<count; j++)
            {
                if (regexp[i]==text[j])
                {
                    j++;
                    break;
                }
            }
            i++;
        }

    }
    else if (state == state1)
    {
        i++;
        j++;
        state= normal;
    }
    else if (state == state2)
    {
        if (regexp[i]=='s')
            state=states;
        else if (regexp[i]=='d')
            state=stated;
        else
        {
            tmp=regexp[i];          //保存\后字符以匹配用
            state = normal;
        }
        i++;
    }
    else if (state == states)       //\s
    {
        if (regexp[i]=='*')
        {
            for (; j<count; j++)
            {
                flag = isspace(text[j]);
                if (!flag)
                    break;
            }
            i++;
        }
        else if (regexp[i]=='?')
        {
            for (m=0; m<2; m++)
            {
                j+=m;
                flag = isspace(text[j]);
                if (!flag)
                    break;
            }
            i++;
        }
        else if (regexp[i]=='+')
        {
            if (!isspace(text[j]))
                return FALSE;
            else
            {
                for (; j<count; j++)
                {
                    flag = isspace(text[j]);
                    if (!flag)
                        break;
                }
            }
            i++;
        }
        else
        {
            if (!isspace(text[j]))
                return FALSE;
            else
                state = normal;
        }
        state = normal;
    }
    else if (state==stated)
    {
        if (regexp[i]=='*')
        {
            for (; j<count; j++)
            {
                flag = isdigit(text[j]);
                if (!flag)
                    break;
            }
            i++;
        }
        else if (regexp[i]=='?')
        {
            for (m=0; m<2; m++)
            {
                j+=m;
                flag = isdigit(text[j]);
                if (!flag)
                    break;
            }
            i++;
        }
        else if (regexp[i]=='+')
        {
            if (!isspace(text[j]))
                return FALSE;
            else
            {
                for (; j<count; j++)
                {
                    flag = isdigit(text[j]);
                    if (!flag)
                        break;
                }
            }
            i++;
        }
        else
        {
            if (!isdigit(text[j]))
                return FALSE;
            else
                state = normal;
        }
        state = normal;
    }
    else if (state == statestar)
    {
        for (; j<count; j++)
        {
            if (text[j]!=tmp)
                break;
        }
        i+=2;
        state = normal;
    }
    else if (state == stateplus)
    {
        if (text[j]!=tmp)
            return FALSE;
        for (; j<count; j++)
        {
            if (text[j]!=tmp)
                break;
        }
        i+=2;
        state = normal;
    }
    else if (state == statequestion)
    {
        for (m=0; m<2; m++)
        {
            j+=m;
            flag = isdigit(text[j]);
            if (!flag)
                break;
        }
        i+=2;
        state = normal;
    }
}
