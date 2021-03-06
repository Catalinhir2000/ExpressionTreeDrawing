#include <iostream>
#include <winbgim.h>
#include <string>
#include <bits/stdc++.h>
#include <limits>
using namespace std;

int alegere = 0;

struct nodLista
{
    string info;
    nodLista* next;
};

typedef nodLista* Lista;

nodLista* elementLista, * ultimulElementLista;
Lista lista = NULL;

struct nodarb
{
    string info;
    nodarb* stanga, * dreapta;
    int x, y;///COORDONATELE CENTRULUI FIECARUI NOD
};

typedef nodarb* Arbore;

nodarb* elementarb, * elementArbore1, * elementArbore2, * elementArbore3, * f_x, * g_x;
Arbore arbore = NULL, p;

bool formulacorecta = true;
string Formula;

void patrat(int x, int y, int L);
void inserareelementinarbore(Arbore& p)
{
    elementarb = new nodarb;
    elementarb->info = elementLista->info;
    elementLista = elementLista->next;
    p = elementarb;
    if (elementarb->info == "+" || elementarb->info == "-" || elementarb->info == "*" || elementarb->info == "/" || elementarb->info == "^" || elementarb->info == "log")
    {
        inserareelementinarbore(p->stanga);
        inserareelementinarbore(p->dreapta);
    }
    else if (elementarb->info == "sin" || elementarb->info == "cos" || elementarb->info == "tan" || elementarb->info == "ctan" || elementarb->info == "arcsin" || elementarb->info == "arccos" || elementarb->info == "arctan" || elementarb->info == "arcctan" || elementarb->info == "ln" || elementarb->info == "rad")
    {
        inserareelementinarbore(p->stanga);
        p->dreapta = NULL;
    }
    else
        p->stanga = p->dreapta = NULL;
}

void afisareArbore(Arbore arbore)///afisare arbore dupa parcurgerea inordine (RSD)
{
    if (arbore->info == "+" || arbore->info == "-" || arbore->info == "*" || arbore->info == "/" || arbore->info == "^")
    {
        if (!(arbore->info == "-" && arbore->stanga->info == "0"))
            afisareArbore(arbore->stanga);
        cout << arbore->info;
        afisareArbore(arbore->dreapta);
    }
    else if (arbore->info == "sin" || arbore->info == "cos" || arbore->info == "tan" || arbore->info == "ctan" || arbore->info == "arcsin" || arbore->info == "arccos" || arbore->info == "arctan" || arbore->info == "arcctan" || arbore->info == "ln" || arbore->info == "rad")
    {
        cout << arbore->info;
        afisareArbore(arbore->stanga);
    }
    else if (arbore->info == "log")
    {
        cout << "log(";
        afisareArbore(arbore->dreapta);
        cout << ",";
        afisareArbore(arbore->stanga);
        cout << ")";
    }
    else
        cout << arbore->info;
}



void inserareelementinlista(Lista& lista, string info)
{
    elementLista = new nodLista;
    elementLista->info = info;
    elementLista->next = NULL;
    if (lista == NULL)
    {
        lista = elementLista;
        ultimulElementLista = lista;
    }
    else
    {
        ultimulElementLista->next = elementLista;
        ultimulElementLista = elementLista;
    }
}


bool dacaformula(string Formula)
{
    /// Verifica daca este <parametru> <semn> <parametru> si daca da, returneaza false
    for (int i = 0; i < Formula.size(); i++)
        if (Formula[i] == '+' || Formula[i] == '-' || Formula[i] == '*' || Formula[i] == '/' || Formula[i] == '^' || Formula.substr(0, 3) == "sin" || Formula.substr(0, 3) == "cos" || Formula.substr(0, 2) == "tan" || Formula.substr(0, 3) == "ctan" || Formula.substr(0, 6) == "arcsin" || Formula.substr(0, 6) == "arccos" || Formula.substr(0, 5) == "arctan" || Formula.substr(0, 6) == "arcctan" || Formula.substr(0, 2) == "ln" || Formula.substr(0, 4) == "rad" || Formula.substr(0, 3) == "log")
            return false;
    return true;
}

