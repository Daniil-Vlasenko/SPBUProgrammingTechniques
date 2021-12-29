#include <iostream>
#include <variant>
#include <unistd.h>
#include <fstream>
using namespace std;


int MAXAGENTS = 100;
struct Agent {
    variant<string, int> name;
    string rank;
};

// Чтение структур из файла
int fromFile(Agent* mas, string inputName) {
    ifstream file(inputName);
    string line;
    int countOfAgents{};
    while(getline(file, line)) {
        // Читаем сроку или номер
        if(line[0] >= 48 && line[0] <= 57)
            mas[countOfAgents].name = stoi(line.substr(0, line.find(' ')));
        else
            mas[countOfAgents].name = line.substr(0, line.find(' '));

        // Читаем звание
        mas[countOfAgents].rank = line.substr(line.find(' ') + 1);

        ++countOfAgents;
    }
    file.close();
    return countOfAgents;
}

// Сравнение по фамилии/номеру (символы больше цифр)
int compare(Agent const &a1, Agent const &a2) {
    if(holds_alternative<string>(a1.name) && holds_alternative<int>(a1.name)) {return 1;}
    if(holds_alternative<int>(a1.name) && holds_alternative<string>(a1.name)) {return 0;}
    if(holds_alternative<int>(a1.name) && holds_alternative<int>(a1.name)) {return a1.name > a2.name;}
    else {return a1.name < a2.name;}
}

// Сортировка указателей по фамилии/номеру (сначала идут те, у кого фамилия)
void sort(Agent ** const ptr_mas, int countOfAgents, int(*compare)(Agent const &a1, Agent const &a2)) {
    for(int i = 0; i < countOfAgents - 1; ++i)
        for(int j = i + 1; j < countOfAgents; ++j){
            if(!compare(*ptr_mas[i], *ptr_mas[j])) {
                Agent *tmp = ptr_mas[j];
                ptr_mas[j] = ptr_mas[i];
                ptr_mas[i] = tmp;
            }
        }
}

// Вывод на экран списка структур
void print(Agent ** const ptr_mas, int countOfAgents) {
    for(int i = 0; i < countOfAgents; ++i) {
        if (holds_alternative<int>(ptr_mas[i]->name))
            cout << get<int>(ptr_mas[i]->name) << " " << ptr_mas[i]->rank << endl;
        if (holds_alternative<string>(ptr_mas[i]->name))
            cout << get<string>(ptr_mas[i]->name) << " " << ptr_mas[i]->rank << endl;
    }
}

// Поиск по фамилии
Agent* search(string name, Agent ** const ptr_mas, int countOfAgents) {
    for(int i = 0; i < countOfAgents; ++i)
        if(holds_alternative<string>(ptr_mas[i]->name)) {
            if (get<string>(ptr_mas[i]->name) == name)
                return ptr_mas[i];
        }
    return nullptr;
}

// Вывод в файл найденного агента
void toFile(Agent *a, string outputName) {
    // Проверка на существование файла
    ifstream input(outputName);
    while(input){
        input.close();
        cout << "File " << outputName << " exists. " << "Do you want to overwrite the file? (y/n): ";
        char c; cin >> c;
        if(c == 'y') {break;}
        std::cout << "Enter name of the new file:";
        std::cin >> outputName;
        input.open(outputName);
    }
    ofstream output(outputName);
    if(a)
        output << get<string>(a->name) << " " << a->rank << '\n';
    else
        output << "Agent wasn't found.\n";
    output.close();
}


int main() {
    chdir("../");   // Адрес, где лежит файл input.txt

    // Создаем файл структур
    string inputName("input.txt"), outputName("output.txt"),
        infile("Ivanov corporal\nUlans sergeant\n645 corporal\n32 officer\nAlneck officer\n");
    ofstream input(inputName);
    input << infile;
    input.close();

    // Тестирование
    Agent mas[MAXAGENTS];
    Agent* ptr_mas[MAXAGENTS];
    for (int i = 0; i < MAXAGENTS; ++i) {
        ptr_mas[i] = mas + i;
    }
    int countOfAgents = fromFile(mas, inputName);
    sort(ptr_mas, countOfAgents, compare);
    print(ptr_mas, countOfAgents);
    Agent* a1 = search("Ivanov", ptr_mas, countOfAgents);
    Agent* a2 = search("Petrov", ptr_mas, countOfAgents);
//    toFile(a1, outputName);
    toFile(a2, outputName);


    return 0;
}
