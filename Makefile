TARGET = ih8sn

ANDROID_NDK_HOME ?= ./android-ndk-r21
export PATH := $(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/linux-x86_64/bin:$(PATH)

ARCH ?= aarch64

CC = $(ARCH)-linux-android29-clang
CXX = $(ARCH)-linux-android29-clang++
CXXFLAGS = \
	-static \
	-std=c++17 \
	-Wall \
	-Wextra

OBJS = \
	main.o

OBJS += \
	aosp/bionic/libc/bionic/system_property_api.o \
	aosp/bionic/libc/bionic/system_property_set.o \
	aosp/bionic/libc/system_properties/context_node.o \
	aosp/bionic/libc/system_properties/contexts_serialized.o \
	aosp/bionic/libc/system_properties/contexts_split.o \
	aosp/bionic/libc/system_properties/prop_area.o \
	aosp/bionic/libc/system_properties/prop_info.o \
	aosp/bionic/libc/system_properties/system_properties.o \
	aosp/system/core/base/strings.o \
	aosp/system/core/property_service/libpropertyinfoparser/property_info_parser.o

INCDIRS = \
	aosp/bionic/libc \
	aosp/bionic/libc/async_safe/include \
	aosp/bionic/libc/system_properties/include \
	aosp/system/core/base/include \
	aosp/system/core/property_service/libpropertyinfoparser/include

# -------- Shoudn't touch after this line --------

CXXFLAGS += $(foreach dir,$(INCDIRS),-I$(dir))

.PHONY: all
all: $(TARGET)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
