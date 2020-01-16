from tkinter import *
def button_clicked():
    print ("Натиснути")
root=Tk()
button1 = Button()
button1.pack()
button2 = Button(root, bg="red", text=u"Натисни",comand=button_clicked)
button2.pack()

root.mainloop()
