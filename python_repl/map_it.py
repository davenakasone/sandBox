"""
$ python3
>>> import webbrowser   # about all that webbrowser does... opens pages
>>> webbrowser.open('https://inventwithpython.com/')

read cla from sys.argv
read clipboard contents
call webbrowser.open()

if there are no CLA...program knows to use clip board
"""
#! python3
import pyperclip  # if you want to take off clipbaord, work this in and make address string ''
import sys
import webbrowser

#address = '5901 Kentucky Ave Raytown, MO 64133' # make '' if other input desired
address = ''
if len(sys.argv) > 1: # take from CLI if there is any, otherwise clipboard
    address = ''
    address = ' '.join(sys.argv[1:]) # CLI usually seperated by spaces, but you want them all as 1 string
elif len(address) > 0:
    address = address   # no change, just using default
else:
    address = pyperclip.paste() # take from clipboard as a last resort
webbrowser.open('https://www.google.com/maps/place/' + address)
