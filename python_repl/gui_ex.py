"""
it's best if you bring this on the desk top and make sure it works on your OS
"""

import tkinter as tk
import os

root = tk.Tk()     # contains your GUI

canvas = tk.Canvas(root, height = 700, width = 700, bg = "#263D42")  # make a canvas
canvas.pack()

frame = tk.Frame(root, bg ="white")                                 # make a frame
frame.place(relwidth = .8, relheight = .8, relx = .1, rely = .1)

openFile = tk.Button(root, text = "Open File", padx = 10, pady = 5, fg = "white", bg = "#263D42")
openFile.pack()

root.mainloop()