	#pragma once
	/***********************************************************/
	/*                         Int_Array	 	               */
	/***********************************************************/

	#include <iostream>
	#include <exception>

	using namespace std;

	/***********************************************************/
/*
	excepton class
*/
	class Bad_Index : public exception
	{
	public:

		Bad_Index(unsigned index);

		unsigned value();

		virtual const char* what() const noexcept override;

	private:
		unsigned bad_index;
		const char* text = nullptr;
	};

	/***********************************************************/

	class Int_Array;
/*
	handler class
*/
	class Int_Array_Handler
	{
	public:
		virtual void handle(Int_Array& a, unsigned n);
		virtual bool condition(Int_Array& a, unsigned n);
	};

	/***********************************************************/

	class Int_Array
	{
	public:
/*
	constructors and destructors
*/
		Int_Array();								// empty container

		Int_Array(unsigned number, int value);		// fill with replicated value

		Int_Array(unsigned number, const int* a);	// fill with array elements

		Int_Array(const Int_Array& source);			// copy constructor

		virtual ~Int_Array();						// destructor
/*
	assignment operator
*/
		Int_Array& operator = (const Int_Array& source);	// assignment
/*
	container main methods and operations
*/
		unsigned size();								// current container size

		int& operator [] (unsigned index);				// element access
/*
	container extension methods
*/
		void insert(unsigned index, int value);			// insertion

		void replicate(unsigned index, unsigned number, int value);	// replication

		void insert(unsigned index, const Int_Array& array);		// include Int_Array

		Int_Array& operator += (const Int_Array& source);	// concatenation
/*
	container reducing methods
*/
		int remove(unsigned index);						// removal

		void remove(unsigned index, unsigned number);	// remove a sequence

		void remove_from(unsigned index);				// cut off method

		void clear();									// clear method
/*
	container handling methods
*/
	unsigned apply(unsigned index, Int_Array_Handler& handler);	

	unsigned apply(Int_Array_Handler& handler);

	bool found(int value, unsigned index, unsigned* n);

	bool found(int value, unsigned* n);
/*
	friend operators
*/
	friend ostream& operator << (ostream& output, const Int_Array& a);

	private:
		
		unsigned current_size = 0;						// current size
		int* data = nullptr;

		void less_than_size(unsigned index);

		void not_more_than_size(unsigned index);
	};

	/***********************************************************/
	/*                    Binary Operators    	               */
	/***********************************************************/

	ostream& operator << (ostream& output, const Int_Array& a);

	/***********************************************************/


