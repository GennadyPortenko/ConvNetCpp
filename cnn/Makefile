SOURCES = tensor_t.test.cpp fc_layer_t.test.cpp
TESTS = $(SOURCES:.cpp=)

DEBUG = 1

#---------------------------------
OBJECTS = $(SOURCES:.cpp=.o)

LDFLAGS += -L/usr/lib
LDFLAGS += -L/lib/boost/lib
LDFLAGS += -lboost_unit_test_framework.dll
CPPFLAGS += -Wall
# CPPFLAGS += ...
CPPFLAGS += -I/usr/local/include

ifdef DEBUG
CPPFLAGS += -g
endif

all: $(TESTS)

$(TESTS): $(OBJECTS)
	echo TESTS = $(TESTS);
	$(foreach var, $(OBJECTS), $(CXX) -o $(var:.o=) $(var) $(LDFLAGS);)

$(OBJECTS): $(SOURCES)
	$(foreach var, $(SOURCES), $(CXX) -c $(CPPFLAGS) $(var) -o $(var:.cpp=.o);)

clean: 
	rm -f *.o

build:
	$(MAKE) clean
	$(MAKE)
