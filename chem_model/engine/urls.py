from django.urls import path
from . import views

app_name = 'engine'

urlpatterns = [
    path('', views.index, name='index'),
    path('FAQ/', views.faq_view, name='faq'),
    path('previous_results/', views.previous_results_view, name='previous_results'),
]



