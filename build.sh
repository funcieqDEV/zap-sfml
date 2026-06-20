#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT_DIR"

mkdir -p build

g++ -std=c++17 -Wall -Wextra -c src/lib/wrapper/sfml.cpp -o build/sfml.o

if [ "$#" -eq 0 ]; then
  thor build
else
  thor "$@"
fi
