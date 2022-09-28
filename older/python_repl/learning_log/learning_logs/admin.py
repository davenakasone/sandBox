from django.contrib import admin

from .models import Topic, Entry # now it is registered with admin site   dot says same directory
admin.site.register(Topic) # this makes it managed by admin site
admin.site.register(Entry)