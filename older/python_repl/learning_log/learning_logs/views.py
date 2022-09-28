"""
when URL request matches pattern defined, django looks for a function index() in views.py
the request object is passed to view function...no data processing needed on the home page


"""
from django.shortcuts import render

def index(request):
	""" home page for learning log """
	return render(request, 'learning_logs/index.html')

