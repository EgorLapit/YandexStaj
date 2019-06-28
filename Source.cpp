#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

int const N = 100;

struct Elem
{
	char value[N];
	struct Elem* next;
};

struct Form
{
	Elem* head;
	Elem* tail;
};

void constr_list(Form& l);
bool chk_empty(Form l);
void tabin(Form& l, int tab_c, Elem* c);
void entin(Form& l);


int main() {
	setlocale(LC_ALL, "Rus");
	Form vars;
	int tab_count = 0, list_count = 0,sv;
	cout << "Начало программы"<< endl;
	constr_list(vars);
	ifstream* file = new ifstream("input.txt");
	cout << "Выберите способо ввода: \n1)консоль\n2)файл\n\nВаш вариант:";
	cin >> sv;
	cout << endl;
	switch (sv) {
	case 1:
		char sts[N];
		cout << "Вводите код, для того чтобы закончить введите \"stop\" через пробел:\n" << endl;
		while (sts != "\"stop\"") {
			Elem* c = new Elem();
			cin >> c->value;
			strcpy_s(sts, c->value);
			if (sts == "\"stop\"") {
				cout << "Ввод закончен." << endl;
				break;
			}
			c->next = NULL;
			for (int i = 0; i < N; i++) {
				if (c->value[i] == '{')
					tab_count++;
				else if (c->value[i] == '}')
					tab_count--;
			}
			if (list_count > 0)
				entin(vars);
			tabin(vars, tab_count, c);
			if (chk_empty(vars))
				vars.head = c;
			else
				vars.tail->next = c;
			vars.tail = c;
			list_count++;
		}
		break;
	case 2:
		cout << "Код взят из файла input.txt" << endl;
		while (!file->eof())
		{
			Elem* c = new Elem();
			file->getline(c->value, N);
			c->next = NULL;
			for (int i = 0; i < N; i++) {
				if (c->value[i] == '{')
					tab_count++;
				else if (c->value[i] == '}')
					tab_count--;
			}
			if (list_count > 0)
				entin(vars);
			tabin(vars, tab_count, c);
			if (chk_empty(vars))
				vars.head = c;
			else
				vars.tail->next = c;
			vars.tail = c;
			list_count++;

		}
		file->close();
		break;
	default:
		cout << "Такого варианта нет!" << endl;
		break;
	}
	char outname[40];
	cout << "Введите название файла для вывода: ";
	cin >> outname;
	cout << endl;
	strcat(outname, ".txt");
	ofstream* out = new ofstream(outname);
	while (vars.head != NULL)
	{
		out->write(vars.head->value, strlen(vars.head->value));
		vars.head = vars.head->next;
	}
	out->close();
	cout << "Данные сохранены в файл "<<outname << endl;
	return 0;
}
void constr_list(Form& l)
{
	l.head = NULL;
}

bool chk_empty(Form l)
{
	return (l.head == NULL);
}
void tabin(Form& l, int tab_c, Elem* c)
{
	int kon = tab_c;
	if (tab_c == 0)
		return;
	if (c->value[0] == '{')
		kon--;
	for (int i = 0; i < kon; i++) {
		Elem* c = new Elem();
		c->value[0] = '\t';
		c->next = NULL;
		if (chk_empty(l))
			l.head = c;
		else
			l.tail->next = c;
		l.tail = c;
	}
}
void entin(Form& l) {
	Elem* c = new Elem();
	c->value[0] = '\n';
	c->next = NULL;
	if (chk_empty(l))
		l.head = c;
	else
		l.tail->next = c;
	l.tail = c;
}
