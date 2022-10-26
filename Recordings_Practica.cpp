/***************************************************************************************
*Project Name : Recordings_Practica                                                    *
*File Name    : Recordings_Practica.cpp                                                *
*Language     : CPP,MSVS ver 2015 and above                                            *
*Programmers  : Ратников Роман Олегович,Фицайло Александр Александрович,               *
*                               группа:М3О-110Б-20                                     *
*Modified By  :                                                                        *
*Created      : 30/05/2021                                                             *
*Last Revision: 24/06/2021                                                             *
*Comment      : Практика                                                               *
***************************************************************************************/

#include <fstream>
#include <iostream>
using namespace std;
struct Avia
{
	string Time;    //Время посадки
	string Mark;    //Марка ЛА
	string Number;  //Бортовой номер
	string Point;   //Пункт отправления
    int Error=0;    //Код ошибки
    bool Info = 0;   //Информация
	
	//Если данные не записаны - табуляция
	Avia()
	{
		Time = "\t";
		Mark = "\t";
	    Number = "\t";
	    Point = "\t";
	    Error = 0;
		Info = 0;
	}
	Avia(string Time,string Mark ,string Number,string Point,int Error,bool Info)
	{
		this->Time = Time;
		this->Mark = Mark;
		this->Number = Number;
		this->Point = Point;
		this->Error = Error;
		this->Info = Info;
	}
	
