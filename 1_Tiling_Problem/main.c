#include <stdio.h>
#include <stdlib.h>
//we use a divide and conquer algorithm that divides the grid into four seperate solvable grids

int filled_pos(int n, int block_c, int block_r, int filled_c, int filled_r);
int intpow(int x, int y);
void fill_centers(int n, int block_c, int block_r, int filled_c, int filled_r);

int main() {
    int n;
    int c;
    int r;
    scanf("%d", &n);
    scanf("%d", &r);
    scanf("%d", &c);
    if (n==0){
        printf("0");
        exit(0);
    }
    long tile_num = (intpow(2, 2 * n) - 1) / 3;
    printf("%ld\n", tile_num);
    fill_centers(n, 0, 0, c, r);
    //int pos = filled_pos(n, 0, 0, c, r);
    //printf("%d", pos);
    return 0;
}

int filled_pos(int n, int block_c, int block_r, int filled_c, int filled_r){
    n--;
    int center_c = block_c + intpow(2, n);
    int center_r = block_r + intpow(2, n);
    if (filled_c < center_c && filled_r < center_r){
        return 1; //top left
    }
    else if (filled_c >= center_c && filled_r < center_r)
    {
        return 2; //top right
    }
    else if (filled_c < center_c && filled_r >= center_r)
    {
        return 3; //bottom left
    }
    else{
        return 4; //bottom right
    }
}

int intpow(int x, int y){
    int result = x;
    if (y==0){
        return 1;
    }
    for (int i=1; i<y; i++) {
        result *= x;
    }
    return result;
}

void fill_centers(int n, int block_c, int block_r, int filled_c, int filled_r){
    int tile_pos_c = block_c + intpow(2, n-1) - 1;
    int tile_pos_r = block_r + intpow(2, n-1) - 1;
    int filled_state = filled_pos(n, block_c, block_r, filled_c, filled_r);
    switch (filled_state)
    {
    case 1:
        printf("0 %d %d\n", tile_pos_r, tile_pos_c);
        if (n==1){
            return;
        }
        fill_centers(n-1, block_c, block_r, filled_c, filled_r);//top left (first block)
        fill_centers(n-1, tile_pos_c + 1, block_r, tile_pos_c + 1, tile_pos_r);//top right
        fill_centers(n-1, block_c, tile_pos_r + 1, tile_pos_c, tile_pos_r + 1);//bottom left
        fill_centers(n-1, tile_pos_c + 1, tile_pos_r + 1, tile_pos_c + 1, tile_pos_r + 1);//bottom right
        break;
    case 2:
        printf("1 %d %d\n", tile_pos_r, tile_pos_c);
        if (n==1){
            return;
        }
        fill_centers(n-1, block_c, block_r, tile_pos_c, tile_pos_r);//top left
        fill_centers(n-1, tile_pos_c + 1, block_r, filled_c, filled_r);//top right (first block)
        fill_centers(n-1, block_c, tile_pos_r + 1, tile_pos_c, tile_pos_r + 1);//bottom left
        fill_centers(n-1, tile_pos_c + 1, tile_pos_r + 1, tile_pos_c + 1, tile_pos_r + 1);//bottom right
        break;
    case 3:
        printf("2 %d %d\n", tile_pos_r, tile_pos_c);
        if (n==1){
            return;
        }
        fill_centers(n-1, block_c, block_r, tile_pos_c, tile_pos_r);//top left
        fill_centers(n-1, tile_pos_c + 1, block_r, tile_pos_c + 1, tile_pos_r);//top right
        fill_centers(n-1, block_c, tile_pos_r + 1, filled_c, filled_r);//bottom left (first block)
        fill_centers(n-1, tile_pos_c + 1, tile_pos_r + 1, tile_pos_c + 1, tile_pos_r + 1);//bottom right
        break;
    case 4:
        printf("3 %d %d\n", tile_pos_r, tile_pos_c);
        if (n==1){
            return;
        }
        fill_centers(n-1, block_c, block_r, tile_pos_c, tile_pos_r);//top left
        fill_centers(n-1, tile_pos_c + 1, block_r, tile_pos_c + 1, tile_pos_r);//top right
        fill_centers(n-1, block_c, tile_pos_r + 1, tile_pos_c, tile_pos_r + 1);//bottom left 
        fill_centers(n-1, tile_pos_c + 1, tile_pos_r + 1, filled_c, filled_r);//bottom right (first block)
        break;
    default:
        printf("don make sense");
        break;
    }
    return;
}