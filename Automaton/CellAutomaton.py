import tkinter as tk
import random
WIDTH = 640
HEIGHT = WIDTH
# Cell table size
SIZE = int(WIDTH/10)
root = tk.Tk()
root.title(u"Cell Automaton")
root.geometry("{}x{}".format(WIDTH,HEIGHT))
canvas = tk.Canvas(root, width = SIZE*10, height = SIZE*10, bg="#2e4057")
canvas.pack()

update_state = 0

class Cell():
    def __init__(self, can, start_x, start_y, size = 10):
        self.can=can
        self.state = random.randint(0,1)
        # self.state = 0
        self.next_state = 0
        self.id = self.can.create_rectangle((start_x, start_y,
                  start_x+size, start_y+size), fill="#2e4057")
        self.can.tag_bind(self.id, "<ButtonPress-1>", self.set_color)

        self.color_change=True

    def set_color(self, event=None):
        self.color_change = not self.color_change
        color="#2e4057"
        if not self.color_change:
            color="#52b788"
            self.state = 1
        self.can.itemconfigure(self.id, fill=color)

    def next(self):
        self.state = self.next_state
        color="#2e4057"
        if self.state == 1:
            color="#52b788"
        self.can.itemconfigure(self.id, fill=color)

def next(x,y):
    sx, ex = x - 1, x + 1
    sy, ey = y - 1, y + 1
    if sx < 0:
        sx = 0
    if sy < 0:
        sy = 0
    if ex > SIZE - 1:
        ex = SIZE - 1
    if ey > SIZE - 1:
        ey = SIZE - 1

    count = 0
    for i in range(sy,ey + 1):
        for j in range(sx, ex + 1):
            if table[i][j].state == 1:
                count += 1

    if table[y][x].state == 1:
        count -= 1
    if count == 3:
        table[y][x].next_state = 1
    elif count >= 4:
        table[y][x].next_state = 0
    elif count <= 1:
        table[y][x].next_state = 0



table = [[0] * SIZE for i in range(SIZE)]
for i in range(SIZE):
    for j in range(SIZE):
        table[i][j] = Cell(canvas,j*10, i*10)

def update():
    for i in range(SIZE):
        for j in range(SIZE):
            next(j,i)
    for i in range(SIZE):
        for j in range(SIZE):
            table[i][j].next()


    root.after(100,update)



root.after(10,update)
root.mainloop()