	//Функция вывода информации
	string GetInfo()
	{
		return Time + ' ' +Mark+' '+ Number+' '+Point;
	}
	//Функция вывода 1 ошибки
	string GetError1()
	{
		if (Info)
		{
			return " Недостаточно данных.";
		}
		return "";
	}
	//Функция вывода 2 ошибки
	string GetError2()
	{   
		
		string Message = " Неправ. формат времени.";
		int symbol = 0;   //Символ
		//Пока не кончилась строчка
		while (Time[symbol] != '\0')
		{
			symbol++;
			
			//Нужное количество символов: 5
			if (symbol > 5)
			{
			
				this->Error = 2;
				return Message ;
				
			}
		}
		if (symbol < 5)
		{
			
			this->Error = 2;
			return "\t" + Message;
		}
		if (Time[2] != ':')
		{
			
			this->Error = 2;
			return Message;
		}
		/* 0 - код 48 в ASCII, 2 - код 50 в ASCII. Проверка по коду в ASCII
		   1 символ [0-2] */
		if (Time[0] < 48 or Time[0]>50)
		{
			
			this->Error = 2;
			return Message;
		}
		// 2 символ [0-9]
		if (Time[1] < 48 or Time[1]>57)
		{   
			
			this->Error = 2;
			return Message;
		}
		//Если 1 символ = 2. 2 символ [0-3]
		if (Time[0] == 50)
		{
			if (Time[1] > 51)
			{
			
			   this->Error = 2;
				return Message;
			}
		}
		//4 символ [0-5]
		if (Time[3] < 48 or Time[3]>53)
		{
			
			this->Error = 2;
			return Message;
		}
		//5 символ [0-9]
		if (Time[4] < 48 or Time[4]>57)
		{
			
			this->Error = 2;
			return Message;
		}
		return "";
	}
	//Функция вывода 3 ошибки
	string GetError3()
	{
		
		int i;
		string Message = " Неправ. формат борт. номера.";
		int symbol = 0;
		while (Number[symbol] != '\0')
		{
			symbol++;
			//Нужное количество символов: 6
			if (symbol > 6)
			{
				
				this->Error = 3;
				return Message;
			}
		}
		if (symbol < 6)
		{
			this->Error = 3;
			return Message;
		}
		/*1 символ от А до Я. 
		 Код ASCII. A:-64 . Я:-33
		*/
		if (Number[0] <-64 or Number[0]>-33)  
		{
			this->Error = 3;
			return Message;
		}
			
		//2 символ
		if (Number[1] != '-')
		{
			this->Error = 3;
			return Message;
		}
		//Номер [0000-9999]
		for (i = 2;i < 6;i++)
		{
			if(Number[i]<48 or Number[i]>57)
			{
				this->Error = 3;
				return Message;
			}
		}
        return "";

	}

};
struct IndexSort
{
	int ind;      //Индекс
	string key;   //Ключ

};
int main()
{
	setlocale(LC_ALL, "Rus");
	const char* fName = "Data.txt"; //Корректный тест
	//const char* fName = "Datat.txt"; //Несуществующий файл
	//const char* fName = "Data1.txt"; //Пустой файл
	//const char* fName = "Data2.txt"; //Нет записей в прав.формате
	//const char* fName = "Data3.txt"; //Корректный тест,все правильные
	fstream fin;
	fin.open(fName);
	//Проверка на существование файла
	if (!fin)
	{
		cout << " Файл " << fName << " не найден" << endl;//Сообщение об ошибке
		fin.close();
		return 1;
	}
	//Проверка на пустоту файл
	if (fin.peek() == EOF)
	{
		cout << " Файл " << fName << " пуст" << endl;
		fin.close();
		return 2;
	}

    int LEN = 0; //Количество строк
	char Buffer;    //Буферная переменная для динамики

	fin >> Buffer;

	//Подсчёт количества строк
	while (fin.peek()!=EOF)
	{
		fin >> Buffer;
		//Если дальше строка
		if (fin.peek() == '\n')
		{
			LEN++;
		}
	}
	LEN++; //Добавляем последнюю строчку

	//Очистка чтения
	fin.clear();
	//Переход на начало для чтения данных
	fin.seekg(0, ios::beg);
	//Динамический массив
	Avia *arr;
	 arr = new Avia[LEN];
	Avia s;
	int i;
	//Чтение данных
	for ( i = 0;i < LEN;i++)
	{
		s.Error = 0;
		s.Info = 0;
		fin >> s.Time;
		//Если нет больше данных в строчке
		if (fin.peek() == '\n')
		{   
			s.Info = 1;
			//Принимаем прочитанные данные
			arr[i] = Avia(s.Time, s.Mark, s.Number, s.Point, s.Error,s.Info);
			continue;
			
		}
		fin >> s.Mark;
		if (fin.peek() == '\n')
		{
			s.Info = 1;
			arr[i] = Avia(s.Time, s.Mark, s.Number, s.Point, s.Error,s.Info);
			continue;
		}
		fin >> s.Number;
		if (fin.peek() == '\n')
		{
			s.Info = 1;
			arr[i] = Avia(s.Time, s.Mark, s.Number, s.Point, s.Error,s.Info);
			continue;
		}
		fin >> s.Point;
		arr[i] = Avia(s.Time,s.Mark,s.Number,s.Point,s.Error,s.Info);
		//Игнорирование ненужных данных
		while (fin.peek() != '\n' and i<LEN-1)
			fin.ignore(1);
			
	}
	
	cout << "\tДанные о самолётах, совершивших посадку" << endl;
	for( i = 0;i<LEN;i++)
	 cout <<" "<<i+1<<")"<<"\t"<< arr[i].GetInfo() <<"\t\t"
		<<arr[i].GetError1()<<arr[i].GetError2()<<arr[i].GetError3()<<endl;

	

	//Массив для сортировки
	IndexSort *arrSort;
	arrSort = new IndexSort[LEN];
	int LenSort = LEN;
	int j = 0;
	for (i = 0;i < LEN;i++)
	{
		if (arr[i].Error == 0)
		{
			
			arrSort[j].ind = i;
			arrSort[j].key = arr[i].Time;
			j++;
		}
		else
		{
			LenSort--;
		}
	}
	string Bufer;  //Переменная для хранения данных
	


	
	//Сортировка
	
	
	int IndMin;   //Переменная для хранения данных
		for (i = 0;i < LenSort;i++)
		{
			
			string Min = arrSort[i].key;
			int iMin = i;
			
			for (j = i + 1;j < LenSort;j++)
			{
				if (arrSort[j].key < Min)
				{
					Min = arrSort[j].key;
					iMin = j;
				}
			

			}
			//Если минимум на своём месте,то менять местами не нужно
			if (iMin != i)
			{
				Bufer = arrSort[iMin].key;
				arrSort[iMin].key = arrSort[i].key;
				arrSort[i].key = Bufer;


				IndMin = arrSort[iMin].ind;
				arrSort[iMin].ind = arrSort[i].ind;
				arrSort[i].ind = IndMin;
			}
		}


	
		if (LenSort == 0)
	    {
		  cout << "  \nНет записей в правильном формате.";
	    }
		else
		{
			cout << "\n\t Записи после сортировки:" << endl;

			for (i = 0;i < LenSort;i++)
			{
				cout << " " << i + 1 << ")\t" << arr[arrSort[i].ind].GetInfo() << endl;
			}
		}
	delete[] arr; //Удаление массивов
	delete[] arrSort;
   return 0;  
}
