from django.http import HttpResponse
from django.shortcuts import render, get_object_or_404

from .models import TestModel, GV_Bank, GV_Relay


def test_view(request):
    tests = TestModel.objects.all()
    output = ', '.join([str(t) for t in tests])
    return HttpResponse(output)

def index(request):
    banks = GV_Bank.objects.all()
    return render(request, 'gv_bank_display/index.html', {'banks': banks})


def bank_display(request):
	banks = GV_Bank.objects.all()
	return render(request, 'gv_bank_display/bank_display.html', {'banks': banks})


def bank_detail(request, pk):
    bank = get_object_or_404(GV_Bank, pk=pk)
    return render(request, 'gv_bank_display/bank_detail.html', {'bank': bank})

def bank_fetch(request, pk):
    try:
        bank = GV_Bank.objects.get(pk=pk)
    except GV_Bank.DoesNotExist:
        return HttpResponse('1')

    bank.fetch_and_update()
    return HttpResponse('0')


def relay_off(request, pk):
    try:
        relay = GV_Relay.objects.get(pk=pk)
    except GV_Relay.DoesNotExist:
        return HttpResponse('1')

    relay.turn_off()
    return HttpResponse('0')


def relay_on(request, pk):
    try:
        relay = GV_Relay.objects.get(pk=pk)
    except GV_Relay.DoesNotExist:
        return HttpResponse('1')

    relay.turn_on()
    return HttpResponse('0')
