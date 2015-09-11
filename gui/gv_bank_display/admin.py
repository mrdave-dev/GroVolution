from django.contrib import admin

from .models import GV_Bank, GV_Relay


class RelayInline(admin.StackedInline):
    model = GV_Relay


class GV_Bank_Admin(admin.ModelAdmin):
    inlines = [RelayInline,]
    fieldsets = [
        (None, {'fields':['bank_name']}),
        ('Last fetch', {'fields':['last_fetch']}),
        ('Timers', {'fields':['wake_time', 'light_duration', 'spray_interval', 'spray_duration']}),
    ]



admin.site.register(GV_Bank, GV_Bank_Admin)
admin.site.register(GV_Relay)
