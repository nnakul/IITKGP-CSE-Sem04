

#   SOCIAL  NETWORK
#   NAKUL AGGARWAL          |   19CS10044
#   PYTHON GUI PROGRAMMING  |   ASSIGNMENT O2 PART O2
#   20.01.2021 TO 09.02.2021


from tkinter import *
from tkinter.font import Font
from tkinter import ttk
from tkinter import filedialog
from tkinter import messagebox
from PIL import Image, ImageTk
import time


class Post :
    def __init__ ( self , sender , reciever , content , img = "", isGroupMsg=False, groupName="" ):
        
        self.sender = sender
        self.reciever = reciever
        self.isGroupMsg = isGroupMsg
        self.groupName = groupName
        self.content = content
        self.imageLoc = img


class User :
    def __init__ ( self, id, contacts) :
        
        self.id = id
        self.contacts = contacts
        self.groups = list()
        self.postsOut = list()
        self.postsIn = list()
        
        
class Group :
    def __init__ ( self, id, members) :
        
        self.id = id
        self.members = members
        self.postsIn = list()
        

def readSocialNetworkFile ( ) :
    
    global USERS, GROUPS, USER_NAMES, LOOKUP
    f = open('social_network.txt', 'r')
    x = int(f.readline())
    
    for i in range(x) :
        line = f.readline()[1:-2]
        tokens = line.split(':')
        contacts = tokens[1].split(', ')
        contacts[0] = contacts[0].strip()
        if len(contacts) == 1 and contacts[0].strip() == "" :
            contacts = []
        userId = tokens[0]
        USER_NAMES.append(userId)
        USERS.append(User(userId, contacts))
        LOOKUP[userId] = USERS[-1]
        
    x = int(f.readline())
    
    for i in range(x) :
        if i == x-1 :   line = f.readline()[1:-1]
        else : line = f.readline()[1:-2]
        tokens = line.split(':')
        members = tokens[1].split(', ')
        members[0] = members[0].strip()
        groupId = tokens[0]
        g = Group(groupId, members)
        LOOKUP[groupId] = g
        GROUPS.append(g)
        for m in members:
            LOOKUP[m].groups.append(groupId)
    
    f.close()


def loadOldMessages ( ) :
    
    try :
        file = open("messages.txt", "r")
    except :
        file = open("messages.txt", "w")
        file.close()
        return
    content = file.read()
    file.close()
    
    posts = content.split("\n"+DELIMITER+"\n")
    for post in posts :
        chunk1 = post.split("\nTO : ")
        fromm = chunk1[0][7:]
        if not fromm in LOOKUP :
            continue
        chunk2 = chunk1[1].split("\nMESSAGE : ")
        to = chunk2[0]
        if not to in LOOKUP :
            continue
        chunk3 = chunk2[1].split("\nIMAGE DEST. : ")
        msg = chunk3[0]
        chunk4 = chunk3[1].split("\nSENT TO A GROUP? : ")
        imgLoc = chunk4[0]
        isGroupMsg = True if chunk4[1] == "yes" else False
        
        if isGroupMsg :
            for m in LOOKUP[to].members :
                if m == fromm : continue
                if not m in LOOKUP :
                    continue
                p = Post( fromm , m , msg , imgLoc , True , to )
                LOOKUP[fromm].postsOut.insert(0, p)
                LOOKUP[m].postsIn.insert(0, p)
                
        else :
            p = Post( fromm , to , msg , imgLoc )
            LOOKUP[fromm].postsOut.insert(0, p)
            LOOKUP[to].postsIn.insert(0, p)


