// HashTable.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>

#define LIST_H
#ifdef LIST_H
#include "ListObj.h"
#endif 

#include "HashTable.h"
#include "HashFunctions.h"
#include "Text.h"

int main() //       Все узлы ссылаются на одно поле?
{
  /*  class List<int> list {};

    for (int i = 0; i < 5; i++) {
        list.push_back(i);
        list.dump();
    }
    for (int i = 0; i < 5; i++) {
        i = i * 100 - 1;
        list.push_front(i);
        i = (i + 1) / 100;
    }
    printf("Let's start\n");
    list.dump();
    int b;
    for(int i = 0; i < 5; i++) b = list.pop_back();
    printf("\n");
    list.dump();

    class List<int> shlist {};

    for (int i = 0; i < 7; i++) shlist.push_back(i);
    for (int i = 0; i < 2; i++) {
        i = i * 100 - 1;
        shlist.push_front(i);
        i = (i + 1) / 100;
    }
    shlist.dump();
    for (int i = 0; i < 5; i++) b = shlist.pop_back();
    printf("\n");
    shlist.dump();*/



    int lenght = LenghtOfFile() + 1;
    char* Text = (char*)calloc(lenght + 1, sizeof(char));
    Text[0] = '\n';
    InputText(Text, lenght);
    int sum_string = SumString(Text);
    struct LineInfo* Line = (struct LineInfo*)calloc(sum_string, sizeof(struct LineInfo));
    FillStruct(Line, Text, lenght, sum_string);

    HashTable<char*> sum{ hash_sum };
    for (size_t i = 0; i < 4000; i++) {
        if (*(Line[i].index + 1) != '\0') {
            //printf("[%s]\n", Line[i].index + 1);
            sum.push(Line[i].index + 1);
            //printf("\n");
            //sum.dump();
            //printf("\n");
        }
    }
    sum.file_dump();

    HashTable<char*> len{ hash_len };
    for (size_t i = 0; i < 4000; i++) {
        if (*(Line[i].index + 1) != '\0') {
            len.push(Line[i].index + 1);
        }
    }
    len.file_dump();

    HashTable<char*> pol{ hash_pol };
    for (size_t i = 0; i < 4000; i++) {
        if (*(Line[i].index + 1) != '\0') {
            pol.push(Line[i].index + 1);
        }
    }
    pol.file_dump();

    free(Text);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
