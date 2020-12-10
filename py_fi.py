# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

import tkinter
#from tkinter import *
import random
import string
from threading import Timer
import time


TmpAns = (random.sample(range(0, 9), 4))
ans = ["", "", "", ""]
ans[0] = str(TmpAns[0])
ans[1] = str(TmpAns[1])
ans[2] = str(TmpAns[2])
ans[3] = str(TmpAns[3])

record = []

round = 1

timerSt = False
startTime = 0

leaderBoard = []






top = tkinter.Tk()
#f1 = tkinter.Frame(top)

#msg = tkinter.Tk()
var = tkinter.StringVar()

Timer_var = tkinter.StringVar()
Timer_var.set("first guess to start")


def renewTimer():
    global global_Time, startTime
    t = Timer(0.05, renewTimer).start()
    #Timer_var.set("time : " + str(time.perf_counter() - startTime))
    if(timerSt):
        Timer_var.set("time : " + str("{:.2f}".format(time.perf_counter() - startTime) ) )


renewTimer()


label_T = tkinter.Label(top, textvariable = Timer_var).grid(row = 0, column = 1)
label_aisatu = tkinter.Label(top, text = "Welcome to Number Game").grid(row = 1, column = 1)
inputText = tkinter.Entry(top)
inputText.grid(row = 2, column = 1)
#btn1 = tkinter.Button(top, text = "RUN", width = 5,height = 1, command = lambda : RUN()).grid(row = 3, column = 1)
txt = tkinter.Text(top)
txt.grid(row = 4, column = 1)




#btn_giveup = tkinter.Button(top, text = "Show Answer", height = 1, command = lambda : option(0)).grid(row = 5, column = 1)
#btn_renew = tkinter.Button(top, text = "New Game", height = 1, command = lambda : option(1)).grid(row = 6, column = 1)
#btn_exit = tkinter.Button(top, text = "Exit", height = 1, command = lambda : option(2)).grid(row = 7, column = 1)

def GameOver(win):
    global  startTime, timerSt
    endTime = time.perf_counter()
    consumeTime = (endTime - startTime)
    timerSt = False
    Timer_var.set("first guess to start")

    startTime = 0
    msg = tkinter.Tk()
    if(win):

        label_R = tkinter.Label(msg, text = "time : " + str("{:.2f}".format(consumeTime))).grid(row = 1, column = 1)
        label_Msg = tkinter.Label(msg, text = "You are " + " " +" place.  Enter your name and submit").grid(row = 2, column = 1)
        inputName = tkinter.Entry(msg)
        inputName.grid(row=3, column=1)
        btn_Submit = tkinter.Button(msg, text = "submit", height = 1, command = lambda: option(3)).grid(row = 4, column = 1)


    btn_renew = tkinter.Button(msg, text="New Game", height=1, command=lambda: option(1)).grid(row=5, column=1)
    btn_exit = tkinter.Button(msg, text="Exit", height=1, command=lambda: option(2)).grid(row=6, column=1)
    msg.mainloop()

def RUN():
    global ans, round, record, timerSt, startTime
    okay = True
    inp = list(inputText.get())
    if(len(inp) != 4):
        txt.insert("end", str(inputText.get()) + "(length error) Try again!\n")
        okay = False

    if(not inputText.get().isdigit()):
        txt.insert("end", str(inputText.get()) + "(character error) Try again!\n")
        okay = False

    if(len(inp) != len(set(inp))):
        txt.insert("end", str(inputText.get()) + "(character repeat) Try again!\n")
        okay = False

    if(inputText.get() in record):
        txt.insert("end", str(inputText.get()) + "number guessed\n")
        okay = False

    if(okay):
        if(not timerSt):
            startTime = time.perf_counter()
            timerSt = True


        record.append(inputText.get())

        A = 0
        B = 0
        if(inp[0] == ans[0]):
            A+=1
        if(inp[1] == ans[1]):
            A+=1
        if(inp[2] == ans[2]):
            A+=1
        if(inp[3] == ans[3]):
            A+=1

        if(inp[0] == ans[1] or inp[0] == ans[2] or inp[0] == ans[3]):
            B+=1
        if(inp[1] == ans[0] or inp[1] == ans[2] or inp[1] == ans[3]):
            B += 1
        if(inp[2] == ans[0] or inp[2] == ans[1] or inp[2] == ans[3]):
            B += 1
        if(inp[3] == ans[0] or inp[3] == ans[1] or inp[3] == ans[2]):
            B += 1

        txt.insert("end", "Round" + str(round) + " " + str(inputText.get()) + " "+ str(A) + "A" + str(B) + "B\n")
        round +=1
        if(A == 4):
            txt.insert("end", "You win! Congrats!\n")
            GameOver(1)
        elif(round > 10):
            txt.insert("end", "You lose! Ans: " + str(ans[0]) + str(ans[1]) + str(ans[2]) + str(ans[3]) +"\n" )
            GameOver(0)








def option(op):
    global ans, round, record, timerSt, startTime

    if(op == 0):
        txt.insert("end", "Ans: " + str(ans[0]) + str(ans[1]) + str(ans[2]) + str(ans[3]) + "\n")
    elif(op == 1):
        Timer_var.set("first guess to start")
        txt.insert("end", "New Game\n")
        TmpAns = (random.sample(range(0, 9), 4))
        ans = ["", "", "", ""]
        ans[0] = str(TmpAns[0])
        ans[1] = str(TmpAns[1])
        ans[2] = str(TmpAns[2])
        ans[3] = str(TmpAns[3])

        record = []

        round = 1

        timerSt = False
        startTime = 0

        return
    elif(op == 2):
        exit()



btn1 = tkinter.Button(top, text = "RUN", width = 5,height = 1, command = lambda : RUN()).grid(row = 3, column = 1)
btn_giveup = tkinter.Button(top, text = "Show Answer", height = 1, command = lambda : option(0)).grid(row = 5, column = 1)
btn_renew = tkinter.Button(top, text = "New Game", height = 1, command = lambda : option(1)).grid(row = 6, column = 1)
btn_exit = tkinter.Button(top, text = "Exit", height = 1, command = lambda : option(2)).grid(row = 7, column = 1)


top.mainloop()
