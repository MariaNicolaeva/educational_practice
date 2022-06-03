#include <iostream>
#include <Windows.h> 
#include <vector> 
#include <fstream>
#include <set>

using namespace std;

//прототипы
vector<string> breakdown_into_words(string name, string& original_string);
void merge_sort(vector <string>& array_of_words, int left, int right);
unsigned int sorting_and_sorttime(vector<string>& array_of_words);
vector <int> counting_words(vector<string> array_of_words, string name, set <int>& sizes_of_words);


int main()
{
    setlocale(0, ""); // поддержка кириллицы в консоли (вывод)
    SetConsoleCP(1251); // поддержка кириллицы в консоли (ввод)
    SetConsoleOutputCP(1251); // поддержка кириллицы в консоли (ввод)

    cout << "Введите номер файла: ";

    string file_name, original_string; //переменные имени файла и исходной строки
    cin >> file_name;

    //разбивка исходного текста на массив слов
    vector <string> array_of_words = breakdown_into_words(file_name, original_string);

    //сортировка слов по длине и вычисление времени сортировки
    unsigned int time = sorting_and_sorttime(array_of_words);

    set <int> sizes_of_words;
    //подсчет количества слов каждой длины
    vector<int> number_of_words = counting_words(array_of_words, file_name, sizes_of_words);

    return 0;
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

unsigned int sorting_and_sorttime(vector<string>& array_of_words) //функция вычисления времени сортировки слов по длине
{
    int start_time = clock();
    merge_sort(array_of_words, 0, array_of_words.size() - 1);
    int end_time = clock();

    return end_time - start_time;
}

void merge_sort(vector <string>& array_of_words, int left, int right) //функция сортировки слов по длине слиянием 
{
    if (left == right)
        return; // границы сомкнулись

    int mid = (left + right) / 2; // определяем середину последовательности
    //рекурсивно вызываем функцию сортировки для каждой половины

    merge_sort(array_of_words, left, mid);
    merge_sort(array_of_words, mid + 1, right);

    int i = left;  // начало первого пути
    int j = mid + 1; // начало второго пути

    vector <string> tmp(array_of_words.size()); // дополнительный массив

    for (int step = 0; step < right - left + 1; step++) // для всех элементов дополнительного массива
    {
        // записываем в формируемую последовательность меньший из элементов двух путей
        // или остаток первого пути если j > right
        if ((j > right) || ((i <= mid) && (array_of_words[i].size() > array_of_words[j].size())))
        {
            tmp[step] = array_of_words[i];
            i++;
        }
        else
        {
            tmp[step] = array_of_words[j];
            j++;
        }
    }
    // переписываем сформированную последовательность в исходный массив

    for (int step = 0; step < right - left + 1; step++)
        array_of_words[left + step] = tmp[step];

}

vector <int> counting_words(vector<string> array_of_words, string name, set <int>& sizes_of_words) //функция подсчета количества слов на каждую букву
{
    set <int> ::iterator it; //итератор для работы с множеством 
    for (int i = 0; i < array_of_words.size(); i++)
    {
        sizes_of_words.insert(array_of_words[i].size()); //добавляем длину слова в множество
    }
    vector <int> number_of_words(sizes_of_words.size()); //создаем массив количества длин

    for (int i = 0; i < array_of_words.size(); i++)
    {
        int j = 0;
        for (it = sizes_of_words.begin(); it != sizes_of_words.end(); it++) //идем по всему множеству
        {
            if (array_of_words[i].size() == *it) //если элемент множества размера слов равен длине слова 
            {
                number_of_words[j]++; //увеличиваем в массиве элемент на 1
                break;
            }
            j++;
        }
    }

    return number_of_words;
}
