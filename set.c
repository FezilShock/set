#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OFFSET 127

// создаем структуру для ноды
typedef struct n
{
    double val;     // переменная для хранения содержимого ноды
    struct n *next; // указатель на следующую ноду
} node;

// объявляем структуру для множества
typedef struct
{
    node *first_node; // указатель на первую ноду множества
    node *now;        // указатель на
    int size;         // переменная для хранения количества элементов
} set;

/**
 * Функция выделяет память под новую ноду и возвращает указатель на неё.
 * Параметр `val` используется для записи значения в ноду
 */
node *create_node(double val)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

// Функция выделяет память под множество и возвращает указатель на множество
set *createSet(void)
{
    set *new_set = (set *)malloc(sizeof(set));
    new_set->first_node = NULL;
    new_set->size = 0;
    return new_set;
}

/*
 * Функция для проверки существования элемента
 * Возвращает NULL, если элемент не найден
 */
bool setSearch(set *set, double var)
{
    if (set->size)
    {
        node *curNode = set->first_node;
        while (curNode != NULL)
        {
            if (curNode->val == var)
                return curNode;
            curNode = curNode->next;
        }
        return NULL;
    }
    else
        return NULL;
}

/*
 * Функция добавления элементов в множество
 * Возвращает 0 если был записан хотя бы один элемент
 * Иначе возвращает -1
 * Параметр `set` - указатель на множество
 */
void setPush(set *set)
{
    double new_var;
    char ch;
    char res = 0;
    res = scanf("%lf", &new_var);
    if (set->first_node == NULL)
    {
        node *tmp = create_node(new_var);
        set->first_node = tmp;
        set->now = tmp;
        ++set->size;
    }
    else
    {
        if (!setSearch(set, new_var))
        {
            node *tmp = create_node(new_var);
            set->now->next = tmp;
            set->now = tmp;
            ++set->size;
        }
    }
}

/*
 * Функция вывода массива
 * Через пробел выводит все элементы множества
 * Параметр `set` - указатель на множество
 */
void setOutput(set *set)
{
    if (set->size)
    {
        node *curNode = set->first_node;
        while (curNode != NULL)
        {
            printf("%-13.3f ", curNode->val);
            curNode = curNode->next;
        }
    }
    else
    {
        printf("Пустое множество");
    }
    putchar('\n');
}

/*
 * Функция вывода бинарного массива
 * Через пробел выводит все элементы бинарного множества
 * Параметр `set` - указатель на множество
 */
void setOutput2(set *set)
{
    node *curNode = set->first_node;
    while (curNode != NULL)
    {
        printf("%017lld ", (long long)curNode->val);
        curNode = curNode->next;
    }
    putchar('\n');
}

/*
 * Функция получения дробной части
 * Параметр `a` - число с плавающей точкой
 * Возвращает дробную часть числа с плавающей точкой
 */
double getfract(double a)
{
    if (a >= 0)
    {
        int b = (int)a;
        return (a - b);
    }
    else
    {
        int b = (int)a;
        return (b - a);
    }
}

/*
 * Функция перевода целой части
 * Параметр `val` - целая часть числа
 * Возвращает двоичное представление целой части числа
 */
double intconvert(int val)
{
    double res = 0;
    long j = 1;
    while (val > 0)
    {
        res += (val % 2) * j;
        val /= 2;
        j *= 10;
    }
    return res;
}

/*
 * Функция перевода дробной части числа
 * Параметр `val` - число с плавающей точкой
 * Возвращает двоичное представление дробной части числа с точностью в 4 цифры
 */
double fractconvert(double val)
{
    val = getfract(val);
    double fract_res = 0;
    double k = 1;
    for (int j = 4; j > 0; j--)
    {
        fract_res += (int)val * k;
        if ((int)val >= 1)
            val -= 1;
        val *= 2;
        k /= 10;
    }
    return fract_res;
}

/*
 * Функция перевода числа в двоичное представление
 * Параметр `val` - число с плавающей точкой
 * Возвращает двоичное представление числа
 */
