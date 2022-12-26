"""
10th video

limiting results is good for managing your resources
manage sqlite syntax with the python library to make whatever you need
"""

import sqlite3
import sys
import os

DB_NAME = 'ClinetInfo.db'
TAB_NAME = 'customers'
my_customers= [
    ('Andrew', 'Arlington', 'aa@gmail.com'), 
    ('Brian', 'Biggs', 'bb@gmail.com'), 
    ('Beth', 'Brown', 'bbrown@gmail.com'),
    ('Billy', 'Brown', 'billyb@gmail.com'),
    ("Charlie", 'Chafer', 'cc@gmail.com'),
    ('Zulu', 'Zimmerman', 'zz@gmail.com'),
    ('Dan', 'Darlington', 'dd@gmail.com'),
    ('Erik', 'Elder', 'ee@gmail.com')
    ]
os.system("clear")


# 1, make a connection to the database 
# creates new one if it does not exist
#conn = sqlite3.connect(f'{DB_NAME}')  # write the file when code is good, this makes the .db file
conn = sqlite3.connect(':memory:')     # work from here to start

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

# 4, make an entry of multiple entiries + check
c.executemany(f"INSERT INTO {TAB_NAME} VALUES (?,?,?)", my_customers)
conn.commit() # the command executes at cursor position
c.execute(f"SELECT rowid, * FROM {TAB_NAME}")
pkeys = c.fetchall()
for key in pkeys :
    print(f"{key}")
print("\n")

# 5, apply the limit
c.execute(f"SELECT rowid, * FROM {TAB_NAME} LIMIT 4")
pkeys = c.fetchall()
for key in pkeys :
    print(f"{key}")
print("\n")

# 6, apply the limit to end
c.execute(f"SELECT rowid, * FROM {TAB_NAME} ORDER BY rowid DESC LIMIT 3")
pkeys = c.fetchall()
for key in pkeys :
    print(f"{key}")
print("\n")


conn.close() # close the connection
print("\n\n\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")
sys.exit()


#####~~~~~END>  vid10.py
