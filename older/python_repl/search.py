"""
https://pypi.org/search/?q=<SEARCH_TERM_HERE>
let requests get the results, bs4 find page, and webbrowser open

you have to know the webpage

$python3 program_name.py SEARCH_TERM
...the rest occurs automatically
"""
#!python3
import bs4
import requests
import sys
import webbrowser

print('searching.....')
url_obj = requests.get('https://google.com/search?q=' 'https://pypi.org/search/?q=' + ' '.join(sys.argv[1:]))
url_obj.raise_for_status()
# it doesn't matter how complicated the element is, you just need elements that correspond to results
search_soup = bs4.BeautifulSoup(url_obj.text, 'html.parser')      # parse html
link_elms = search_soup.select('.package-snippet')                # results all have 'package-snippet'
num_open = min(5, len(link_elms))                                 # open finds 5 or length
for i in range(num_open):
    url_to_open = 'https://pypi.org' + link_elms[i].get('href')    # have to add first part...href is internal to page
    print(f"opening {url_to_open}")
    webbrowser.open(url_to_open)
