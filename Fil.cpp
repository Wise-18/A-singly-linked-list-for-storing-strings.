#include <iostream>
#include <string>

using namespace std;

//узел списка
struct Node {
	string str; //строка
	Node* next; //указатель на след. узел

	//конструктор
	Node(string str) {
		this->str = str;
		next = nullptr;
	}
};

//односвязный список хранящий строки
class List {
private:
	Node* head; //голова списка
	int size; //размер списка

public:

	//конструктор
	List() {
		head = nullptr;
		size = 0;
	}

	//размер списка
	int getSize() const {
		return size;
	}

	//добавление данных по номеру
	void insert(string str, int i) {
		if (i >= 0 && i < size) {
			Node* t = new Node(str);

			//нехватка памяти
			if (!t) {
				throw exception("Exception: bad alloc");
			}

			//вставка в начало списка
			if (i == 0) {
				t->next = head;
				head = t;
			}
			else {
				Node* prev = head;
				Node* cur = head;
				while (cur->next && i > 0) {
					i--;
					prev = cur;
					cur = cur->next;
				}
				t->next = prev->next;
				prev->next = t;
			}
		}

		//заполняем голову
		else if (!head && i == 0) {
			head = new Node(str);
		}
		else {

			//вышли за диапазон допустимых значений
			throw exception("Exception: out of range");
		}
		size++;
	}

	//удаление данных по номеру
	void remove(int i) {
		if (i >= 0 && i < size) {
			Node* c = nullptr;

			//удаляем голову
			if (i == 0) {
				c = head;
				head = head->next;
				delete c;
			}
			else {
				Node* prev = head;
				Node* cur = head;
				while (cur->next && i > 0) {
					i--;
					prev = cur;
					cur = cur->next;
				}
				prev->next = cur->next;
				delete cur;
			}
			size--;
		}
		else throw exception("Exception: out of range");
	}

	//вывод списка
	void print() const {
		if (!head) {
			cout << "list is empty" << endl;
		}
		else {
			Node* cur = head;
			while (cur) {
				cout << cur->str << endl;
				cur = cur->next;
			}
			cout << "size = " << getSize() << endl;
		}
	}

	//полная очистка списка
	void clear() {
		while (head) {
			Node* cur = head;
			head = head->next;
			delete cur;
		}
		head = nullptr;
		size = 0;
	}

	//деструктор
	~List() {
		clear();
	}
};

//ввод номера
int getIndex() {
	string index;
	cout << "enter index: ";
	getline(cin, index);
	return index[0] - '0';
}

//тест класса
int main() {
	string str;
	char ch;
	List list;
	do {
		try {
			cout << "1 - insert string" << endl;
			cout << "2 - remove string" << endl;
			cout << "3 - print list" << endl;
			cout << "4 - clear list" << endl;
			cout << "5 - exit" << endl;
			cout << ">> ";
			getline(cin, str);
			ch = str[0] - '0';
			if (ch < 1 || ch > 5)
				throw exception("Exception: invalid number");
			switch (ch) {
			case 1: {

				//вставка по номеру
				int i = getIndex();
				cout << "enter string -> ";
				getline(cin, str);
				list.insert(str, i);
				break;
			}
			case 2: {

				//удаление по номеру
				int i = getIndex();
				list.remove(i);
				break;
			}
			case 3: {

				//вывод списка на экран
				list.print();
				break;
			}
			case 4: {

				//очистка списка
				list.clear();
				cout << "list is empty" << endl;
				break;
			}
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
		cout << endl;
	} while (ch != 5);
	cout << endl;
	system("pause");
	return 0;
}