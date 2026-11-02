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
