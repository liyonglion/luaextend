
#源码根路径
ROOT_DIR = $(shell pwd)
#动态库路径
LIB_PATH = $(ROOT_DIR)/lib

SRC_DIR = $(ROOT_DIR)/src
#所有的目标
TARGETS = 
LuaPkg = /usr/local
INSTALLDIR = /usr/local/luaextend
MKDIR = mkdir
MKDIRALL = mkdir -p
RM = rm -f
RMALL = $(RM) -rf
CC = gcc
CP = cp -R -f
CFLAGS = 
LDFLAGS = 
PLAT = 
INSTALL_DEPS = 


BASESRC = $(SRC_DIR)/cstring.c \
		  $(SRC_DIR)/defer.c \
		  $(SRC_DIR)/errdef.c \
		  $(SRC_DIR)/slicestring.c\
		  $(SRC_DIR)/stringapi.c
#中间文件
BASE_OBJS = $(patsubst %.c, %.o, $(BASESRC))
OBJS = $(BASE_OBJS)

include src/os.mk

.PHONY: all clean install

all:$(TARGETS)

w32:
	$(MAKE) all CC="gcc -std=gnu99" CFLAGS="-I$(LuaPkg)/include -I$(SRC_DIR) -I$(SRC_DIR)/lionos -I$(SRC_DIR)/path -I$(SRC_DIR)/strings -DWINDOW" LDFLAGS="-L$(LuaPkg)/lib -llua53 -lm -shared" PLAT="win32"

acrossmingw:
	$(MAKE) all CC="i686-w64-mingw32-gcc -std=gnu99" CFLAGS="-I$(SRC_DIR) -I$(SRC_DIR)/lionos -I$(SRC_DIR)/path -I$(SRC_DIR)/strings -DWINDOW" LDFLAGS="-llua53 -lm -shared" PLAT="win32"

linux:
	$(MAKE) all CC="gcc -std=gnu99" CFLAGS="-I$(LuaPkg)/include -I$(SRC_DIR) -I$(SRC_DIR)/lionos -I$(SRC_DIR)/path -I$(SRC_DIR)/strings -DLINUX -fPIC" LDFLAGS="-L$(LuaPkg)/lib -llua -lm -shared -fPIC" PLAT="LINUX"

clean:
	-$(RM) $(OBJS)
	-$(RMALL) $(LIB_PATH)/*

install:$(INSTALL_DEPS)

#静态模式匹配
${OBJS}:%.o:%.c
	${CC} -c $< -o $@ ${CFLAGS}
