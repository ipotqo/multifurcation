FROM gcc:4.9@sha256:6356ef8b29cc3522527a85b6c58a28626744514bea87a10ff2bf67599a7474f5
RUN sh scripts/build.sh
CMD ["./build/multifurcation"]