bool verificaparanteza(string Formula)
{
    /// Verifica daca formula e de tipul <paranteza deschisa> <formula> <paranteza inchisa>
    if (Formula[0] == '(' && Formula[Formula.size() - 1] == ')')
    {
        int j = 0;
        for (int i = 0; i < Formula.size(); i++)
            if (Formula[i] == '(')
                j++;
            else if (Formula[i] == ')')
                j--;
            else if (j == 0 && i != Formula.size() - 1)
                return false;
        return true;
    }
    return false;
}

int locatieplusminus(string Formula)
{
    int pozitiesemn = -1, indiceParanteza = 0;
    bool gasitsemn = 0;
    /** Cauta semnele [+] sau [-] */
    for (int i = 0; i < Formula.size() && gasitsemn == 0; i++)
        if (Formula[i] == '(')
            indiceParanteza++;
        else if (Formula[i] == ')')
            indiceParanteza--;
        else if ((Formula[i] == '+' || Formula[i] == '-') && indiceParanteza == 0)
        {
            pozitiesemn = i;
            gasitsemn = 1;
        }
    return pozitiesemn;
}

int locatieinmultire(string Formula)
{
    int pozitiesemn = -1, indiceParanteza = 0;
    bool gasitsemn = 0;
    /** Cauta semnul [*] */
    for (int i = 0; i < Formula.size() && gasitsemn == 0; i++)
        if (Formula[i] == '(')
            indiceParanteza++;
        else if (Formula[i] == ')')
            indiceParanteza--;
        else if ((Formula[i] == '*') && indiceParanteza == 0)
        {
            pozitiesemn = i;
            gasitsemn = 1;
        }
    return pozitiesemn;
}

int locatieimpartire(string Formula)
{
    int pozitiesemn = -1, indiceParanteza = 0;
    bool gasitsemn = 0;
    /** Cauta semnul [/] */
    for (int i = 0; i < Formula.size() && gasitsemn == 0; i++)
        if (Formula[i] == '(')
            indiceParanteza++;
        else if (Formula[i] == ')')
            indiceParanteza--;
        else if ((Formula[i] == '/') && indiceParanteza == 0)
        {
            pozitiesemn = i;
            gasitsemn = 1;
        }
    return pozitiesemn;
}

int locatieputere(string Formula)
{
    int pozitiesemn = -1, indiceParanteza = 0;
    bool gasitsemn = 0;
    /** Cauta semnul [^] */
    for (int i = 0; i < Formula.size() && gasitsemn == 0; i++)
        if (Formula[i] == '(')
            indiceParanteza++;
        else if (Formula[i] == ')')
            indiceParanteza--;
        else if ((Formula[i] == '^') && indiceParanteza == 0)
        {
            pozitiesemn = i;
            gasitsemn = 1;
        }

    return pozitiesemn;
}

int locatiesemn(string Formula)
{
    int pozitiesemn = locatieplusminus(Formula);

    if (pozitiesemn == -1)
        pozitiesemn = locatieinmultire(Formula);

    if (pozitiesemn == -1)
        pozitiesemn = locatieimpartire(Formula);

    if (pozitiesemn == -1)
        pozitiesemn = locatieputere(Formula);

    return pozitiesemn;
}

int locatiesinus(string Formula)
{
    if (Formula.substr(0, 3) == "sin")
        return 0;
    else if (Formula.substr(0, 3) == "cos")
        return 1;
    else if (Formula.substr(0, 2) == "tan" /** || s.substr(0,3) == "tan" */)
        return 2;
    else if (Formula.substr(0, 3) == "ctan" /** || s.substr(0,3) == "cot" */)
        return 3;
    else if (Formula.substr(0, 6) == "arcsin" /** || s.substr(0,4) == "asin" */)
        return 4;
    else if (Formula.substr(0, 6) == "arccos" /** || s.substr(0,4) == "acos" */)
        return 5;
    else if (Formula.substr(0, 5) == "arctan" /** || s.substr(0,4) == "atan" */)
        return 6;
    else if (Formula.substr(0, 6) == "arcctan" /** || s.substr(0,4) == "acot" */)
        return 7;
    else if (Formula.substr(0, 2) == "ln")
        return 8;
    else if (Formula.substr(0, 4) == "rad")
        return 9;
    else if (Formula.substr(0, 3) == "log")
        return 10;
    else
        return -1;
}

