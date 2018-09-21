# 沐心测试 MakeFile
#指定编译器
# 编译命令  make [bit=64|32]
# 清理命令 make clean [bit=64|32]
CC := gcc

#指定目标位数 64  32
ifdef bit
BIT := $(bit)
else
BIT := 64
endif

PATHX := x$(BIT)
ifeq ($(BIT),64)
wr=windres --target=pe-x86-64
else
wr=windres --target=pe-i386
endif

FUJIAA:= -finput-charset=UTF-8 -fexec-charset=GBK -m$(BIT)
OBJS := $(PATHX)\main.o $(PATHX)\mainb.o $(PATHX)\main.res
main.exe:MDPATH $(OBJS)
	$(CC) -o $(PATHX)\main.exe $(OBJS)  -mwindows -m$(BIT)
$(PATHX)\main.o:main.c main.h
	$(CC) $(FUJIAA) -c main.c -o $(PATHX)\main.o
$(PATHX)\mainb.o:mainb.c main.h
	$(CC) $(FUJIAA) -c mainb.c -o $(PATHX)\mainb.o
$(PATHX)\main.res:main.rc res/icon.ico res/uac.manifest
	$(wr) --input-format=rc -O coff -i "main.rc" -o "$(PATHX)\main.res"
MDPATH:
	if not exist "$(PATHX)" md "$(PATHX)"
.PHONY:clean
clean:
	del $(PATHX)\*.o $(PATHX)\*.res