def newUserSelected ( ) :
    
    global CURRENT_USER, SCREEN 
    old = CURRENT_USER
    CURRENT_USER = DROP.get()
    
    if old != CURRENT_USER :
        HEADER.configure( text = "   ∆ SOCIAL NETWORK ♪                               USER CHANGED" )
        var = IntVar()
        root.after(250, var.set, 1)
        root.wait_variable(var)
        HEADER.configure( text = "   ∆ SOCIAL NETWORK ♪" )
    
    if SCREEN == "menu" or old == CURRENT_USER :   return
    
    SCREEN = "menu"
    HOMEPAGE_L.grid_forget()
    width_ = 25
    font_ = 23
    
    for l in GROUP_LABELS:      l.grid_forget()
    for l in CONTACT_LABELS:    l.grid_forget()
    for l in INBOX_WIDGETS:     l.grid_forget()
    for l in COMPOSE_LABELS:
        if l is None : continue
        l.grid_forget()
        
    global SHOW_INBOX, SHOW_CONTACTS, SHOW_GROUPS, COMPOSE_MSG
    SHOW_INBOX = Button(root, text='SHOW INCOMING MESSAGES', bg="white", width=width_, font=('',font_,'bold'), command=showInbox)
    SHOW_CONTACTS = Button(root, text='SHOW CONTACT LIST', bg="white", width=width_, font=('',font_,'bold'), command=showContacts)
    SHOW_GROUPS = Button(root, text='SHOW GROUPS', bg="white", width=width_, font=('',font_,'bold'), command=showGroups)
    COMPOSE_MSG = Button(root, text='COMPOSE MESSAGE', bg="white", width=width_, font=('',font_,'bold'), command=composeMessage)

    start = 4
    span = 32
    first = 2
    gap = 35
    
    root.grid_rowconfigure(start, minsize=45)
    
    SHOW_INBOX.grid(row=start+1, column=first, columnspan=span, sticky=W+E)
    root.grid_rowconfigure(start+2, minsize=gap)
    
    SHOW_CONTACTS.grid(row=start+3, column=first, columnspan=span, sticky=W+E)
    root.grid_rowconfigure(start+4, minsize=gap)
    
    SHOW_GROUPS.grid(row=start+5, column=first, columnspan=span, sticky=W+E)
    root.grid_rowconfigure(start+6, minsize=gap)
    
    COMPOSE_MSG.grid(row=start+7, column=first, columnspan=span, sticky=W+E)
    root.grid_rowconfigure(start+8, minsize=gap)
    

def goBack ( ) :
    
    global CURRENT_USER, SCREEN 
    if SCREEN == "menu" or SCREEN == "home" :   return
    SCREEN = "menu"
    
    width_ = 25
    font_ = 23
    
    for l in GROUP_LABELS:      l.grid_forget()
    for l in CONTACT_LABELS:    l.grid_forget()
    for l in INBOX_WIDGETS:     l.grid_forget()
    for l in COMPOSE_LABELS:
        if l is None : continue
        l.grid_forget()
    
    global SHOW_INBOX, SHOW_CONTACTS, SHOW_GROUPS, COMPOSE_MSG
    SHOW_INBOX = Button(root, text='SHOW INCOMING MESSAGES', bg="white", width=width_, font=('',font_,'bold'), command=showInbox)
    SHOW_CONTACTS = Button(root, text='SHOW CONTACT LIST', bg="white", width=width_, font=('',font_,'bold'), command=showContacts)
    SHOW_GROUPS = Button(root, text='SHOW GROUPS', bg="white", width=width_, font=('',font_,'bold'), command=showGroups)
    COMPOSE_MSG = Button(root, text='COMPOSE MESSAGE', bg="white", width=width_, font=('',font_,'bold'), command=composeMessage)

    start = 4
    span = 32
    first = 2
    gap = 35
    
    root.grid_rowconfigure(start, minsize=45)
    
    SHOW_INBOX.grid(row=start+1, column=first, columnspan=span, sticky=W+E)
    root.grid_rowconfigure(start+2, minsize=gap)
    
    SHOW_CONTACTS.grid(row=start+3, column=first, columnspan=span, sticky=W+E)
    root.grid_rowconfigure(start+4, minsize=gap)
    
    SHOW_GROUPS.grid(row=start+5, column=first, columnspan=span, sticky=W+E)
    root.grid_rowconfigure(start+6, minsize=gap)
    
    COMPOSE_MSG.grid(row=start+7, column=first, columnspan=span, sticky=W+E)
    root.grid_rowconfigure(start+8, minsize=gap)
    

