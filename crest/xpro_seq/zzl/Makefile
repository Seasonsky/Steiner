
SUFFIX  = cpp
GCC = g++ -std=c++11

IFLAG = -I. 

BINPATH = .
OBJPATH = .

SOURCES = $(wildcard *.$(SUFFIX))
OBJECTS = $(SOURCES:%.$(SUFFIX)=$(OBJPATH)/%.o)
HEADERS = $(wildcard ./*.h)
CFLAGS = $(IFLAG) -c   


TARGET = $(BINPATH)/a.out 

$(TARGET):$(OBJECTS) 
	$(GCC) -o $(TARGET) $(OBJECTS)

$(OBJPATH)/%.o: %.$(SUFFIX) $(HEADERS)
	$(GCC) -o $@ $(CFLAGS) $<
	@echo "-- Making is okay --"        
.KEEP_STATE:
clean:
	@-rm -rf *.o *.a *.out *~ *.stackdump 	
	@-rm -rf $(OBJECTS)
	@-rm -rf $(BINPATH)/$(TARGET)
debug:
	@$(MAKE) -f makefile DBG="-g"
opt:
	@$(MAKE) -f makefile DBG="-O3"
info:

	@echo "                                 "	
	@echo "Final executable files: $(TARGET)"
	@echo "Source files: $(SOURCES)"
	@echo "Object files: $(OBJECTS)"
	@echo "                                 "
