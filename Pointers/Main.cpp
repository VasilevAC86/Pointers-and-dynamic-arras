# include <iostream>
#include<cstdlib>
#include<ctime>

// Блок прототипов функций
double* memory_Selection(short size); // Выделение памяти под динамический массив
void array_Filling(double* pointer, short size); // Заполнение массива случайными числами из выбранного пользователем диапазона
template<typename T>
void array_Print(T* pointer, short size); // Шаблонная процедура вывода массива в консоль
template<typename T>
void memory_Clearing(T* pointer); // Шаблонная процедура очистки памяти от массива
void array_Resize(double*& pointer, short& size, short resize); // Изменение массива
void memory_Clearing_Matrix(short** pointer, short size); // Процедура очистки памяти от динамической матрицы

int main() {

	// Задача 1. 5 функций для работы с указателем
	std::cout << "\033[91mTask 1. 5 functions for working with a pointer\033[0m\n\n";
	double* pointer; // Объявляем указатель на будущий массив
	short size, resize; // Переменные для хранения размера массива и величины, на которую изменяется размер массива
	char my_Choise='0'; // Переменная для хранения выбора пользователя
	std::cout << "Enter array's size = ";
	std::cin >> size;
	while (size < 1) { // Цикл проверки введённого пользователем размера массива
		std::cout << "Input error! The array's size cannot be less than 1!\nEnter array's size = ";
		std::cin >> size;
	}
	pointer = memory_Selection(size); // Инициализируем указатель на динамический массив результатом функции memory_Selection
	array_Filling(pointer, size);
	std::cout << "\n\033[93mSource array consists of the following elements: \033[0m\n";
	array_Print(pointer, size);	
	while (my_Choise != '1') { // Цикл запроса у пользователя потребности в изменении размера массива
		std::cout << "\n\033[93mDo you want to change the array's size?\nPress '1' if you don't want to change the array's size \033[91m\033[4mor\033[0m\033[93m press any other key if you want to change the array's size\nYour choise \033[0m-> ";
		std::cin >> my_Choise;
		if (my_Choise == '1') { //Если пользователь не хочет менять размер массива, то
			std::cout << "\n\033[92mFinal array consist of the following elements: \033[0m\n\n";
			array_Print(pointer, size);
			break; // прекращаем бесконечный цикл
		}
		else {
			std::cout << "\nEnter a number to resize the array -> ";
			std::cin >> resize;
			while (resize < 0 && abs(resize) >= size) { // Цикл проверки числа на которое изменяется размер массива
				std::cout << "The size of final array cannot be less 1!\nEnter a number to resize the array one more time -> ";
				std::cin >> resize;
			}
			array_Resize(pointer, size, resize);
			std::cout << "\n\033[93mArray consist of the following elements: \033[0m\n";
			array_Print(pointer, size); // Печатаем новый массив, учитывая, что переменная size изменена в array_Resize
		}
	}
	memory_Clearing(pointer); // Чистим память от динамического массива
	pointer = nullptr; // Перенапрявляем указатель на нейтральное значение

	// Задача 2. Логический массив из динамической матрицы
	std::cout << "\n\033[91mTask 2. Logical array from dynamic matrix\033[0m\n\nEnter the number of rows = ";
	short rows, cols; 
	std::cin >> rows;
	std::cout << "Enter the number of cols = ";
	std::cin >> cols;
	short** dmx = new short* [rows]; // Выделяем память под одномерный массив указателей
	for (short i = 0; i < rows; i++) // Цикл выделения памяти под одномерный массив каждому указателю
		dmx[i] = new short[cols];
	std::cout << std::endl;
	for (short i = 0; i < rows; i++) // Цикл заполнения динамического массива данными
		for (short j = 0; j < cols; j++) {
			std::cout << "Enter array element N [" << i << ", " << j << "] = ";
			std::cin >> dmx[i][j];
		}
	std::cout << "\n\033[93mSource array consists of the following elements: \033[0m\n\n";
	for (short i = 0; i < rows; i++) {
		std::cout << "{ ";
		for (short j = 0; j < cols; j++) 
			std::cout << dmx[i][j] << "\t";
		std::cout << "\b\b\b\b\b\b\b }" << std::endl;
	}
	bool* arr = new bool[cols]; // Выделяем память под динамический логический массив
	for (short j = 0; j < cols; j++) { // Цикл заполнения логического массива arr 
		bool key_Mistake = true; // Переменная для хранения кода ошибки
		for (short i = 0; i < rows / 2; i++) { // Цикл проверки элементов в текущем столбце матрицы dmx
			if (dmx[i][j] != dmx[rows - i - 1][j]) {
				key_Mistake = false;
				break;
			}
		}
		if (key_Mistake)
			arr[j] = true;
		else
			arr[j] = false;
	}
	std::cout << "\n\033[92mThe logical array consists of the following elements: \033[0m\n";
	memory_Clearing_Matrix(dmx, rows); // Чистим память от динамической матрицы
	std::cout.setf(std::ios_base::boolalpha);
	std::cout << std::endl;
	array_Print(arr, cols); 
	memory_Clearing(arr); // Чистим память от логического массива

	return 0;
}

double* memory_Selection(short size) {
	return new double[size]; // Выделяем область динамической памяти под массив размером size
}

void array_Filling(double* pointer, short size) {
	double start, end; // Переменные для хранения начала и конца диапазона чисел для заполнения массива
	std::cout << "\nEnter a range of numbers to fill the array:\nEnter the start of the array = ";
	std::cin >> start;
	std::cout << "Enter the end of the range = ";
	std::cin >> end;
	while (end <= start) { // Цикл проверки диапазона 
		std::cout << "Input error! The end of the range cannot be less than the beginning!\nEnter the start of the range = ";
		std::cin >> start;
		std::cout << "Enter the end of the range = ";
		std::cin >> end;
	}
	srand(time(NULL));
	for (short i = 0; i < size; i++) {
		*pointer = rand() * (end - start) / RAND_MAX + start; // В область памяти, на которую указывает pointer, записываем случайное вещественное число
		pointer++; // Указатель смещаем на кол-во ячеек памяти, соответствующее типу double
	}
}

template<typename T>
void array_Print(T* pointer, short size) {
	std::cout << "{ ";
	for (short i = 0; i < size; i++) {
		std::cout << *pointer << ", ";
		pointer++; // Указатель смещаем на область памяти, где хранится следующий элемент динамического массива 
	}
	std::cout << "\b\b }\n";
}

template<typename T>
void memory_Clearing(T* pointer) {
	delete[] pointer;
}

void array_Resize(double*& pointer, short& size, short resize) {	
	short length = size + resize;
	double* tmp = new double[length]; // Выделяем память под новый динамический массив
	for (short i = 0; i < length; i++) { // Цикл заполнения области памяти, выденной под новый массив, предыдущим массивом
		if (i < size) 
			tmp[i] = pointer[i];					
		else
			tmp[i] = i - size;					
	}
	memory_Clearing(pointer); // Чистим область памяти, занятую предыдущим массивом
	pointer = tmp; // Указатель pointer перенапрявляем с очищенной области памяти на новую область памяти, указатель tmp удалиться после зевершения работы процедуры
	size = length; // Изменяем длину массива во всей программе
}

void memory_Clearing_Matrix(short** pointer, short size) {
	for (short i = 0; i < size; i++)
		delete[] pointer[i];
	delete[] pointer;
}