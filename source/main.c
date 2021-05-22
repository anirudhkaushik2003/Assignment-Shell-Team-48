#include "processor/input.h"
#include "processor/prompt.h"
#include "processor/tokenizer.h"
#include "utils/files.h"
#include "commands/execvp.h"
#include "utils/Subjects.h"

void status_sleepy()
{
    char pet[] = "            ,.  ,.\n            ||  ||\n           ,''--''.\n          : (-)(-) :\n         ,'   --   `.\n         :          :\n         :          :\n   -slp- `._m____m_,' \n";
    char pet2[] = "            ,.  ,.\n            ||  ||\n           ,''--''.\n          : (o)(o) :\n         ,'   --   `.\n         :          :\n         :          :\n   -slp- `._m____m_,' \n";
    char pet3[] = "            ,.  ,.\n            ||  ||\n           ,''--''.\n          : (o)(o) :\n         ,'    O   `.\n        :            :\n        :            :\n   -slp- `._m____m_,' \n";
    system("clear");
    int i;
    while (i < 2)
    {
        printf(BLUE);
        printf("%s\n", pet2);
        usleep(500000);
        system("clear");
        printf("%s\n", pet3);
        usleep(500000);
        system("clear");
        printf("%s\n", pet);
        usleep(10000);
        system("clear");
        printf(RESET);
        i++;
    }
}

int main()
{
    status_sleepy();
    clearScreen();
    start_point = 0;
    UseCond = 0;
    int i;
    token_mat a;
    enterSubjectDirectory();
    Initialize_subject_array();
    while (1)
    {
        Initialize();
        String Input;
        prompt_print();
        i = 0;
        char temp;
        Input.str = (char *)malloc(sizeof(char) * MAX_TOKEN_LENGTH);
        while (1)
        {
            temp = (char)getchar();
            if (temp != '\n')
                Input.str[i++] = temp;
            else
            {
                Input.str[i] = '\0';
                break;
            }
        }

        tokenize_input(Input);
    }
}