int logBaza(string s)
{
    for (int i = 0; i < s.size(); i++)
        if (s[i] == ',')
            return i;
    return -1;
}

/*int locatieparanteza(string s)
{
    int pozitiesemn = -1;
    for(int i = 0; i< s.size(); i++)
        if(1)
            return 0;
}
*/
void convertireInLista(string s)
{
    while (verificaparanteza(s))
    {
        s.erase(0, 1);
        s.erase(s.size() - 1, 1);
    }

    /// Verifica daca are formule
    if (dacaformula(s))
    {
        inserareelementinlista(lista, s);
        return;
    }
    int pozitiesemn = locatiesemn(s);

    if (pozitiesemn == -1)
    {
        pozitiesemn = locatiesinus(s);
        if (pozitiesemn != -1)
            switch (pozitiesemn)
            {
            case 0:
                inserareelementinlista(lista, "sin");
                convertireInLista(s.substr(3));
                break;
            case 1:
                inserareelementinlista(lista, "cos");
                convertireInLista(s.substr(3));
                break;
            case 2:
                inserareelementinlista(lista, "tan");
                convertireInLista(s.substr(2));
                break;
            case 3:
                inserareelementinlista(lista, "ctan");
                convertireInLista(s.substr(3));
                break;
            case 4:
                inserareelementinlista(lista, "arcsin");
                convertireInLista(s.substr(6));
                break;
            case 5:
                inserareelementinlista(lista, "arccos");
                convertireInLista(s.substr(6));
                break;
            case 6:
                inserareelementinlista(lista, "arctan");
                convertireInLista(s.substr(5));
                break;
            case 7:
                inserareelementinlista(lista, "arcctan");
                convertireInLista(s.substr(6));
                break;
            case 8:
                inserareelementinlista(lista, "ln");
                convertireInLista(s.substr(2));
                break;
            case 9:
                inserareelementinlista(lista, "rad");
                convertireInLista(s.substr(4));
                break;
            case 10:
                ///<!>
                pozitiesemn = logBaza(s.substr(3));
                if (pozitiesemn != -1)
                {
                    inserareelementinlista(lista, "log");
                    convertireInLista(s.substr(3 + pozitiesemn + 1, s.size() - pozitiesemn - 5));
                    convertireInLista(s.substr(3 + 1, pozitiesemn - 1));
                }
                else
                {
                    inserareelementinlista(lista, "ln");
                    convertireInLista(s.substr(3));
                }

                break;
            }
        return;
    }

    if (pozitiesemn == 0)
        if (s[pozitiesemn] == '+')
            convertireInLista(s.substr(1));
        else if (s[pozitiesemn] == '-')
        {
            inserareelementinlista(lista, s.substr(pozitiesemn, 1));
            convertireInLista("0");
            convertireInLista(s.substr(pozitiesemn + 1, s.size() - (pozitiesemn + 1)));
        }
        else
            formulacorecta = false;

    else if (pozitiesemn == s.size() - 1)
        formulacorecta = false;

    else if (formulacorecta)
    {
        inserareelementinlista(lista, s.substr(pozitiesemn, 1));
        convertireInLista(s.substr(0, pozitiesemn));
        convertireInLista(s.substr(pozitiesemn + 1, s.size() - (pozitiesemn + 1)));
    }
}

