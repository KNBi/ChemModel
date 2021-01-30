from django.shortcuts import render
from .forms import FormulaValidation
from .utils import graph_script
from .utils import save_results_script


# mongod --dbpath \..\..\mongoDB-databases\
# Create your views here.
def index(request):
    if request.method == "POST":
        form = FormulaValidation(request.POST)
        if form.is_valid():
            formula = form.cleaned_data["formula"]
            out = save_results_script.get_or_create_graph(formula)

            if out:
                out = graph_script.create_graph(out)

                return render(request, 'index.html', {'out': out, 'formula': formula, 'results_counter': len(out)})
    else:
        form = FormulaValidation()

    return render(request, 'index.html', {'form': form})


def faq_view(request):
    return render(request, 'faq.html')


