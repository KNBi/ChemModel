From ubuntu:latest

From python:3.7

COPY ./chem_model chem_model

WORKDIR /chem_model

RUN pip install -r requirements.txt

# WORKDIR engine/utils/

# RUN /bin/sh -c 'g++ -fPIC -shared -o engine/utils/lic.so engine/utils/lic.cpp'

# COPY lic.so ../utils

# WORKDIR ../../

