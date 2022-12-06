"""
    parsing HTML is best if you use a program
    the standards change fast
    
    beautiful soup is a good way to go    
    some people don't like robots scraping their website
    
    ...better to format data to fit program (JSON, YAML, XML...etc)
    these protocols should be independent of language
"""

import urllib.request
import urllib.parse
import urllib.error
from bs4 import BeautifulSoup
import sys

link = 'http://info.cern.ch/'

def main() :
    ex1()
    sys.exit()

def ex1() :
    html = urllib.request.urlopen(link).read()
    soup = BeautifulSoup(html, 'html.parser')
    atags = soup('a') # anchor tags
    for tag in atags :
        print(tag.get('href', None))
    
if __name__ == '__main__' :
    main()
