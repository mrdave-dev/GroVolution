# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('gv_bank_display', '0002_testmodel'),
    ]

    operations = [
        migrations.AlterModelOptions(
            name='gv_bank',
            options={'verbose_name': 'Bank', 'verbose_name_plural': 'Banks'},
        ),
        migrations.AlterModelOptions(
            name='gv_relay',
            options={'verbose_name': 'Relay', 'verbose_name_plural': 'Relays'},
        ),
    ]
