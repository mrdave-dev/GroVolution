# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('gv_bank_display', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='TestModel',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, primary_key=True, auto_created=True)),
                ('created_at', models.DateTimeField(auto_now_add=True)),
                ('title', models.CharField(max_length=255)),
                ('description', models.TextField()),
            ],
        ),
    ]
