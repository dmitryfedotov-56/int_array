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
		cout << " �������� " << value;
		if (a.found(value, &n))
			cout << " ������� � ������� " << n;
		else
			cout << " �� �������";
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

		cout << " �������� ��������� �� �������" << endl;
		Int_Array a(7, s);
		show('a', a);

		e = a[3];
		cout << " ������� c ������� 3 ����� " << e << endl << endl;

		cout << " ������� ������� � ������� 3" << endl;
		a[3] = 100;
		show('a', a);

		cout << " ����������� ������� � ������� 3" << endl;
		a[3] = e;
		show('a', a);

		cout << " ������ ������� �� ��������" << endl;
		e = a.remove(3);
		show('a', a);

		cout << " ������� ������� � ��������" << endl;
		a.insert(3, e);
		show('a', a);

		cout << " ������� ������� �����" << endl;
		a.insert(0, -1);
		show('a', a);

		cout << " ������ ������� �����" << endl;
		a.remove(0);
		show('a', a);

		cout << " ������� ������� ������" << endl;
		a.insert(a.size(), 7);
		show('a', a);

		cout << " ������ ������� ������" << endl;
		a.remove(a.size() -1);
		show('a', a);

		cout << " ������� ������������������ � ��������" << endl;
		a.replicate(3, 3, 0);
		show('a', a);

		cout << " ������ ������������������ �� ��������" << endl;
		a.remove(3, 3);
		show('a', a);

		cout << " ��������� ��������� a � b" << endl;
		b = a;
		show('b', b);

		cout << " ������ ��� �������� b �����" << endl;
		b.remove(0, 2);
		show('b', b);

		cout << " ������ ��� �������� b ������" << endl;
		b.remove(b.size() - 2, 2);
		show('b', b);

		cout << " ������ ������������������ �� �������� a" << endl;
		a.remove(2, 3) ;
		show('a', a);

		cout << " ������� ��������� b � ��������� a" << endl;
		a.insert(2, b);
		show('a', a);

		cout << " ��������� ��������� a � b" << endl;
		b = a;
		show('b', b);

		Addition addition(7);

		cout << " �������� �������� ����������" << endl;
		b.apply(addition);
		show('b', b);

		cout << " ���������� ����������" << endl;
		// a.insert(a.size(), b);
		a += b;
		show('a', a);

		search(a, 7);

		search(a, 100);

		cout << endl;

		cout << " � �������, ��� ������������ �������" << endl;
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

		cout << endl <<" ������� ����� �������" << endl;
		char c = _getch();
	}

	/***********************************************************/
