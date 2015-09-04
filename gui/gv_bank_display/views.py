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
