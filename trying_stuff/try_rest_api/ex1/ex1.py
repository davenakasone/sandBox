"""
    rest api
    try these guys:
        https://api.stackexchange.com/docs/questions
"""

import requests
import json
import os
import sys

os.system("clear")
url = "https://api.stackexchange.com/2.3/questions?order=desc&sort=activity&site=stackoverflow"

response = requests.get(url)
print(f"\n{response.json()}")
print(f"\n{response.json['items']}")
print("\n\n\t\t~ ~ ~ SCRIPT COMPLETE ~ ~ ~\n\n")
sys.exit()


########~~~~~~~~END>  ex1.py
