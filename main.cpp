#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#include <conio.h>

void sleep(unsigned int seconds)
{
    Sleep(seconds);
}

void clear() 
{
    system("cls");
}

#else
#include <unistd.h>
#include <termios.h>

char getch(void) // copied from stack overflow
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

void clear() 
{
    system("clear");
}
#endif

using namespace std;

class Shopping 
{
private:
    int pCode;
    float price;
    float discount;
    string pName;

public:
    Shopping() 
    {
        clear();
    }
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void Shopping::menu()
{
    menu:
    clear();
    int choice;
    string email;
    char password[31];

    cout << "\t\t\t\t____________________________________________________________\n";
    cout << "\t\t\t\t                                                            \n";
    cout << "\t\t\t\t                    Supermarket main menu                   \n";
    cout << "\t\t\t\t                                                            \n";
    cout << "\t\t\t\t____________________________________________________________\n";
    cout << "\t\t\t\t                                                            \n";
    cout << "\t\t\t\t\t[  1) Administrator |\n";
    cout << "\t\t\t\t\t]                   |\n";
    cout << "\t\t\t\t\t[  2) Customer      |\n";
    cout << "\t\t\t\t\t]                   |\n";
    cout << "\t\t\t\t\t[  3) Exit          |\n";
    cout << "\t\t\t\t\t]                   |\n";
    cout << "\t\t\t\t\t-- Type 1, 2 or 3  --\n\t\t\t\t\t> ";
    cin >> choice;

    int i = 0;
    
    switch(choice)
    {
        case 1:
            clear();
            cout << "\t\t\t\t____________________________________________________________\n";
            cout << "\t\t\t\t                      Please log in!                        \n";
            cout << "\t\t\t\t____________________________________________________________\n";
            cout << "\t\t\t\t[    Please input an email    ]\n\t\t\t\t> "; cin >> email;
            cout << "\t\t\t\t[   Please input a password   ]\n\t\t\t\t> "; 

            char ch;

            while ((ch = getch()) != '\n')
            {
                password[i] = ch;
                i++;
            } // Password masking

            if (email == "admin@example.com" && strcmp(password, "admin"))
            {
                administrator();
            }

            else
            {
                clear();
                cout << "[ FAILED ] Invalid email and/or password!\n";
                sleep(3);
            }
            break;
        
        case 2:
            buyer();
            break;
        
        case 3:
            clear();
            exit(0);
        
        default:
            clear();
            cout << "[ FAILED ] Invalid input!\n";
            sleep(3);
            clear();
            break;
    }
    goto menu;
}

void Shopping::administrator()
{
    menu:
    clear();
    int choice;
    cout << "\t\t\t____________________________________________________________\n";
    cout << "\t\t\t                      ADMINISTRATOR MENU                    \n";
    cout << "\t\t\t____________________________________________________________\n";
    cout << "\n\t\t\t[_______1) Add product________]";
    cout << "\n\t\t\t]                             [";
    cout << "\n\t\t\t[______2) Modify product______]";
    cout << "\n\t\t\t]                             [";
    cout << "\n\t\t\t[______3) Delete product______]";
    cout << "\n\t\t\t]                             [";
    cout << "\n\t\t\t[____4) Go to the main menu___]\n";
    cout << "\n\t\t\t-- Please enter your choice! --\n\t\t\t> "; cin >> choice;

    switch(choice)
    {
        case 1:
            add();
            break;
        
        case 2:
            edit();
            break;
        
        case 3:
            rem();
            break;
        
        case 4:
            menu();
            break;
        
        default:
            clear();
            cout << "[ FAILED ] Invalid input!\n";
            sleep(3);
            clear();
            break;
    }  
    goto menu;
}

void Shopping::buyer() 
{
    menu:
    clear();
    int choice;
    cout << "\t\t\t____________________________________________________________\n";
    cout << "\t\t\t                        Customer menu                       \n";
    cout << "\t\t\t____________________________________________________________\n";
    cout << "\n\t\t\t[_______1) Buy product________]";
    cout << "\n\t\t\t]                             [";
    cout << "\n\t\t\t[____2) Go to the main menu___]\n";
    cout << "\n\t\t\t-- Please enter your choice! --\n\t\t\t> "; cin >> choice;

    switch(choice)
    {
        case 1:
            receipt();
            break;
        
        case 2:
            menu();
            break;
        
        default:
            clear();
            cout << "[ FAILED ] Invalid input!\n";
            sleep(3);
            clear();
            break;
    }  
    goto menu;
}

void Shopping::add() 
{
    menu:
    clear();

    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\t\t\t____________________________________________________________\n";
    cout << "\t\t\t                 Configure the new product                  \n";
    cout << "\t\t\t____________________________________________________________\n";
    cout << "\t\t\t\t[     Product code         ==|\n\t\t\t\t> "; cin >> pCode;
    cout << "\t\t\t\t[     Product name         ==|\n\t\t\t\t> "; cin >> pName;
    cout << "\t\t\t\t[     Product price        ==|\n\t\t\t\t> "; cin >> price;
    cout << "\t\t\t\t[     Product discount     ==|\n\t\t\t\t> "; cin >> discount;

    clear();

    cout << "[ LOG ] Trying to open database file...\n";

    data.open("database.db", ios::in);

    if(!data)
    {
        cout << "[ LOG ] Database file doesn't exist. Creating it now and adding new product...\n";

        data.open("database.db", ios::app | ios::out);
        data << " " << pCode << " " << pName << " " << price << " " << discount << endl;

        cout << "[ LOG ] Database file created successfully, along with the new product!\n";

        data.close();
    }
    
    else
    {
        cout << "[ LOG ] Database file exists. Checking tokens...\n";

        data >> c >> n >> p >> d;

        while (!data.eof())
        {
            if (pCode == c)
            {
                token++;
            }

            data >> c >> n >> p >> d;
        }

        data.close();

        if (token == 1)
        {
            cout << "[ FAILED ] Product code already exists! Returning to menu...\n";
            sleep(3);
            goto menu;
        }
        else 
        {
            cout << "[ LOG ] Product code is unique. Adding new product to database...\n";

            data.open("database.db", ios::app | ios::out);
            data << " " << pCode << " " << pName << " " << price << " " << discount << endl;

            cout << "[ LOG ] Product added succesfully!\n";

            data.close();
        }
    }
    cout << "[ LOG ] Success! Returning to the administrator menu...\n";
    sleep(5);
}

void Shopping::edit()
{
    menu:
    clear();

    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\t\t\t____________________________________________________________\n";
    cout << "\t\t\t                      Edit a product                        \n";
    cout << "\t\t\t____________________________________________________________\n";
    cout << "\t\t\t\t[     Product code         ==|\n\t\t\t\t> "; cin >> pkey;

    clear();

    cout << "[ LOG ] Trying to open database file...\n";
    data.open("database.db", ios::in);

    if (!data)
    {
        cout << "[ FAILED ] Database file doesn't exist. Returning to menu...\n";
        sleep(3);
        goto menu;
    }

    else
    {
        cout << "[ LOG ] Database file exists. Checking tokens...\n";

        data1.open("database.temp", ios::app | ios::out);

        data >> pCode >> pName >> price >> discount;
        while (!data.eof())
        {
            if (pkey == pCode)
            {
                cout << "[ ? ] Enter a new product code:\n> "; cin >> c;
                cout << "[ ? ] Enter a new product name:\n> "; cin >> n;
                cout << "[ ? ] Enter a new product price:\n> "; cin >> p;
                cout << "[ ? ] Enter a new product discount:\n> "; cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << endl;
                cout << "[ LOG ] Product edited successfully!\n";
                token++;
            }
            else
            {
                data1 << " " << pCode << " " << pName << " " << price << " " << discount << endl;
            }
            data >> pCode >> pName >> price >> discount;
        }
        data.close();
        data1.close();

        std::remove("database.db");
        std::rename("database.temp", "database.db");

        if (token == 0)
        {
            cout << "[ FAILED ] Product code doesn't exist! Returning to menu...\n";
            sleep(3);
            goto menu;
        }

        cout << "[ LOG ] Success! Returning to the administrator menu...\n";

        sleep(5);
    }
}

void Shopping::rem()
{
    menu:
    clear();

    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\t\t\t____________________________________________________________\n";
    cout << "\t\t\t                     Remove a product                       \n";
    cout << "\t\t\t____________________________________________________________\n";
    cout << "\t\t\t\t[     Product code         ==|\n\t\t\t\t> "; cin >> pkey;
    clear();

    cout << "[ LOG ] Trying to open database file...\n";
    data.open("database.db", ios::in);

    sleep(1);

    if (!data)
    {
        cout << "[ FAILED ] Database file doesn't exist. Returning to menu...\n";
        sleep(3);
        goto menu;
    }

    else
    {
        cout << "[ LOG ] Database file exists. Checking tokens...\n";

        data1.open("database.temp", ios::app | ios::out);

        data >> pCode >> pName >> price >> discount;
        
        while (!data.eof())
        {
            if (pkey != pCode)
            {
                data1 << " " << pCode << " " << pName << " " << price << " " << discount << endl;
                data >> pCode >> pName >> price >> discount;
            }
            else
            {
                token++;
                data >> pCode >> pName >> price >> discount;
            }
        }
        data.close();
        data1.close();

        std::remove("database.db");
        std::rename("database.temp", "database.db");

        if (token == 0)
        {
            cout << "[ FAILED ] Product code doesn't exist! Returning to menu...\n";
            sleep(3);
            goto menu;
        }

        cout << "[ LOG ] Success! Returning to the administrator menu...\n";

        sleep(5);
    }
}

void Shopping::list()
{
    menu:
    clear();

    fstream data;
    data.open("database.db", ios::in);
    cout << "\t\t\t____________________________________________________________\n";
    cout << "\t\t\t                Product Code / Name / Price                 \n";
    cout << "\t\t\t____________________________________________________________\n";
    data >> pCode >> pName >> price >> discount;
    while (!data.eof())
    {
        cout << "\t\t\t\t>> " << pCode << " / " << pName << " / " << price << endl;
        data >> pCode >> pName >> price >> discount;
    }
    data.close();
}

void displayProducts(int arrc[], int arrq[], int count)
{
    fstream data;
    int c, p, d, sum = 0;
    string n;
    if (count == 0)
    {
        cout << "\t\t\t\t<< No products in the cart. >>\n";
    }
    else
    {
        for (int i = 0; i < count; ++i)
        {
            data.open("database.db", ios::in);
            while(!data.eof())
            {
                data >> c >> n >> p >> d;
                if(arrc[i] == c)
                {
                    cout << "\t\t\t\t<< " << n << " / " << p << " / " << arrq[i] << endl;
                    sum += arrq[i] * p;
                    break;
                }
            }
            data.close();
        }
        cout << "\t\t\t\t<< Current total: " << sum << "$ >>\n";
    }
}

void displayProductsDetailed(int arrc[], int arrq[], int count)
{
    fstream data;
    int c, p, d, sum = 0;
    string n;
    if (count == 0)
    {
        cout << "\t\t\t\t<< No products in the cart. >>\n";
    }
    else
    {
        for (int i = 0; i < count; ++i)
        {
            data.open("database.db", ios::in);
            while(!data.eof())
            {
                data >> c >> n >> p >> d;
                if(arrc[i] == c)
                {
                    cout << "\t\t\t\t<< " << n << "\t" << p << "$ >>" << "\n";
                    cout << "\t\t\t\t\t- Product code: " << c << endl;
                    cout << "\t\t\t\t\t- Quantity: " << arrq[i] << endl;
                    cout << "\t\t\t\t\t- Discount: " << d << "%" << endl;
                    sum += arrq[i] * p;
                    break;
                }
            }
            data.close();
        }
        cout << "\t\t\t\t<< Total: " << sum << "$ >>\n\n";
    }
}

void Shopping::receipt() 
{
    menu:
    clear();
    
    fstream data;
    int arrc[100];
    int arrq[100];
    string choice = "y";
    int c = 0;
    float amount = 0;
    float discount = 0;
    float total = 0;

    // cout << "\t\t\t____________________________________________________________\n";
    // cout << "\t\t\t                          RECEIPT                           \n";
    // cout << "\t\t\t____________________________________________________________\n";

    data.open("database.db", ios::in);

    if (!data)
    {
        cout << "[ FAILED ] Database file doesn't exist. Returning to menu...\n";
        sleep(3);
    }

    else 
    {
        do
        {
            clear();

            list();

            cout << "\n\t\t\t____________________________________________________________\n";
            cout <<   "\t\t\t|                                                          |\n";
            cout <<   "\t\t\t|                Please place your order.                  |\n";
            cout <<   "\t\t\t|                                                          |\n";
            cout <<   "\t\t\t|__________________________________________________________|\n\n";

            displayProducts(arrc, arrq, c);

            cout << "\n\t\t\t| Product code           >> "; cin >> arrc[c];
            cout <<   "\t\t\t| Product quantity       >> "; cin >> arrq[c];

            c++;

            cout << "\n\t\t\t| Do you want to order more products? (y/n) >> "; cin >> choice;

        } while (choice == "y" || choice == "Y");

        clear();

        // receipt
        cout << "\t\t\t____________________________________________________________\n";
        cout << "\t\t\t                          RECEIPT                           \n";
        cout << "\t\t\t____________________________________________________________\n\n";

        displayProductsDetailed(arrc, arrq, c);

        sleep(10);
        data.close();
    }
}

int main()
{
    Shopping shoppingInstance;
    shoppingInstance.menu();

    return 0;
}