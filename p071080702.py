import tkinter
top = tkinter.Tk()
f1 = tkinter.Frame(top)
f2 = tkinter.Frame(top)


isEmpty = True
isOperator = False
isError = False
operates = 0
var = tkinter.StringVar()
var.set("0")

def SetValue():	# 設定Label的值
    Screen = tkinter.Label(f1, textvariable = var).grid(row = 0, column = 1)

def Click(x):
    #請完成function內的code
    global isEmpty, isOperator, operates
    #var.set(var.get() + " " + x)
    if(x.isdigit()):

        if(isEmpty):
            var.set(x)
        elif(isOperator):
            var.set(var.get() + " " + x)
        else:
            var.set(var.get() + x)
        isEmpty = False
        isOperator = False
    else:
        if(isOperator):
            var.set(var.get()[:-1] + x)
            return
        elif(isEmpty and x == "-"):
            var.set(var.get()[:-1] + x)
            isEmpty = False
            return
        isOperator = True
        isEmpty = False
        operates += 1
        var.set(var.get() + " " + x)





def Clear():
    #請完成function內的code
    global isEmpty
    isEmpty = True
    var.set("0")

def Calculate():
    #請完成function內的code
    global isError, isEmpty, isOperator, operates
    print("cal")
    Stage = 0

    x = var.get().split()
    var.set("CALCULATING")
    print(x)

    #x = map(int, tmp)
    while(operates > 0):
        for v, op in enumerate(x):
            print(v, op, len(x))
            if(v == len(x)-1):
                Stage = 1
                print("ns")
            if(Stage == 0 and (op == "x" or op == "/")):
                if(op == "x"):
                    x[v-1] = str(float(x[v-1]) * float(x[v+1]))
                    print(x[v - 1])
                    del x[v]
                    del x[v]
                    operates -= 1
                    break
                elif(op == "/"):
                    if(int(x[v+1]) == 0):
                        var.set("ERROR")
                        isEmpty = True
                        isError = True
                        return
                    x[v-1] = str(float(x[v-1]) / float(x[v+1]))
                    print(x[v - 1])
                    del x[v]
                    del x[v]
                    operates -= 1
                    break
            elif(Stage == 1 and(op == "+" or op == "-")):
                if(op == "+"):
                    x[v-1] = str(float(x[v-1]) + float(x[v+1]))
                    #print(x[v-1])
                    del x[v]
                    del x[v]
                    operates -= 1
                    break
                elif(op == "-"):
                    x[v-1] = str(float(x[v-1]) - float(x[v+1]))
                    print(x[v-1])
                    del x[v]
                    del x[v]
                    operates -= 1
                    break



        print(x[0])

    print("fin")
    var.set(x[0])
    isOperator = False




SetValue()


# Button的排列:請設定row和column
# 請將？？？填完並在完成第一、二、三行

btn7 = tkinter.Button(f2,text = "7",borderwidth = 5,width = 5,height = 5, command = lambda : Click("7")).grid(row = 1,column = 0)
btn8 = tkinter.Button(f2,text = "8",borderwidth = 5,width = 5,height = 5, command = lambda : Click("8")).grid(row = 1,column= 1)
btn9 = tkinter.Button(f2,text = "9",borderwidth = 5,width = 5,height = 5, command = lambda : Click("9")).grid(row = 1,column= 2)
btnPlus = tkinter.Button(f2,text = "+",borderwidth = 5,width = 5,height = 5, command = lambda : Click("+")).grid(row = 1,column= 3)
btn4 = tkinter.Button(f2,text = "4",borderwidth = 5,width = 5,height = 5, command = lambda : Click("4")).grid(row = 2,column= 0)
btn5 = tkinter.Button(f2,text = "5",borderwidth = 5,width = 5,height = 5, command = lambda : Click("5")).grid(row = 2,column= 1)
btn6 = tkinter.Button(f2,text = "6",borderwidth = 5,width = 5,height = 5, command = lambda : Click("6")).grid(row = 2,column= 2)
btnMinus = tkinter.Button(f2,text = "-",borderwidth = 5,width = 5,height = 5, command = lambda : Click("-")).grid(row = 2,column= 3)
btn1 = tkinter.Button(f2,text = "1",borderwidth = 5,width = 5,height = 5, command = lambda : Click("1")).grid(row = 3,column= 0)
btn2 = tkinter.Button(f2,text = "2",borderwidth = 5,width = 5,height = 5, command = lambda : Click("2")).grid(row = 3,column= 1)
btn3 = tkinter.Button(f2,text = "3",borderwidth = 5,width = 5,height = 5, command = lambda : Click("3")).grid(row = 3,column= 2)
btnX = tkinter.Button(f2,text = "x",borderwidth = 5,width = 5,height = 5, command = lambda : Click("x")).grid(row = 3,column= 3)
btn0 = tkinter.Button(f2,text = "0",borderwidth = 5,width = 5,height = 5, command = lambda : Click("0")).grid(row = 4,column= 0)
btnClear = tkinter.Button(f2,text = "C",borderwidth = 5,width = 5,height = 5, command = Clear).grid(row = 4,column= 1)
btnEqual = tkinter.Button(f2,text = "=",borderwidth = 5,width = 5,height = 5, command = lambda : Calculate()).grid(row = 4,column= 2)
btnDiv = tkinter.Button(f2,text = "/",borderwidth = 5,width = 5,height = 5, command = lambda : Click("/")).grid(row = 4,column= 3)
f1.pack()
f2.pack()
#windows.mainloop()
top.mainloop()
