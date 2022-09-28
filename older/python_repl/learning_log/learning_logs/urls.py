"""
only for learning_logs
"""

from django.urls import path
from . import views

app_name = 'learning_logs'

urlpatterns = [
	# home page ... empty matches base
	path('', views.index, name = 'index'),

]