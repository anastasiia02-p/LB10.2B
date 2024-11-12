#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <cmath>

using namespace std;


enum Speciality { ITIS, ME, KN, FI, TN };
string speciality_str[] = { "����������� ",
                            "���������� �� ��������", "����'����� �����",
                            "Գ���� �� �����������", "������� ��������" };

struct Students
{
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    union
    {
        int grade_nm;
        int grade_program;
        int grade_ped;
    };
};

#pragma pack(pop)

void Create(Students* S, const int N);
void Print(Students* S, const int N);
void p_sort(Students* S, int N);
int* i_sort(Students* S, const int N);
void i_print(Students* S, int* I, const int N);
bool b_search(Students* S, const int N, const string surname, const int course, const int grade_physics);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "������ ������� ��������: "; cin >> N;

    Students* S = new Students[N];
    int MenuItem;

    while (true)
    {
        cout << endl << "������ ��:" << endl;
        cout << "1 - ������ ���������� ��� ��������" << endl;
        cout << "2 - ������� ���������� ��� ��������" << endl;
        cout << "3 - Գ����� ������������ ����������" << endl;
        cout << "4 - �������� ������������ ����������" << endl;
        cout << "5 - �������� ����� ��������" << endl;
        cout << "0 - ��������� ������ ��������" << endl;
        cout << "������: "; cin >> MenuItem; cout << endl;

        switch (MenuItem)
        {
        case 1:
            Create(S, N);
            break;
        case 2:
            Print(S, N);
            break;
        case 3:
            p_sort(S, N);
            Print(S, N);
            break;
        case 4:
            i_print(S, i_sort(S, N), N);
            break;
        case 5:
        {
            string f_surname;
            int f_course, f_grade_physics;

            cout << "������ ������ ������: " << endl;
            cout << "�������: ";
            cin.ignore();
            getline(cin, f_surname);

            cout << "����: ";
            cin >> f_course;

            cout << "������ � ������: ";
            cin >> f_grade_physics;

            if (b_search(S, N, f_surname, f_course, f_grade_physics))
            {
                cout << "������� ���������" << endl;
            }
            else
            {
                cout << "������� �� ���������" << endl;
            }
            break;
        }
        case 0:
            delete[] S;
            return 0;
        }
    }
}

void Create(Students* S, const int N)
{
    for (int i = 0; i < N; i++)
    {
        int speciality;
        cout << "����� ��������: " << i + 1 << endl;
        cin.ignore();
        cout << "�������: "; getline(cin, S[i].surname);

        do
        {
            cout << "����: "; cin >> S[i].course;
        } while (S[i].course < 1 || S[i].course > 6);

        do
        {
            cout << "������������(0 - �����������, 1 - ���������� �� ��������, 2 - ����'����� �����,";
            cout << "3 - Գ���� �� �����������, 4 - ������� ��������): ";
            cin >> speciality;
            S[i].speciality = (Speciality)speciality;
        } while (S[i].speciality < 0 || S[i].speciality > 4);

        do
        {
            cout << "������ � ������: "; cin >> S[i].grade_physics;
        } while (S[i].grade_physics < 1 || S[i].grade_physics > 5);

        do
        {
            cout << "������ � ����������: "; cin >> S[i].grade_math;
        } while (S[i].grade_math < 1 || S[i].grade_math > 5);

        switch (S[i].speciality)
        {
        case KN:
            do
            {
                cout << "������ � �������������: "; cin >> S[i].grade_program;
            } while (S[i].grade_program < 1 || S[i].grade_program > 5);
            break;
        case ITIS:
            do
            {
                cout << "������ � ��������� ������: "; cin >> S[i].grade_nm;
            } while (S[i].grade_nm < 1 || S[i].grade_nm > 5);
            break;
        default:
            do
            {
                cout << "������ � ���������: "; cin >> S[i].grade_ped;
            } while (S[i].grade_ped < 1 || S[i].grade_ped > 5);
        }
        cout << endl;
    }
}

void Print(Students* S, const int N)
{
    cout << "======================================================================================================================================" << endl;
    cout << "|  �  |   �������   | ���� |      ������������      |  Գ����  |  ����������  |  �������������  |  ������� ������  |  ���������  |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << S[i].surname
            << "| " << setw(4) << right << S[i].course << " "
            << "| " << setw(24) << left << speciality_str[S[i].speciality]
            << "|  " << setw(7) << right << S[i].grade_physics << " "
            << "|  " << setw(11) << right << S[i].grade_math << " ";

        switch (S[i].speciality)
        {
        case KN:
            cout << "|" << setw(9) << S[i].grade_program << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        case ITIS:
            cout << "|" << setw(9) << "-" << setw(9);
            cout << "|" << setw(9) << S[i].grade_nm << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        default:
            cout << "|" << setw(9) << "-" << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << S[i].grade_ped << setw(7) << "|";
            break;
        }

        cout << endl << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

void p_sort(Students* S, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (S[i].grade_physics < S[j].grade_physics ||
                (S[i].grade_physics == S[j].grade_physics && S[i].course > S[j].course) ||
                (S[i].grade_physics == S[j].grade_physics && S[i].course == S[j].course && S[i].surname < S[j].surname))
            {
                swap(S[i], S[j]);
            }
        }
    }
}

int* i_sort(Students* S, const int N)
{
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;

    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (S[I[i]].grade_physics < S[I[j]].grade_physics ||
                (S[I[i]].grade_physics == S[I[j]].grade_physics && S[I[i]].course > S[I[j]].course) ||
                (S[I[i]].grade_physics == S[I[j]].grade_physics && S[I[i]].course == S[I[j]].course && S[I[i]].surname < S[I[j]].surname))
            {
                swap(I[i], I[j]);
            }
        }
    }
    return I;
}

void i_print(Students* S, int* I, const int N)
{
    cout << "======================================================================================================================================" << endl;
    cout << "|  �  |   �������   | ���� |      ������������      |  Գ����  |  ����������  |  �������������  |  ������� ������  |  ���������  |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << S[I[i]].surname
            << "| " << setw(4) << right << S[I[i]].course << " "
            << "| " << setw(24) << left << speciality_str[S[I[i]].speciality]
            << "|  " << setw(7) << right << S[I[i]].grade_physics << " "
            << "|  " << setw(11) << right << S[I[i]].grade_math << " ";

        switch (S[I[i]].speciality)
        {
        case KN:
            cout << "|" << setw(9) << S[I[i]].grade_program << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        case ITIS:
            cout << "|" << setw(9) << "-" << setw(9);
            cout << "|" << setw(9) << S[I[i]].grade_nm << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        default:
            cout << "|" << setw(9) << "-" << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << S[I[i]].grade_ped << setw(7) << "|";
            break;
        }

        cout << endl << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

bool b_search(Students* S, const int N, const string surname, const int course, const int grade_physics)
{
    int L = 0, R = N - 1, m;
    while (L <= R)
    {
        m = (L + R) / 2;

        if (S[m].grade_physics == grade_physics && S[m].course == course && S[m].surname == surname)
        {
            return true;
        }
        else if (S[m].grade_physics < grade_physics ||
            (S[m].grade_physics == grade_physics && S[m].course < course) ||
            (S[m].grade_physics == grade_physics && S[m].course == course && S[m].surname < surname))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    }
    return false;
}
