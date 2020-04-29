from tkinter import *
from tkinter import messagebox


window1 = Tk()
window1.title("Welcome to POV Display")
window1.geometry("400x400+500+150")

window2 = Tk()
window2.title("Free Text")
window2.geometry("400x400+500+150")
window2.withdraw()

window3 = Tk()
window3.title("Heart Rate")
window3.geometry("400x400+500+150")
window3.withdraw()

window4 = Tk()
window4.title("Audio Visualizer")
window4.geometry("400x400+500+150")
window4.withdraw()

window5 = Tk()
window5.title("Free Style Drawing")
window5.geometry("400x400+500+150")
window5.withdraw()

window6 = Tk()
window6.title("Free Style Drawing")
window6.geometry("1150x550+150+100")
window6.withdraw()

lbl = Label(window1, text='POV Display', font=("Arial Bold",25), padx=100)
lbl.grid(column=0, row=0, pady = 10)
#read.focus()
chk_state = BooleanVar()
chk_state.set(1)  # set check state
#############################################################################################################
def clicked1():
    window1.withdraw()
    window2.update()
    window2.deiconify()
    window2.focus_force()
def backbutton1():
    window2.withdraw()
    window1.update()
    window1.deiconify()
    window1.focus_force()
def clicked2():
    window1.withdraw()
    window3.update()
    window3.deiconify()
    window3.focus_force()
def backbutton2():
    window3.withdraw()
    window1.update()
    window1.deiconify()
    window1.focus_force()
def clicked3():
    window1.withdraw()
    window4.update()
    window4.focus_force()
    window4.deiconify()
def backbutton3():
    window4.withdraw()
    window1.update()
    window1.deiconify()
    window1.focus_force()
def clicked4():
    window1.withdraw()
    window5.update()
    window5.deiconify()
    window5.focus_force()
def backbutton4():
    window5.withdraw()
    window1.update()
    window1.deiconify()
    window1.focus_force()

def frontbutton():
    window5.withdraw()
    window6.update()
    window6.deiconify()
    window6.focus_force()

def backbutton5():
    window6.withdraw()
    window5.update()
    window5.deiconify()
    window5.focus_force()

#####################################################################################################################################window 1
btn1 = Button(window1, text="Free Text", bg="black", fg="white", padx = 10, pady = 5, command=clicked1)
btn1.grid(column=0, row=2, pady = 10)
btn1.config(height=1, width = 30)

btn2 = Button(window1, text="Heart Rate", bg="black", fg="white", command=clicked2, padx = 10, pady = 5)
btn2.grid(column=0, row=3, pady=10)
btn2.config(height=1, width = 30)

btn3 = Button(window1, text="Audio Visualizer", bg="black", fg="white", command=clicked3, padx = 10, pady = 5)
btn3.grid(column=0, row=4, pady=10)
btn3.config(height=1, width = 30)

btn4 = Button(window1, text="Free Style Drawing", bg="black", fg="white", command=clicked4, padx = 10, pady = 5)
btn4.grid(column=0, row=5, pady=10)
btn4.config(height=1, width = 30)

chk = Checkbutton(window1, text='Choose', var=chk_state)
chk.grid(column=0, row=6)
################################################################################################################################################window 2

btn1 = Button(window2, text="Back", bg="black", fg="white", command=backbutton1, padx = 10, pady = 5)
btn1.grid(column=0, row=0)
btn1 = Button(window3, text="Back", bg="black", fg="white", command=backbutton2, padx = 10, pady = 5)
btn1.grid(column=0, row=0)
btn1 = Button(window4, text="Back", bg="black", fg="white", command=backbutton3, padx = 10, pady = 5)
btn1.grid(column=0, row=0)
btn1 = Button(window5, text="Back", bg="black", fg="white", command=backbutton4, padx = 10, pady = 5)
btn1.grid(column=0, row=0)
btn1 = Button(window6, text="Back", bg="black", fg="white", command=backbutton5, padx = 10, pady = 5)
btn1.grid(column=0, row=0)
#################################################################################################################################Free Text###################
lbl = Label(window2, text='Free Text', font=("Arial Bold",25), padx=70)
lbl.grid(column=1, row=1, pady = 10)
free_text = Entry(window2, width=30)
free_text.grid(column=1, row=5, padx = 60, pady=50)
btn2 = Button(window2, text="Send", bg="black", fg="white", padx = 10)
btn2.grid(column=1, row=7)
##################################################################################################################################Heart rate Monitoring
lbl = Label(window3, text='Heart Rate', font=("Arial Bold",25), padx=60)
lbl.grid(column=1, row=1, pady = 1)
lbl = Label(window3, text='Monitoring', font=("Arial Bold",25), padx=60)
lbl.grid(column=1, row=2, pady = (10,100))
btn2 = Button(window3, text="Start", bg="black", fg="white", padx = 50)
btn2.grid(column=1, row=7)
################################################################################################################################Audio Visualizer
lbl = Label(window4, text='Audio Visualizer', font=("Arial Bold",25), padx=25)
lbl.grid(column=1, row=1, pady = (1,80))



btntochange = Button(window4, text="Start", bg="black", fg="white", padx = 30)
btntochange.grid(column=1, row=7)
################################################################################################################################Free style Drawing
values = [0 for x in range(1080)]

lbl = Label(window5, text='Free Drawing', font=("Arial Bold",25), padx=35)
lbl.grid(column=1, row=1, pady = (1,80))

btn2 = Button(window5, text="Start", bg="black", command=frontbutton, fg="white", padx = 30)
btn2.grid(column=1, row=7)

def printvalues():
    lbl.config(text = values)
    lbl.config(font=("Arial Bold",10))
btn3 = Button(window5, text="Send", bg="black", command=printvalues, fg="white", padx = 30)
btn3.grid(column=1, row=8)

(rows,cols) =  (18,60)
btn=  [[Button() for x in range(cols)] for x in range(rows)]
values_number = 0
def btnClick(i,j, values_number):
    btn[i][j].config(bg = 'red')
    btn[i][j].config(text="1")
    values[round(values_number/60)] = 1

for i in range(18):
    for j in range(60):
        btn[i][j] = Button(window6, text='0', bg="black", fg='white', padx='1', pady='1',  command = lambda i=i, j=j, values_number=values_number: btnClick(i, j, values_number))
        btn[i][j].config(width='1', height='1')
        btn[i][j].grid(column=j+1, row=i+1)
        values_number=values_number+1
###########################################################################################################################################

a = 1
print(bin(a))
window1.mainloop()
window2.mainloop()
window3.mainloop()
window4.mainloop()
window5.mainloop()
window6.mainloop()


