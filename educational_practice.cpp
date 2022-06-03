#include <iostream>
#include <Windows.h> 
#include <vector> 
#include <fstream>
#include <set>

using namespace std;

//прототипы
vector<string> breakdown_into_words(string name, string& original_string);

void main()
{
    setlocale(0, ""); // поддержка кириллицы в консоли (вывод)
    SetConsoleCP(1251); // поддержка кириллицы в консоли (ввод)
    SetConsoleOutputCP(1251); // поддержка кириллицы в консоли (ввод)

    cout << "Введите номер файла: ";

    string file_name, original_string; //переменные имени файла и исходной строки
    cin >> file_name;

    //разбивка исходного текста на массив слов
    vector <string> array_of_words = breakdown_into_words(file_name, original_string);

}
vector<string> breakdown_into_words(string name, string& original_string) //функция разбивки исходного текста на массив слов
{
    fstream file_original; //создаем переменную файла

    string original_str = "original_" + name + ".txt"; //создаем строку имени файла
    file_original.open(original_str, ios::in); // открываем файл

    vector<string> array_of_words = {};
    string s = "";

    char ch;

    if (file_original.is_open()) //если файл открылся 
    {
        while (file_original.get(ch))
        {
            original_string += ch;
        }
        file_original.close(); // Закрытие файла
    }
    else
    {
        cout << "Исходный файл не открылся";
        exit(0);
    }

    original_string = '"' + original_string + '"'; //чтобы не было переполнения строки

    for (int i = 0; i < original_string.length() - 1; i++)
    {
        if (original_string[i] >= 'A' && original_string[i] <= 'Z' || original_string[i] >= 'a' && original_string[i] <= 'z') //если символ строки буква из латиницы

        {
            s += original_string[i]; //собираем слово 
            if ((original_string[i + 1] < 'A' || (original_string[i + 1] > 'Z' && original_string[i + 1] < 'a') || original_string[i + 1] > 'z') && original_string[i + 1] != '-') //разделитель - все кроме букв
            {
                array_of_words.push_back(s); //добавляем в массив строку
                s = ""; //обнуляем строку
            }
        }
        else
        {
            if (original_string[i] >= '0' && original_string[i] <= '9' || original_string[i] == ',' && original_string[i + 1] >= '0' && original_string[i + 1] <= '9') //если символ строки цифра или запятая 
            {
                s += original_string[i]; //собираем слово 
                if ((original_string[i + 1] < '0' || original_string[i + 1] > '9') && original_string[i + 1] != ',') //ищем конец числа
                {
                    array_of_words.push_back(s); //добавляем в массив строку (число)
                    s = ""; //обнуляем строку
                }
            }
            else
            {
                if (original_string[i] == '-' && ((original_string[i + 1] >= '0' && original_string[i + 1] <= '9') || (original_string[i + 1] >= 'A' && original_string[i + 1] <= 'z' && s != ""))) //если символ строки минус и следующий символ цифра
                {
                    s += original_string[i]; //собираем слово 
                }
            }
        }
    }
    return array_of_words;
}
