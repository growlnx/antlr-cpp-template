ROOT := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

.DEFAULT_GOAL := debug

debug:
	$(MAKE) -C $(ROOT)src MODE=debug

release:
	$(MAKE) -C $(ROOT)src MODE=release

antlr:
	$(MAKE) -C $(ROOT)src antlr

format:
	$(MAKE) -C $(ROOT)src format

clean:
	$(MAKE) -C $(ROOT)src clean

.PHONY: debug release antlr format clean
