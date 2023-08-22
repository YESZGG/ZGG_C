SRC = $(wildcard *.c)
ELF = $(SRC:%.c=%.elf)

PWD = $(shell pwd)

CPPFLAGS += -I $(PWD)/cJSON
CPPFLAGS += -I $(PWD)/netwarp

LDFLAGS += -L $(PWD)/cJSON
LDFLAGS += -L $(PWD)/netwrap
LDFLAGS += -lcjson
LDFLAGS += -lvnet
LDFLAGS += -Wl,-rpath=$(PWD)/cJSON
LDFLAGS += -Wl,-rpath=$(PWD)/netwrap

vpath %.so.%=$(PWD)/cJSON

$(ELF):%.elf:%.c
	$(CC) $< -o $@ $(CPPFLAGS) $(LDFLAGS)

install:
	$(MAKE) -C $(PWD)/cJSON
	$(MAKE) -C $(PWD)/netwrap

clean:
	$(RM) $(ELF)

distclean:clean
	$(MAKE) -C $(PWD)/cJSON clean
