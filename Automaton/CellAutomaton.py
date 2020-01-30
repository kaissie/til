import tkinter as tk
import random
WIDTH = 640
HEIGHT = WIDTH

CELL_SIZE  = 10
TABLE_SIZE = int(WIDTH/CELL_SIZE)

root = tk.Tk()
root.title(u"Life game")
root.geometry("{}x{}".format(WIDTH,HEIGHT))
canvas = tk.Canvas(root, width = TABLE_SIZE*CELL_SIZE, height = TABLE_SIZE*CELL_SIZE, bg="#2e4057")
canvas.pack()

update_state = True

class Cell():
    def __init__(self, can, start_x, start_y, size = CELL_SIZE):
        self.can=can
        self.state = random.randint(0,1)
        self.next_state = 0
        self.id = self.can.create_rectangle((start_x, start_y,
                  start_x+size, start_y+size), fill="#2e4057")
        self.can.tag_bind(self.id, "<ButtonPress-1>", self.set_color)

        self.color_change=True

    def set_color(self, event=None):
        self.color_change = not self.color_change
        color="#2e4057"
        state = 0
        if not self.color_change:
            color="#52b788"
            state = 1
        self.can.itemconfigure(self.id, fill=color)
        self.state = state
        self.next_state = state

    def next(self):
        self.state = self.next_state
        color="#2e4057"
        if self.state == 1:
            color="#52b788"
        self.can.itemconfigure(self.id, fill=color)

class CellAutomaton():
    def __init__(self):
        self.__table = []
        self.__create_cells()

    def __create_cells(self):
        self.__table = [[0] * TABLE_SIZE for i in range(TABLE_SIZE)]
        for i in range(TABLE_SIZE):
            for j in range(TABLE_SIZE):
                self.__table[i][j] = Cell(canvas,j*CELL_SIZE, i*CELL_SIZE)

    def __calc_state(self,x,y):
        sx, ex = x - 1, x + 1
        sy, ey = y - 1, y + 1
        if sx < 0:
            sx = 0
        if sy < 0:
            sy = 0
        if ex > TABLE_SIZE - 1:
            ex = TABLE_SIZE - 1
        if ey > TABLE_SIZE - 1:
            ey = TABLE_SIZE - 1

        count = 0
        for i in range(sy,ey + 1):
            for j in range(sx, ex + 1):
                if self.__table[i][j].state == 1:
                    count += 1
        # except self state
        if self.__table[y][x].state == 1:
            count -= 1
        if count == 3:
            self.__table[y][x].next_state = 1
        elif count >= 4:
            self.__table[y][x].next_state = 0
        elif count <= 1:
            self.__table[y][x].next_state = 0

    def update(self):
        # update state
        for i in range(TABLE_SIZE):
            for j in range(TABLE_SIZE):
                self.__calc_state(j,i)

        # next generation
        for i in range(TABLE_SIZE):
            for j in range(TABLE_SIZE):
                self.__table[i][j].next()

def space_press(event):
    global update_state
    update_state = not update_state

def r_press(event):
    global update_state
    for i in range(TABLE_SIZE):
        for j in range(TABLE_SIZE):
            table[i][j].state = 0
    update_state = False
    update()


cella = CellAutomaton()
def loop():
    if update_state:
        cella.update()

    root.after(100,loop)

root.bind("<space>",space_press)
root.bind("r",r_press)
root.after(10,loop)
root.mainloop()

"""
def main():
    pass

if __name__ = '__main__':
    main()
"""
