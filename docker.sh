#!/bin/bash
set -e

if command -v git &>/dev/null && git rev-parse --show-toplevel &>/dev/null; then
    BASE_DIR="$(git rev-parse --show-toplevel)"
elif BASE_DIR="$(find "$(realpath "${PWD}")" \
    -maxdepth 10 \
    -type f \
    -name .root \
    -exec dirname {} \; | head -n1)" && [ -n "${BASE_DIR}" ]; then :
else
    BASE_DIR="$(dirname "$(realpath "$0")")"
fi

DOCKER_IMAGE="arena"

docker build -t ${DOCKER_IMAGE} ${BASE_DIR}

DOCKER_ARGS=(
    "--rm"
    "--interactive"
    "--tty"
    "--name=libarena"
    "--user=admin"
    "--network=host"
    "--ipc=host"
    "--privileged=true"
    "--security-opt=seccomp=unconfined"
    "--cap-add=SYS_PTRACE"
    "--env=DISPLAY=${DISPLAY}"
    "--env=NVIDIA_VISIBLE_DEVICES=all"
    "--env=NVIDIA_DRIVER_CAPABILITIES=all"
    "--env=TZ=Asia/Seoul"
    "--mount=source=/etc/localtime,target=/etc/localtime,type=bind,consistency=cached:ro"
    "--mount=source=/etc/timezone,target=/etc/timezone,type=bind,consistency=cached:ro"
    "--mount=source=/dev,target=/dev,type=bind,consistency=cached:ro"
    "--mount=source=/run/udev,target=/run/udev,type=bind,consistency=cached:ro"
    "--mount=source=/run/dbus/system_bus_socket,target=/run/dbus/system_bus_socket,type=bind,consistency=cached:ro"
    "--mount=source=/media,target=/media,type=bind,consistency=cached"
    "--mount=source=/mnt,target=/mnt,type=bind,consistency=cached"
    "--mount=source=/tmp/.X11-unix,target=/tmp/.X11-unix,type=bind,consistency=cached"
    "--mount=source=${HOME}/.ssh,target=${HOME}/.ssh,type=bind,consistency=cached"
    "--mount=source=${BASE_DIR},target=/workspaces/libarena,type=bind"
    "--workdir=/workspaces/libarena"
    "${DOCKER_IMAGE}"
)

CONTAINER_COMMANDS="
    ulimit -c 0;
    /bin/bash
"

docker run "${DOCKER_ARGS[@]}" /bin/bash -c "${CONTAINER_COMMANDS}"
