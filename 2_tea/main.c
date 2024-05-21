#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct two_arr
{
    long* a;
    long* t;
};

struct two_arr TA;

void merge(long l, long m, long r)
{
    long i, j, k;
    long n1 = m - l + 1;
    long n2 = r - m;

    long L[n1], R[n2];
    long L2[n1], R2[n2];

    for (i = 0; i < n1; i++){
        L[i] = TA.t[l + i];
        L2[i] = TA.a[l + i];
    }

    for (j = 0; j < n2; j++){
        R[j] = TA.t[m + 1 + j];
        R2[j] = TA.a[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            TA.t[k] = L[i];
            TA.a[k] = L2[i];
            i++;
        }
        else {
            TA.t[k] = R[j];
            TA.a[k] = R2[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        TA.t[k] = L[i];
        TA.a[k] = L2[i];
        i++;
        k++;
    }

    while (j < n2) {
        TA.t[k] = R[j];
        TA.a[k] = R2[j];
        j++;
        k++;
    }
}

void mergeSort(long l, long r)
{
    if (l < r) {
        long m = l + (r - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

double second_floor(double num){
    return num;
}

int main(){
    long n;
    long T;
    scanf("%ld", &n);
    scanf("%ld", &T);
    TA.a = calloc(n, sizeof(long));
    TA.t = calloc(n, sizeof(long));
    long temp;

    for(long i = 0; i < n; i++){
        scanf("%ld", &temp);
        TA.a[i] = temp;
    }

    for(long i = 0; i < n; i++){
        scanf("%ld", &temp);
        TA.t[i] = temp;
    }

    mergeSort(0, n-1);
    double amount = 0;
    double current_temp = 0;
    double remain = 0;
    for (long i = 0; i < n; i++){
        if (TA.t[i] <= T){
            current_temp = (TA.t[i] * TA.a[i] + current_temp * amount) / (amount + TA.a[i]);
            amount += TA.a[i];
        }
        else{
            remain = ((T - current_temp) * amount) / (TA.t[i] - T);
            if (remain <= TA.a[i]){
                current_temp = (TA.t[i] * remain + current_temp * amount) / (amount + remain);
                amount += remain;
                break;
            }
            else{
                current_temp = (TA.t[i] * TA.a[i] + current_temp * amount) / (amount + TA.a[i]);
                amount += TA.a[i];  
            }
        }
    }
    /*
    printf("%lf\n", current_temp);

    printf("%lf\n", amount);
    */



    if (amount <= 0.005){
        printf("0.00");
    }
    else{
    printf("%.2lf", amount - 0.005);
    }

    /*
    mergeSort(0, n-1);
    for (long i = 0; i < n; i++)
        printf("%ld ", TA.t[i]);
    printf("\n");
    for (long i = 0; i < n; i++)
        printf("%ld ", TA.a[i]);
    printf("\n");
    */

    return 0;
}

