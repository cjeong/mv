# top-level Makefile
MAKE = make

# targets
sublibs = sys 
subbins = 
subdirs = $(sublibs) $(subbins)
libraries = $(addsuffix .a, $(addprefix $(libdir)/, $(sublibs)))

# misc
TAGS = etags
TAGSFLAGS = -a
tagfile = ./TAGS

# default rule
default: all

# rules
all:
	@for dir in $(subdirs); do \
		echo making $$dir...; \
		($(MAKE) -C $$dir) \
	done

tags:
	@for dir in $(subdirs); do \
		echo tagging $$dir...; \
		($(MAKE) -C $$dir tags) \
	done
	$(TAGS) $(TAGSFLAGS) -o $(tagfile) include/*.h include/*/*.h

check:
	@for dir in $(subtools); do \
		echo making $$dir...; \
		($(MAKE) -C $$dir check) \
	done

doc:
	doxygen ../etc/doxygen.conf

clean:
	@for dir in $(subdirs); do \
		echo cleaning $$dir...; \
		($(MAKE) -C $$dir clean) \
	done
