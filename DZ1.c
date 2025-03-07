#include <stdio.h>
#include <stdlib.h>

long double drob(long double a)
{   
    if(a >= 0){
        long b = (long) a;
        return (a-b);
    }else{
        long b = (long) a;
        return (b-a);
    }
}

void output(long double *digits,long double *digits2,long double *digits2_1, int size, int flag){
    int unique = 1;
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            if(digits[j] == digits[i]){
                unique = 0;
            }
        }
        if (unique){
            if (flag == 0 && digits[i] != 0 || flag == 1) {
                printf("%.2Lf ", digits[i]);
            }
        }
    }        
    printf("\n");
    
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
                if(digits2[j] == digits2[i] && digits2_1[j] == digits2_1[i] ){
                    goto pass2;
                }
                
        }
        if (flag == 0 && digits2[i] != 0 || flag == 1) {
            printf("%ld.%04ld ", (long)digits2[i], (long)digits2_1[i]);
        }
        pass2:;
    }
}

void translation(long double *digits,long double *digits2,long double *digits2_1, int size)
{
    for(int i = 0; i < size; i++){
        if (digits[i] >= 0){
            long dv = (long)digits[i];
            long res = 0;
            long j = 1;
            while(dv > 0){
                res += (dv % 2) * j;
                dv /= 2;
                j *= 10;
            }
            digits2[i] = res;
            
            long double ost = (long double)drob(digits[i]);
            int res_drob = 0;
            for(int j = 4, k = 10000; j >= 0; j--){
                res_drob += (int)ost * k;
                if((int)ost >= 1) ost -=1;
                ost *= 2;
                k = k / 10;
                
            }
            digits2_1[i] = res_drob;
        }
        if (digits[i] < 0){
            long dv = (long)digits[i];
            long res = 0;
            long j = 1;
            while(dv < 0){
                res += (dv % 2) * j;
                dv /= 2;
                j *= 10;
            }
            digits2[i] = res;

            long double ost = (long double)drob(digits[i]);
            int res_drob = 0;
            for(int j = 4, k = 10000; j >= 0; j--){
                res_drob += (int)ost * k;
                if((int)ost >= 1) ost -=1;
                ost *= 2;
                k = k / 10;
                
            }
            digits2_1[i] = res_drob;
        }
    }
}

int main (void)
{
    int size, c, scan, flag = 0;
    long double var;
    
    printf("----------------Задание множества чисел----------------\n");
    restart:;
    do{
        printf("Введите количество элементов множества (целое число): ");
        scan = scanf("%d,", &size);
        while((c = getchar()) != '\n' && c != EOF)
        { }
        if (scan == 0) printf("[Ошибка ввода]\n");
        if (size < 0) goto restart;
    } while(scan != 1);

    long double *digits = (long double*)malloc(size * sizeof(long double));
    long double *digits2 = (long double*) malloc(size * sizeof(long double));
    long double *digits2_1 = (long double*)malloc(size * sizeof(long double));
    
    switch (size){
        case 1: 
            printf("Введите %d элемент (%d число)\n", size, size);
            break;
        case 2: 
            printf("Введите %d элемента (%d числа)\n", size, size);
            break;
        case 3: 
            printf("Введите %d элемента (%d числа)\n", size, size);
            break;
        case 4: 
            printf("Введите %d элемента (%d числa)\n", size, size);
            break;
        default: 
            printf("Введите %d элементов (%d чисел)\n", size, size);
            break;
    }
    
    
    for(int i = 0; i < size; i++){
        int scan2 = scanf("%Lf", &var);
        if (scan2 == 1){
            _Bool unique = 1;
            for(int j = 0; j < size; j++){
                if(digits[j] == var && j != i && var != 0){
                    unique = 0;
                    break;
                }
            }
            if(unique){
                digits[i] = var;
            }

            if(var == 0){
                flag = 1;
            }
        }else{
            printf("----------------Ошибка ввода----------------\n");
            return 0;
        }
    }
    printf("----------------Множество задано----------------\n");

    translation(digits,digits2,digits2_1, size);

    output(digits,digits2,digits2_1, size, flag);

    free(digits);
    free(digits2);
    free(digits2_1);
    return 0;
}