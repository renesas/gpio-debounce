./bld/:
	meson setup bld -Dunity:extension_fixture=true -Dunity:extension_memory=enabled

.PHONY: build test clean pack examples

build: ./bld/
	meson compile -C bld

test: build
	meson test -C bld --print-errorlogs

clean:
	rm -rf ./bld/
	rm -f compile_commands.json
	rm -rf ./doxy_out/
	rm -rf ./pack/out/

examples:
	scripts/examples.sh
