#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

void print_file(const string &);

int main()
{
    string fname;

    cout << "Please, input a file name to print its data formatted:" << endl;
    cout << ">";
    cin >> fname;

    print_file(fname);

    return 0;
}

void print_file(const string &fname)
{
    const auto colomn1_name = "Succeeded",
               colomn2_name = "Name",
               colomn3_name = "Surname",
               colomn4_name = "Avg mark",
               colomn5_name = "Attended";
    auto colomn1_size = strlen(colomn1_name),
         colomn2_size = strlen(colomn2_name),
         colomn3_size = strlen(colomn3_name),
         colomn4_size = strlen(colomn4_name),
         colomn5_size = strlen(colomn5_name);
    const auto separator = ',';
    const auto precision = 3;
    ifstream fin;
    vector<float> mark_vec;
    vector<int> attended_vec;
    vector<string> name_vec, surname_vec;

    fin.exceptions(ifstream::badbit | ifstream::failbit);
    try
    {
        fin.open(fname);

        // зчитуємо дані з файлу у відповідні структури даних
        while (!fin.eof())
        {
            string line, name, surname, number;

            // визначаємо ширину відповідних колонок
            getline(fin, name, separator);
            name_vec.push_back(name);
            if (name.size() > colomn2_size)
                colomn2_size = name.size();

            getline(fin, surname, separator);
            surname_vec.push_back(surname);
            if (surname.size() > colomn3_size)
                colomn3_size = surname.size();

            getline(fin, number, separator);
            if (number.find('.') + precision + 1 > colomn4_size)
                colomn4_size = number.size();
            mark_vec.push_back(atof(number.c_str()));

            getline(fin, number, '\n');
            if (number.size() > colomn5_size)
                colomn5_size = number.size();
            attended_vec.push_back(atoi(number.c_str()));
        }
    }
    catch (exception &ex)
    {
        cout << ex.what() << endl;

        exit(EXIT_FAILURE);
    }

    // виводимо заголовки відповідних колонок
    cout << setw(colomn1_size) << left << colomn1_name << " ";
    cout << setw(colomn2_size) << left << colomn2_name << " ";
    cout << setw(colomn3_size) << left << colomn3_name << " ";
    cout << setw(colomn4_size) << left << colomn4_name << " ";
    cout << setw(colomn4_size) << left << colomn5_name << endl;

    // виводимо необхідні дані у відповідних колонках з урахуванням вимог до форматування
    int colomn1_offset, colomn5_offset;
    for (auto i = 0; i != name_vec.size(); ++i)
    {
        colomn1_offset = colomn1_size / 2 + 1;
        if (mark_vec[i] > 4 && attended_vec[i] > 5)
            cout << setw(colomn1_offset) << "+";
        else
            cout << setw(colomn1_offset) << " ";
        cout << setw(colomn1_offset) << " ";

        cout << setw(colomn2_size) << left << name_vec[i] << " ";
        cout << setw(colomn3_size) << left << surname_vec[i] << " ";
        cout << setw(colomn4_size) << right << setprecision(precision) << mark_vec[i] << " ";

        colomn5_offset = colomn5_size / 2 + 1;
        cout << setw(colomn5_offset) << attended_vec[i];
        cout << setw(colomn5_offset) << " " << endl;
    }
}