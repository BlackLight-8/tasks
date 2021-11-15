
#include <string>
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <Windows.h>

using namespace boost::filesystem;

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    std::string aPath1, aPath2; //храним пути к файлу
    size_t aSize1, aSize2; //храним размер файлов
    char buffer1, buffer2; //буферы для проверки файлов
    bool sameFiles = false;
    std::cout << "Данная программа предназначена для проверки файлов двух выбранных папок на дубликаты.\n\n";
    if (argc == 1)
    {
        std::cout << "Введите полный путь к первой папке с файлами:\n";
        getline(std::cin, aPath1);
        //cin >> aPath1;
        std::cout << "Введите полный путь ко второй папке с файлами:\n";
        getline(std::cin, aPath2);
        //cin >> aPath2;
    }
    else if (argc == 3)
    {
        aPath1 = argv[1];
        aPath2 = argv[2];
        std::cout << "Заданы пути:\n" << aPath1 << "\n" << aPath2 << "\n\n";
    }
    else
    {
        std::cout << "Передайте два полных пути к папкам для проверки на дубликаты файлов, если в пути содержаться пробелы - необходимо взять его в двойные кавычки.";
        for (int i = 0; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
        return 1;
    }
    path p1(aPath1);
    path p2(aPath2);
    
    
    try
    {
        for (auto i = directory_iterator(p1); i != directory_iterator(); i++) //перебираем содержимое первой папки
        {
            if (!is_directory(i->path())) //проверка директория или файл (директории отсекаются)
            {
                aPath1 = i->path().string();
                aSize1 = file_size(i->path());
                for (auto j = directory_iterator(p2); j != directory_iterator(); j++) //перебираем содержимое второй папки
                {
                    if (!is_directory(j->path())) //проверка директория или файл (директории отсекаются)
                    {
                        aPath2 = j->path().string();
                        aSize2 = file_size(j->path());
                        if (aSize1 == aSize2) //проверяем размер файла для ускорения идентификации дубликатов (если размер разный файлы точно разные)
                        {
                            std::ifstream fin1(aPath1, std::ios_base::binary);
                            std::ifstream fin2(aPath2, std::ios_base::binary);
                            if (!fin1.is_open()) //проверяем и выводим ошибку если файл из ПЕРВОЙ папки не открылся
                            {
                                std::cout << "Файл " << i->path().filename().string() << " не может быть открыт!\n";
                            }
                            else //файл из первой папки открылся успешно
                            {
                                if (!fin2.is_open()) //проверяем и выводим ошибку если файл из ВТОРОЙ папки не открылся
                                {
                                    std::cout << "Файл " << j->path().filename().string() << " не может быть открыт!\n";
                                }
                                else //файл из второй папки открылся успешно
                                {
                                    sameFiles = true;
                                    while (!fin1.eof() && sameFiles) //проверяем весь файл пока не дойдем до конца
                                    {
                                        fin1 >> buffer1;
                                        fin2 >> buffer2;
                                        if (buffer1 != buffer2) //если нашли отличие, то выходим из цикла, файлы - разные
                                        {
                                            sameFiles = false;
                                        }
                                    }
                                    fin1.close();
                                    fin2.close();
                                    if (sameFiles && fin2.eof()) //если попали сюда, значит файлы одинаковые и во втором файле тоже дошли до конца
                                    {
                                        std::cout << "Файл " << j->path() << " является копией файла " << i->path() << "!\n";
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    catch (const filesystem_error& ex)
    {
        std::cout << ex.what() << "\n";
    }
    system("pause");
    return 0;
}