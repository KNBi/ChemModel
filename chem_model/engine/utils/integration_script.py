import subprocess
import os
from ctypes import cdll, c_char


def call_c2(formula):
    try:
        graph = subprocess.check_output(args=["engine\\utils\\projekt_lic.exe"])

        graph = graph.decode()
        graph = graph.split()
        for i in graph:
            i.split('b')
    except Exception as e:
        graph = 0

    return graph


def call_c(formula):
    lic_lib = cdll.LoadLibrary("engine/utils/lic.so")
    graph_algorithm = lic_lib.main
    graph_algorithm.restype = c_char
    graph_algorithm()

    graphs = []
    with open('results.txt', 'r') as file:
        for line in file.read():
            line = line.strip()
            if len(line):
                graphs.append(line)

    return graphs


def call_c3(formula):
    print(os.getcwd())
    graph = subprocess.check_output(args=["engine\\utils\\lic"])
    graphs = []
    with open('results.txt', 'r') as file:
        for line in file.read():
            line = line.strip()
            if len(line):
                graphs.append(line)

    return graphs