def nextPageGroups ( residual_groups ) :
    
    global GROUP_LABELS
    for widget in GROUP_LABELS :
        widget.grid_forget()

    GROUP_LABELS = list()
    i = 0
    initRow = 7
    
    root.grid_rowconfigure(initRow-3, minsize=25)
    root.grid_rowconfigure(initRow-4, minsize=25)
    l = Label(root, text="  □  LIST OF GROUPS", fg="#FF8C00", bg="white", width=60, font=('',29,'bold'))
    l.grid(row=initRow-2, column=1, columnspan=34)
    root.grid_rowconfigure(initRow-1, minsize=35)
    GROUP_LABELS.append(l)
    
    flag = 0
    count = 0
    for g in residual_groups :
        if count == 15 :
            next_button = Button( root, text="NEXT PAGE", fg="white", bg="black", width=35, font=('',22,'bold'), 
                                  command=lambda : nextPageGroups(residual_groups[15:]) )
            next_button.grid(row=initRow+i, column=19, columnspan=15)
            GROUP_LABELS.append(next_button)
            return
        l = Label(root, text="   ●   "+g, fg="black", bg="white", width=35, font=('',24,'bold'), anchor="w")
        GROUP_LABELS.append(l)
        if flag == 0 :
            l.grid(row=initRow+i, column=2, columnspan=15)
            flag = 1
        elif flag == 1 :
            l.grid(row=initRow+i, column=19, columnspan=15)
            flag = 0
            root.grid_rowconfigure(initRow+1+i, minsize=20)
            i += 2
        count += 1


def showGroups ( ) :
    
    global GROUP_LABELS, CURRENT_USER, SCREEN
    
    GROUP_LABELS = list()
    user = LOOKUP[CURRENT_USER]
    SHOW_INBOX.grid_forget()
    SHOW_CONTACTS.grid_forget()
    SHOW_GROUPS.grid_forget()
    COMPOSE_MSG.grid_forget()
    
    SCREEN = "groups"
    
    i = 0
    initRow = 7
    
    root.grid_rowconfigure(initRow-3, minsize=25)
    root.grid_rowconfigure(initRow-4, minsize=25)
    l = Label(root, text="  □  LIST OF GROUPS", fg="#FF8C00", bg="white", width=60, font=('',29,'bold'))
    l.grid(row=initRow-2, column=1, columnspan=34)
    root.grid_rowconfigure(initRow-1, minsize=35)
    GROUP_LABELS.append(l)
    
    flag = 0
    count = 0
    for g in user.groups :
        if count == 15 :
            next_button = Button( root, text="NEXT PAGE", fg="white", bg="black", width=35, font=('',22,'bold'), command=lambda : nextPageGroups(user.groups[15:]) )
            next_button.grid(row=initRow+i, column=19, columnspan=15)
            GROUP_LABELS.append(next_button)
            return
        l = Label(root, text="   ●   "+g, fg="black", bg="white", width=35, font=('',24,'bold'), anchor="w")
        GROUP_LABELS.append(l)
        if flag == 0 :
            l.grid(row=initRow+i, column=2, columnspan=15)
            flag = 1
        elif flag == 1 :
            l.grid(row=initRow+i, column=19, columnspan=15)
            flag = 0
            root.grid_rowconfigure(initRow+1+i, minsize=20)
            i += 2
        count += 1


def showFullMessage ( e ) :
    
    global CURRENT_MESSAGE, INBOX_WIDGETS, PICTURE, picture, CURRENT_USER
    idx = INBOX_WIDGETS[2].curselection()[0]
    post = LOOKUP[CURRENT_USER].postsIn[idx]
    
    INBOX_WIDGETS[-1].config(state=NORMAL)
    INBOX_WIDGETS[-1].delete(1.0, END)
    INBOX_WIDGETS[-1].insert(END, post.content) 
    
    if post.imageLoc.strip() != "" :
        INBOX_WIDGETS[-1].insert(END, "\n")
        try :
            image = Image.open(post.imageLoc.strip())
        except :
            INBOX_WIDGETS[-1].config(state=DISABLED)
            return
        forSize = ImageTk.PhotoImage(image)
        height = forSize.height()
        width = forSize.width()
        if width > 1440 :
            height = int( 1440 * height / width )
            width = 1440
        picture = ImageTk.PhotoImage( image.resize((width, height), Image.ANTIALIAS) )
        INBOX_WIDGETS[-1].image_create(END, image=picture)
    
    INBOX_WIDGETS[-1].config(state=DISABLED)


