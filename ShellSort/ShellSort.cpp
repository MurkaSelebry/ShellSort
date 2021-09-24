#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;
int Step(vector<int>&, int);
template<typename T>
void Sort(vector <T>&);
template<typename T>
void PrintArray(vector <T>);
template<typename T>
void Random(vector<T>&);
int main()
{
    vector<int> arr(16);
    Random(arr);
    PrintArray(arr);//печатаем рандомный массив (исходный)
    Sort(arr);
    PrintArray(arr);//печатаем отсортированный массив
}
/// <summary>
/// Функция сортировки методом Шелла с использование проходов по методу Седжвика
/// </summary>
/// <typeparam name="T">Данный шаблон, а именно T поможет нам 
/// работать с различными видами массивов (int,double и т.д.)</typeparam>
/// <param name="Array">В параметрах получаем ссылку на массив, чтобы его отсортировать</param>
template<typename T>
void Sort(vector <T>& arr) {
    vector<int> interval_arr;//массив интервалов будет служить нам для уменьшения прохода между элементами
    //к примеру, если длина массива 16, то будет 1 и 5, сначала мы будем использовать 5, а потом 1
    int interval;
    int c = Step(interval_arr, arr.size());
    //Вызываем функцию для вычисления массива интервалов под заданный размер
    //возьмем то же число 16, в итоге counter будет равно 1
    //(длина массива 2, но мы уменьшаем на 1, чтобы удобнее было работать с циклом)
    while (c >= 0) {
        interval = interval_arr[c--];//уменьшаем интервал по мере прохода массива
        for (int i = interval; i < arr.size(); i++) {
        //цикл для перебора элементов, начиная с интервала
            int j;
            T t = arr[i];//приравниваем к t значение начиная от интервала, увеличивающася с каждой итерацией
            // на этом моменте начинается знакомая нам сортировка вставками,
            //только вот со своеобразным свапом элементов 
            for (j = i - interval; j >= 0 && arr[j] > t; j -= interval)
                arr[j + interval] = arr[j];
            arr[j+interval] = t;//записываем t на место последнего перемещаемого элемента      
        }
    }
}
/// <summary>
/// Функция определения шага или прохода по методу Седжвика по таким формулам:
/// d(четн)=9*2^i-9*2^(i/2)+1
/// d(нечетн)=8*2^i-6*2^((i+1)/2)+1
/// ПРИ ЭТОМ: size/3>d
/// </summary>
/// <param name="Interval">Получаем ссылку на массив интервалов,
///  чтобы его заполнить</param>
/// <param name="Size of Array">Получаем размер массива,
///  которого надо отсортировать, чтобы соотвествовать условию Седжвика</param>
/// <returns>Возвращаем длину массива интервалов</returns>
int Step(vector<int>& s, int size) {
    int c = -1;
    do {
        if (++c % 2 == 0) s.push_back(9 * pow(2, c) - 9 * pow(2, c / 2) + 1);
        else s.push_back(8 * pow(2, c) - 6 * pow(2, (c + 1) / 2) + 1);
    } while (3 * s[c] < size);
    return --c;
}
/// <summary>
/// Просто шаблонная функция печати массива
/// </summary>
/// <typeparam name="T">Получаем тип данных массива для печати</typeparam>
/// <param name="Array for Print">Получаем массив для печати</param>
template<typename T>
void PrintArray(vector <T> arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}
/// <summary>
/// Функция, которая заполняет массив рандомными(случайными) элементами
/// </summary>
/// <typeparam name="T">Получаем тип данных массива для заполнения</typeparam>
/// <param name="Array for Random">Получаем массив для заполнения</param>
template<typename T>
void Random(vector<T>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % 2001 - 1000;
    }
}
