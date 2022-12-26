"""
first video

database itself just holds information
you should design it to be accessable and useful
relational database might not always be the best paradigm

see the documentation: https://docs.python.org/3/library/sqlite3.html
https://www.sqlite.org/datatype3.html

there are only 5 datatypes
"""

import sqlite3 # built-in to python
import sys
import os

DB_NAME = 'ClinetInfo.db'
TAB_NAME = 'customers'
os.system("clear")

# 1, make a connection to the database 
# creates new one if it does not exist
conn = sqlite3.connect(f'{DB_NAME}')  # write the file when code is good, this makes the .db file
#conn = sqlite3.connect(':memory:')     # work from here to start

# 2, make a cursor to start interacting with the database
c = conn.cursor()

# 3, make a table
# there are a few ways to execute commands
c.execute(f"""CREATE TABLE {TAB_NAME} (
    first_name text,
    last_name text,
    email text
    )""") 
conn.commit() # the command executes at cursor position

# 4, make an entry
c.execute(f"""INSERT INTO {TAB_NAME} VALUES (
    'ISAAC', 
    'NEWTON', 
    'gravity@gmail.com'
    )""") # notice double quotes and single
conn.commit() # the command executes at cursor position


conn.close() # close the connection
print("\n\n\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")
sys.exit()


#####~~~~~END>  vid1.py
