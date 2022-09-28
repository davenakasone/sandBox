"""
plan project from what it should do
1. get text from clipboard
2. find all phone numbers and emails in the text
3. save data

this works on your machine...need the copy paste mechanism    just copy some info and run the program
"""
import pyperclip
import re

phoneRegex = re.compile(r'''(
    (\d{3}|\(\d{3}\))? (\s|-|\.)?
    (\d{3})
    (\s|-|\.) 
    (\d{4}) 
    (\s*(ext|x|ex|ext.|ex.)\s*(\d{1,6}))?
    )''' , re.VERBOSE)
test1 = "my number is (203) 345-2321 x243" # test
result1 = phoneRegex.search(test1).group() # test
print (result1)  # test

emailRegex = re.compile(r'''(
    [a-zA-Z0-9._%+-]+ 
    @ 
    [a-zA-Z0-9.-]+ 
    (\.[a-zA-Z]{2,4})
    )''', re.VERBOSE)
test2 = "my email is gunit69@hotmail.com"
result2 = emailRegex.search(test2).group()
print(result2)

text = str(pyperclip.paste()) # will be one tupple per match
matches = []
for groups in phoneRegex.findall(text):
    phoneNum ='-'.join([groups[1], groups[3], groups[5]])
    if groups[8] != '':
        phoneNum += ' x' + groups[8]
    matches.append(phoneNum)
for groups in emailRegex.findall(text):
    matches.append(groups[0])

if len(matches) > 0:
    pyperclip.copy('\n'.join(matches))
    print('copied to clipboard...')
    print('\n'.join(matches))
else:
    print('no numbers or emails found')