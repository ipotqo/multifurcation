FROM ubuntu:latest
RUN apt-get update
# RUN apt-get upgrade
# RUN apt-get build-essential
RUN apt-get install -y sudo git gcc g++ make cmake

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