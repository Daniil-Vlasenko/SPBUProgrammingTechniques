#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>

using namespace std;


const int NMARK = 5;
const int NSIMB = 10;
const int NSTUDENT = 100;

struct STUDENT {
    char name[NSIMB]{};
    int mark[NMARK]{};
    float avr{};
};

// Подсчет средней оценки для студентов
void comput_var(STUDENT *l, int n) {
    for(int j = 0; j < n; ++j){
        for(int i : l[j].mark)
            l[j].avr += i;
        l[j].avr /= 5;
    }
}

// Ввод студентов с консоли
int input_all(STUDENT* l) {
    int countOfStudents;

    cout << "Enter the number of students: ";
    cin >> countOfStudents;
    for(int i = 0; i < countOfStudents; ++i) {
        cout << "Enter the student's name (10 characters): ";
        cin >> l[i].name;
        cout << "Enter the student's marks (5 marks): ";
        for(int & j : l[i].mark)
            cin >> j;
    }

    comput_var(l, countOfStudents);
    return countOfStudents;
}

// Ввод студентов из файла
void from_file(char const *fname, STUDENT* l, int &n) {
    ifstream input(fname, ios_base::in | ios_base::binary);

    // Узнаем размер файла
    input.seekg(0, ios::end);
    long sizef = input.tellg();
    input.seekg(0, ios::beg);
    n = sizef / sizeof(STUDENT);

    // Чтение из бинарного файла в массив
    input.read((char*)l, sizef);

    comput_var(l, n);
    input.close();
}


// Сравнение студентов по имени (-1 - <, 0 - =, 1 - >)
int  cmp_name1(STUDENT const &s1, STUDENT const &s2) {
    return strcmp(s1.name, s2.name);
}

// Сравнение студентов по имени (1 - < , 0 - >=)
int  cmp_name2(STUDENT const &s1, STUDENT const &s2) {
    return strcmp(s1.name, s2.name) < 0 ? 1 : 0;
}

// Сортировка n студентов из массива в порядке убывания по значениям
void sort(STUDENT *l,  int n, int (*compare)(STUDENT const&, STUDENT const&)) {
    std::sort(l, l + n, *compare);
}

// Вывод n студентов в файл
void to_file(char const *fname, STUDENT const *l, int n) {
    ofstream out(fname, ios_base::out | ios_base::binary);
    out.write((char*)l, n * sizeof(STUDENT));
    out.close();
}

// Бинарный поиск студента
STUDENT* search(STUDENT const &ls, STUDENT *l, int n, int (*compare)(STUDENT const&, STUDENT const&)) {
    int left{}, right = n - 1, middle, tmp1, tmp2;
    if((tmp1 = compare(ls, l[left])) < 0 || (tmp2 = compare(ls, l[right])) > 0) {return nullptr;} // Студент вне массива
    if(!tmp1) {return l;} // Студент - первый элемент массива
    if(!tmp2) {return l + right;} // Студент - последний элемент массива

    // Поиск студента
    while(true){
        middle = (right + left) / 2;
        if(!(tmp1 = compare(ls, l[middle])))
            return l + middle;
        if(left >= right - 1)
            return nullptr;
        if(tmp1 > 0)
            left = middle ;
        else
            right = middle;
    }
}

// Вывод структуры в консоль
void print_one(STUDENT const &ls) {
    cout << "name: " << ls.name << " marks: ";
    for (int i : ls.mark)
        cout << i << " ";
    cout << "avr: " << ls.avr << endl;
}

// Вывод n студентов
void print_all(STUDENT const *l, int n) {
    for(int i = 0; i < n; ++i)
        print_one(l[i]);
}


int main() {
    chdir("../");   // Адрес, где лежит файл input.txt

    // Создание бинарного файла
    char inputFile[] = "inputFile.b", outputFile[] = "outputFile.b";
    ofstream input(inputFile, ofstream::binary);
//    STUDENT l[3];
    STUDENT l[4];
    strcpy(l[0].name, "Aa");
    strcpy(l[1].name, "Cc");
    strcpy(l[2].name, "Bb");
    strcpy(l[3].name, "Dd");
    l[0].mark[0] = 3; l[0].mark[1] = 3; l[0].mark[2] = 4; l[0].mark[3] = 5; l[0].mark[4] = 5;
    l[1].mark[0] = 4; l[1].mark[1] = 5; l[1].mark[2] = 5; l[1].mark[3] = 5; l[1].mark[4] = 5;
    l[2].mark[0] = 3; l[2].mark[1] = 3; l[2].mark[2] = 2; l[2].mark[3] = 2; l[2].mark[4] = 2;
    l[3].mark[0] = 2; l[3].mark[1] = 3; l[3].mark[2] = 3; l[3].mark[3] = 2; l[3].mark[4] = 2;
//    input.write((char*)l, sizeof(STUDENT) * 3);
    input.write((char*)l, sizeof(STUDENT) * 4);
    input.close();

    // Тестирование
//    ifstream input(inputFile);
//    if (!input) {
//        cout << "Error: there is no file to read." << endl;
//        return -1;
//    }
//    input.close();

    STUDENT lnew[100];
    int n{};
    from_file(inputFile, lnew, n);
    sort(lnew, n, cmp_name2);
    ofstream output(outputFile);
    output.write((char*)lnew, n * sizeof(STUDENT));
    output.close();

    STUDENT st1; strcpy(st1.name, "Qq");
    STUDENT *ls = search(st1, lnew, n, cmp_name1);
    if(ls) print_one(*ls);
    else cout << "Student "<< st1.name <<" not found" << endl;
    STUDENT st2; strcpy(st2.name, "Bq");
    ls = search(st2, lnew, n, cmp_name1);
    if(ls) print_one(*ls);
    else cout << "Student "<< st2.name <<" not found" << endl;
    ls = search(lnew[3], lnew, n, cmp_name1);
    print_one(*ls);


    print_all(lnew, n);

    return 0;
}