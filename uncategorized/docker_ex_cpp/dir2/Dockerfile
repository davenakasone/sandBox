FROM gcc:8.4
# your image and the version, can also use "latest"

COPY . /usr/src/cpp_test
# "dot" will get all local files, source is where gcc lives in image
# or list by files   COPY main.cpp /usr/src
# you will make a "cpp_test" where it all gets copied

WORKDIR /usr/src/cpp_test
# where you want to work, all commands run here

#RUN make
RUN g++ -o test main.cpp
# compiles in cpp_test
# can also run make file, needs more though

CMD ["./test"]
# what you want to run in container, run the binary

#ARG VERSION=20.04
# FROM ubuntu:${VERSION}
# RUN apt-get update -y
# CMD ["bash"]
# could have use the Makefile, but want consistent compilation
# go to docker hub and get gcc official image

# $ docker build . -t cppex:1111
# ....only lower case allowed  nice to put a tag number in

# $ docker run --rm -it cppex:1111
# rm flag removes container if it exists, then reruns
# good for compiling

