	/***********************************************************/
	/*                      Int_Array Demo	 	               */
	/***********************************************************/

	#include <conio.h>

	#include "int_array.h"

	void show(char c, Int_Array& array)
	{
		cout << " " << c << " = " << array << endl << endl;
	};

	/***********************************************************/

	void search(Int_Array& a, int value ) 
	{
		unsigned n;
		cout << " значение " << value;
		if (a.found(value, &n))
			cout << " найдено в позиции " << n;
		else
			cout << " не найдено";
		cout << endl;
	};

	/***********************************************************/

	class Addition : public Int_Array_Handler 
	{
	public:
		virtual void handle(Int_Array& a, unsigned n) 
		{
			a[n] = a[n] + addition;
		};

		Addition(int x) : addition(x) {};

	private:
		int addition = 0;
	};

	/***********************************************************/

	void int_array_test() 
	{
		int e;

		int s[] = { 0,1,2,3,4,5,6 };

		Int_Array b;

		cout << " создадим контейнер из массива" << endl;
		Int_Array a(7, s);
		show('a', a);

		e = a[3];
		cout << " элемент c номером 3 равен " << e << endl << endl;

		cout << " изменим элемент с номером 3" << endl;
		a[3] = 100;
		show('a', a);

		cout << " восстановим элемент с номером 3" << endl;
		a[3] = e;
		show('a', a);

		cout << " уберем элемент из середины" << endl;
		e = a.remove(3);
		show('a', a);

		cout << " вставим элемент в середину" << endl;
		a.insert(3, e);
		show('a', a);

		cout << " добавим элемент слева" << endl;
		a.insert(0, -1);
		show('a', a);

		cout << " уберем элемент слева" << endl;
		a.remove(0);
		show('a', a);

		cout << " добавим элемент справа" << endl;
		a.insert(a.size(), 7);
		show('a', a);

		cout << " уберем элемент справа" << endl;
		a.remove(a.size() -1);
		show('a', a);

		cout << " вставим последовательность в середину" << endl;
		a.replicate(3, 3, 0);
		show('a', a);

		cout << " уберем последовательность из середины" << endl;
		a.remove(3, 3);
		show('a', a);

		cout << " скопируем контейнер a в b" << endl;
		b = a;
		show('b', b);

		cout << " удалим два элемента b слева" << endl;
		b.remove(0, 2);
		show('b', b);

		cout << " удалим два элемента b справа" << endl;
		b.remove(b.size() - 2, 2);
		show('b', b);

		cout << " удалим последовательность из середины a" << endl;
		a.remove(2, 3) ;
		show('a', a);

		cout << " вставим контейнер b в контейнер a" << endl;
		a.insert(2, b);
		show('a', a);

		cout << " скопируем контейнер a в b" << endl;
		b = a;
		show('b', b);

		Addition addition(7);

		cout << " увеличим элементы контейнера" << endl;
		b.apply(addition);
		show('b', b);

		cout << " объединяем контейнеры" << endl;
		// a.insert(a.size(), b);
		a += b;
		show('a', a);

		search(a, 7);

		search(a, 100);

		cout << endl;

		cout << " и наконец, все торжественно обрушим" << endl;
		e = a[100];
	};

	/***********************************************************/

	int main()
	{
		setlocale(LC_ALL, "");

		try 
		{
			int_array_test();
		}
		catch (exception& e) 
		{
			cout << e.what() << endl;
		};

		cout << endl <<" нажмите любую клавишу" << endl;
		char c = _getch();
	}

	/***********************************************************/
