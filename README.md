# SOA CMS Development Environment

This project uses a Docker container to provide a consistent development environment for working with the `soa-cms-dev` stack.

## 🚀 Prerequisites

- You must have [Docker](https://www.docker.com/) installed and working on your system.

To verify:

```bash
docker --version

For building the image locally, run

```bash
docker build -t soa-cms-dev .

And then run the container 

```bash
docker run --rm -it -v $(pwd):/workspace -w /workspace soa-cms-dev

Inside the workspace, compile the standalone code:

```bash
mkdir -p build
cd build
cmake ..
make
