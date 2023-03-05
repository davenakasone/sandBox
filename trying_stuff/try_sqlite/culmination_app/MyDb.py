"""
    handles database 
"""

import sqlite3

class MyDb :
    
    def __init__(self) -> None :
        self.cursor = None
        self.connector = None
        self.loader = ''
        self.fetched = []
        
    def prepare(self, in_memory=True, db_name="myDB") -> bool :
        if (in_memory is True) and (len(db_name) < 1) :
            print("no database specified")
            return False
        if in_memory is True :
            try :
                self.connector = sqlite3.connect(database=':memory:')
            except Exception as e :
                print(e)
                return False
        else :
            try :
                self.connector = sqlite3.connect(database=f"{db_name}")
            except Exception as e :
                print(e)
                return False
        try :
            self.cursor = self.connector.cursor()
        except Exception as e :
            print(e)
            return False
        return True
    
    def execute(self, command: str, printing=False) -> bool :
        try :
            self.cursor.execute(command)
        except Exception as e :
            print(e)
            return False
        if printing is True :
            print(command)
        return True
    
    def executemany(self, command: str, dlist= ['a', 'b', 'c'], printing=False) -> bool :
        try :
            self.cursor.executemany(command, dlist)
        except Exception as e :
            print(e)
            return False
        if printing is True :
            print(command)
        return True
    
    def commit(self) -> bool :
        try :
            self.connector.commit()
        except Exception as e :
            print(e)
            return False
        return True
    
    def fetchall(self) -> bool :
        try :
            self.fetched = self.cursor.fetchall()
        except Exception as e :
            print(e)
            return False
        return True
    
    def printtable(self, tname) -> None :
        if self.execute(f"SELECT rowid, * FROM {tname}") is False :
            return
        if self.fetchall() is False :
            return
        for record in self.fetched :
            print(f"{record}")
        print("\n")
    
    def printfetched(self) -> None :
        if len(self.fetched) < 1 :
            return
        for f in self.fetched :
            print(f"{f}")
        print("\n")
    
    def __del__(self) :
        try :
            self.connector.close()
        except Exception as e :
            print(e)
            return
        print("DB connection successfully closed")
            
        
####~~~~END> MyDb.py
