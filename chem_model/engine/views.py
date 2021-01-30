from django.shortcuts import render
from .utils import integration_script
from .forms import FormulaValidation
from .utils import graph_script
from .utils import save_results_script
from django.contrib.auth.forms import User
from .models import SingleRecord
from .models import Records
from django.http import HttpResponse


# Create your views here.
def index(request):
    if request.method == "POST":
        form = FormulaValidation(request.POST)
        if form.is_valid():
            out = []
            formula = form.cleaned_data["formula"]
            out = integration_script.call_c(formula)
            if out:
                out = graph_script.create_graph(out)
                if request.user.is_authenticated:
                    save_results_script.save_to_db(out, request.user.username, formula)
                return render(request, 'index.html', {'out': out, 'formula': formula, 'results_counter': len(out)})
    else:
        form = FormulaValidation()

    return render(request, 'index.html', {'form': form})


def faq_view(request):
    return render(request, 'faq.html')


