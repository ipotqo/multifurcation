FROM gcc:4.9
RUN sh scripts/build.sh
CMD ["./build/multifurcation"]