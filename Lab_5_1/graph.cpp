#include <iostream>
#include <syncstream>
#include<thread>
#include <windows.h>
#include<latch>

using namespace std;

latch done_a_latch(5);
latch done_b_latch(2);
latch done_c_latch(4);
latch done_d_latch(4);

void f(char set, int action)
{
	osyncstream(cout) << "З набору " << set << " виконано дію " << action << "." << endl;
}

void thread1() {
	f('a', 1);
	done_a_latch.count_down();
	done_a_latch.wait();
	f('b', 1);
	f('b', 3);
	f('c', 5);
	done_b_latch.count_down();
	done_b_latch.wait();
	f('e', 2);
	done_c_latch.count_down();
	done_c_latch.wait();
	f('f', 2);
	f('f', 8);
	f('g', 6);
	done_d_latch.wait();
	f('h', 4);
	f('i', 3);
	
}

void thread2() {
	f('a', 2);
	done_a_latch.count_down();
	done_a_latch.wait();
	f('c', 1);
	f('c', 3);
	f('d', 5);
	done_b_latch.wait();
	f('e', 3);
	done_c_latch.count_down();
	done_c_latch.wait();
	f('f', 3);
	f('f', 9);
	f('g', 7);
	done_d_latch.count_down();
	done_d_latch.wait();
	f('h', 5);
	f('i', 4);

}

void thread3() {
	f('a', 3);
	done_a_latch.count_down();
	done_a_latch.wait();
	f('d', 1);
	f('d', 3);
	f('c', 6);
	done_b_latch.wait();
	f('e', 4);
	done_c_latch.count_down();
	done_c_latch.wait();
	f('f', 4);
	f('g', 1);
	f('g', 8);
	done_d_latch.count_down();
	done_d_latch.wait();
	f('h', 6);
	f('i', 5);
}

void thread4() {
	f('a', 4);
	done_a_latch.count_down();
	done_a_latch.wait();
	f('b', 2);
	f('b', 4);
	f('d', 6);
	done_b_latch.count_down();
	done_b_latch.wait();
	f('e', 5);
	done_c_latch.wait();
	f('f', 5);
	f('g', 2);
	done_d_latch.count_down();
	done_d_latch.wait();
	f('h', 1);
	f('h', 7);
}

void thread5() {
	f('a', 5);
	done_a_latch.count_down();
	done_a_latch.wait();
	f('c', 2);
	f('c', 4);
	f('c', 7);
	done_b_latch.wait();
	done_c_latch.count_down();
	done_c_latch.wait();
	f('f', 6);
	f('g', 3);
	f('g', 4);
	done_d_latch.wait();
	f('h', 2);
	f('i', 1);
}

void thread6() {
	done_a_latch.wait();
	f('d', 2);
	f('d', 4);
	done_b_latch.wait();
	f('e', 1);
	done_c_latch.wait();
	f('f', 1);
	f('f', 7);
	f('g', 5);
	done_d_latch.count_down();
	done_d_latch.wait();
	f('h', 3);
	f('i', 2);

}

int main()
{
	SetConsoleOutputCP(1251);
	cout << "Обчислення розпочато." << endl;
	thread t1(thread1);
	thread t2(thread2);
	thread t3(thread3);
	thread t4(thread4);
	thread t5(thread5);
	thread t6(thread6);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	cout << "Обчислення завершено." << endl;
}