#-------------------------------------------------------------------------------
# General makefile for C/C++ projects using SFML on linux
#-------------------------------------------------------------------------------

TARGET		:=	$(shell basename $(CURDIR))
SOURCES		:=	include include/game/camera include/game/map include/game/misc include/game/player include/game/spawner include/game/states include/aw/ include/aw/colSystem include/aw/general include/aw/states include/aw/utilities
INCLUDES	:=	include include/aw include/game
BUILD		:=	build

#-------------------------------------------------------------------------------
SYSTEM		:=	$(shell uname -s)
CFILES		:=	$(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(wildcard $(dir)/*.cpp))
OFILES		:=	$(addprefix $(BUILD)/,$(CFILES:%.c=%.o)\
			$(CPPFILES:%.cpp=%.o))
DEPENDFILES	:=	$(OFILES:%.o=%.d)
CC		:=	gcc
CXX		:=	g++
INCLUDEFILES	:=	$(foreach dir,$(INCLUDES),$(wildcard $(dir)/*.h))
INCLUDE		:=	$(addprefix -I,$(INCLUDES))
DEPENDFLAGS	:=	-MMD -MP
CFLAGS		:=	$(INCLUDE) -Wall -O2
CXXFLAGS	:=	$(CFLAGS) -std=c++11
# Set LIBSUFFIX to -s for static build (for some reason not working :/ )
LIBSUFFIX	:=	
LIBS		:=	tgui$(LIBSUFFIX) sfml-audio$(LIBSUFFIX) sfml-graphics$(LIBSUFFIX) sfml-window$(LIBSUFFIX) sfml-system$(LIBSUFFIX) GL GLU X11 Xrandr freetype GLEW jpeg sndfile openal
LDFLAGS		:=	$(addprefix -l,$(LIBS))

all: setup $(TARGET)

$(TARGET): $(OFILES)
	$(CXX) $(CFLAGS) -o $(TARGET) $^ $(LDFLAGS)

.PHONY: setup clean

setup:
	$(foreach source,$(SOURCES),$(shell echo \
	$(shell [ -d $(BUILD)/$(source) ] || ( mkdir -p $(BUILD)/$(source)) )))

clean:
	-rm -fr $(TARGET) $(BUILD)

-include $(DEPENDFILES)

#-------------------------------------------------------------------------------
$(BUILD)/%.o: %.c
	@echo $(notdir $<)
	$(CC) $(DEPENDFLAGS) $(CXXFLAGS) $(INCLUDE) -c $< -o $@
	@echo

$(BUILD)/%.o: %.cpp
	@echo $(notdir $<)
	$(CXX) $(DEPENDFLAGS) $(CXXFLAGS) $(INCLUDE) -c $< -o $@
	@echo
