from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect
from django.contrib import auth


def index(request):
    return render(request, 'home.html')

def logout_view(request):
    auth.logout(request)
    return HttpResponseRedirect("/")
