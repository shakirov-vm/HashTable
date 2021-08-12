
#include "Text.h"

const char input[] = "ENRUSFULL.txt";

int LenghtOfFile()
{
    struct stat buff;
    stat(input, &buff);
    unsigned long len_onegin = buff.st_size;

    return len_onegin;
}
void InputText(char* Text, int lenght)
{
    FILE* potok = fopen(input, "r+");

    if (potok == nullptr) {
        printf("Failed to open input file. LINE: %d\n", __LINE__);
        free(Text);
    }

    size_t readed = fread(Text + 1, sizeof(char), lenght, potok);
    printf("%d - readed\n", readed);
    fclose(potok);
}
int SumString(char* Text)
{
    int sum_string = 0;
    int i = 1;

    for (i; Text[i] != '\0'; i++)
    {
        if (Text[i] == '\n')
        {
            Text[i] = '\0';
            sum_string++;
        }
    }

    return sum_string;
}
void FillStruct(struct LineInfo* Line, char* Text, int lenght, int sum_string)
{
    int i = 0;
    int j = 0;

    Line[0].index = Text;

    for (i; i < lenght; i++)
    {
        if (Text[i] == '\n')
        {
            Text[i] = '\0';
            Line[j].index = &Text[i];

            j++;
        }
    }

    for (i = 0; i <= sum_string; i++)
    {
        for (j = 0; *(Line[i].index + 1 + j) != '\0'; j++) {}
        Line[i].len = j + 1;
    }
}

void fill_struct(char* lines, size_t sum_string, char** eng, char** rus) {
    sum_string *= 2;
    size_t string = 0;
    size_t index = 0;
    for (size_t i = 0; string < sum_string; ) {
        while (lines[i] != '\0') i++;
        i++;
        if (string % 2 == 0) {
            eng[index] = lines + i;
            //printf("%d: [%s] - ", index, eng[index]);
        }
        else {
            rus[index] = lines + i;
            //printf("[%s]\n", rus[index]);
            index++;
        }
        string++;
    }
    printf("\nEND FILL\n\n");
}