"""
    paste your API key in "top_secret.txt"    
    if you have not already:
        $ pip3 install openai
        $ pip3 install gradio
    
    $ python3 app.py
    paste the url in your browser
    [ctrl] + [z] to exit
    
    https://gradio.app/quickstart/
    https://github.com/gradio-app/gradio
    
    https://github.com/openai/openai-python
    https://beta.openai.com/docs/api-reference?lang=python
"""
import gradio as gr
import os
import openai
import sys
os.system("clear")

# constants for the script
PROMPT = "conversaiton with an AI helper"
CB = None
INITED = False


"""
    pick first line if your enviroment variable has the API key
    else, let gkey() copy the key and bring it into the script
        and let gkey() automatically be called when script begins 
"""
# openai.api_key = os.getenv("OPENAI_API_KEY")
def gkey() -> None :
    """call this if API key is not placed in environment variable"""
    try :
        fptr = open("top_secret.txt", "r")
    except :
        sys.exit()
    my_key = fptr.readline().strip()
    print(f"got:  {my_key}")
    fptr.close()
    try :
        openai.api_key = my_key
    except :
        sys.exit()
gkey() # automatic call
#print(openai.Model.list()) # for viewing available models

"""
    let the 'openai' module create a session
    openai_create() wrapper should be called automatically
    most 'opeanai' and 'gradio' capabilities need some type of wrapping function
    API for openai is ready for use
"""
def openai_create(prom:str="START CHAT") :
    """chat session is initialzied"""    
    response = openai.Completion.create(
        model="text-davinci-003",
        prompt=prom,
        temperature=0.7,
        max_tokens=256,
        top_p=1,
        frequency_penalty=0,
        presence_penalty=0,
        stop=[" Human:", " AI: "]
        )
    return response.choices[0].text
openai_create(PROMPT) # automatic call

"""
    this is reqired for 'gradio'
    the history is for storing the state
    callbacks will be routed here
"""
def chatgpt_clone(input, history) :
    """keep the history + maintain API to openai"""
    history = history or [] # if history does not exist, then it is an empty list
    s = list(sum(history, ())) # make the history a list
    s.append(input) # update history with current input
    inp = ' '.join(s) # prepare the update to send
    output = openai_create(inp) # send the current input
    history.append((input, output)) # update the history after response is received
    return history, history

"""
    prepare 'gradio' app for chatting
"""
block = gr.Blocks() # gradio can be created with 'interface' or 'block'
with block :
    chatbot = gr.Chatbot()
    message = gr.Textbox(placeholder=PROMPT)
    state = gr.State()
    submit = gr.Button("SEND")
    submit.click(chatgpt_clone, inputs=[message, state], outputs=[chatbot, state])
block.launch(debug=True, share=True) # this link hosts the chat session

# def stop() -> None :
#     """call to close the script"""
#     print("\n\n\t\t ~ ~ ~ SCRIPT COMPLETE ~ ~ ~\n\n")
#     sys.exit()
