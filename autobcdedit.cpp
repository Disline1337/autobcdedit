#include <iostream>
#include <Windows.h>

int main() {
    // Запуск команды bcdedit для получения информации о загрузочных параметрах
    system("bcdedit /enum");

    // Парсинг вывода команды bcdedit
    FILE* pipe = _popen("bcdedit /enum", "r");
    if (pipe) {
        const int maxBufferSize = 128;
        char buffer[maxBufferSize];
        system("cls");
        while (!feof(pipe)) {
            if (fgets(buffer, maxBufferSize, pipe) != NULL) {
                std::string line(buffer);

                // Проверка наличия строки "testsigining" в выводе команды
                if (line.find("testsigning") != std::string::npos) {
                    // Извлечение состояния testsigining
                    std::string state = line.substr(24, 3);
                    std::cout << "testsigning:" << state << " " << strcmp(state.c_str(), "Yes") << std::endl;
                    if (strcmp(state.c_str(), "Yes") == 0)
                    {
                        system("bcdedit /set testsigning off");
                        printf("Overrided to Disabled\n");
                    }
                    else
                    {
                        system("bcdedit /set testsigning on");
                        printf("Overrided to Enabled\n");
                    }
                }

                // Проверка наличия строки "nointegritychecks" в выводе команды
                if (line.find("nointegritychecks") != std::string::npos) {
                    // Извлечение состояния nointegritychecks
                    std::string state = line.substr(24, 3);
                    std::cout << "nointegritychecks:" << state << " " << strcmp(state.c_str(), "Yes") << std::endl;
                    if (strcmp(state.c_str(), "Yes") == 0)
                    {
                        system("bcdedit /set nointegritychecks off");
                        printf("Overrided to Disabled\n");
                    }
                    else
                    {
                        system("bcdedit /set nointegritychecks on");
                        printf("Overrided to Enabled\n");
                    }
                }
            }
        }
        _pclose(pipe);
    }
    Sleep(5000);
    return 0;
}
