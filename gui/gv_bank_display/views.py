from django.http import HttpResponse
from django.shortcuts import render, get_object_or_404
from django.contrib.auth.decorators import login_required

from .models import TestModel, GV_Bank, GV_Relay

@login_required
def index(request):
    banks = GV_Bank.objects.all()
    return render(request, 'gv_bank_display/index.html', {'banks': banks})


@login_required
def bank_display(request):
	banks = GV_Bank.objects.all()
	return render(request, 'gv_bank_display/bank_display.html', {'banks': banks})


@login_required
def bank_detail(request, pk):
    bank = get_object_or_404(GV_Bank, pk=pk)
    return render(request, 'gv_bank_display/bank_detail.html', {'bank': bank})


@login_required
def bank_fetch(request, pk):
    try:
        bank = GV_Bank.objects.get(pk=pk)
    except GV_Bank.DoesNotExist:
        return HttpResponse('1')

    bank.fetch_and_update()
    return HttpResponse('0')


@login_required
def relay_off(request, pk):
    try:
        relay = GV_Relay.objects.get(pk=pk)
    except GV_Relay.DoesNotExist:
        return HttpResponse('1')

    relay.turn_off()
    return HttpResponse('0')


@login_required
def relay_on(request, pk):
    try:
        relay = GV_Relay.objects.get(pk=pk)
    except GV_Relay.DoesNotExist:
        return HttpResponse('1')

    relay.turn_on()
    return HttpResponse('0')
