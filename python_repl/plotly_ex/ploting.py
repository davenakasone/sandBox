"""
plotly is supposed to make interactive visualizations
most of them scale automatically and are made for a web browser
it will give information for mouse hoovers, and all kinds of events

this is rolling 2 dice, like craps or street dice shooting
need $ python3 -m pip install --user plotly

many configuration options
"""

from plotly.graph_objs import Bar, Layout
from plotly import offline

from die import Die

die = Die()
results = []
for roll_num in range(1_000): # rolling it 1,000 times
    result = die.roll()
    results.append(result)
#print(results) # testing

# analyze the freqs
freqs = []
for value in range(1,die.num_sides + 1):
    frequency = results.count(value)  # python is high level af
    freqs.append(frequency)
print(freqs) 
print("there were [", sum(freqs), "]  rolls")

# make a histogram
x_values = list(range(1, die.num_sides + 1)) # possible values 1 to 6...ploty only accepts lists, not ranges 
data = [Bar(x = x_values, y = freqs)] # the bar and frequency passed to x and y  ...also needs a list

x_axis_config = {'title': 'values received'}
y_axis_config = {'title': 'frequencies'}

my_layout = Layout(title = 'Result of 1,000 rolls', xaxis = x_axis_config, yaxis = y_axis_config)
offline.plot({'data': data, 'layout': my_layout}, filename = 'd6.html') # needs a dictionary of data and layout obj
