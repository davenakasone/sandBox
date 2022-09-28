FROM ubuntu:20.04
# base image must be first, specify OS and version

RUN apt-get -y update && apt-get install -y
# update and install base image

RUN apt-get -y install clang
# need to install software (compling with clang, not gcc)

RUN apt-get -y install make
# install for Makefile ??? ...good idea

COPY . /usr/src/cpp_test
# copy this directory to image

WORKDIR /usr/src/cpp_test
# working from here on image

#RUN clang++ -Wall -std=c++14 -o test main.cpp
RUN make raw
# what you want to compile ...use that Makefile if possible

CMD ["./test"]
# run the program

# $ docker build . -t cpx:2222
# $ docker run --rm -it cpx:2222
