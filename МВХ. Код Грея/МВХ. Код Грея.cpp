// Л.р. №4 
// МВХ. Поиск в ширину. Код Грея

#include <iostream>
#include <bitset>
#include <vector>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std;

string Grey(string a, int L)
{
	string b = a;
	int c;
	a.erase(L - 1);
	string d = "0";
	d += a;
	a = b;
	b = "";
	for (int j = 0; j < L; j++)
	{
		c = (((stoi(d.substr(j, 1))) + (stoi(a.substr(j, 1)))));
		if (c == 2) { c = 0; }
		if (c == 0) { b += "0"; }
		if (c == 1) { b += "1"; }
	}
	d = b;
	return d;
}

string UNGrey(string a, int L)
{
	string z = "";
	string d = "";
	string b = "0";
	int c;
	vector <string> vec3(L);
	vec3[0] = a;
	d = a;
	z = a;
	for (int n = 1; n < L; n++)
	{
		z.erase(L - 1);
		b += z;
		vec3[n] = b;
		z = vec3[n];
		b = "0";
		cout << vec3[n] << endl;
	}
	b = "";

	for (int n = 0; n < L - 1; n++)
	{
		for (int m = 0; m < L; m++)
		{
			c = (((stoi(d.substr(m, 1))) + (stoi(vec3[n + 1].substr(m, 1)))));
			if (c == 2) { c = 0; }
			if (c == 0) { b += "0"; }
			if (c == 1) { b += "1"; }
		}
		d = b;
		b = "";
	}
	return d;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(static_cast<unsigned int>(time(0)));

	int L = 5;
	int N, i, x, k1 = 0;
	int max = 0;                   // максимальная приспособленность
	string M[32];                 // массив кодировок
	int P1 = 0;
	int P[32];
	string maxS = "";           // пустая кодировка
	vector <string> vec(5);   // вектор соседей
	string u1 = "1";         // используем для создания инверсии
	string u2 = "0";
	string u3 = "";
	string u4 = "";
	int j = 0;
	int p = 0;
	int z = 0;
	int U[5];
	int t[5];
	int e = 0;

	cout << "Бинарное кодирование: " << endl;

	while (j != 32)
	{
		string S;
		for (int i = 0; i < L; i++)     // cоздаем строку
		{
			int a = rand() % 2;
			S += '0' + a;
		}

		for (int i = 0; i < 32; i++)  //проверка на повтор
		{
			if (M[i] == S)
			{
				k1 = 1;
				break;
			}
		}

		if (k1 == 0)    // условия вхождения
		{
			M[j] = S;
			cout << "S: " << S << '\t';

			for (int i = 0; i < L; i++)    // переводим из двоичной в десятичную
			{
				p *= 2;
				p += S[i] - '0';
				S[i] = p;
			}
			P[j] = p;                    // Задаем приспособленность
			cout << "    " << "P:" << P[j] << endl;
			p = 0;
			j++;
		}
		k1 = 0;
	}

	cout << endl << "      Код Грея: " << endl;

	for (int j = 0; j < 32; j++)
	{
		M[j] = Grey(M[j], L);
		cout << "S: " << M[j] << "    " << "P: " << P[j] << endl;
	}

	cout << endl << "Введите число шагов " << endl;
	cin >> N;

	i = 0;
	j = 0;
	k1 = 0;
	int index = 0;
	index = rand() % 32;
	maxS = M[index];

	while (i < N)
	{
		cout << endl << "i = " << i + 1 << endl;

		for (int j = 0; j < 5; j++)
		{
			if ((stoi(M[index].substr(j, 1))) == 0)  // создаем инверсию кодировки
			{
				u3 = M[index];
				u3.replace(j, 1, u1);
				vec[j] = u3;
				u3 = "";
			}

			else
			{
				u3 = M[index];
				u3.replace(j, 1, u2);
				vec[j] = u3;
				u3 = "";
			}
		}

		cout << "Кодировка:" << M[index] << endl;
		cout << "Приспособленность: " << P[index] << endl;

		if (P[index] > max)
		{
			max = P[index];
		}

		cout << "max = " << max << endl;
		cout << "Окрестность: " << endl;


		for (int k1 = 0; k1 < 5; k1++)
		{
			cout << "Сосед: " << vec[k1] << '\t';

			for (int j = 0; j < 32; j++)
			{
				if (vec[k1] == M[j])
				{
					cout << "Приспособленность: " << P[j] << endl;
					P1 = P[j];
					z = j;
				}

				U[k1] = P1;
				t[k1] = z;
			}
		}
		P1 = 0;
		j = 0;

		for (int k1 = 0; k1 < 5; k1++)
		{
			j++;
			if (P1 == U[k1] || P1 < U[k1])
			{
				P1 = U[k1];
				z = k1;             // Запоминаем позицию лучшего
				if (max < P1)
				{
					max = P1;
					e = j;
				}
			}
		}

		if (max == P1)
		{
			maxS = vec[e - 1];
			cout << "Замена max!" << endl;
			cout << "maxS = " << maxS << endl;
			cout << "max = " << max << endl;
			index = t[z];
			i++;
		}
		else
		{
			cout << endl << "local max" << endl;
			cout << "maxS = " << maxS << endl;
			cout << "max = " << max << endl;
			break;
		}

	}

	cout << endl << "-----------------------------------------" << endl;
	cout << "Ответ: " << endl;
	cout << "maxS по Грею: " << endl << maxS << endl;
	cout << "Обычный maxS = " << UNGrey (maxS, L) << endl;
	cout << "max = " << max << endl;
	cout << "-----------------------------------------" << endl;
}
