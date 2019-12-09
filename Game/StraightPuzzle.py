import tkinter as tk
import random
from enum import IntFlag, auto

DEBUG_MODE = True

class Direction(IntFlag):
    Up = 1
    Right = 2
    Down = 3
    Left = 4


def create_wall(canvas, x, y, wall_pos, cell_size):
    width = 8
    x0, y0 = x, y
    w, h = width, width
    print(wall_pos)
    if wall_pos == 1:
        y0 = y - (width / 2)
        w = cell_size
    elif wall_pos == 2:
        x0 = x + cell_size - (width / 2)
        h = cell_size
    elif wall_pos == 3:
        y0 = y + cell_size - (width / 2)
        w = cell_size
    else:
        x0 = x - (width / 2)
        h = cell_size

    canvas.create_rectangle(x0, y0, x0 + w, y0 + h, fill="#70C1B3", width=0)

def launch(table):
    size =len(table)
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
                # create_wall(canvas, x0, y0, table[i][j], cell_size)


    canvas.place(x=0, y=0)
    root.mainloop()

def print_table(table):
    for c in table:
        print(*c)
    print()
def write_table(table,f):
    for c in table:
        f.writelines([str(n) + " " for n in c])
        f.write('\n')
    f.write('\n')

def prevent_line(table, p):
    size = len(table)
    # Lowwer side
    for i in range(p[0] + 1, size):
        if table[i][p[1]] == "#" or table[i][p[1]] == "S":
            break
        table[i][p[1]] = "+"
    # Right side
    for i in range(p[1] + 1, size):
        if table[p[0]][i] == "#" or table[p[0]][i] == "S":
            break
        table[p[0]][i] = "+"

    # Upper side
    for i in range(p[0]-1, -1, -1):
        if table[i][p[1]] == "#" or table[i][p[1]] == "S":
            break
        table[i][p[1]] = "+"
    # Left side
    for i in range(p[1]-1, -1, -1):
        if table[p[0]][i] == "#" or table[p[0]][i] == "S":
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


def create_table():
    size = 5
    point_num = 4
    table = [[0 for i in range(size)] for j in range(size)]
    start_point = (random.randint(0, size - 1), random.randint(0, size - 1))

    table[start_point[0]][start_point[1]] = "S"
    prev_point = list(start_point)
    last_bit = random.randint(0, 1)



    i = 0
    while i < point_num + 1:
        is_goal = i == point_num
        # 0:horizontal or 1:vertical
        if last_bit == 1:
            rand = random.randint(1, size - 2)
            if is_goal:
                rand = random.randint(0, size - 1)
            # rand = 1
            cur_point = [rand, prev_point[1]]
            # print("v : {}".format( cur_point))
            if not scan_line(table, prev_point, cur_point):
                continue

            # update table
            if (table[rand][prev_point[1]] == 0 or i == 0) and rand != prev_point[0]:
                if DEBUG_MODE:
                    print("v : pre>{} cur>{}".format(prev_point, cur_point))
                if rand < prev_point[0]:
                    if not is_goal:
                        table[rand - 1][prev_point[1]] = '#'

                else:
                    if not is_goal:
                        table[rand + 1][prev_point[1]] = '#'
                if DEBUG_MODE:
                    print_table(table)
                prevent_line(table, prev_point)
                prev_point = [rand, prev_point[1]]
                last_bit = (last_bit + 1) % 2
                i += 1
                if DEBUG_MODE:
                    print_table(table)


        else:
            rand = random.randint(1, size - 2)
            if is_goal:
                rand = random.randint(0, size - 1)
            cur_point = [prev_point[0], rand]
            if not scan_line(table, prev_point, cur_point):
                continue
            # update table
            if (table[prev_point[0]][rand] == 0 or i == 0) and rand != prev_point[1]:
                if DEBUG_MODE:
                    print("h : pre>{} cur>{}".format(prev_point, cur_point))
                if rand < prev_point[1]:
                    if not is_goal:
                        table[prev_point[0]][rand - 1] = '#'

                else:
                    if not is_goal:
                        table[prev_point[0]][rand + 1] = '#'
                if DEBUG_MODE:
                    print_table(table)
                prevent_line(table, prev_point)
                prev_point = [prev_point[0], rand]
                last_bit = (last_bit + 1) % 2
                i += 1
                if DEBUG_MODE:
                    print_table(table)


    table[prev_point[0]][prev_point[1]] = 'G'
    return  table

def main():
    print("Non stop Maze")
    for _ in range(1):
        table = create_table()
    print_table(table)
    launch(table)

if __name__ == "__main__":
    main()
