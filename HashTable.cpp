// HashTable.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <locale.h>

#define LIST_H
#ifdef LIST_H
#include "ListObj.h"
#endif 

#include "Table.h"

#include "HashTable.h"
#include "HashFunctions.h"
#include "Text.h"

int main()
{
    setlocale(LC_ALL, "");

    size_t lenght = LenghtOfFile();
    char* Text = (char*)calloc(lenght + 1, sizeof(char));
    InputText(Text, lenght);

    size_t sum_string = SumString(Text);
    sum_string /= 2;

    printf("sum string - %d\n", sum_string);
    char** eng = (char**)calloc(sum_string, sizeof(char*));
    char** rus = (char**)calloc(sum_string, sizeof(char*));

    sum_string++; // Иначе последнее не выведется
    fill_struct(Text, sum_string, eng, rus);

    /*for (size_t i = 0; i < sum_string; i++) {
        printf("[%s] - [%s]\n", eng[i], rus[i]);
    }*/

    HashTable<char*, char* > sum{ hash_sum };
    for (size_t i = 0; i < sum_string; i++) {
        sum.push(eng[i], rus[i]);
    }
    sum.file_dump();

    HashTable<char*, char* > len{ hash_len };
    for (size_t i = 0; i < sum_string; i++) {
        len.push(eng[i], rus[i]);
    }
    len.file_dump();

    HashTable<char*, char* > pol{ hash_pol };
    for (size_t i = 0; i < sum_string; i++) {
        pol.push(eng[i], rus[i]);
    }
    pol.file_dump();

    //for (size_t i = 0; i < sum_string; i++) if ((i % 5) == 0) printf("\n%d: %s - %s", i, eng[i], pol.find_value(eng[i]));

    printf("\nNow delete\n");
    for (size_t i = 0; i < sum_string; i++) if ((i % 3) == 0) pol.delete_value(eng[i]);

    len.list_size();

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
