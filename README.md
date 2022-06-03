# Учебная практика
Программа предназначена для анализа текста на английском языке (символы латиницы). На вход программы требуется файл с расширением .txt. 

Программа считывает текст из файла, разбивает его на слова, создает (или использует уже созданные) файлы для вывода результата и анализа, сортирует слова в массиве по количеству символов в порядке убывания и выводит в выходной файл. Также в файл анализа выводится небольшой анализ текста: исходный текст, параметры сортировки (латиница, по кол-ву символов, по убыванию, учитывать числа, сортировка слиянием), количество слов, время сортировки, статистика (количество слов каждой длины).

Название исходного файла вводится с консоли, остальные файлы создаются в процессе работы программы. Погрешность разбивки слов +- 1 слово, при кол-ве слов 2000.

Для разбивки исходного текста на массив слов используется функция:

vector<string> breakdown_into_words(string name, string& original_string) 
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

Для сортировки массива слов используется функция сортировки слиянием:

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

Скриношот файла с исходными данными:
![image](https://user-images.githubusercontent.com/106019319/171847328-29961cf8-58da-4b6a-a088-259686c76918.png)

Скриношот файла с отсортированными словами:

![image](https://user-images.githubusercontent.com/106019319/171847736-215e020f-0ec9-4919-8124-c7b4cd5add46.png)

Скриношот файла с анализом текста:
                                   
![image](https://user-images.githubusercontent.com/106019319/171848276-dd4801ce-4d54-412c-abfe-3694df271a98.png)
                                   
Скриношот консоли:
                                   
![image](https://user-images.githubusercontent.com/106019319/171849290-26ded746-88a6-4a39-8299-3d44900454bd.png)
![image](https://user-images.githubusercontent.com/106019319/171849383-be78dccc-45b8-4a03-84cd-d8001183cdf0.png)

                                   
                  
                                   
