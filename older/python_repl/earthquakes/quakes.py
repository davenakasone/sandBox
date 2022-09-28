"""
for JSON data, use the JSON module
plotly also has a mapping tool in it
that JSON is fugly
we stole it from https://earthquake.usgs.gov/earthquakes/feed

the metadata section is very important
* python's geoJSON format goes long, lat to be like x,y    don't do lat, long

you improve style by knowing what you want to communicate about the data

to see all the color scales
from plotly import colors
for key in colors.PLOTLY_SCALES.keys():
    print(key)
ploty stores colorscales in colors module...color scales defined by dictionary PLOTLY_SCALES
each scale has a begin and end...move them around all you want

the coordinates appear by default, you can show a lot on the hoover
"""

import json
from plotly.graph_objs import Scattergeo, Layout
from plotly import offline

#filename = 'eq_data_1_day_m1.json' # taking it all
filename = 'eq_data_30_day_m1.json'
with open(filename) as f:
    all_eq_data = json.load(f)

writename = 'observe.json' # just to check meta, major nest-levles, errors
with open(writename, 'w') as f:
    json.dump(all_eq_data, f, indent = 4)

# check 'features' to store all the earth quake dictionaries...make sure it is 158
map_title = all_eq_data['metadata']['title'] # automate taking the title
print(map_title)
all_eq_dicts = all_eq_data['features']
print('there appears to be: ', len(all_eq_dicts), 'earthquakes recorded')

# now you want all the magnitudes...and locaiton
mags, lons, lats, hover_texts =[], [], [], []
for eq_dict in all_eq_dicts:
    mag = eq_dict['properties']['mag']
    lon = eq_dict['geometry']['coordinates'][0]
    lat = eq_dict['geometry']['coordinates'][1]
    title = eq_dict['properties']['title']
    mags.append(mag)
    lons.append(lon)
    lats.append(lat)
    hover_texts.append(title)
print('check some mags: \n', mags[:9]) # just to check first few
print('check some lons: \n', lons[:9]) # just to check first few
print('check some lats: \n', lats[:9]) # just to check first few

# not put earthquakes on a map
# data = [Scattergeo(lon = lons, lat = lats)] # easy way
data = [{
    'type': 'scattergeo',
    'lon': lons,
    'lat': lats,
    'text': hover_texts,
    'marker': {
        'size': [5*mag for mag in mags],
        'color': mags,
        'colorscale': "Viridis",
        'reversescale': True,
        'colorbar': {'title': 'Magnitude'},
    },
}] # best way to do it
my_layout = Layout(title = map_title)
fig = {'data': data, 'layout': my_layout}
offline.plot(fig, filename = 'global_earthquakes.html')


