#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int getch(void);
void get_password(char *password);

int main()
{
    char password[20];
    get_password(password);
    printf("%s\n", password);

    return 0;
}

int getch(void)
{
    int ch;
    struct termios tm, tm_old;
    tcgetattr(STDIN_FILENO, &tm);
    tm_old = tm;
    tm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tm);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &tm_old);
    return ch;
}

void get_password(char *password)
{
    int i = 0;
    char ch;

    printf("Enter password: ");
    while ((ch = getch()) != '\n')
    {
        if (ch == '\b')
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
        else
        {
            password[i] = ch;
            printf("*");
            i++;
        }
    }
    password[i] = '\0';
    printf("\n");
}
