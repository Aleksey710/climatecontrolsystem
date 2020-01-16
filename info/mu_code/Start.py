from tkinter import *
import time
def tick():
        label1.after(200, tick)
        label1['text'] = time.strftime('%H:%M:%S')        # час:хвилини:сек
        label2['text'] = time.strftime('%d-%m-%Y')

root=Tk()
root.title ("Годиник")
root["bg"] = ('white')  # колір фону вікна
label1 = Label(font='sums 14', fg='black', bg='white') # назва шрифта, розмір шрифта, колір шрифта, колір фону часів
label1.place(x=685, y=420)  # розташування віджета часів
label2 = Label(font='suns 14', fg='black', bg='white') # назва шрифта, розмір шрифта, колір шрифта, колір фону дати
label2.place(x=670, y=440)  # розташування віджета дати
root.geometry('800x480+-1+-28') # ширина=800, высота=480, x=300, y=200
not1 = Label(root, text= 'Аварія', font=("sums", 18),bg='red', fg= 'white', width= 30)

not1.place(x=30, y=150)  # розташування віджета "Аварія"
label1.after_idle(tick)
label2.after_idle(tick)
root.mainloop()

