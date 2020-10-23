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


def previous_results_view(request):
    filtered = False
    formula = None

    if request.method == "POST":
        formula = request.POST.get('formula', None)
        filtered = True if formula else False

    previous_out = []
    if request.user.is_authenticated:
        formulas = []
        f_obj = Records.objects.filter(user__username=request.user.username)
        for i in f_obj:
            if formula:
                if i.formula == formula:
                    formulas.append(i.formula)
            else:
                formulas.append(i.formula)
        formulas = list(set(formulas))
        for i in formulas:
            obj = SingleRecord.objects.filter(records__user__username=request.user.username).filter(records__formula=i)
            previous_out.append([j.picture_base64 for j in obj])

    return render(request, 'previous_results.html', {'previous_out': previous_out,
                                                     'filtered': filtered,
                                                     'formula': formula,
                                                     })


def faq_view(request):
    return render(request, 'faq.html')


