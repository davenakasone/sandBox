import time

print("only this will print if you run as a script")
"""
def process_data(data):
	print('starting to process data...')
	modified_data = data + ' that has been changed'
	time.sleep(2)
	print('done processing data')
	return modified_data

#run in terminal and only first print() statement works
"""


"""
def process_data(data):
	print('starting to process data...')
	modified_data = data + ' that has been changed'
	time.sleep(2)
	print('done processing data')
	return modified_data

if __name__ == '__main__':             
	data = "internet data...."
	print(data)
	modified_data = process_data(data)
	print(modified_data)

# special value __main__ for __name__ variable means python executes script, not importing
"""


"""
# best, no reuse

def process_data(data):
	print('starting to process data...')
	modified_data = data + ' that has been changed'
	time.sleep(2)
	print('done processing data')
	return modified_data

def main():
	data = "internet data...."
	print(data)
	modified_data = process_data(data)
	print(modified_data)

if __name__ == '__main__':             
	main()
"""

# now you can use these function inside the CLI

def process_data(data):
	print('starting to process data...')
	modified_data = data + ' that has been changed'
	time.sleep(2)
	print('done processing data')
	return modified_data

def read_data():
	print('reading data...')
	time.sleep(2)
	print('data been got')
	inp = 'internet data'
	return inp

def write_data(data):
	print('writing data....')
	time.sleep(2)
	print(f'wrote: {data}')

def main():
	data = read_data()
	modified_data = process_data(data)
	write_data(modified_data)

if __name__ == '__main__':        # allows importing from CLI and running functions seperate
	main()


