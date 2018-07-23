FROM debian:stretch
LABEL maintainer="Hostmasternode Developers <dev@hostmasternode.com>"
LABEL description="Dockerised HostmasternodeCore, built from Travis"

RUN apt-get update && apt-get -y upgrade && apt-get clean && rm -fr /var/cache/apt/*

COPY bin/* /usr/bin/
