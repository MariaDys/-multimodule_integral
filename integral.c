#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#define _GNU_SOURCE

extern float f1(float);
extern float f2(float);
extern float f3(float);
int iterations = 0;

float Integral(float (*f)(float), float a, float b, float eps2) {
    float value = 0;
    float num = (b-a)/(eps2);
    for (int i = 0; i < num; i++) {
    value +=eps2*0.5*(f(a+eps2*i)+f(a+(i+1)*eps2));
  }
  return value;
}

float root(float(*f)(float), float(*g)(float), float a, float b, float eps1){
    iterations = 0;
    int flag;
    if (((f(a)-g(a)<0)&&(f((a+b)/2)-g((a+b)/2) <= (f(a)-g(a)+f(b)-g(b))/2))||(f(a)-g(a)>0)&&(f((a+b)/2)-g((a+b)/2)>(f(a)-g(a)+f(b)-g(b))/2)){
        flag = 1;
    }
    else{
        flag = 0;
    }
    float c = (a*(f(b)-g(b))-b*(f(a)-g(a)))/((f(b)-g(b))-g(b))-(f(a)-g(a));
    while (flag*(f(c)-g(c))*(f(c+eps1)-g(c+eps1))+(1-flag)*(f(c)-g(c))*(f(c-eps1)-g(c-eps1))>0){
        c = (a*(f(b)-g(b))-b*(f(a)-g(a)))/((f(b)-g(b)) - (f(a)-g(a)));
        if (flag){
            a = c;
            iterations++;
        }
        else {
            b = c;
            iterations++;
        }
    }
        return c;
}

int main(int argc, const char * argv[]) {
    int a_key = 0, n_key = 0;
    char key;
    float (*func_massiv[3])(float) = {&f1, &f2, &f3};
    //func_massiv[0] = &f1;
    //func_massiv[1] = &f2;
    //func_massiv[2] = &f3;
    while((key = getopt(argc, argv, "hrian"))!= EOF){
        switch(key){
            case 'h':
                printf("\nУравнения кривых:\nf1 = exp(-x) + 3\nf2 = 2x - 2\nf3 = 1/x\n");
                printf("\nКлючи командной строки:\n\n");
                printf("-r:\nВычисление корня x уравнения f(x) = g(x) на отрезке [a, b] с точностью ε1.\nНеобходимо ввести функцию f(x){1,2,3}, функцию g(x){1,2,3}, левую границу отрезка a, правую границу отрезка b, точность вычислений ε1\n\n");
                printf("-n:\nЧисло итераций, потребовавшихся на приближенное решение уравнений при поиске точек пересечения f1, f2, f3\n\n");
                printf("-i:\nВычисление величины определенного интеграла от функции f(x) на отрезке [a, b] с точностью ε2.\nВведите номер функции {1,2,3}, нижнюю границу интегрирования a, верхнюю границу интегрирования b, точность вычислений ε2\n\n");
                printf("-a:\nАбсциссы точек пересечения кривых f1, f2, f3\n\n");
                printf("-h:\nВывод всех допустимых ключей командной строки (справка)\n\n");
                return 0;
                break;
            case 'a':
                a_key = 1;
                break;
            case 'n':
                n_key = 1;
                break;
            case 'r':
                printf("Aбсцисса точки пересечения кривых: %f\n", root(func_massiv[atoi(argv[2]) - 1], func_massiv[atoi(argv[3]) - 1], atof(argv[4]), atof(argv[5]), atof(argv[6])));
                return 0;
            case 'i':
                printf("Величина определенного интеграла от введенной функции %f\n", Integral(func_massiv[ atoi(argv[2])-1], atof(argv[3]), atof(argv[4]), atof(argv[5])));
                return 0;
        }
    }

    float x1 = root((float(*)(float))f1,(float(*)(float)) f3, 0.1, 1, 0.00001);
    float x1_iter = iterations;
    float x2 = root((float(*)(float))f2,(float(*)(float))f3, 1, 2, 0.00001);
    float x2_iter = iterations;
    float x3 = root((float(*)(float))f1,(float(*)(float)) f2, 2, 3, 0.00001);
    float x3_iter = iterations;
    if (a_key == 1){
        printf("Абсцисса точки пересечения функций f1 и f3: %f\nАбсцисса точки пересечения функций f2 и f3: %f\nАбсцисса точки пересечения функций f1 и f2: %f\n", x1, x2, x3);
        return 0;
    }
    if (n_key == 1){
        printf("Число итераций, потребовавшихся при поиске пересечения f1 и f3: %f\nЧисло итераций, потребовавшихся при поиске пересечения f2 и f3: %f\nЧисло итераций, потребовавшихся при поиске пересечения f1 и f2: %f\n", x1_iter, x2_iter, x3_iter);
        return 0;
    }
    float s1 = Integral((float(*)(float))f1, x1, x3, 0.00001);
    float s2 = Integral((float(*)(float))f3, x1, x2, 0.00001);
    float s3 = Integral((float(*)(float))f2, x2, x3, 0.00001);
    float S_result = s1 - s2 - s3;

    printf("Площадь заданной фигуры, вычисленная по формуле трапеций: %f\n" , S_result);
    return 0;
    }
