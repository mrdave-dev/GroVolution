from django.shortcuts import render
from django.http import HttpResponse

from .models import TestModel

def test_view(request):
    tests = TestModel.objects.all()
    output = ', '.join([str(t) for t in tests])
    return HttpResponse(output)

def index(request):
    return render(request, 'gv_bank_display/index.html')
