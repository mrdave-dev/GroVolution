# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='GV_Bank',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('bank_name', models.CharField(max_length=200)),
                ('last_fetch', models.DateTimeField(verbose_name='last fetch')),
                ('wake_time', models.IntegerField()),
                ('light_duration', models.IntegerField()),
                ('spray_interval', models.IntegerField()),
                ('spray_duration', models.IntegerField()),
            ],
        ),
        migrations.CreateModel(
            name='GV_relay',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('label', models.CharField(max_length=2)),
                ('number', models.IntegerField()),
                ('status', models.BooleanField()),
                ('bank', models.ForeignKey(to='gv_bank_display.GV_Bank')),
            ],
        ),
    ]
