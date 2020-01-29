import tkinter as tk

LAYOUT = [
    ['7', '8', '9', '/'],
    ['4', '5', '6', '*'],
    ['1', '2', '3', '-'],
    ['0', 'C', '=', '+'],
]

class Calculator(tk.Frame):
    def __init__(self,master = None):
        super().__init__(master)
        self.create_widget()

    def create_widget(self):
        self.display_text = tk.StringVar()
        display_label = tk.Label(text="CALCULATOR", font=("Courier",24), textvariable = self.display_text)
        display_label.grid(row=0,column =0,columnspan=4)
        # button generate
        button_list = []
        for y, row in enumerate(LAYOUT, 1):
            for x, char in enumerate(row):
                b = tk.Button(text=char, command=self.btn_click(char), font=("Courier",24),width=5)
                b.grid(column=x, row=y, sticky=(tk.N, tk.S, tk.E, tk.W))
                button_list.append(b)

    def btn_click(self, n):
        def func():
            text = self.display_text.get()
            if text == "" and not n.isdigit(): return
            if text == "0": text = ""

            if n == 'C':
                text = ""
            elif n == '=':
                if not text[-1].isdigit():
                    text = text[0:-1]
                self.display_text.set(eval(text))
                return
            elif not n.isdigit() and not text[-1].isdigit():
                text = text[0:-1] + str(n)
            else:
                text = text + str(n)
            self.display_text.set(text)
        return func

def main():
    root = tk.Tk()
    root.title("CALCULATOR")
    Calculator(root)
    root.mainloop()

if __name__ == '__main__':
    main()
