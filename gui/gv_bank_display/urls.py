from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^test$', views.test_view),
    url(r'^$', views.index),
	url(r'^banks$', views.bank_display),
    url(r'(?P<pk>\d+)/$', views.bank_detail),
]
