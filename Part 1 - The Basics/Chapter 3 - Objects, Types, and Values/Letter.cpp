// Letter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main()
{
    string first_name;
    string friend_name;
    char friend_sex{};
    int age{};

    cout << "Inserisci il nome della persona a cui vuoi scrivere\n";
    cin >> first_name;

    cout << "Inserisci il nome di un suo amico\n";
    cin >> friend_name;

    cout << "Inserisci il sesso dell'amico m/f\n";
    cin >>friend_sex;

    cout << "Inserisci l'eta' di " << first_name << '\n';
    cin >> age;

    if (age == 0 || age < 0 || age>110)
    {
        cout << "Starai scherzando!\n";
    }

    cout << "\nCiao " << first_name << ", come stai? Io bene. Mi manchi.\n"
        << "Se vedi " << friend_name;

    if (friend_sex == 'm')
    {
        cout << " chiedigli ";
    }
    else
    {
        cout << " chiedile ";
    }
    cout << "di chiamarmi al telefono. Ho sentito che hai organizzato una festa di compleanno,\n"
        << "adesso hai " << age << " anni";

    if (age <= 12)
    {
        cout << ", il prossimo anno avrai " << age + 1 << " anni.\n";
    }
    else if (age == 17)
    {
        cout << ", il prossimo anno potrai votare.\n";
    }
    else if (age >= 70)
    {
        cout << ", goditi la pensione.\n";
    }
    else
    {
        cout << ".\n";
    }

    cout << "\nCordiali saluti,\n" << "\nMarco Fadda\n";

    system("PAUSE");
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
