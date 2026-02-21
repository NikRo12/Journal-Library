CXX = g++
CXXFLAGS = -fPIC -Wall -Wextra -std=c++11
LDFLAGS = -shared -pthread
LIB_NAME = liblogger.so

SRCDIR = src
OBJDIR = obj

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = $(LIB_NAME)

all: $(TARGET)
	@cp $(SRCDIR)/journal_api.h ./

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR)

.PHONY: all clean