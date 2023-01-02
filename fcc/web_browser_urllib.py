import urllib.request
import urllib.parse
import urllib.error
import sys

server = 'data.pr4e.org'
link = f'http://{server}/romeo.txt'
link2 = 'http://www.csun.edu/~sk36711/WWW/tutorials/how_web_pages_work.html'

def main() :
    ex1()
    ex2()
    sys.exit()

def ex1() :
    fptr = urllib.request.urlopen(link) # headers are consumed
    for line in fptr :
        print(line.decode())

def ex2() :
    # if you can find links, you could keep opening and getting
    fptr = urllib.request.urlopen(link2)
    for line in fptr :
        print(line.decode())

if __name__ == '__main__' :
    main()
