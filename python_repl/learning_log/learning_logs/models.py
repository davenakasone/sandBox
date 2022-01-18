"""
models tell django how to work with data stored in app
it is just a class
django is very large and you should be familiar with the documentation
"""
from django.db import models


class Topic(models.Model):    # inherits from django
	""" a topic the user is learning about """
	text = models.CharField(max_length = 200)  # a piece of data made of characters or text
	date_added = models.DateTimeField(auto_now_add = True) # set to current time

	def __str__(self):
		""" returns a string representation of the model """
		return self.text

class Entry(models.Model):
	""" specifics learned about a topic """
	topic = models.ForeignKey(Topic, on_delete = models.CASCADE) #foreign key is DB term another record in another DB
	# when topic deleted, all entries to it also deleted
	text = models.TextField()
	date_added = models.DateTimeField(auto_now_add = True)

	class Meta:
		verbose_name_plural = 'entries' # when needing to refer to more than one

		def __str__(self): # what info to show when refereing to individual entries
			""" return string representation of model """
			return f"{self.text[:50]}..."
