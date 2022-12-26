"""
putting everything together
"""

import sys
import os

from MyDb import MyDb

os.system("clear")

DB_NAME = 'ClinetInfo.sqlite'
TAB_NAME = 'customers'
TAB_FIELDS = ['first_name', 'last_name', 'email']
my_customers= [
    ('Andrew', 'Arlington', 'aa@gmail.com'), 
    ('Beth', 'Brown', 'bbrown@gmail.com'),
    ('Billy', 'Brown', 'billyb@gmail.com'),
    ('Brian', 'Biggs', 'bb@gmail.com'), 
    ('Zulu', 'Zimmerman', 'zz@gmail.com'),
    ('Dan', 'Darlington', 'dd@gmail.com'),
    ('Erik', 'Elder', 'ee@gmail.com'),
    ("Charlie", 'Chafer', 'cc@gmail.com')
    ]
mydb = MyDb()
if mydb.prepare(True, DB_NAME) is False :
    print("failed to prepare()")
    sys.exit()

#
mydb.loader = f"""CREATE TABLE {TAB_NAME} (
    {TAB_FIELDS[0]} text,
    {TAB_FIELDS[1]} text,
    {TAB_FIELDS[2]} text
    )"""
if mydb.execute(command=mydb.loader, printing=True) is False :
    print("failed to execute()")
    sys.exit()
if mydb.commit() is False :
    print("failed to commit()")
    sys.exit()

#
mydb.loader = f"""INSERT INTO {TAB_NAME} VALUES (
    'Isaac', 
    'Newton', 
    'calculus_inventor@gmail.com'
    )"""
if mydb.execute(command=mydb.loader, printing=True) is False :
    print("failed to execute()")
    sys.exit()
if mydb.commit() is False :
    print("failed to commit()")
    sys.exit()
mydb.printtable(TAB_NAME)

#
mydb.loader = f"INSERT INTO {TAB_NAME} VALUES (?,?,?)"
if mydb.executemany(command=mydb.loader, dlist=my_customers, printing=True) is False :
    print("failed to executemany()")
    sys.exit()
if mydb.commit() is False :
    print("failed to commit()")
    sys.exit()
mydb.printtable(TAB_NAME)

#
mydb.loader = f"""UPDATE {TAB_NAME} SET 
    {TAB_FIELDS[0]} = 'Gottfried', 
    {TAB_FIELDS[1]} = 'Leibniz', 
    {TAB_FIELDS[2]} = 'real_calculus_inventor@gmail.com' 
    WHERE rowid = 1"""
if mydb.execute(command=mydb.loader, printing=True) is False :
    print("failed to execute()")
    sys.exit()
if mydb.commit() is False :
    print("failed to commit()")
    sys.exit()
mydb.printtable(TAB_NAME)

#
mydb.loader = f"DELETE from {TAB_NAME} WHERE rowid = 1"
if mydb.execute(command=mydb.loader, printing=True) is False :
    print("failed to execute()")
    sys.exit()
if mydb.commit() is False :
    print("failed to commit()")
    sys.exit()
mydb.printtable(TAB_NAME)

# 
mydb.loader = f"SELECT rowid, * FROM {TAB_NAME} ORDER BY {TAB_FIELDS[1]} ASC"
if mydb.execute(command=mydb.loader, printing=True) is False :
    print("failed to execute()")
    sys.exit()
if mydb.fetchall() is False :
    print("failed to fetchall()")
    sys.exit()
mydb.printfetched()

#
mydb.loader = f"SELECT rowid, * FROM {TAB_NAME} WHERE {TAB_FIELDS[1]} LIKE 'B%'"
if mydb.execute(command=mydb.loader, printing=True) is False :
    print("failed to execute()")
    sys.exit()
if mydb.fetchall() is False :
    print("failed to fetchall()")
    sys.exit()
mydb.printfetched()

#
mydb.loader = f"SELECT rowid, * FROM {TAB_NAME} WHERE last_name LIKE 'Br%' OR rowid = 9"
if mydb.execute(command=mydb.loader, printing=True) is False :
    print("failed to execute()")
    sys.exit()
if mydb.fetchall() is False :
    print("failed to fetchall()")
    sys.exit()
mydb.printfetched()

#
mydb.loader = f"SELECT rowid, * FROM {TAB_NAME} WHERE last_name LIKE 'Br%' AND rowid = 3"
if mydb.execute(command=mydb.loader, printing=True) is False :
    print("failed to execute()")
    sys.exit()
if mydb.fetchall() is False :
    print("failed to fetchall()")
    sys.exit()
mydb.printfetched()

#
lim = 3
mydb.loader = f"SELECT rowid, * FROM {TAB_NAME} LIMIT {lim}"
if mydb.execute(command=mydb.loader, printing=True) is False :
    print("failed to execute()")
    sys.exit()
if mydb.fetchall() is False :
    print("failed to fetchall()")
    sys.exit()
mydb.printfetched()

#
lim = 4
mydb.loader = f"SELECT rowid, * FROM {TAB_NAME} ORDER BY rowid DESC LIMIT {lim}"
if mydb.execute(command=mydb.loader, printing=True) is False :
    print("failed to execute()")
    sys.exit()
if mydb.fetchall() is False :
    print("failed to fetchall()")
    sys.exit()
mydb.printfetched()

#
mydb.loader = f"DROP TABLE {TAB_NAME}"
if mydb.execute(command=mydb.loader, printing=True) is False :
    print("failed to execute()")
    sys.exit()
else :
    print(f"deleted: {TAB_NAME}")


print("\n\n\t\t~ ~ ~ PROGRAM COMPLETE ~ ~ ~\n\n")
sys.exit()


#####~~~~~END>  app.py
