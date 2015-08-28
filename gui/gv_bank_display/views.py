from django.shortcuts import render
from django.http import HttpResponse

from .models import TestModel

def test_view(request):
    tests = TestModel.objects.all()
    output = ', '.join([str(t) for t in tests])
    return HttpResponse(output)


