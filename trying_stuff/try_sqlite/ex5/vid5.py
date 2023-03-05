"""
fifth video

query methods
searching is very important
use existing tools https://www.techonthenet.com/sqlite/comparison_operators.php
"""

import sqlite3
import sys
import os

DB_NAME = 'ClinetInfo.db'
TAB_NAME = 'customers'
my_customers= [
    ('Andrew', 'Arlinton', 'aa@gmail.com'), 
    ('Brian', 'Biggs', 'bb@gmail.com'), 
    ("Charlie", 'Chafer', 'cc@gmail.com'),
    ('Dan', 'Darlington', 'dd@gmail.com'),
    ('Erik', 'Elder', 'ee@gmail.com')
    ]
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

# 4, make an entry of multiple entiries
c.executemany(f"INSERT INTO {TAB_NAME} VALUES (?,?,?)", my_customers)
conn.commit() # the command executes at cursor position

# 5, make a query
# many comparison operators
c.execute(f"SELECT * FROM {TAB_NAME} WHERE last_name = 'Elder'")
queries = c.fetchall()
for q in queries :
    print(f"{q}")

conn.close() # close the connection
print("\n\n\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")
sys.exit()


#####~~~~~END>  vid5.py
