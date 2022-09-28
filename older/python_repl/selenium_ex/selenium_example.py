"""
to interact with a website
selenium takes a package...and you need a web driver    pip
https://chromedriver.chromium.org/

when you have a site, pick an element...need html used to make the element ..ID, tag, name, class
ID best, name second, class last...but can be ambiguous  selenium returns first instance found
"""
#import selenium
from selenium import webdriver
from selenium.webdriver.common.keys import Keys # gives access to enter, escape...lets you interact
import time
#for the explicit wait
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC


PATH = 'chromedriver' # have to set binary in usr/local/bin on computer
driver = webdriver.Chrome(PATH)
site = 'https://www.fbi.gov/'

driver.get(site)
print('this page is called: ', driver.title)
time.sleep(5)

search = driver.find_element_by_name('SearchableText') # the id of the search box
search.send_keys('jihad') # search for jihad
search.send_keys(Keys.RETURN) # and hit enter to search
time.sleep(5) # so you can see if it works

print(driver.page_source) # not that useful, but brings all sourcecode for the page...pick what you want
# see how tags are organized to find what you want
results = driver.find_element_by_name('search-results')

try:
    results = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.ID, 'results')))
except:
    driver.quit()

print(results.text)

time.sleep(5)
driver.close() # single tab
#driver.quit() # entire browser




"""
to interact with a website
selenium takes a package...and you need a web driver    pip
https://chromedriver.chromium.org/

when you have a site, pick an element...need html used to make the element ..ID, tag, name, class
ID best, name second, class last...but can be ambiguous  selenium returns first instance found

#import selenium
from selenium import webdriver
from selenium.webdriver.common.keys import Keys # gives access to enter, escape...lets you interact
import time


PATH = 'chromedriver' # have to set binary in usr/local/bin on computer
driver = webdriver.Chrome(PATH)
site = 'https://www.fbi.gov/'

driver.get(site)
print('this page is called: ', driver.title)
time.sleep(5)

search = driver.find_element_by_name('SearchableText') # the id of the search box
search.send_keys('jihad') # search for jihad
search.send_keys(Keys.RETURN) # and hit enter to search
time.sleep(5) # so you can see if it works

print(driver.page_source) # not that useful, but brings all sourcecode for the page...pick what you want
# see how tags are organized to find what you want
results = driver.find_element_by_name('search-results')
print(results.text)

time.sleep(5)
driver.close() # single tab
#driver.quit() # entire browser
"""