void coordArbore(Arbore arbore, int val)//DFS
{
    if (arbore == NULL)
        return;
    if (arbore->stanga != NULL)
    {
        arbore->stanga->x = arbore->x - val;
        arbore->stanga->y = arbore->y + 100;
    }
    if (arbore->dreapta != NULL)
    {
        arbore->dreapta->x = arbore->x + val;
        arbore->dreapta->y = arbore->y + 100;
    }
    coordArbore(arbore->stanga, val / 2);
    coordArbore(arbore->dreapta, val / 2);
}

void afiseazaArbore(Arbore arbore);
void deseneaza()
{
    initwindow(1200, 700);
    patrat(arbore->x, arbore->y, 50);

    int k = arbore->info.length(); // string -> char
    char info1[k + 1];
    strcpy(info1, arbore->info.c_str());

    settextstyle(1, 0, 5);
    outtextxy(arbore->x - 20, arbore->y - 20, info1);
    afiseazaArbore(arbore);

    getch();
    closegraph();
}

void afiseazaArbore(Arbore arbore) //DFS
{
    if (arbore == NULL)
        return;
    if (arbore->stanga != NULL)
    {
        patrat(arbore->stanga->x, arbore->stanga->y, 50);
        int k = arbore->stanga->info.length();
        char info1[k + 1];
        strcpy(info1, arbore->stanga->info.c_str());
        ///redimensionare text
        if (arbore->stanga->info == "sin" || arbore->stanga->info == "cos" ||
            arbore->stanga->info == "tan" || arbore->stanga->info == "ctan" ||
            arbore->stanga->info == "log" || arbore->stanga->info == "sqrt" || arbore->stanga->info == "ln")
            settextstyle(1, 0, 2);
        else
            if (arbore->stanga->info == "arccsin" || arbore->stanga->info == "arccos" ||
                arbore->stanga->info == "arctan" || arbore->stanga->info == "arcctan")
                settextstyle(1, 0, 1);
            else
                settextstyle(1, 0, 5);
        outtextxy(arbore->stanga->x - 20, arbore->stanga->y - 20, info1);
        line(arbore->x, arbore->y + 25, arbore->stanga->x, arbore->stanga->y - 25);
    }
    if (arbore->dreapta != NULL)
    {
        patrat(arbore->dreapta->x, arbore->dreapta->y, 50);
        int k = arbore->dreapta->info.length();
        char info1[k + 1];
        strcpy(info1, arbore->dreapta->info.c_str());
        ///redimensionare text
        if (arbore->dreapta->info == "sin" || arbore->dreapta->info == "cos" ||
            arbore->dreapta->info == "tan" || arbore->dreapta->info == "ctan" ||
            arbore->dreapta->info == "log" || arbore->dreapta->info == "sqrt" || arbore->dreapta->info == "ln")
            settextstyle(1, 0, 2);
        else
            if (arbore->dreapta->info == "arccsin" || arbore->dreapta->info == "arccos" ||
                arbore->dreapta->info == "arctan" || arbore->dreapta->info == "arcctan")
                settextstyle(1, 0, 1);
            else
                settextstyle(1, 0, 5);
        outtextxy(arbore->dreapta->x - 20, arbore->dreapta->y - 20, info1);
        line(arbore->x, arbore->y + 25, arbore->dreapta->x, arbore->dreapta->y - 25);
    }
    afiseazaArbore(arbore->stanga);
    afiseazaArbore(arbore->dreapta);

}

void patrat(int x, int y, int L)
{
    int l = L / 2;
    line(x - l, y - l, x + l, y - l);
    line(x + l, y - l, x + l, y + l);
    line(x + l, y + l, x - l, y + l);
    line(x - l, y + l, x - l, y - l);
}

int main()
{
    string Formula;
    cout << "Scrieti expresia dorita: ";
    cin >> Formula;
    cout << "\n";
    convertireInLista(Formula);
    if (formulacorecta)
    {
        elementLista = lista;
        inserareelementinarbore(arbore);
        cout << "Arborele de expresie: ";
        afisareArbore(arbore);
        cout << "\n";
        cout << "\n";
        arbore->x = 600;
        arbore->y = 50;
        int val = 300;
        coordArbore(arbore, val);
        deseneaza();
    }



}
