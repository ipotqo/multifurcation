#!/usr/bin/zsh

docker_user=ipoqto
docker_container=multifurcation
docker_name=main

# Docker Build
docker build -t $docker_container .

# Docker Name (Tag)
docker tag $docker_container $docker_user/$docker_container

# Docker Push
docker push $docker_user/$docker_container