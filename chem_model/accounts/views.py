from django.shortcuts import render, redirect
from django.contrib.auth.forms import UserCreationForm, User, AuthenticationForm
from django.contrib.auth import authenticate, login, logout


def signup_view(request):
    if request.method == "POST":
        form = UserCreationForm(request.POST)
        if form.is_valid():
            form.save()
            username = form.cleaned_data['username']
            password = form.cleaned_data['password1']
            user = authenticate(username=username, password=password)
            login(request, user)
            return redirect('engine:index')
    else:
        form = UserCreationForm()
    return render(request, 'accounts/signup.html', {'form': form})


def login_view(request):
    if request.method == "POST":
        form = AuthenticationForm(data = request.POST)
        if form.is_valid():
            username = form.cleaned_data['username']
            password = form.cleaned_data['password']
            user = authenticate(username=username, password=password)
            login(request, user)
            return redirect('engine:index')
    else:
        form = AuthenticationForm()
    return render(request, 'accounts/login.html', {'form': form})


def logout_view(request):
    if request.method == 'POST':
        logout(request)
        return redirect('engine:index')