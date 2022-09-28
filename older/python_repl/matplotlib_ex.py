"""
pyplot has a lot of ways to plot
plt is a convention
subplots()
you can adjust any feature you want
font size and others are something you will want to use often

lots of parameters to pass if you want to, lots of predefined styles
$ import matplotlib.pyplot as plt
$ plt.style.available
['Solarize_Light2', '_classic_test_patch', 'bmh', 'classic', 'dark_background
', 'fast', 'fivethirtyeight', 'ggplot', 'grayscale', 'seaborn', 'seaborn-brig
ht', 'seaborn-colorblind', 'seaborn-dark', 'seaborn-dark-palette', 'seaborn-d
arkgrid', 'seaborn-deep', 'seaborn-muted', 'seaborn-notebook', 'seaborn-paper',
'seaborn-pastel', 'seaborn-poster', 'seaborn-talk', 'seaborn-ticks', 'seaborn-white',
'seaborn-whitegrid', 'tableau-colorblind10']
pick one... plt.style.use('seaborn-pastel')  before hand



"""

import matplotlib.pyplot as plt  # just going to show f(x) = x^2 [1:5]

input_values = [1, 2, 3, 4, 5]
squares = [1, 4, 9, 16, 25] # assumes x = 0 for first number, unless told otherwise

plt.style.use('bmh')
fig, ax = plt.subplots() # fig is entire object and can be a collection of plots
# ax is single plot in the fig


#custom axis
ax.set_title("Square Numbers", fontsize = 24)   # title your graph
ax.set_xlabel("Value", fontsize = 14)            # title axis
ax.set_ylabel("Square of Value", fontsize = 14)
ax.tick_params(axis = 'both' , labelsize = 14) # style the tick marks


ax.plot(input_values, squares, linewidth = 3) # this method tries to plot data given...you can even save it as a file
plt.show()


