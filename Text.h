#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <assert.h>

struct LineInfo
{
    int len;
    char* index;
};

int LenghtOfFile();
void InputText(char* Text, int lenght);
int SumString(char* onegin);
void FillStruct(struct LineInfo* Line, char* Text, int lenght, int sum_string);