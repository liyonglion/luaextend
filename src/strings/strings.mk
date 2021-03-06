#目标名
STRINGS_TARGET = strings
#string 生成OBJ路径和动态库路径
STRINGS_OBJ_DIR = ${SRC_DIR}/${STRINGS_TARGET}
STRING_LIB_PATH = ${LIB_PATH}/${STRINGS_TARGET}
#源文件
STRING_SOURCE = $(STRINGS_OBJ_DIR)/strings.c \
				$(STRINGS_OBJ_DIR)/md5.c \
				$(STRINGS_OBJ_DIR)/base64.c
#中间文件
STRINGS_OBJS = $(patsubst %.c, %.o, $(STRING_SOURCE))
#安装依赖
INSTALL_DEPS += install-$(STRINGS_TARGET)
STRINGS_LIB = ${STRINGS_TARGET}

ifeq (${PLAT}, win32)
	STRINGS_LIB =  ${STRING_LIB_PATH}/${STRINGS_TARGET}.dll
else
	STRINGS_LIB =  ${STRING_LIB_PATH}/${STRINGS_TARGET}.so
endif

#添加进全局目标集合
TARGETS += ${STRINGS_LIB}

OBJS += ${STRINGS_OBJS}

${STRINGS_LIB}: ${STRINGS_OBJS} $(BASE_OBJS)
	-$(MKDIR) $(STRING_LIB_PATH)
	${CC} -o ${STRINGS_LIB} $^ ${LDFLAGS}

install-strings:
	-$(MKDIRALL) $(INSTALLDIR)/$(STRINGS_TARGET)/
	-$(CP) $(STRING_LIB_PATH)/$(STRINGS_TARGET).* $(INSTALLDIR)/$(STRINGS_TARGET)/
