#include <iostream> //cin cout
#include <string> //to_string(), stoi() itd...
#include <math.h> //pow()

#define MAX_SIZE 50 //max rozmiar stosu

using namespace std;

bool isINF(string input);   //Sprawdza czy wyrazenie jest infiksowe czy w ONP
bool isOperator(char c);    //Sprawdza czy kolejny znak jest operatorem
int priority(char c);   //Sprawdza priorytet operatora

string equasion(string a, char operation, string b);    //Wykonuje odpowiednie dzialanie przy obliczaniu ONP

class Stack
{
    string stack[MAX_SIZE];
    int Top=-1;
public:
    Stack();
    bool isEmpty(); //Sprawdza czy stos pusty
    void push(string c);    //Wstawia na stos
    string top();   //Zwraca ostatni element stosu
    void pop();     //Usuwa element ze stosu
    void makeEmpty();   //"Czysci" stos
};

//-------------------------|MAIN|--------------------------
int main()
{
    Stack stack;
    string input;   //Wejscie (INF lub ONP)
    string output = "";
    cout<<"--------|   Program konwertuje wyrazenie   |--------\n";
    cout<<"--------|    w postaci infiksowej do ONP   |--------\n";
    cout<<"--------|oraz oblicza wartosc wyrazenia ONP|--------\n";
    cout<<endl;
    cout<<"Podaj wyrazenie INF lub ONP: ";
    getline(cin, input);

    //--------------------|INF na ONP|---------------------
    if(isINF(input))
    {
        stack.makeEmpty();
        for(unsigned int i=0; i<input.length(); i++)
        {
            char c=input[i];
            if(isdigit(c))
                output += c;

            if(isOperator(c))
            {
                output+=" ";
                if(!stack.isEmpty())
                {
                    while(priority(stack.top()[0]) >= priority(c))
                    {
                        output += stack.top() + " ";
                        stack.pop();
                        if(stack.isEmpty())
                            break;
                    }
                }
                stack.push(string(1,c));
            }
            if(c=='(')
                stack.push(string(1,c));

            if(c==')')
            {
                while(stack.top().compare("(") != 0)
                {
                    output += " " + stack.top();
                    stack.pop();
                }
                stack.pop();    //Usuwamy nawias "(" ze stosu
            }
        }
        while(!stack.isEmpty())
        {
            output += " " + stack.top();
            stack.pop();
        }
        cout<<"\n\n---------------|Po konwersji|---------------\n\n";
        cout<<output<<endl;
        cout<<"\n--------------------------------------------\n";
    }
    //-----------------------------------------------------

    //---------------------|Wynik ONP|---------------------
    else
    {
        stack.makeEmpty();
        string reader = "";
        for(unsigned int i=0; i<input.length(); i++)
        {
            char c = input[i];
            if(isdigit(c))
            {
                do
                {
                    reader += string(1, c);
                    i++;
                    c = input[i];
                }
                while(c != ' ');    //Czytamy cyfry az do napotkania spacji
                stack.push(reader);
                reader = "";
                continue;
            }
            if(isOperator(c))
            {
                if(c=='~')
                {
                    string a = stack.top();
                    stack.pop();

                    stack.push(equasion(a, c, ""));
                }
                else
                {
                    string a = stack.top();
                    stack.pop();

                    string b = stack.top();
                    stack.pop();

                    stack.push(equasion(b, c, a));
                }
            }
        }
        cout<<"\n\n---------------|Wynik ONP|---------------\n\n";
        cout<<"\t\t   "<<stack.top()<<endl;
        cout<<"\n-----------------------------------------\n";
    }
    //-----------------------------------------------------

    return 0;
}
//--------------|Czy element jest operatorem|----------------
bool isOperator(char c)
{
    if(c=='+' || c=='-' || c=='*' || c=='/' || c=='~' || c=='^')
        return true;

    return false;
}
//------------------------------------------------------------

//--------------|Czy wyrazenie jest INFiksowe|----------------
bool isINF(string input)
{
    char c = input.back(); //Pobiera ostatni element wejscia
    if(isdigit(c) || c==')')
        return true;

    return false;
}
//------------------------------------------------------------

//--------------------|Sprawdz priorytet|---------------------
int priority(char c)
{
    switch (c)
    {
        case '~':;
        case '+':;
        case '-':return 1;
        case '*':;
        case '/':return 2;
        case '^':return 3;
    }
    return 0;
}
//------------------------------------------------------------

//------------------|Oblicz rownanie|-------------------------
string equasion(string a, char operation, string b)
{
    int sol;
    int aa = stoi(a);   //stoi() zamienia string na integer
    int bb;
    if(operation != '~')
        bb = stoi(b);
    switch (operation)
    {
        case '~':
            sol = -1*aa;
            break;
        case '+':
            sol = aa + bb;
            break;
        case '-':
            sol = aa - bb;
            break;
        case '*':
            sol = aa * bb;
            break;
        case '/':
            sol = aa / bb;
            break;
        case '^':
            sol = (int)pow(aa, bb);
            break;
        default:
            break;
    }
    return(to_string(sol)); //to_string zamienia integer na string
}
//------------------------------------------------------------

//---------------------|Metody stosu|-------------------------
Stack::Stack()
{
    Top = -1;
}
bool Stack::isEmpty()
{
    return Top==-1;
}
void Stack::push(string c)
{
    Top++;
    stack[Top] = c;
}
string Stack::top()
{
    return stack[Top];
}
void Stack::pop()
{
    if(Top>-1)
    {
        Top--;
    }
}
void Stack::makeEmpty()
{
    Top = -1;
}
//------------------------------------------------------------
