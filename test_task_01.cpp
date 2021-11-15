
#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <Windows.h>
#include "myFile.h"


using namespace boost::filesystem;

bool checkDuplicates(string path1, string path2)
{
    char buffer1, buffer2;
    bool sameFiles;
    
    std::ifstream fin1(path1, std::ios_base::binary);
    std::ifstream fin2(path2, std::ios_base::binary);
    if (!fin1.is_open()) //проверяем и выводим ошибку если файл из ПЕРВОЙ папки не открылся
    {
        std::cout << "Файл " << path1 << " не может быть открыт!\n";
    }
    else //файл из первой папки открылся успешно
    {
        if (!fin2.is_open()) //проверяем и выводим ошибку если файл из ВТОРОЙ папки не открылся
        {
            std::cout << "Файл " << path2 << " не может быть открыт!\n";
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
            if (sameFiles) //если попали сюда, значит файлы одинаковые
            {
                return sameFiles;
            }
        }
    }
    fin1.close();
    fin2.close();

    return false;
}


int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    std::string aPath1, aPath2; //храним пути к файлу
    size_t aSize1, aSize2; //храним размер файлов

    std::list<myFile> files;

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
                files.push_back(myFile(aSize1, aPath1));
            }
        }
        for (auto i = directory_iterator(p2); i != directory_iterator(); i++) //перебираем содержимое первой папки
        {
            if (!is_directory(i->path())) //проверка директория или файл (директории отсекаются)
            {
                aPath1 = i->path().string();
                aSize1 = file_size(i->path());
                files.push_back(myFile(aSize1, aPath1));
            }
        }
    }
    catch (const filesystem_error& ex)
    {
        std::cout << ex.what() << "\n";
        return 1;
    }
    for (auto it = files.begin(); it != files.end(); it++)
    {
        if (!it->isDuplicate())
        {
            for (auto it2 = std::next(it); it2 != files.end(); it2++)
            {
                if (!it2->isDuplicate())
                {
                    if (it->getSize() == it2->getSize())
                    {
                        if (checkDuplicates(it->getPath(),it2->getPath()))
                        {
                            it->isDuplicate(true);
                            it2->isDuplicate(true);
                            it->setDupPath(it2->getPath());
                            it2->setDupPath(it->getPath());
                        }
                    }
                }
            }
        }
    }
    for (auto it = files.begin(); it != files.end(); it++)
    {
        if (it->isDuplicate())
        {
            std::cout << it->getPath() << " IS COPY OF " << it->getDupPath() << "\n";
        }
    }
    system("pause");
    return 0;
}