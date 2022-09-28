"""
the dictionary is supposed to be key-value pairs of immutable data
values shouldn't be changed once put in

python can't usually gauruntee order in the dictionary
"""


my_dic = {'key1': 5, 'key2': 10, 'key3': 15}
# strings, numbers, tupples ...no lists
print(f"my_dic:  {my_dic}")
print(f"values:  {my_dic['key1']}  ,  {my_dic['key2']}  ,  {my_dic['key3']}")

print("\nadd a value 'keyX'")
if 'keyX' in my_dic :
    print(f"{my_dic['keyX']}")
else :
    my_dic['keyX'] = 20
    print("added a key-value pair, entre not found")
print(f"my_dic:  {my_dic}")

# getting
valX = my_dic.get('keyX')
print(f"\nthe value of keyX:  {valX}")
valY = my_dic.get('keyY')
print(f"returns 0 if get() does not find,  keyY:  {valY}")

# key names, value names
key_names = my_dic.keys()
val_vals = my_dic.values()
print("\nthis dictionary has:")
print(f"keys:  {key_names}")
print(f"values:  {val_vals}")

# items to iterate
my_items = my_dic.items()
print(f"\nitem view as tupples:  {my_items}")
for k, v in my_dic.items() :
    print(k, v)


########~~~~~~~~END>  ex_dict.py
