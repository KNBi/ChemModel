from ..models import Record
from datetime import date
from . import integration_script


def save_to_db(results, formula):
    record, created = Record.objects.get_or_create(date=date.today(), formula=formula, results=results)


def get_or_create_graph(formula):
    try:
        out = Record.objects.get(formula=formula)
        out = list(out.results)
        for i in range(len(out)):
            tmp_out = out[i].strip('\'')
            if len(tmp_out) == 0:
                continue
            if tmp_out.is_numeric() or tmp_out == '-':
                out[i] = tmp_out
    except Exception:
        out = None

    if not out:
        out = integration_script.call_c(formula)
        save_to_db(out, formula)

    return out