def showInbox ( ) :

    global CURRENT_USER, SCREEN, INBOX_WIDGETS
    
    user = LOOKUP[CURRENT_USER]
    SHOW_INBOX.grid_forget()
    SHOW_CONTACTS.grid_forget()
    SHOW_GROUPS.grid_forget()
    COMPOSE_MSG.grid_forget()
    
    SCREEN = "inbox"
    
    frame = Frame(root)
    scrollbar = Scrollbar( frame , orient = VERTICAL )
    messages = Listbox( frame , width = 65 , yscrollcommand = scrollbar.set, font=('',16,'bold'), activestyle='none', height=5, 
                        selectbackground=THEME, selectforeground="white", selectmode=SINGLE )
    INBOX_WIDGETS = [ frame , scrollbar , messages ]
    
    for post in user.postsIn :
        if post.isGroupMsg :
            messages.insert(END, post.sender + " posted in the group -- " + post.groupName )
        else :  messages.insert(END, post.sender + " sent a personal message " )
            
    scrollbar.config(command=messages.yview)
    scrollbar.grid(row=4, column=35, rowspan=5, sticky=N+S+W)
    
    frame.grid(row=4, column=1, columnspan=34, rowspan=5)
    
    messages.grid(row=4, column=1, columnspan=34, padx=5, pady=5)
    messages.bind('<Double-1>', showFullMessage)
    
    DISPLAY = Text( root, bg='white', height=17, font=('Helvetica',16,''), wrap=WORD, padx=8, pady=8 )
    DISPLAY.insert(END, " YOUR MESSAGE WILL BE DISPLAYED HERE...") 
    DISPLAY.config(state=DISABLED)
    
    root.grid_rowconfigure(9, minsize=20)
    DISPLAY.grid(row=10, column=1, columnspan=34, rowspan=13, sticky=N+S+E+W)
    
    INBOX_WIDGETS.append(DISPLAY)


def nextPageContacts ( residual_contacts ) :
    
    global CONTACT_LABELS
    for widget in CONTACT_LABELS :
        widget.grid_forget()

    CONTACT_LABELS = list()
    i = 0
    initRow = 7
    
    root.grid_rowconfigure(initRow-3, minsize=25)
    root.grid_rowconfigure(initRow-4, minsize=25)
    l = Label(root, text="  □  LIST OF CONTACTS", fg="#FF8C00", bg="white", width=60, font=('',29,'bold'))
    l.grid(row=initRow-2, column=1, columnspan=34)
    root.grid_rowconfigure(initRow-1, minsize=30)
    CONTACT_LABELS.append(l)
    
    flag = 0
    count = 0
    
    for c in residual_contacts :
        
        if count == 23 :
            next_button = Button( root, text="NEXT PAGE", fg="white", bg="black", width=22, font=('',22,'bold'), 
                                  command=lambda : nextPageContacts(residual_contacts[23:]) )
            next_button.grid(row=initRow+i, column=24, columnspan=11)
            CONTACT_LABELS.append(next_button)
            return
        
        l = Label(root, text="   ●   "+c, fg="black", bg="white", width=22, font=('',24,'bold'), anchor="w")
        CONTACT_LABELS.append(l)
        if flag == 0 :
            l.grid(row=initRow+i, column=1, columnspan=11)
            flag = 1
        elif flag == 1 :
            l.grid(row=initRow+i, column=12, columnspan=12)
            flag = 2
        elif flag == 2 :
            l.grid(row=initRow+i, column=24, columnspan=11)
            flag = 0
            root.grid_rowconfigure(initRow+1+i, minsize=20)
            i += 2
        count += 1


