#!/usr/bin/zsh

docker_user=ipotqo
docker_container=multifurcation
docker_name=multifurcation

# Docker Login
# docker login -u $docker_user

# Docker Pull
# docker pull $docker_user/$docker_container:$docker_name

# Docker Build
docker build -t $docker_container .

# Docker Name (Tag)
docker tag $docker_name $docker_user/$docker_container

# Docker Push
docker push $docker_user/$docker_container