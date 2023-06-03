SHADER_COMPILER = external/bgfx/.build/linux64_gcc/bin/shadercRelease
DEFAULT_SHADER_FLAGS = --verbose -i external/bgfx/src/
BUILD_DIR = build_dir/shaders/

.PHONY: all
all: spirv 100_es opengl

$(BUILD_DIR)spirv/simple.fragment.bin: src/shaders/simple.fragment.sc
	@mkdir -p $(@D)
	$(SHADER_COMPILER) -f src/shaders/simple.fragment.sc -o $(BUILD_DIR)spirv/simple.fragment.bin --platform linux --type fragment $(DEFAULT_SHADER_FLAGS) -p spirv

$(BUILD_DIR)spirv/simple.vertex.bin: src/shaders/simple.vertex.sc
	@mkdir -p $(@D)
	$(SHADER_COMPILER) -f src/shaders/simple.vertex.sc -o $(BUILD_DIR)spirv/simple.vertex.bin --platform linux --type vertex $(DEFAULT_SHADER_FLAGS) -p spirv

.PHONY: spirv
spirv: $(BUILD_DIR)spirv/simple.fragment.bin $(BUILD_DIR)spirv/simple.vertex.bin

$(BUILD_DIR)100_es/simple.fragment.bin: src/shaders/simple.fragment.sc
	@mkdir -p $(@D)
	$(SHADER_COMPILER) -f src/shaders/simple.fragment.sc -o $(BUILD_DIR)100_es/simple.fragment.bin --platform linux --type fragment $(DEFAULT_SHADER_FLAGS) -p 100_es

$(BUILD_DIR)100_es/simple.vertex.bin: src/shaders/simple.vertex.sc
	@mkdir -p $(@D)
	$(SHADER_COMPILER) -f src/shaders/simple.vertex.sc -o $(BUILD_DIR)100_es/simple.vertex.bin --platform linux --type vertex $(DEFAULT_SHADER_FLAGS) -p 100_es

.PHONY: 100_es
100_es: $(BUILD_DIR)100_es/simple.fragment.bin $(BUILD_DIR)100_es/simple.vertex.bin

$(BUILD_DIR)opengl/simple.fragment.bin: src/shaders/simple.fragment.sc
	@mkdir -p $(@D)
	$(SHADER_COMPILER) -f src/shaders/simple.fragment.sc -o $(BUILD_DIR)opengl/simple.fragment.bin --platform linux --type fragment $(DEFAULT_SHADER_FLAGS)

$(BUILD_DIR)opengl/simple.vertex.bin: src/shaders/simple.vertex.sc
	@mkdir -p $(@D)
	$(SHADER_COMPILER) -f src/shaders/simple.vertex.sc -o $(BUILD_DIR)opengl/simple.vertex.bin --platform linux --type vertex $(DEFAULT_SHADER_FLAGS)

.PHONY: opengl
opengl: $(BUILD_DIR)opengl/simple.fragment.bin $(BUILD_DIR)opengl/simple.vertex.bin

