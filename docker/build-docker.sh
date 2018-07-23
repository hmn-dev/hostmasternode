#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/..

DOCKER_IMAGE=${DOCKER_IMAGE:-hostmasternodepay/hostmasternoded-develop}
DOCKER_TAG=${DOCKER_TAG:-latest}

BUILD_DIR=${BUILD_DIR:-.}

rm docker/bin/*
mkdir docker/bin
cp $BUILD_DIR/src/hostmasternoded docker/bin/
cp $BUILD_DIR/src/hostmasternode-cli docker/bin/
cp $BUILD_DIR/src/hostmasternode-tx docker/bin/
strip docker/bin/hostmasternoded
strip docker/bin/hostmasternode-cli
strip docker/bin/hostmasternode-tx

docker build --pull -t $DOCKER_IMAGE:$DOCKER_TAG -f docker/Dockerfile docker
