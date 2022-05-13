

#   PLOT  GENERATOR
#   NAKUL AGGARWAL          |   19CS10044
#   PYTHON GUI PROGRAMMING  |   ASSIGNMENT O2 PART O1
#   20.01.2021 TO 09.02.2021


from math import *
from tkinter import *
from tkinter import messagebox
from PIL import Image , ImageTk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg


OFFSET = 3
BACKGROUND = 'white'
FOREGROUND = 'black'
BORDER = 'darkslategrey'

root = Tk()
root.title('by NAKUL AGGARWAL')
root.configure(bg=BACKGROUND)

logo = Image.open('LOGO_PLOT_GEN.png')
logo = logo.resize((500,50))
logo = ImageTk.PhotoImage(logo)
logo_label = Label(image=logo)
logo_label.image = logo
logo_label.grid(row=OFFSET, column=0, columnspan=5)


def makePlot () :
    
    success = 1
    exp_orig = input_exp.get().strip()
    
    if not len(exp_orig):
        messagebox.showerror('ERROR', 'NO EXPRESSION ENTERED !')
        return
    if not len(input_lowerb.get().strip()):
        messagebox.showerror('ERROR', 'NO LOWER BOUND ENTERED !')
        return
    if not len(input_upperb.get().strip()):
        messagebox.showerror('ERROR', 'NO UPPER BOUND ENTERED !')
        return
    try :
        l = float(input_lowerb.get())
    except :
        messagebox.showerror('ERROR', 'LOWER BOUND MUST BE A FLOATING POINT OR AN INTEGERAL NUMBER !')
        return
    try :
        u = float(input_upperb.get())
    except :
        messagebox.showerror('ERROR', 'UPPER BOUND MUST BE A FLOATING POINT OR AN INTEGERAL NUMBER !')
        return
    if u <= l:
        messagebox.showerror('ERROR', 'LOWER BOUND MUST BE STRICTLY LESS THAN THE UPPER BOUND !')
        return
    
    exp_orig = exp_orig.replace('^', '**').replace('PI', '(pi)')
    exp_orig = exp_orig.replace('log', 'log10').replace('ln', 'log')

    X = list()
    Y = list()
    count = 10e3
    step = ( u - l ) / count
    x = l + step
    
    while x < u :
        X.append(x)
        exp = exp_orig + ""
        exp.replace('x', "({})".format(x))
        try:
            Y.append( eval(exp) )
        except:
            messagebox.showerror('ERROR', 'APPLICATION IS UNABLE TO INTERPRET THE EXPRESSION AT SOME VALUES !')
            return
        x += step
    
    f = Figure( figsize=(7,5), dpi=100)
    a = f.add_subplot(111)
    a.plot(X, Y, linewidth=2, color='#FF1493')
    a.title.set_text(input_exp.get().strip())
    a.grid()
    canvas = FigureCanvasTkAgg(f, root)
    canvas.draw()
    canvas.get_tk_widget().grid(row=8+OFFSET, column=0, columnspan=5)


def clear ():
    
    input_exp.delete(0, END)
    input_exp.insert(0, "")
    input_lowerb.delete(0, END)
    input_lowerb.insert(0, "")
    input_upperb.delete(0, END)
    input_upperb.insert(0, "")


field_exp = Label(root, text="ENTER EXPRESSION\t", fg=FOREGROUND, bg=BACKGROUND, anchor=W, width=23, bd=5, font=('',15,'bold'))
input_exp = Entry(root, width=45, bg='white', font=('raleway',15), highlightthickness=2)

field_lowerb = Label(root, text="ENTER LOWER BOUND\t", fg=FOREGROUND, bg=BACKGROUND, anchor=W, width=23, bd=5, font=('',15,'bold'))
input_lowerb = Entry(root, width=45, bg='white', font=('raleway',15), highlightthickness=2)

field_upperb = Label(root, text="ENTER UPPER BOUND\t", fg=FOREGROUND, bg=BACKGROUND, anchor=W, width=23, bd=5, font=('',15,'bold'))
input_upperb = Entry(root, width=45, bg='white', font=('Raleway',15), highlightthickness=2)

generate = Button(root, text='PLOT FUNCTION', width=20, font=('',12,'bold'), pady=12, command=makePlot)
clear_btn = Button(root, text='CLEAR ALL FIELDS', width=20, font=('',12,'bold'), pady=12, command=clear)
close_btn = Button(root, text="CLOSE WINDOW", width=20, font=('',12,'bold'), pady=12, command=root.destroy)

generate['background']='white'
clear_btn['background']='white'
close_btn['background']='white'

input_exp.config(highlightbackground = BORDER, highlightcolor= BORDER)
input_upperb.config(highlightbackground = BORDER, highlightcolor= BORDER)
input_lowerb.config(highlightbackground = BORDER, highlightcolor= BORDER)

field_exp.grid(row=2+OFFSET, column=0, columnspan=1)
input_exp.grid(row=2+OFFSET, column=2, columnspan=3, padx=5)
field_lowerb.grid(row=3+OFFSET, column=0, columnspan=1)
input_lowerb.grid(row=3+OFFSET, column=2, columnspan=3)
field_upperb.grid(row=4+OFFSET, column=0, columnspan=1)
input_upperb.grid(row=4+OFFSET, column=2, columnspan=3)

clear_btn.grid(row=6+OFFSET, column=0, columnspan=1)
generate.grid(row=6+OFFSET, column=2, columnspan=2)
close_btn.grid(row=6+OFFSET, column=4, columnspan=1)

def onEnter_generate (e):
    generate['background']='black'
    generate['foreground']='white'
    
def onLeave_generate (e):
    generate['background']='white'
    generate['foreground']='black'
    
def onEnter_clear_btn (e):
    clear_btn['background']='black'
    clear_btn['foreground']='white'
    
def onLeave_clear_btn (e):
    clear_btn['background']='white'
    clear_btn['foreground']='black'
    
def onEnter_close_btn (e):
    close_btn['background']='black'
    close_btn['foreground']='white'
    
def onLeave_close_btn (e):
    close_btn['background']='white'
    close_btn['foreground']='black'

generate.bind("<Enter>", onEnter_generate )
generate.bind("<Leave>", onLeave_generate )
clear_btn.bind("<Enter>", onEnter_clear_btn )
clear_btn.bind("<Leave>", onLeave_clear_btn )
close_btn.bind("<Enter>", onEnter_close_btn )
close_btn.bind("<Leave>", onLeave_close_btn )

root.grid_rowconfigure(0, minsize=20)
root.grid_rowconfigure(1+OFFSET, minsize=20)
root.grid_rowconfigure(5+OFFSET, minsize=20)
root.grid_rowconfigure(7+OFFSET, minsize=20)

root.mainloop()
