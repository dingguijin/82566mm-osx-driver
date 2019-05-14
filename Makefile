CC = /Developer/usr/bin/gcc 
CXX = /Developer/usr/bin/g++ 
SYSROOT = /Developer/SDKs/MacOSX10.7.sdk
ARCHFLAGS = -arch x86_64 -isysroot ${SYSROOT} -mmacosx-version-min=10.7 -Xlinker -kext
ROOTDIR = `pwd`

CXXFLAGS = -x c++ ${ARCHFLAGS} -fmessage-length=0 -pipe -nostdinc -fno-builtin \
	-Wno-trigraphs -fno-exceptions -fno-rtti -fcheck-new -fasm-blocks \
	-force_cpusubtype_ALL -static -msoft-float -Os -fno-common \
	-mkernel -finline -fno-keep-inline-functions -Wreturn-type \
	-Wunused-variable -DKERNEL -DKERNEL_PRIVATE -DDRIVER_PRIVATE -DAPPLE \
	-DNeXT -fapple-kext -gdwarf-2 \
	-I/System/Library/Frameworks/Kernel.framework/PrivateHeaders \
        -I/Developer/SDKs/MacOSX10.7.sdk/System/Library/Frameworks/Kernel.framework/Headers \
	-I.

CFLAGS = -x c ${ARCHFLAGS} -fmessage-length=0 -pipe -nostdinc -std=c99 -fno-builtin \
	-Wno-trigraphs -fasm-blocks -force_cpusubtype_ALL -static -msoft-float -Os -fno-common \
	-mkernel -finline -fno-keep-inline-functions -Wreturn-type -Wunused-variable \
	-DKERNEL -DKERNEL_PRIVATE -DDRIVER_PRIVATE -DAPPLE -DNeXT -gdwarf-2 \
	-I/System/Library/Frameworks/Kernel.framework/PrivateHeaders \
        -I/Developer/SDKs/MacOSX10.7.sdk/System/Library/Frameworks/Kernel.framework/Headers \
	-I.

CXXLDFLAGS = -lcpp_kext -static -nostdlib -r -lkmodc++ 
CLDFLAGS = -lkmod -lcc_kext

COBJS = Intel82566MM_info.o e1000_nvm.o e1000_ich8lan.o e1000_phy.o e1000_manage.o e1000_mac.o e1000_80003es2lan.o e1000_82571.o e1000.o
CXXOBJS = Intel82566MM.o

DRIVER_IMAGE = Intel82566MM
all: ${DRIVER_IMAGE}
	cp ${DRIVER_IMAGE} ${ROOTDIR}/Intel82566MM.kext/Contents/MacOS/

%.o: %.cpp
	${CC} -c ${CXXFLAGS} $< -o $@
%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

${DRIVER_IMAGE}: ${COBJS} ${CXXOBJS}
	${CXX} ${ARCHFLAGS} ${CXXOBJS} ${CXXLDFLAGS} ${COBJS} ${CLDFLAGS} -o ${DRIVER_IMAGE} 

clean:
	rm -f *.o ${DRIVER_IMAGE} *~
