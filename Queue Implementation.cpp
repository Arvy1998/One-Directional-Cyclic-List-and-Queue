#include <iostream>
#include <cstdlib>
#include <fstream>

#define MAX_SIZE 99

using namespace std;

ofstream rezultatai;

class Queue {
private:
	int item[MAX_SIZE];
	int rear;
	int front;
public:
	Queue();
	void enqueue(int);
	int dequeue();
	int size();
	void first_display();
	void result_display();
	bool isEmpty();
	bool isFull();
};

Queue::Queue() {
	rear = -1;
	front = 0;
}

void Queue::enqueue(int data) {
	item[++rear] = data;
}

int Queue::dequeue() {
	return item[front++];
}

void Queue::first_display() {
	cout << "Seka pries pasikeitimus: " << endl;
	rezultatai << "Seka pries pasikeitimus: " << endl;
	if (!this->isEmpty()) {
		for (int i = front; i <= rear; i++) {
			cout << item[i] << " ";
			rezultatai << item[i] << " ";
		}
		rezultatai << endl;
		cout << endl;
	}
	else {
		cout << "Queue Underflow" << endl;
		rezultatai << "Queue Underflow" << endl;
		rezultatai << endl;
	}
}

void Queue::result_display() {
	cout << "Seka po pasikeitimu: " << endl;
	rezultatai << "Seka po pasikeitimu: " << endl;
	if (!this->isEmpty()) {
		for (int i = front; i <= rear; i++) {
			cout << item[i] << " ";
			rezultatai << item[i] << " ";
		}
		rezultatai << endl;
		cout << endl;
	}
	else {
		cout << "Queue Underflow" << endl;
		rezultatai << "Queue Underflow" << endl;
		rezultatai << endl;
	}
}

int Queue::size() {
	return (rear - front + 1);
}

bool Queue::isEmpty() {
	if (front>rear) {
		return true;
	}
	else {
		return false;
	}
}

bool Queue::isFull() {
	if (this->size() >= MAX_SIZE) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	Queue queue;
	int choice, data;
	ifstream duomenys;
	duomenys.open("duom.txt", ios::out);
	if (duomenys.is_open()) {
		while (!duomenys.eof() && !queue.isFull() && !duomenys.fail() && !duomenys.bad()) {
			duomenys >> data;
			queue.enqueue(data);
		}
		duomenys.close();
	}
	queue.first_display();
	rezultatai.open("rez.txt", ios::in);
	while (1) {
		cout << "\n1. Enqueue\n2. Dequeue\n3. Size\n4. Quit";
		cout << "\nEnter your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			if (rezultatai.good()) {
				if (!queue.isFull()) {
					cout << "\nEnter data: ";
					cin >> data;
					queue.enqueue(data);
					queue.result_display();
				}
				else {
					cout << "Queue is Full" << endl;
					rezultatai << "Queue is Full" << endl;
				}
			}
			break;
		case 2:
			if (rezultatai.good()) {
				if (!queue.isEmpty()) {
					cout << "The data dequeued is :" << queue.dequeue();
					rezultatai << "The data dequeued is :" << queue.dequeue();
					queue.result_display();
				}
				else {
					cout << "Queue is Empty" << endl;
					rezultatai << "Queue is Empty" << endl;
				}
			}
			break;
		case 3:
			if (rezultatai.good()) {
				cout << "Size of Queue is " << queue.size();
				rezultatai << "Size of Queue is " << queue.size();
			}
			break;
		case 4:
			exit(0);
			break;
		}
	}
	rezultatai.close();
	return 0;
}
