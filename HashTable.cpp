﻿// HashTable.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>

#define LIST_H
#ifdef LIST_H
#include "List.h"
#endif 

#include "HashTable.h"
#include "HashFunctions.h"

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
    HashTable<char*> test{};
    char* str_1 = (char*)calloc(10, sizeof(char));
    sprintf(str_1, "blablabla\0");
    test.push(str_1);
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