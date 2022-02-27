# local makefile
# without customization it doesn't do much
# no sharing or installing targets defined in the lib/makefile-cc yet, should share to $(RESOURCES)

# this file is also included into lib/makefile-cc
-include $(RESOURCES)/lib/makefile-env
-include makefile-env

.PHONY: all 
all: version

.PHONY: dep
dep:
	if [ -e $(DEPFILE) ]; then rm $(DEPFILE); fi
	$(MAKE) $@

.PHONY: lib
lib:
	$(MAKE) $@

.PHONY: exec
exec:
	$(MAKE) $@

.PHONY: share
share:
	$(MAKE) $@

.PHONY: clean
clean:
	$(MAKE) $@

.PHONY: dist-clean
dist-clean:
	$(MAKE) $@

%::
	$(MAKE) $@




