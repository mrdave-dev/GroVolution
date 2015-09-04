from django.db import models

import re, json

class GV_Bank(models.Model):
    bank_name = models.CharField(max_length=200)
    last_fetch = models.DateTimeField('last fetch')
    wake_time = models.IntegerField()
    light_duration = models.IntegerField()
    spray_interval = models.IntegerField()
    spray_duration = models.IntegerField()

    def update_relays(self):
        # boil down filename
        local_fn = re.search(r'[\w\d]+\.json', self.bank_name).group()

        # parse data
        with open(self.bank_name, 'r') as data_file:
            data = json.load(data_file)

        # update object
        for relay in data[local_fn]['relays']:
            r = GV_Relay.objects.get(label=relay['label'], number=relay['number'])
            r.status = relay['status']
            r.save()

    def __str__(self):
        return self.bank_name

    class Meta:
        verbose_name = "Bank"
        verbose_name_plural = "Banks"


class GV_Relay(models.Model):
	bank = models.ForeignKey(GV_Bank)
	label = models.CharField(max_length=2)
	number = models.IntegerField()
	status = models.BooleanField()

	def __str__(self):
		return str(self.label) + str(self.number)

	class Meta:
		verbose_name = "Relay"
		verbose_name_plural = "Relays"


class TestModel(models.Model):
    created_at = models.DateTimeField(auto_now_add=True)
    title = models.CharField(max_length=255)
    description = models.TextField()

    def __str__(self):
        return self.title


