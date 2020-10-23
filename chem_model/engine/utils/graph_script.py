import networkx as nx
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import io
import base64
from PIL import Image
import copy


def create_elements_dict(elements_lst):
    dict = {}
    help_dict = {}
    for i in range(0, len(elements_lst) - 1, 2):
        if elements_lst[i + 1] not in help_dict:
            help_dict[elements_lst[i + 1]] = 1
        else:
            help_dict[elements_lst[i + 1]] += 1

        dict[elements_lst[i]] = elements_lst[i + 1] + str(help_dict[elements_lst[i + 1]])

    return dict


def extract_formula(out):
    main_lst = []
    tmp_lst = []
    for i in range(0, len(out)):
        if out[i] == '-' and len(tmp_lst) != 0:
            main_lst.append(copy.deepcopy(tmp_lst))
            tmp_lst.clear()
        elif out[i] != '-':
            tmp_lst.append(out[i])
    main_lst.append(copy.deepcopy(tmp_lst))
    return main_lst


def create_graph(out):
    elements_dict = {}
    outcomes_lst = []
    outcomes_lst = extract_formula(out)
    elements_dict = create_elements_dict(outcomes_lst.pop(-1))

    return_lst = []

    for formula in outcomes_lst:
        tmp_d = {}
        G = nx.Graph()

        for j in range(0, len(formula) - 1, 2):
            if (elements_dict[formula[j]], elements_dict[formula[j + 1]]) in G.edges:
                tmp_d[(elements_dict[formula[j]], elements_dict[formula[j + 1]])] += 1
            else:
                G.add_edge(elements_dict[formula[j]], elements_dict[formula[j + 1]])
                tmp_d[(elements_dict[formula[j]], elements_dict[formula[j + 1]])] = 1

        pos = nx.spring_layout(G)
        nx.draw_networkx_edge_labels(G, pos, edge_labels=tmp_d)
        nx.draw(G, pos=pos, with_labels=True)

        img = io.BytesIO()
        output = io.StringIO()
        plt.savefig(img, format="png")
        img = Image.open(img)
        byte_str = io.BytesIO()
        img.save(byte_str, format="PNG")

        b64 = base64.b64encode(byte_str.getvalue())
        return_lst.append(b64.decode("ascii"))
        plt.close()

    return return_lst
