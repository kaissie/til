import tkinter as tk
import random

FRAMERATE = 17
W = 480
H = 640

class Bird:
    def __init__(self, cv, y = H/2):
        self.cv = cv
        self.size = 20
        self.y = H / 2
        self.vy = 0
        self.ay = 0.2
        self.up_count = 0

    def draw(self):
        self.cv.delete('bird')
        self.cv.create_oval(W / 2 - self.size, self.y - self.size, W / 2 + self.size, self.y + self.size, fill="#33b490", width="0", tags="bird")
        
    def up(self, event = None):
        self.vy = -8
        
        if self.up_count < 10:
            self.up_count += 1
            root.after(FRAMERATE, self.up)
        else:
            self.vy = 0
            self.up_count = 0
        self.draw()

    def down(self):
        if self.vy < 9.8:
            self.vy += self.ay
        self.y += self.vy
        self.draw()
        root.after(FRAMERATE, self.down)

    
class Pipe:
    GAP = 160
    COLOR = "#33b490"
    def __init__(self, cv, y = H/2):
        self.cv = cv
        self.x = W
        self.height = random.randrange(50, 450)
        self.top = self.height
        self.bottom = self.height + self.GAP
        self.width = 80

    def move(self):
        self.x -= 5
        self.draw()
        if self.x < -self.width:
            self.x = W
            self.height = random.randrange(50, 450)
            self.top = self.height
            self.bottom = self.height + self.GAP
            self.COLOR = "#33b490"
            
        root.after(FRAMERATE, self.move)

    def draw(self):
        self.cv.delete('pipe')
        self.cv.create_rectangle(self.x,           0, self.x + self.width, self.top, fill=self.COLOR, width="0", tags="pipe")
        self.cv.create_rectangle(self.x, self.bottom, self.x + self.width,        H, fill=self.COLOR, width="0", tags="pipe")

def collision():
    if (bird.y - bird.size  < pipe.top) or (pipe.bottom < bird.y + bird.size ):
        if (W / 2 + bird.size) > pipe.x and (W / 2 - bird.size < pipe.x + pipe.width):
            pipe.COLOR = "#ff5151"
    root.after(FRAMERATE,collision)
       
root = tk.Tk()
canvas = tk.Canvas(root, bg='#fff5e3', width=W, height=H)
canvas.pack()
bird = Bird(canvas)
pipe = Pipe(canvas)

def launch():
    root.title(u"Flappy Bird")
    root.geometry("{}x{}".format(W,H))
    root.minsize(W, H)

    
    root.bind("<space>", bird.up)
    root.after(FRAMERATE, bird.down)
    root.after(FRAMERATE, pipe.move)
    root.after(FRAMERATE,collision)
    root.mainloop()


def main():
    print("Flappy Bird!")
    
    launch()

if __name__ == "__main__":
    main()