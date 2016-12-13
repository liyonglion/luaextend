#目标名
PATH_TARGET = path
#path 生成OBJ路径和动态库路径
PATH_OBJ_DIR = ${SRC_DIR}/${PATH_TARGET}
PATH_LIB_PATH = ${LIB_PATH}/${PATH_TARGET}
#源文件
PATH_SOURCE = $(PATH_OBJ_DIR)/path.c 
#中间文件
PATH_OBJS = $(patsubst %.c, %.o, $(PATH_SOURCE))
#安装依赖
INSTALL_DEPS += install-$(PATH_TARGET)

PATH_LIB = ${PATH_TARGET}

ifeq (${PLAT}, win32)
	PATH_LIB =  ${PATH_LIB_PATH}/${PATH_TARGET}.dll
else
	PATH_LIB =  ${PATH_LIB_PATH}/${PATH_TARGET}.so
endif

#添加进全局目标集合
TARGETS += ${PATH_LIB}

OBJS += ${PATH_OBJS}

${PATH_LIB}: ${PATH_OBJS} $(BASE_OBJS)
	-$(MKDIR) $(PATH_LIB_PATH)
	${CC} -o ${PATH_LIB} $^ ${LDFLAGS}

install-path:
	-$(MKDIRALL) $(INSTALLDIR)/$(PATH_TARGET)/
	-$(CP) $(PATH_LIB_PATH)/$(PATH_TARGET).* $(INSTALLDIR)/$(PATH_TARGET)/
