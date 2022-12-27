	/***********************************************************/
	/*                         Int_Array	 	               */
	/***********************************************************/

	#define _CRT_SECURE_NO_WARNINGS

	#include <string.h>

	#include "int_array.h"

	/***********************************************************/
	/*                     Exception Class	 	               */
	/***********************************************************/

	#define MESSAGE " error: invaid Int_Array index "	// exception message

	char buffer[sizeof(MESSAGE) + 12]{0};				// max. message length

	Bad_Index::Bad_Index(unsigned index) :exception() 
	{ 
		bad_index = index; 
		strcpy(buffer, MESSAGE);
		int n = sprintf(&buffer[sizeof(MESSAGE) - 1], "%d", index);
		text = buffer;
	};

	unsigned Bad_Index::value() { return bad_index; };

	const char* Bad_Index::what() const noexcept { return text; };

	/***********************************************************/
	/*                         Index Check	 	               */
	/***********************************************************/

	void Int_Array::less_than_size(unsigned index)
	{
		if (index < current_size)return;
		throw Bad_Index(index);
	};

	void Int_Array::not_more_than_size(unsigned index) 
	{
		if (index <= current_size)return;
		throw Bad_Index(index);
	};

	/***********************************************************/
	/*                         Constructors 	               */
	/***********************************************************/

	Int_Array::Int_Array() {};

	Int_Array::Int_Array(unsigned number, int value)	// replication
	{
		data = new int[number];
		current_size = number;
		for (unsigned i = 0; i < number; i++)data[i] = value;
	};

	Int_Array::Int_Array(unsigned number, const int* a)		// array data
	{
		data = new int[number];
		current_size = number;
		for (unsigned i = 0; i < number; i++)data[i] = a[i];
	};

	Int_Array::Int_Array(const Int_Array& source)		// copy constructor
	{
 		current_size = source.current_size;
		data = new int[current_size];
		for (unsigned i = 0; i < current_size; i++)data[i] = source.data[i];
	};

	Int_Array::~Int_Array() 
	{ 
		delete data; 
	};
		
	/***********************************************************/
	/*                 Main Methods and Operations             */
	/***********************************************************/

	int& Int_Array::operator [] (unsigned index) 
	{
		less_than_size(index);
		return data[index];
	};

	/***********************************************************/

	unsigned Int_Array::size() { return current_size; };

	/***********************************************************/

	Int_Array& Int_Array::operator=(const Int_Array& source)	// assignment
	{
		unsigned new_size = source.current_size;
		int* new_data = new int[new_size];
		for (unsigned i = 0; i < new_size; i++)new_data[i] = source.data[i];
		delete data;
		data = new_data;
		current_size = new_size;
		return *this;
	};

	/***********************************************************/
	/*                   Extension Methods     	               */
	/***********************************************************/

	void Int_Array::insert(unsigned index, int value)			// insertion
	{
		unsigned j;
		not_more_than_size(index);
		unsigned new_size = current_size + 1;
		int* new_data = new int[new_size];
		for (unsigned i = 0; i < index; i++)new_data[i] = data[i];
		if(index < new_size)new_data[index] = value;
		for (unsigned i = index; i < current_size; i++) 
		{ 
			j = i + 1;
			if (j < new_size)new_data[j] = data[i];
		};
		current_size = new_size;
		delete[] data;
		data = new_data;
	};

	/***********************************************************/

	void Int_Array::replicate(unsigned index, unsigned number, int value) // replication
	{
		not_more_than_size(index);
		unsigned new_size = current_size + number;
		unsigned limit = index + number;
		int* new_data = new int[new_size];

		for (unsigned i = 0; i < index; i++)			// old part
		{ 
			if (i < new_size)new_data[i] = data[i];
		};
		for (unsigned i = index; i < limit; i++)		// new sequence
		{ 
			if(i < new_size)new_data[i] = value; 
		};
		for (unsigned i = index; i < current_size; i++) // remaining part
		{ 
			new_data[i + number] = data[i]; 
		};
		current_size = new_size;
		delete[] data;
		data = new_data;
	};

	/***********************************************************/

	void Int_Array::insert(unsigned index, const Int_Array& array) 	// insert Int_Array
	{
		not_more_than_size(index);
		unsigned number = array.current_size;
		unsigned new_size = current_size + number;
		unsigned limit = index + number;
		int* new_data = new int[new_size];

		for (unsigned i = 0; i < index; i++)			// old part
		{ 
			if (i < new_size)new_data[i] = data[i];
		};
		for (unsigned i = index; i < limit; i++)		// new sequence
		{
			if(i < new_size)new_data[i] = array.data[i - index];
		};
		for (unsigned i = index; i < current_size; i++) // remaining part
		{ 
			new_data[i + number] = data[i];
		};
		current_size = new_size;
		delete[] data;
		data = new_data;
	};


	/***********************************************************/

	Int_Array& Int_Array::operator += (const Int_Array& source)
	{
		insert(size(), source);
		return *this;
	};

	/***********************************************************/
	/*                     Reducing Methods   	               */
	/***********************************************************/

	int Int_Array::remove(unsigned index)						// removal
	{
		not_more_than_size(index);
		int value = data[index];
		unsigned new_size = current_size - 1;
		int* new_data = new int[new_size];
		for (unsigned i = 0; i < index; i++) 
		{ 
			if (i < new_size)new_data[i] = data[i];
		};
		for (unsigned i = index; i < current_size; i++) 
		{ 
			if(i < new_size)new_data[i] = data[i + 1]; 
		};
		current_size = new_size;
		delete[] data;
		data = new_data;
		return value;
	};

	/***********************************************************/

	void Int_Array::remove(unsigned index, unsigned number)	// remove a sequence
	{
		not_more_than_size(index);
		if (index + number > current_size)number = current_size - index;
		unsigned new_size = current_size - number;
		int* new_data = new int[new_size];
		for (unsigned i = 0; i < index; i++) 
		{ 
			if(i < new_size)new_data[i] = data[i]; 
		};
		for (unsigned i = index + number; i < current_size; i++)
		{
			new_data[i - number] = data[i];
		};
		current_size = new_size;
		delete[] data;
		data = new_data;
	};

	/***********************************************************/

	void Int_Array::remove_from(unsigned index)	 // cut off method
	{
		remove(index, size() - index);
	};

	/***********************************************************/

	void Int_Array::clear() // clear container
	{
		delete[] data;
		current_size = 0;
	};

	/***********************************************************/
	/*                         Handling      	               */
	/***********************************************************/

	void Int_Array_Handler::handle(Int_Array& a, unsigned n) {};

	bool Int_Array_Handler::condition(Int_Array& a, unsigned n) { return false; };

	unsigned Int_Array::apply(unsigned index, Int_Array_Handler& handler)
	{
		for (unsigned i = index; i < current_size; i++) 
		{
			if (handler.condition(*this, i))return i;
			handler.handle(*this, i);
		};
		return current_size;
	};

	/***********************************************************/

	unsigned Int_Array::apply(Int_Array_Handler& handler)	// apply from the start
	{ 
		return apply(0, handler);
	};

	/***********************************************************/

	class Searcher : public Int_Array_Handler 
	{
	private:
		int value;

	public:
		bool condition(Int_Array& array, unsigned n)
		{
			return(array[n] == value);
		};

		Searcher(int to_find) : value(to_find) {};
	};

	/***********************************************************/

	bool Int_Array::found(int value, unsigned index, unsigned* n)
	{
		Searcher seracher(value);
		*n = apply(index, seracher);
		if (*n < size())return true;
		return false;
	};

	bool Int_Array::found(int value, unsigned* n) { return found(value, 0, n); };

	/***********************************************************/
	/*                   Function Operators    	               */
	/***********************************************************/

	ostream& operator << (ostream& output, const Int_Array& a)
	{
		for (unsigned i = 0; i < a.current_size; i++)cout << a.data[i] << " ";
		return output;
	};

	/***********************************************************/

	
	