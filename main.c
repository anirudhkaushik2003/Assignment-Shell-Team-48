#include "processor/input.h"
#include "processor/prompt.h"
#include "processor/tokenizer.h"
#include "utils/files.h"
int main()
{
    start_point = 0;
    int i;
    enterSubjectDirectory();
    while (1)
    {
        Initialize();
        String Input;
        prompt_print();

        i = 0;
        char temp;
        Input.str = (char*)malloc(sizeof(char) * MAX_TOKEN_LENGTH);
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
