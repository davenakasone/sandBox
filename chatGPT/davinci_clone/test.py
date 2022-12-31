import gradio as gr
import os
import openai
import sys
import pprint
os.system("clear")

MY_KEY = ""

# openai.api_key = os.getenv("OPENAI_API_KEY")
def gkey() -> None :
    """call this if API key is not placed in environment variable"""
    try :
        fptr = open("top_secret.txt", "r")
    except :
        sys.exit()
    MY_KEY = fptr.readline().strip()
    print(f"got:  {MY_KEY}")
    fptr.close()
gkey()

response = openai.Completion.create(
  model="text-davinci-003",
  prompt="",
  temperature=0.7,
  max_tokens=256,
  top_p=1,
  frequency_penalty=0,
  presence_penalty=0
)

def stop() -> None :
    print("\n\n\t\t ~ ~ ~ SCRIPT COMPLETE ~ ~ ~\n\n")
    sys.exit()