def showContacts ( ) :
    
    global CONTACT_LABELS, CURRENT_USER, SCREEN
    CONTACT_LABELS = list()
    
    user = LOOKUP[CURRENT_USER]
    SHOW_INBOX.grid_forget()
    SHOW_CONTACTS.grid_forget()
    SHOW_GROUPS.grid_forget()
    COMPOSE_MSG.grid_forget()
    
    SCREEN = "contacts"
    i = 0
    initRow = 7
    
    root.grid_rowconfigure(initRow-3, minsize=25)
    root.grid_rowconfigure(initRow-4, minsize=25)
    l = Label(root, text="  □  LIST OF CONTACTS", fg="#FF8C00", bg="white", width=60, font=('',29,'bold'))
    l.grid(row=initRow-2, column=1, columnspan=34)
    root.grid_rowconfigure(initRow-1, minsize=30)
    CONTACT_LABELS.append(l)
    
    flag = 0
    count = 0
    
    for c in user.contacts :
        
        if count == 23 :
            next_button = Button( root, text="NEXT PAGE", fg="white", bg="black", width=22, font=('',22,'bold'), 
                                  command=lambda : nextPageContacts(user.contacts[23:]) )
            next_button.grid(row=initRow+i, column=24, columnspan=11)
            CONTACT_LABELS.append(next_button)
            return
        
        l = Label(root, text="   ●   "+c, fg="black", bg="white", width=22, font=('',24,'bold'), anchor="w")
        CONTACT_LABELS.append(l)
        if flag == 0 :
            l.grid(row=initRow+i, column=1, columnspan=11)
            flag = 1
        elif flag == 1 :
            l.grid(row=initRow+i, column=12, columnspan=12)
            flag = 2
        elif flag == 2 :
            l.grid(row=initRow+i, column=24, columnspan=11)
            flag = 0
            root.grid_rowconfigure(initRow+1+i, minsize=20)
            i += 2
        count += 1


def chooseImage ( ) :
    
    global COMPOSE_LABELS, FILE_SELECTED
    if not COMPOSE_LABELS[-1] is None :
        COMPOSE_LABELS[-1].grid_forget()
    root.filename = filedialog.askopenfilename(title='SELECT AN IMAGE', filetypes=((".jpg IMAGES","*.jpg"), (".png IMAGES", "*.png")) )
    FILE_SELECTED = root.filename
    l = Label(root, text = root.filename, bg=BACKGROUND, font=('',18,''), anchor="w") 
    l.grid(row=16, column=13, columnspan=20)
    COMPOSE_LABELS[-1] = l


def sendMessage ( ) :
    
    global COMPOSE_LABELS, FILE_SELECTED
    
    sender = CURRENT_USER
    user = LOOKUP[sender]
    reciever = COMPOSE_LABELS[2].get().strip()
    message = COMPOSE_LABELS[4].get("1.0", "end-1c").strip()
    img = FILE_SELECTED
    
    FILE_SELECTED = ""
    
    if reciever == "" :
        messagebox.showerror('ERROR', 'YOU MUST SPECIFY A RECIEVER !')
        return
    
    if not reciever in user.contacts and not reciever in user.groups :
        messagebox.showerror('ERROR', 'YOU ARE NOT IN CONTACT WITH ANY USER / GROUP WITH THIS ID !')
        return
        
    if img == "" and message == "" :
        messagebox.showerror('ERROR', 'NO ATTATCHED / WRITTEN MATERIAL WAS FOUND TO BE POSTED TO THE RECIEVER !')
        return
    
    file = open( "messages.txt" , "a" )
    file.write( "FROM : " + sender )
    file.write( "\nTO : " + reciever )
    file.write( "\nMESSAGE : " + message )
    file.write( "\nIMAGE DEST. : " + img )
    
    if reciever in user.contacts :
        file.write( "\nSENT TO A GROUP? : no\n" + DELIMITER + "\n"  )
        file.close()
        post = Post ( sender , reciever , message , img )
        user.postsOut.append(post)
        LOOKUP[reciever].postsIn.insert(0,post)
        goBack()
        return
        
    for member in LOOKUP[reciever].members :
        if member == sender :   continue
        post = Post ( sender , member , message , img , True , reciever )
        user.postsOut.append(post)
        LOOKUP[member].postsIn.insert(0,post)
    
    file.write( "\nSENT TO A GROUP? : yes\n" + DELIMITER + "\n" )
    file.close()
    goBack()
    return


