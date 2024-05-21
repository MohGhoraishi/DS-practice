#include <stdio.h>
#include <stdlib.h>

struct bakery
{
    long total_k;
    long* pos_one_array;
    long* pos_many_array;
    long one_count;
    long many_count;
    int* line_array;
    int* k_array;
    long current_customer;
    int line_counter;
    long* order_one;
    long* order_many;
    long last_one;
    long last_many;
    long last_left_one;
    long last_left_many;
    long one_offset;
    long many_offset;
};

struct complete_input
{   
    long q;
    int* in_one;
    long* in_two;
    int* in_three;
};

struct complete_input ci;
struct bakery bk;

void get_inputs(long q);
void event(long num);
void customer_enters(long num);
void bake_bread(long num);
void question(long num);
void customer_leaves();
void sell_bread();
void choose_customer();

int main(){
    long q;
    scanf("%li", &q);
    while ((getchar()) != '\n');
    bk.total_k = 0;
    bk.one_count = 0;
    bk.many_count = 0;
    bk.pos_one_array = calloc(q, sizeof(long));
    bk.pos_many_array = calloc(q, sizeof(long));
    bk.line_array = calloc(q, sizeof(int));
    bk.k_array = calloc(q, sizeof(int));
    bk.order_one = calloc(q, sizeof(long));
    bk.order_many = calloc(q, sizeof(long));
    bk.last_one = 0;
    bk.last_many = 0;
    bk.line_counter = 0;
    bk.current_customer = 0;
    bk.last_left_many = 0;
    bk.last_left_one = 0;
    bk.one_offset = 0;
    bk.many_offset = 0;

    ci.q = q;
    ci.in_one = calloc(q, sizeof(int));
    ci.in_two = calloc(q, sizeof(long));
    ci.in_three = calloc(q, sizeof(int));

    for (long i = 0; i < q; i++)
    {
        ci.in_one[i] = 0;
        ci.in_two[i] = 0;
        ci.in_three[i] = 0;
        bk.pos_many_array[i] = 0;
        bk.pos_one_array[i] = 0;
    }

    get_inputs(q);
    bk.current_customer = q;
    
    for (long i = 0; i < q; i++)
    {
        event(i);
        sell_bread();
        choose_customer();
    }
    
    /*
    for (long i = 0; i < q; i++)
    {
        printf("%li\n", bk.total_k);
    }
    free(bk.pos_one_array);
    free(bk.pos_many_array);
    free(bk.line_array);
    free(bk.k_array);
    free(bk.id_array);
    */
    return 0;
}

void get_inputs(long q){
    for (long i = 0; i < q; i++)
    {
        int one = 0;
        long two = 0;
        int three = 0;
        scanf("%d", &one);
        scanf("%li", &two);
        if (one == 1){
            scanf("%d", &three);
        }
        ci.in_one[i] = one;
        ci.in_two[i] = two;
        ci.in_three[i] = three;
    }
    return;
}

void event(long num){
    int input = ci.in_one[num];
    switch (input)
    {
    case 1:
        customer_enters(num);
        break;
    case 2:
        bake_bread(num);
        break;
    case 3:
        question(num);
        break;
    default:
        exit(0);
        break;
    }
    return;
}

void customer_enters(long num){
    long id = ci.in_two[num];
    int k = ci.in_three[num];
    bk.k_array[id - 1] = k;
    if (k == 1 && bk.one_count <= 2 * bk.many_count){
        bk.pos_one_array[id - 1] = bk.one_count + 1;
        bk.line_array[id - 1] = 1;
        bk.order_one[bk.last_one] = id;
        bk.last_one++;
        bk.one_count++;
    }
    else{
        bk.pos_many_array[id - 1] = bk.many_count + 1;
        bk.line_array[id - 1] = 2;
        bk.order_many[bk.last_many] = id;
        bk.last_many++;
        bk.many_count++;
    }
}

void bake_bread(long num){
    int baked_k = ci.in_two[num];
    bk.total_k += baked_k;
}

void question(long num){
    long id = ci.in_two[num];
    if (bk.line_array[id-1] == 1){
        if (bk.pos_one_array[id-1] - bk.one_offset < 1){
            printf("-1\n");
        }
        else{
            printf("%li\n", bk.pos_one_array[id-1] - bk.one_offset);
        }
    }
    else{
         if (bk.pos_many_array[id-1] - bk.many_offset < 1){
            printf("-1\n");
        }
        else{
            printf("%li\n", bk.pos_many_array[id-1] - bk.many_offset);
        }
    }
    return;
}

void sell_bread(){
    if (bk.k_array[bk.current_customer-1] == 0){
        return;
    }
    else{
        if (bk.total_k >= bk.k_array[bk.current_customer-1]){
            customer_leaves();
            printf("Customer %li left\n", bk.current_customer);
            bk.k_array[bk.current_customer-1] = 0;
            choose_customer();
            sell_bread();
        }
    }
    return;
}

void customer_leaves(){
    bk.total_k -= bk.k_array[bk.current_customer-1];
    if (bk.line_array[bk.current_customer-1] == 1){
        bk.one_count--;
        bk.one_offset++;
    }
    else{
        bk.many_count--;
        bk.many_offset++;
    }
}

void choose_customer(){
    if (bk.k_array[bk.current_customer-1] != 0){
        return;
    }
    if (bk.one_count == 0 && bk.many_count == 0){
        bk.current_customer = ci.q;
    }
    
    else if (bk.one_count == 0 && bk.many_count != 0)
    {
        bk.current_customer = bk.order_many[bk.last_left_many];
        bk.last_left_many++;
        bk.line_counter = 0;
    }
    else if (bk.one_count != 0 && bk.many_count == 0)
    {
        bk.current_customer = bk.order_one[bk.last_left_one];
        bk.last_left_one++;
        bk.line_counter++;
    }
    else{
        if (bk.line_counter >= 2){
             bk.current_customer = bk.order_many[bk.last_left_many];
            bk.last_left_many++;
            bk.line_counter = 0;
        }
        else{
            bk.current_customer = bk.order_one[bk.last_left_one];
            bk.last_left_one++;
            bk.line_counter++;
        }
    }
    
}
