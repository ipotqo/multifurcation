FROM ubuntu:latest@sha256:67211c14fa74f070d27cc59d69a7fa9aeff8e28ea118ef3babc295a0428a6d21
RUN apt-get update
# RUN apt-get upgrade
# RUN apt-get build-essential
RUN apt-get install -y sudo git gcc g++ make cmake ruby-full python3.8 texlive-xelatex gnuplot 

ENV PATH=/usr/bin/gcc:$PATH
ENV PATH=/usr/bin/cmake:$PATH

RUN cmake --version

# RUN export PATH="/usr/local/opt/cm/bin:$PATH"

# RUN git clone https://www.github.com/ipotqo/multifurcation
# RUN cd multifurcation
# RUN ls

WORKDIR /multifurcation/
COPY . /multifurcation
RUN sh scripts/build.sh
CMD [ "./build/multifurcation" ]

RUN cd mwe
RUN sh scripts/mwe.sh