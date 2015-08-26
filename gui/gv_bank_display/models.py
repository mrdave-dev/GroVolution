from django.db import models

class GV_Bank(models.Model):
	bank_name = models.CharField(max_length=200)
	last_fetch = models.DateTimeField('last fetch')
	wake_time = models.IntegerField()
	light_duration = models.IntegerField()
	spray_interval = models.IntegerField()
	spray_duration = models.IntegerField()
	

class GV_Relay(models.Model):
	bank = models.ForeignKey(GV_Bank)
	label = models.CharField(max_length=2)
	number = models.IntegerField()
	status = models.BooleanField()
