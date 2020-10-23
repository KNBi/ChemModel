from django import forms
import chempy
import platform

atoms_dict = {
    1: 'H',
    6: 'C',
    7: 'N',
    8: 'O',
    15: 'P',
    11: 'Na',
    19: 'K',
    35: 'Br',
    53: 'I',
    9: 'F',
    17: 'Cl',
    16: 'S',
    3: 'Li'
}


class FormulaValidation(forms.Form):
    formula = forms.CharField(required = True)

    def clean(self):
        formula = self.cleaned_data["formula"]

        if len(formula) < 2:
            self.cleaned_data["formula"] = None
            raise forms.ValidationError("Error! Single element or invalid formula!")
        try:
            formula = chempy.Substance.from_formula(formula)
        except:
            self.cleaned_data["formula"] = None
            raise forms.ValidationError("Error! Invalid formula")

        for at in list(formula.composition.keys()):
            if at not in atoms_dict:
                self.cleaned_data["formula"] = None
                raise forms.ValidationError("Error! Our solution supports only few elements, "
                                            "check FAQ page for more information.")

        return self.cleaned_data

    def _post_clean(self):
        atoms_lst = []
        amounts_lst = []
        if self.cleaned_data["formula"]:
            f = chempy.Substance.from_formula(self.cleaned_data["formula"])
            amounts_lst = list(f.composition.values())

            for i in range(0, len(amounts_lst)):
                amounts_lst[i] = str(amounts_lst[i])

            for at in list(f.composition.keys()):
                atoms_lst.append(atoms_dict[at])

            file = open('formula.txt', 'w')

            file.write(" ".join(atoms_lst))
            file.write("\n")
            file.write(" ".join(amounts_lst))

            file.close()
