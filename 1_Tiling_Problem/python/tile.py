def filled_pos(n, block_c, block_r, filled_c, filled_r):
    n = n - 1
    center_c = block_c + 2 ** n
    center_r = block_r + 2 ** n
    if filled_c < center_c and filled_r < center_r:
        return 1
    elif filled_c >= center_c and filled_r < center_r:
        return 2
    elif filled_c < center_c and filled_r >= center_r:
        return 3
    else:
        return 4

def fill_centers(n, block_c, block_r, filled_c, filled_r):
    tile_pos_c = block_c + 2**(n-1) - 1
    tile_pos_r = block_r + 2**(n-1) - 1
    filled_state = filled_pos(n, block_c, block_r, filled_c, filled_r)
    if filled_state == 1:
        print("0 " + str(tile_pos_r) + " " + str(tile_pos_c))
        if n==1:
            return
        fill_centers(n-1, block_c, block_r, filled_c, filled_r)
        fill_centers(n-1, tile_pos_c + 1, block_r, tile_pos_c + 1, tile_pos_r)
        fill_centers(n-1, block_c, tile_pos_r + 1, tile_pos_c, tile_pos_r + 1)
        fill_centers(n-1, tile_pos_c + 1, tile_pos_r + 1, tile_pos_c + 1, tile_pos_r + 1)
    elif filled_state == 2:
        print("1 " + str(tile_pos_r) + " " + str(tile_pos_c))
        if n==1:
            return
        fill_centers(n-1, block_c, block_r, tile_pos_c, tile_pos_r)
        fill_centers(n-1, tile_pos_c + 1, block_r, filled_c, filled_r)
        fill_centers(n-1, block_c, tile_pos_r + 1, tile_pos_c, tile_pos_r + 1)
        fill_centers(n-1, tile_pos_c + 1, tile_pos_r + 1, tile_pos_c + 1, tile_pos_r + 1)
    elif filled_state == 3:
        print("2 " + str(tile_pos_r) + " " + str(tile_pos_c))
        if n==1:
            return
        fill_centers(n-1, block_c, block_r, tile_pos_c, tile_pos_r)
        fill_centers(n-1, tile_pos_c + 1, block_r, tile_pos_c + 1, tile_pos_r)
        fill_centers(n-1, block_c, tile_pos_r + 1, filled_c, filled_r)
        fill_centers(n-1, tile_pos_c + 1, tile_pos_r + 1, tile_pos_c + 1, tile_pos_r + 1)
    else:
        print("3 " + str(tile_pos_r) + " " + str(tile_pos_c))
        if n==1:
            return
        fill_centers(n-1, block_c, block_r, tile_pos_c, tile_pos_r)
        fill_centers(n-1, tile_pos_c + 1, block_r, tile_pos_c + 1, tile_pos_r)
        fill_centers(n-1, block_c, tile_pos_r + 1, tile_pos_c, tile_pos_r + 1)
        fill_centers(n-1, tile_pos_c + 1, tile_pos_r + 1, filled_c, filled_r)

n = int(input())
line = input()
l = line.split(" ")
c = int(l[0])
r = int(l[1])
if n==0:
    print("0")
else:
    tile_num = int((2 ** (2 * n) - 1) / 3)
    print(str(tile_num))
    fill_centers(n, 0, 0, c, r)
