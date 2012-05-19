PACKAGE_NAME = com.example.Monkey.Poop
PROJET_NAME = Physics2d
ACTIVITY_NAME = .$(PROJET_NAME)
#JAVA_HOME = /usr/lib/jvm/java-6-sun/unzipped_src/

DEBUG_TARGET= bin/$(PROJET_NAME)-debug.apk
RELEASE_TARGET= bin/$(PROJET_NAME).apk

.PHONY: force

ANT_FLAGS = -emacs 
NDK_DEBUG_FLAGS = \
									"NDK_DEBUG=1" \
									"V=1" \

NDK_RELEASE_FLAGS =

JAVA_FILES := $(wildcard src/*/*/*.java) $(wildcard src/*/*/*/*.java)
CPP_FILES := \
	$(wildcard jni/*.cpp) \
	$(wildcard jni/*.h) \
	$(wildcard jni/*/*.cpp) \
	$(wildcard **/.cpp) \

PROJECT_BUILD_FILES = local.properties build.xml

all: $(DEBUG_TARGET) 

$(PROJECT_BUILD_FILES):
	android update project --name $(PROJET_NAME) --target 7 -p ./

$(DEBUG_TARGET): $(PROJECT_BUILD_FILES) force
	$(MAKE) tags
	ndk-build $(NDK_DEBUG_FLAGS) 
	ant debug

$(RELEASE_TARGET): force
	$(MAKE) tags
	ndk-build $(NDK_RELEASE_FLAGS) 
	ant release

run: install

install: 
	ant clean
	ndk-build $(NDK_DEBUG_FLAGS) 
	ant $(ANT_FLAGS) debug install
	adb shell "am start -n $(PACKAGE_NAME)/$(ACTIVITY_NAME)"

install_release:
	ant clean
	ndk-build $(NDK_RELEASE_FLAGS) 
	ant $(ANT_FLAGS) release install
	adb shell "am start -n $(PACKAGE_NAME)/$(ACTIVITY_NAME)"

#adb install -r $(DEBUG_TARGET)

uninstall:
	ndk-build uninstall

clean: force
	ant clean
	ndk-build $(NDK_DEBUG_FLAGS) clean

sdk_tags:
	-ctags -R -o $(HOME)/.vim/ctags/android_java --sort=yes \
	  --fields=+iaKsS --extra=+q \
		--c++-kinds=+p \
		$(JAVA_HOME) \
	  $(ANDROID_SDK)/android_src_git/

#--java-types=cfimp --language-force=java \

tags: $(JAVA_FILES) $(CPP_FILES)
	-ctags -R --sort=yes \
	--java-types=cfimp \
	  --fields=+iaKsS --extra=+q \
		--c++-kinds=+p \
		./src/ ./


#/usr/lib/jvm/java-6-sun/com/sun/org/apache/xerces/



