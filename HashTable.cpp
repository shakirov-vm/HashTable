// HashTable.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>

#define LIST_H
#ifdef LIST_H
#include "List.h"
#endif 

#include "HashTable.h"
#include "HashFunctions.h"
#include "Text.h"

int main()
{
    /*std::cout << "Hello World!\n";

    class List<int> list {};
    int a = 0;
    for(int i = 0; i < 5; i++) list.push_back(i);
    for(int i = 0; i < 5; i++) list.push_front(i * 100 - 1);
    printf("Let's start\n");
    list.dump();

    for(int i = 0; i < 5; i++) a = list.pop_back();*/
    int lenght = LenghtOfFile() + 1;
    char* Text = (char*)calloc(lenght + 1, sizeof(char));
    Text[0] = '\n';
    InputText(Text, lenght);
    int sum_string = SumString(Text);
    struct LineInfo* Line = (struct LineInfo*)calloc(sum_string, sizeof(struct LineInfo));
    FillStruct(Line, Text, lenght, sum_string);

    HashTable<char*> sum{};
    for (size_t i = 0; i < 1000; i++) {
        sum.push(Line[i].index + 1, hash_sum);
        printf("[%s]\n", Line[i].index + 1);
    }

    sum.table[0].dump();

    sum.dump();

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