double convert(double val)
{
    long total;
    if (val > 0)
    {
        double res = intconvert(val);         // получаем целую часть числа
        double fract_res = fractconvert(val); // получаем дробную часть  числа
        res += fract_res;                     // складываем их
        short power = 0;                      // переменная для хранения степени
        // приводим число в экспоненциальный нормализованный вид
        if (res > 1)
        {
            while ((int)res > 1)
            {
                res *= 0.1;
                power++;
            }
        }
        else
        {
            while ((int)res < 1)
            {
                res *= 10;
                power--;
            }
        }
        res -= 1;                           // откидываем неявную единицу у мантиссы
        power += OFFSET;                       // смещаем степень экспоненты
        long powerres = intconvert(power);   // переводим степень экспоненты в двоичное представление
        total = powerres * 1e8 + res * 1e8; // складывает мантиссу и экспоненту
    }
    else if (val == 0)
    {
        total = 0;
    }
    else
    {
        val = -val;
        double res = intconvert(val);          // получаем целую часть числа
        double fract_res = fractconvert(val); // получаем дробную часть  числа
        res += fract_res;                     // складываем их
        short power = 0;                      // переменная для хранения степени
        // приводим число в экспоненциальный нормализованный вид
        if (res > 1)
        {
            while ((int)res > 1)
            {
                res *= 0.1;
                power++;
            }
        }
        else
        {
            while ((int)res < 1)
            {
                res *= 10;
                power--;
            }
        }
        res -= 1;                                  // откидываем неявную единицу у мантиссы
        power += OFFSET;                              // смещаем степень экспоненты
        long powerres = intconvert(power);          // переводим степень экспоненты в двоичное представление
        total = 1e16 + powerres * 1e8 + res * 1e8; // складывает мантиссу и экспоненту, добавляем 1 как последний бит
    }
    return total;
}

/*
 * Функция заполнения двоичного множества
 * Параметр `main_set` - указатель на исходное множество
 * Параметр `bin_set` - указатель на массив с числами в двоичном представлении
 */
void binconvert(set *main_set, set *bin_set)
{
    node *curNode = main_set->first_node;
    node *tmp = create_node(convert(curNode->val));
    bin_set->first_node = tmp;
    bin_set->now = tmp;
    ++bin_set->size;
    curNode = curNode->next;
    while (curNode != NULL)
    {
        node *tmp = create_node(convert(curNode->val));
        bin_set->now->next = tmp;
        bin_set->now = tmp;
        curNode = curNode->next;
        ++bin_set->size;
    }
}

/*
 * Функция освобождения памяти, занятой множеством
 * Параметр `set` - указатель на множество
 */
void freeset(set *set)
{
    if (set->size)
    {
        node *curNode = set->first_node;
        while (curNode != NULL)
        {
            node *delNode = curNode;
            curNode = curNode->next;
            free(delNode);
        }
        free(curNode);
    }
    free(set);
}

void help(void)
{
    puts("Команды для работы с множеством:\n1 - добавить в множество числа.\n2 - вывести значения исходного множества.\n3 - вывести значения множества в двоичном представлении.\n0 - выход из программы.");
}

int main(void)
{
    set *main_set = createSet();
    set *bin_set = createSet();
    int menu = 0;
    int input = 1;

    help();
    while (input)
    {
        puts("Введите команду: ");
        input = scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            puts("---------------------------Ввод чисел------------------------------");
            puts("Введите число: ");
            setPush(main_set);
            binconvert(main_set, bin_set);
            break;
        case 2:
            puts("------------------Вывод исходного множества чисел------------------");
            setOutput(main_set);
            break;
        case 3:
            puts("------------------Вывод множества чисел в двоичном представлении(точность мантиссы 9 байт0)------------------");
            setOutput2(bin_set);
            break;

        case 0:
            freeset(main_set);
            freeset(bin_set);
            return 0;
        default:
            help();
        }
    }
    return 0;
}