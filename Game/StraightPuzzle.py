import tkinter as tk
import random
from enum import IntFlag, auto

DEBUG_MODE = False

def launch(table):
    size = len(table)
    root = tk.Tk()
    cell_size = int(64 * (8/size))
    margin = 4
    cwidth = size * cell_size

    root.title(u"Non stop Maze")
    root.geometry("{}x{}".format(cwidth+margin*2, cwidth+margin*2))
    root.minsize(cwidth, cwidth)
    canvas = tk.Canvas(root, bd=4, bg='#F3FFBD', width=cwidth, height=cwidth)
    for i in range(size):
        for j in range(size):
            bcolor = "#fff5e3"
            x0 = j * cell_size + margin
            y0 = i * cell_size + margin
            if table[i][j] == "S":
                bcolor = "#FF1654"
                canvas.create_rectangle(x0, y0, x0 + cell_size, y0 + cell_size, fill=bcolor, width=0)
            elif table[i][j] == 'G':
                bcolor = "#247BA0"
                canvas.create_rectangle(x0, y0, x0 + cell_size, y0 + cell_size, fill=bcolor, width=0)
            elif table[i][j] == '#':
                bcolor = "#70C1B3"
                canvas.create_rectangle(x0, y0, x0 + cell_size, y0 + cell_size, fill=bcolor, width=0)

    canvas.place(x=0, y=0)
    root.mainloop()

def print_table(table):
    for c in table:
        print(*c)
    print()

def prevent_line(table, p):
    size = len(table)
    stoppers = ["#", "S", "*"]
    # Lowwer side
    for i in range(p[0] + 1, size):
        if table[i][p[1]] in stoppers:
            break
        table[i][p[1]] = "+"
    # Right side
    for i in range(p[1] + 1, size):
        if table[p[0]][i] in stoppers:
            break
        table[p[0]][i] = "+"
    # Upper side
    for i in range(p[0]-1, -1, -1):
        if table[i][p[1]] in stoppers:
            break
        table[i][p[1]] = "+"
    # Left side
    for i in range(p[1]-1, -1, -1):
        if table[p[0]][i] in stoppers:
            break
        table[p[0]][i] = "+"

def scan_line(table, start, end):
    if start == end:
        return False
    # on horizontal line
    elif start[0] == end[0]:
        sign = 1
        if start[1] > end[1]:
            sign = -1
        for i in range(start[1]+sign, end[1], sign):
            if table[start[0]][i] == "#":
                return False
        return True
    # on vertical line
    elif start[1] == end[1]:
        sign = 1
        if start[0] > end[0]:
            sign = -1
        for i in range(start[0]+sign, end[0], sign):
            if table[i][start[1]] == "#":
                return False
        return True
    else:
        print("Error: start{} and end{} is not on line".format(start,end))

def toward_next(table, start, end):
    if start == end:
        return False
    # on horizontal line
    elif start[0] == end[0]:
        sign = 1
        if start[1] > end[1]:
            sign = -1
        for i in range(start[1]+sign, end[1]+sign, sign):
            table[start[0]][i] = "*"
    # on vertical line
    elif start[1] == end[1]:
        sign = 1
        if start[0] > end[0]:
            sign = -1
        for i in range(start[0]+sign, end[0]+sign, sign):
            table[i][start[1]] = "*"
    else:
        print("Error: start{} and end{} is not on line".format(start,end))

def get_block_pos(src,dest):
    if src == dest:
        print("Error: src{} and dest{} is same".format(src,dest))
    # on horizontal line
    elif src[0] == dest[0]:
        if dest[1] < src[1]:
            return [src[0], dest[1] - 1]
        else:
            return [src[0], dest[1] + 1]
    # on vertical line
    elif src[1] == dest[1]:
        if dest[0] < src[0]:
            return [dest[0] - 1, src[1]]
        else:
            return [dest[0] + 1, src[1]]
    else:
        print("Error: src{} and dest{} is not linked".format(src,dest))

def create_table(size = 5, point_num = 4):
    table = [[0 for i in range(size)] for j in range(size)]

    start_point = (random.randint(0, size - 1), random.randint(0, size - 1))
    table[start_point[0]][start_point[1]] = "S"

    prev_point = list(start_point)
    is_vertical = bool(random.randint(0, 1))

    i = 0
    rand_count = 0
    while i < point_num + 1:
        if rand_count > point_num * 2:
            table = [[0 for i in range(size)] for j in range(size)]
            start_point = (random.randint(0, size - 1), random.randint(0, size - 1))
            table[start_point[0]][start_point[1]] = "S"

            prev_point = list(start_point)
            is_vertical = bool(random.randint(0, 1))

            i = 0
            rand_count = 0

        is_goal = i == point_num
        # get random number
        if is_goal:
            rand = random.randint(0, size - 1)
        else:
            rand = random.randint(1, size - 2)

        if is_vertical: # vertical line
            cur_point = [rand, prev_point[1]]
        else:           # horizontal line
            cur_point = [prev_point[0], rand]

        if not scan_line(table, prev_point, cur_point):
            rand_count += 1
            continue
        if (table[cur_point[0]][cur_point[1]] != 0):
            rand_count += 1
            continue

        block_pos = get_block_pos(prev_point,cur_point)
        if not is_goal:
            if (table[block_pos[0]][block_pos[1]] == "*"):
                rand_count += 1
                continue
            table[block_pos[0]][block_pos[1]] = '#'

        if DEBUG_MODE:
            print("pre>{} cur>{} | block{}".format(prev_point, cur_point,block_pos))
        if DEBUG_MODE:
            print_table(table)

        prevent_line(table, prev_point)
        toward_next(table, prev_point, cur_point)
        prev_point = cur_point
        is_vertical = not is_vertical
        i += 1
        if DEBUG_MODE:
            print_table(table)

    table[prev_point[0]][prev_point[1]] = 'G'
    return  table

def main():
    print("Non stop Maze")
    table = create_table()

    print_table(table)
    launch(table)

if __name__ == "__main__":
    main()