def composeMessage ( ) :
    
    global COMPOSE_LABELS, CURRENT_USER, SCREEN, FILE_SELECTED

    user = LOOKUP[CURRENT_USER]
    SHOW_INBOX.grid_forget()
    SHOW_CONTACTS.grid_forget()
    SHOW_GROUPS.grid_forget()
    COMPOSE_MSG.grid_forget()
    
    SCREEN = "compose"
    
    i = 0
    initRow = 7
    
    root.grid_rowconfigure(initRow-3, minsize=20)
    root.grid_rowconfigure(initRow-4, minsize=20)
    head = Label(root, text="  □  COMPOSE NEW MESSAGE", fg="#FF8C00", bg="white", width=60, font=('',29,'bold'))
    head.grid(row=initRow-2, column=1, columnspan=34)
    root.grid_rowconfigure(initRow-1, minsize=35)
    
    askReciever = Label(root, text="RECIEVER'S USER ID  ", bg=BACKGROUND, font=('',22,'bold'), anchor="w")
    reciever = Entry(root, width=50, bg='white', font=('',20,''), highlightthickness=2)
    askReciever.grid(row=initRow, column=2, columnspan=8)
    reciever.grid(row=initRow, column=13, columnspan=20)
    
    root.grid_rowconfigure(initRow+1, minsize=25)
    
    initRow += 2
    
    root.grid_rowconfigure(initRow, minsize=20)
    
    l = Label(root, text = "ENTER MESSAGE  ", bg=BACKGROUND, font=('',22,'bold'), anchor="w") 
    l.grid(row=initRow+1, column=2, columnspan=8)
    textbox = Text(root, height = 8, width = 65, font=('',16,''), highlightthickness=2, padx=5, pady=4, wrap=WORD)
    textbox.grid(row=initRow+1, column=13, columnspan=20, rowspan=5)
    
    root.grid_rowconfigure(initRow+6, minsize=28)
    
    CHOOSE_IMG = Button(root, text='CHOOSE IMAGE', bg='white',  font=('',22,'bold'), command = chooseImage)
    CHOOSE_IMG.grid(row=initRow+7, column=2, columnspan=8)
    
    root.grid_rowconfigure(initRow+8, minsize=30)
    
    SEND = Button(root, text='SEND MESSAGE', bg='white',  font=('',22,'bold'), command = sendMessage)
    SEND.grid(row=initRow+9, column=1, columnspan=34)
    
    root.grid_rowconfigure(initRow+10, minsize=30)
    
    COMPOSE_LABELS = [ head , askReciever, reciever, l , textbox , CHOOSE_IMG , SEND, None ]


def defocus ( event ) :
    
    event.widget.master.focus_set()


SHOW_INBOX = None
SHOW_CONTACTS = None
SHOW_GROUPS = None
COMPOSE_MSG = None
GROUP_LABELS = list()
CONTACT_LABELS = list()
COMPOSE_LABELS = list()
INBOX_WIDGETS = list()
CURRENT_USER = ""
FILE_SELECTED = ""
PICTURE = None

THEME = "#1E90FF"
BACKGROUND = "#b3ecff"
DELIMITER = "$$$$$$$$$$"

root = Tk()
root.title('by NAKUL AGGARWAL')
root.configure(bg=BACKGROUND)

HEADER = Label(root, text="   ∆ SOCIAL NETWORK ♪", fg="white", bg=THEME, anchor=W, width=48, bd=5, font=('',40,'bold'))
HEADER.grid(row=0, column=0, columnspan=36)

USERS = list()
GROUPS = list()
POSTS = list()
USER_NAMES = list()
LOOKUP = dict()

SCREEN = "home"

readSocialNetworkFile()
loadOldMessages()

BACK = Button(root, text='GO BACK', font=('',20,'bold'), bg='white', command = goBack)
BACK.grid(row=2, column=0, columnspan=10)

clicked = StringVar()
clicked.set("CHOOSE USER")

style = ttk.Style()
style.configure('W.TCombobox',arrowsize = 100)
DROP = ttk.Combobox(root, value=USER_NAMES, state="readonly", style='W.TCombobox', font=('',30,'bold'), justify='center')
DROP.bind("<FocusIn>", defocus)
root.grid_rowconfigure(1, minsize=20)
DROP.grid(row=2, column=12, columnspan=12, padx=12)

CHANGE_USER = Button(root, text='CHANGE USER', bg='white',  font=('',20,'bold'), command = newUserSelected)
CHANGE_USER.grid(row=2, column=24, columnspan=14)

root.grid_rowconfigure(3, minsize=20)

HOMEPAGE = Image.open('HOMEPAGE_BACKG.jpg')
HOMEPAGE = HOMEPAGE.resize((1545,650))
HOMEPAGE = ImageTk.PhotoImage(HOMEPAGE)
HOMEPAGE_L = Label(image=HOMEPAGE, bg=BACKGROUND)
HOMEPAGE_L.grid(row=4, column=0, columnspan=36, rowspan=8)

root.mainloop()
