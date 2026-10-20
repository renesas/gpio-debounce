# Button Management

This is a software module to help users debounce GPIOs. This README covers development steps. For documentation related to the module itself, see [debounce.md](./docs/debounce.md).

## Needed Tools
- C build tools (build-essential package on Debian/Ubuntu)
- Meson build framework

## How to run tests
```sh
# This sets up the bld directory. Only needs to be run once
# The -D flag is important because it sets a config flag for the bld directory
meson setup bld -Dunity:extension_fixture=true
# Compile all of the code using the bld directory
meson compile -C bld
# Run the test executables through meson verbosely
meson test -C bld -v
```

The Makefile has these commands already, so you can do
```sh
make # Run when there's no build directory
make test # Build + run tests
make clean # Get everything back to what it was before
```

## Pre-commit

This repository uses [pre-commit](https://pre-commit.com) to perform checks and run [uncrustify](https://github.com/uncrustify/uncrustify) before every commit.

The pre-commit rules are configured to run these steps on all staged files:
- Ensure that staged files don't have trailing whitespace.
- Ensure that files end with a newline.
- Prevent large files from being committed to the repo.
- Run uncrustify on all staged files.

If any of the pre-commit lints fail, your staged files will be modified and you must stage them again.

To install pre-commit into this project, follow the steps below.

### Install pre-commit using a python project manager like uv (recommended)

```bash
uv sync
uv run pre-commit install
```

### Install pre-commit with pip + venv

```bash
# Create a virtual environment in the directory .venv
python -m venv .venv

# Install dev dependency inside venv
.venv/bin/pip install --group dev

# Activate venv, install pre-commit, deactivate venv
. .venv/bin/activate
pre-commit install
deactivate
```

## Generating Documentation

It is possible to run `doxygen` to generate API documentation. An HTML page can be found in ./doxy_out/html/index.html

## Directory Structure

- [src](./src/): Source code files
- [include](./include): Headers needed for everything to work
- [tests](./tests): Unit tests
- [tests/mocks](./tests/mocks): Mock FSP modules with associated tests
- [tests/runners](./tests/runners): Test runners for unit tests
- [docs](./docs): Contains additional documentation and assets
- [examples](./examples): Example projects
- [examples/artifacts](./examples/artifacts): Runnable .hex files
