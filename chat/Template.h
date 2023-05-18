#pragma once
#include <fstream>
#include <iostream>
#include "NewExceptions.h"

template<class Type>
class Array {

	template <class V>
	class Iterator {
		friend class Array<Type>;
	public:

		Iterator<V>(const Iterator<V>& it) : m_item(it.m_item) {}

		bool operator==(const Iterator<V>& _it) {
			return m_item == _it.m_item;
		}
		bool operator!=(const Iterator<V>& _it) {
			return m_item != _it.m_item;
		}
		Iterator& operator++() {
			m_item++;
			return *this;
		}
		V& operator*() {
			return *m_item;
		}

	private:
		Type* m_item{};

		explicit Iterator(Type* p) : m_item(p) {}
	};

	typedef Iterator<Type> iterator;
	typedef Iterator<Type> const_iterator;

public:

	iterator begin() {
		return iterator(m_array);
	}
	const_iterator begin() const {
		return const_iterator(m_array);
	}

	iterator end() {
		return iterator(m_end);
	}
	const_iterator end() const {
		return const_iterator(m_end);
	}

	Type& operator[](size_t index) {
		return m_array[index];
	}

	size_t getCapacity() { return m_capacity; }
	size_t getSize() { return m_size; }

	Array() {
		m_array = new Type[1];

		m_capacity = 1;
	}

	void increaseEnd(int amount) {
		m_end = m_array + amount;
	}

	void addMemory() {
		try {
			m_capacity *= 2;

			Type* tmp = m_array;

			m_array = new Type[m_capacity];
			for (size_t i = 0; i < m_size; ++i) {
				m_array[i] = tmp[i];
			}
			delete[] tmp;
		}
		catch (std::bad_alloc ba) {
			std::cerr << ba.what() << std::endl;
		}

	}

	void pushBack(const Type& object) {
		if (m_size == m_capacity) addMemory();
		m_array[m_size++] = object;
	}

	void indexPushBack(const Type& object, int index) {
		try {
			if (index < 0 || index > m_size) {
				throw bad_index();
			}

			if (m_size == m_capacity) addMemory();
			m_size++;

			Type* tmp = m_array;
			m_array = new Type[m_capacity];

			if (index == 1) {
				m_array[0] = object;
				for (size_t i = 1; i < m_size; ++i) {
					m_array[i] = tmp[i - 1];
				}
			}

			if (index > 1) {
				for (size_t i = 0; i < index - 1; i++) {
					m_array[i] = tmp[i];
				}

				m_array[index - 1] = object;

				for (size_t i = index; i < m_size; i++) {
					m_array[i] = tmp[i - 1];
				}
			}
			delete[] tmp;
		}
		catch (std::exception& e) {
			std::cout << e.what() << '\n';
			system("pause");
			return;
		}
	}

	void remove(size_t index) {
		if (index > m_size)
			throw std::out_of_range("This index is out of range!\n");
		for (size_t i = index; i < m_size; ++i) {
			m_array[i - 1] = m_array[i];
		}

		--m_size;
	}

	void erase() {
		delete[] m_array;

		m_size = 0;
		m_capacity = 1;

		m_array = new Type[1];
		m_end = m_array;

	}

	friend std::ostream& operator<<(std::ostream& out, const Array<Type> obj) {
		for (int i = 0; i < obj.m_size; i++) {
			out << obj.m_array[i];
		}
		out << '\n';

		return out;
	}


	void write_on_file(std::string filename) {

		std::ofstream out(filename);
		//out.open(filename);

		if (out.is_open()) {
			for (int i = 0; i < m_size; i++) {
				out << m_array[i];
			}
		}
		out.close();
	}

	void write_on_file(std::string filename, Type& obj) {
		std::ofstream out(filename, std::ios::app);

		if (out.is_open()) {
			out << obj;
		}
	}

	void read_from_file(std::string filename) {
		
		std::ifstream in(filename, std::ios::in);
		erase();

		if (in.is_open()) {
			Type obj;

			while (in >> obj) {
				if (m_size == m_capacity) addMemory();
				m_array[m_size++] = obj;
			}
		}


		in.close();
		
	}

private:
	Type* m_array{};
	Type* m_end{};

	size_t m_capacity{};
	size_t m_size{};
};