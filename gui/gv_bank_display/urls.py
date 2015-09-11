from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^$', views.index),
	url(r'^banks$', views.bank_display),
    url(r'(?P<pk>\d+)/$', views.bank_detail),
    url(r'(?P<pk>\d+)/fetch/', views.bank_fetch),
    url(r'relays/(?P<pk>\d+)/off/', views.relay_off),
    url(r'relays/(?P<pk>\d+)/on/', views.relay_on),
]
