
MAKEFLAGS += Rr
CXX := em++
CXXFLAGS := -Wall -Wextra -Wpedantic -Wshadow -std=c++14
OBJECTS :=  ./build/camera.o ./build/cart.o ./build/cart_obj.o ./build/common.o ./build/key.o ./build/main.o ./build/mouse.o ./build/obj_loader.o ./build/shader.o ./build/spline.o ./build/track_obj.o ./build/vao.o

.PHONY: all clean

all: a.out.js

a.out.js: $(OBJECTS)
	$(CXX) $(OBJECTS)

clean:
	rm -f ./build/*.o a.out.js

./build/%.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

build/camera.o: src/camera.cpp src/camera.hpp src/common.hpp \
 src/glm/glm.hpp src/glm/detail/_fixes.hpp src/glm/detail/setup.hpp \
 src/glm/detail/../simd/platform.h src/glm/fwd.hpp \
 src/glm/detail/qualifier.hpp src/glm/detail/setup.hpp src/glm/vec2.hpp \
 src/glm/./ext/vector_bool2.hpp src/glm/./ext/../detail/type_vec2.hpp \
 src/glm/./ext/../detail/type_vec2.inl \
 src/glm/./ext/../detail/./compute_vector_relational.hpp \
 src/glm/./ext/../detail/./setup.hpp \
 src/glm/./ext/vector_bool2_precision.hpp src/glm/./ext/vector_float2.hpp \
 src/glm/./ext/vector_float2_precision.hpp \
 src/glm/./ext/vector_double2.hpp \
 src/glm/./ext/vector_double2_precision.hpp src/glm/./ext/vector_int2.hpp \
 src/glm/./ext/vector_int2_sized.hpp \
 src/glm/./ext/../ext/scalar_int_sized.hpp \
 src/glm/./ext/../ext/../detail/setup.hpp src/glm/./ext/vector_uint2.hpp \
 src/glm/./ext/vector_uint2_sized.hpp \
 src/glm/./ext/../ext/scalar_uint_sized.hpp src/glm/vec3.hpp \
 src/glm/./ext/vector_bool3.hpp src/glm/./ext/../detail/type_vec3.hpp \
 src/glm/./ext/../detail/type_vec3.inl \
 src/glm/./ext/vector_bool3_precision.hpp src/glm/./ext/vector_float3.hpp \
 src/glm/./ext/vector_float3_precision.hpp \
 src/glm/./ext/vector_double3.hpp \
 src/glm/./ext/vector_double3_precision.hpp src/glm/./ext/vector_int3.hpp \
 src/glm/./ext/vector_int3_sized.hpp src/glm/./ext/vector_uint3.hpp \
 src/glm/./ext/vector_uint3_sized.hpp src/glm/vec4.hpp \
 src/glm/./ext/vector_bool4.hpp src/glm/./ext/../detail/type_vec4.hpp \
 src/glm/./ext/../detail/type_vec4.inl \
 src/glm/./ext/vector_bool4_precision.hpp src/glm/./ext/vector_float4.hpp \
 src/glm/./ext/vector_float4_precision.hpp \
 src/glm/./ext/vector_double4.hpp \
 src/glm/./ext/vector_double4_precision.hpp \
 src/glm/./ext/../detail/setup.hpp src/glm/./ext/vector_int4.hpp \
 src/glm/./ext/vector_int4_sized.hpp src/glm/./ext/vector_uint4.hpp \
 src/glm/./ext/vector_uint4_sized.hpp src/glm/mat2x2.hpp \
 src/glm/./ext/matrix_double2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.inl \
 src/glm/./ext/../detail/../matrix.hpp \
 src/glm/./ext/../detail/../detail/setup.hpp \
 src/glm/./ext/../detail/../mat2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3_precision.hpp \
 src/glm/./ext/../detail/../mat2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4_precision.hpp \
 src/glm/./ext/../detail/../mat3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2_precision.hpp \
 src/glm/./ext/../detail/../mat3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3_precision.hpp \
 src/glm/./ext/../detail/../mat3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4_precision.hpp \
 src/glm/./ext/../detail/../mat4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2_precision.hpp \
 src/glm/./ext/../detail/../mat4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3_precision.hpp \
 src/glm/./ext/../detail/../mat4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4_precision.hpp \
 src/glm/./ext/../detail/../detail/func_matrix.inl \
 c:\users\mm\desktop\wgl\src\glm\geometric.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_geometric.inl \
 c:\users\mm\desktop\wgl\src\glm\exponential.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/func_exponential.inl \
 c:\users\mm\desktop\wgl\src\glm\vector_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_vector_relational.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/_vectorize.hpp \
 c:\users\mm\desktop\wgl\src\glm\common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/_fixes.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_common.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/compute_common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 src/glm/./ext/matrix_double2x2_precision.hpp \
 src/glm/./ext/matrix_float2x2.hpp \
 src/glm/./ext/matrix_float2x2_precision.hpp src/glm/trigonometric.hpp \
 src/glm/detail/func_trigonometric.inl src/glm/packing.hpp \
 src/glm/detail/func_packing.inl src/glm/detail/type_half.hpp \
 src/glm/detail/type_half.inl src/glm/integer.hpp \
 src/glm/detail/func_integer.inl src/glm/gtc/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_projection.hpp \
 src/glm/gtc/../ext/../gtc/constants.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\setup.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.inl \
 src/glm/gtc/../ext/../gtc/constants.inl \
 src/glm/gtc/../ext/matrix_projection.inl \
 src/glm/gtc/../ext/matrix_clip_space.hpp \
 src/glm/gtc/../ext/matrix_clip_space.inl \
 src/glm/gtc/../ext/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_transform.inl src/glm/gtc/matrix_transform.inl \
 src/glm/gtc/quaternion.hpp src/glm/gtc/../ext/vector_relational.hpp \
 src/glm/gtc/../ext/vector_relational.inl \
 src/glm/gtc/../ext/../detail/type_float.hpp \
 src/glm/gtc/../ext/../detail/setup.hpp \
 src/glm/gtc/../ext/quaternion_common.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.inl \
 src/glm/gtc/../ext/quaternion_common.inl \
 src/glm/gtc/../ext/quaternion_float.hpp \
 src/glm/gtc/../ext/../detail/type_quat.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.inl \
 src/glm/gtc/../ext/../detail/type_quat.inl \
 src/glm/gtc/../ext/quaternion_float_precision.hpp \
 src/glm/gtc/../ext/quaternion_double.hpp \
 src/glm/gtc/../ext/quaternion_double_precision.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.inl \
 src/glm/gtc/../ext/quaternion_transform.hpp \
 src/glm/gtc/../ext/quaternion_transform.inl src/glm/gtc/quaternion.inl \
 src/glm/gtc/epsilon.hpp src/glm/gtc/../detail/setup.hpp \
 src/glm/gtc/epsilon.inl src/glm/gtx/quaternion.hpp \
 src/glm/gtx/../ext/quaternion_exponential.hpp \
 src/glm/gtx/../ext/quaternion_exponential.inl \
 src/glm/gtx/../gtx/norm.hpp src/glm/gtx/../gtx/../gtx/component_wise.hpp \
 src/glm/gtx/../gtx/../gtx/../detail/setup.hpp \
 src/glm/gtx/../gtx/../gtx/component_wise.inl src/glm/gtx/../gtx/norm.inl \
 src/glm/gtx/quaternion.inl src/cart.hpp src/vao.hpp
build/cart.o: src/cart.cpp src/cart.hpp src/common.hpp src/glm/glm.hpp \
 src/glm/detail/_fixes.hpp src/glm/detail/setup.hpp \
 src/glm/detail/../simd/platform.h src/glm/fwd.hpp \
 src/glm/detail/qualifier.hpp src/glm/detail/setup.hpp src/glm/vec2.hpp \
 src/glm/./ext/vector_bool2.hpp src/glm/./ext/../detail/type_vec2.hpp \
 src/glm/./ext/../detail/type_vec2.inl \
 src/glm/./ext/../detail/./compute_vector_relational.hpp \
 src/glm/./ext/../detail/./setup.hpp \
 src/glm/./ext/vector_bool2_precision.hpp src/glm/./ext/vector_float2.hpp \
 src/glm/./ext/vector_float2_precision.hpp \
 src/glm/./ext/vector_double2.hpp \
 src/glm/./ext/vector_double2_precision.hpp src/glm/./ext/vector_int2.hpp \
 src/glm/./ext/vector_int2_sized.hpp \
 src/glm/./ext/../ext/scalar_int_sized.hpp \
 src/glm/./ext/../ext/../detail/setup.hpp src/glm/./ext/vector_uint2.hpp \
 src/glm/./ext/vector_uint2_sized.hpp \
 src/glm/./ext/../ext/scalar_uint_sized.hpp src/glm/vec3.hpp \
 src/glm/./ext/vector_bool3.hpp src/glm/./ext/../detail/type_vec3.hpp \
 src/glm/./ext/../detail/type_vec3.inl \
 src/glm/./ext/vector_bool3_precision.hpp src/glm/./ext/vector_float3.hpp \
 src/glm/./ext/vector_float3_precision.hpp \
 src/glm/./ext/vector_double3.hpp \
 src/glm/./ext/vector_double3_precision.hpp src/glm/./ext/vector_int3.hpp \
 src/glm/./ext/vector_int3_sized.hpp src/glm/./ext/vector_uint3.hpp \
 src/glm/./ext/vector_uint3_sized.hpp src/glm/vec4.hpp \
 src/glm/./ext/vector_bool4.hpp src/glm/./ext/../detail/type_vec4.hpp \
 src/glm/./ext/../detail/type_vec4.inl \
 src/glm/./ext/vector_bool4_precision.hpp src/glm/./ext/vector_float4.hpp \
 src/glm/./ext/vector_float4_precision.hpp \
 src/glm/./ext/vector_double4.hpp \
 src/glm/./ext/vector_double4_precision.hpp \
 src/glm/./ext/../detail/setup.hpp src/glm/./ext/vector_int4.hpp \
 src/glm/./ext/vector_int4_sized.hpp src/glm/./ext/vector_uint4.hpp \
 src/glm/./ext/vector_uint4_sized.hpp src/glm/mat2x2.hpp \
 src/glm/./ext/matrix_double2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.inl \
 src/glm/./ext/../detail/../matrix.hpp \
 src/glm/./ext/../detail/../detail/setup.hpp \
 src/glm/./ext/../detail/../mat2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3_precision.hpp \
 src/glm/./ext/../detail/../mat2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4_precision.hpp \
 src/glm/./ext/../detail/../mat3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2_precision.hpp \
 src/glm/./ext/../detail/../mat3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3_precision.hpp \
 src/glm/./ext/../detail/../mat3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4_precision.hpp \
 src/glm/./ext/../detail/../mat4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2_precision.hpp \
 src/glm/./ext/../detail/../mat4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3_precision.hpp \
 src/glm/./ext/../detail/../mat4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4_precision.hpp \
 src/glm/./ext/../detail/../detail/func_matrix.inl \
 c:\users\mm\desktop\wgl\src\glm\geometric.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_geometric.inl \
 c:\users\mm\desktop\wgl\src\glm\exponential.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/func_exponential.inl \
 c:\users\mm\desktop\wgl\src\glm\vector_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_vector_relational.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/_vectorize.hpp \
 c:\users\mm\desktop\wgl\src\glm\common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/_fixes.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_common.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/compute_common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 src/glm/./ext/matrix_double2x2_precision.hpp \
 src/glm/./ext/matrix_float2x2.hpp \
 src/glm/./ext/matrix_float2x2_precision.hpp src/glm/trigonometric.hpp \
 src/glm/detail/func_trigonometric.inl src/glm/packing.hpp \
 src/glm/detail/func_packing.inl src/glm/detail/type_half.hpp \
 src/glm/detail/type_half.inl src/glm/integer.hpp \
 src/glm/detail/func_integer.inl src/glm/gtc/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_projection.hpp \
 src/glm/gtc/../ext/../gtc/constants.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\setup.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.inl \
 src/glm/gtc/../ext/../gtc/constants.inl \
 src/glm/gtc/../ext/matrix_projection.inl \
 src/glm/gtc/../ext/matrix_clip_space.hpp \
 src/glm/gtc/../ext/matrix_clip_space.inl \
 src/glm/gtc/../ext/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_transform.inl src/glm/gtc/matrix_transform.inl \
 src/glm/gtc/quaternion.hpp src/glm/gtc/../ext/vector_relational.hpp \
 src/glm/gtc/../ext/vector_relational.inl \
 src/glm/gtc/../ext/../detail/type_float.hpp \
 src/glm/gtc/../ext/../detail/setup.hpp \
 src/glm/gtc/../ext/quaternion_common.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.inl \
 src/glm/gtc/../ext/quaternion_common.inl \
 src/glm/gtc/../ext/quaternion_float.hpp \
 src/glm/gtc/../ext/../detail/type_quat.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.inl \
 src/glm/gtc/../ext/../detail/type_quat.inl \
 src/glm/gtc/../ext/quaternion_float_precision.hpp \
 src/glm/gtc/../ext/quaternion_double.hpp \
 src/glm/gtc/../ext/quaternion_double_precision.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.inl \
 src/glm/gtc/../ext/quaternion_transform.hpp \
 src/glm/gtc/../ext/quaternion_transform.inl src/glm/gtc/quaternion.inl \
 src/glm/gtc/epsilon.hpp src/glm/gtc/../detail/setup.hpp \
 src/glm/gtc/epsilon.inl src/vao.hpp src/spline.hpp src/obj_loader.hpp
build/cart_obj.o: src/cart_obj.cpp src/obj_loader.hpp src/vao.hpp \
 src/common.hpp src/glm/glm.hpp src/glm/detail/_fixes.hpp \
 src/glm/detail/setup.hpp src/glm/detail/../simd/platform.h \
 src/glm/fwd.hpp src/glm/detail/qualifier.hpp src/glm/detail/setup.hpp \
 src/glm/vec2.hpp src/glm/./ext/vector_bool2.hpp \
 src/glm/./ext/../detail/type_vec2.hpp \
 src/glm/./ext/../detail/type_vec2.inl \
 src/glm/./ext/../detail/./compute_vector_relational.hpp \
 src/glm/./ext/../detail/./setup.hpp \
 src/glm/./ext/vector_bool2_precision.hpp src/glm/./ext/vector_float2.hpp \
 src/glm/./ext/vector_float2_precision.hpp \
 src/glm/./ext/vector_double2.hpp \
 src/glm/./ext/vector_double2_precision.hpp src/glm/./ext/vector_int2.hpp \
 src/glm/./ext/vector_int2_sized.hpp \
 src/glm/./ext/../ext/scalar_int_sized.hpp \
 src/glm/./ext/../ext/../detail/setup.hpp src/glm/./ext/vector_uint2.hpp \
 src/glm/./ext/vector_uint2_sized.hpp \
 src/glm/./ext/../ext/scalar_uint_sized.hpp src/glm/vec3.hpp \
 src/glm/./ext/vector_bool3.hpp src/glm/./ext/../detail/type_vec3.hpp \
 src/glm/./ext/../detail/type_vec3.inl \
 src/glm/./ext/vector_bool3_precision.hpp src/glm/./ext/vector_float3.hpp \
 src/glm/./ext/vector_float3_precision.hpp \
 src/glm/./ext/vector_double3.hpp \
 src/glm/./ext/vector_double3_precision.hpp src/glm/./ext/vector_int3.hpp \
 src/glm/./ext/vector_int3_sized.hpp src/glm/./ext/vector_uint3.hpp \
 src/glm/./ext/vector_uint3_sized.hpp src/glm/vec4.hpp \
 src/glm/./ext/vector_bool4.hpp src/glm/./ext/../detail/type_vec4.hpp \
 src/glm/./ext/../detail/type_vec4.inl \
 src/glm/./ext/vector_bool4_precision.hpp src/glm/./ext/vector_float4.hpp \
 src/glm/./ext/vector_float4_precision.hpp \
 src/glm/./ext/vector_double4.hpp \
 src/glm/./ext/vector_double4_precision.hpp \
 src/glm/./ext/../detail/setup.hpp src/glm/./ext/vector_int4.hpp \
 src/glm/./ext/vector_int4_sized.hpp src/glm/./ext/vector_uint4.hpp \
 src/glm/./ext/vector_uint4_sized.hpp src/glm/mat2x2.hpp \
 src/glm/./ext/matrix_double2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.inl \
 src/glm/./ext/../detail/../matrix.hpp \
 src/glm/./ext/../detail/../detail/setup.hpp \
 src/glm/./ext/../detail/../mat2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3_precision.hpp \
 src/glm/./ext/../detail/../mat2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4_precision.hpp \
 src/glm/./ext/../detail/../mat3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2_precision.hpp \
 src/glm/./ext/../detail/../mat3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3_precision.hpp \
 src/glm/./ext/../detail/../mat3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4_precision.hpp \
 src/glm/./ext/../detail/../mat4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2_precision.hpp \
 src/glm/./ext/../detail/../mat4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3_precision.hpp \
 src/glm/./ext/../detail/../mat4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4_precision.hpp \
 src/glm/./ext/../detail/../detail/func_matrix.inl \
 c:\users\mm\desktop\wgl\src\glm\geometric.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_geometric.inl \
 c:\users\mm\desktop\wgl\src\glm\exponential.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/func_exponential.inl \
 c:\users\mm\desktop\wgl\src\glm\vector_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_vector_relational.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/_vectorize.hpp \
 c:\users\mm\desktop\wgl\src\glm\common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/_fixes.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_common.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/compute_common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 src/glm/./ext/matrix_double2x2_precision.hpp \
 src/glm/./ext/matrix_float2x2.hpp \
 src/glm/./ext/matrix_float2x2_precision.hpp src/glm/trigonometric.hpp \
 src/glm/detail/func_trigonometric.inl src/glm/packing.hpp \
 src/glm/detail/func_packing.inl src/glm/detail/type_half.hpp \
 src/glm/detail/type_half.inl src/glm/integer.hpp \
 src/glm/detail/func_integer.inl src/glm/gtc/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_projection.hpp \
 src/glm/gtc/../ext/../gtc/constants.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\setup.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.inl \
 src/glm/gtc/../ext/../gtc/constants.inl \
 src/glm/gtc/../ext/matrix_projection.inl \
 src/glm/gtc/../ext/matrix_clip_space.hpp \
 src/glm/gtc/../ext/matrix_clip_space.inl \
 src/glm/gtc/../ext/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_transform.inl src/glm/gtc/matrix_transform.inl \
 src/glm/gtc/quaternion.hpp src/glm/gtc/../ext/vector_relational.hpp \
 src/glm/gtc/../ext/vector_relational.inl \
 src/glm/gtc/../ext/../detail/type_float.hpp \
 src/glm/gtc/../ext/../detail/setup.hpp \
 src/glm/gtc/../ext/quaternion_common.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.inl \
 src/glm/gtc/../ext/quaternion_common.inl \
 src/glm/gtc/../ext/quaternion_float.hpp \
 src/glm/gtc/../ext/../detail/type_quat.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.inl \
 src/glm/gtc/../ext/../detail/type_quat.inl \
 src/glm/gtc/../ext/quaternion_float_precision.hpp \
 src/glm/gtc/../ext/quaternion_double.hpp \
 src/glm/gtc/../ext/quaternion_double_precision.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.inl \
 src/glm/gtc/../ext/quaternion_transform.hpp \
 src/glm/gtc/../ext/quaternion_transform.inl src/glm/gtc/quaternion.inl \
 src/glm/gtc/epsilon.hpp src/glm/gtc/../detail/setup.hpp \
 src/glm/gtc/epsilon.inl
build/common.o: src/common.cpp src/common.hpp src/glm/glm.hpp \
 src/glm/detail/_fixes.hpp src/glm/detail/setup.hpp \
 src/glm/detail/../simd/platform.h src/glm/fwd.hpp \
 src/glm/detail/qualifier.hpp src/glm/detail/setup.hpp src/glm/vec2.hpp \
 src/glm/./ext/vector_bool2.hpp src/glm/./ext/../detail/type_vec2.hpp \
 src/glm/./ext/../detail/type_vec2.inl \
 src/glm/./ext/../detail/./compute_vector_relational.hpp \
 src/glm/./ext/../detail/./setup.hpp \
 src/glm/./ext/vector_bool2_precision.hpp src/glm/./ext/vector_float2.hpp \
 src/glm/./ext/vector_float2_precision.hpp \
 src/glm/./ext/vector_double2.hpp \
 src/glm/./ext/vector_double2_precision.hpp src/glm/./ext/vector_int2.hpp \
 src/glm/./ext/vector_int2_sized.hpp \
 src/glm/./ext/../ext/scalar_int_sized.hpp \
 src/glm/./ext/../ext/../detail/setup.hpp src/glm/./ext/vector_uint2.hpp \
 src/glm/./ext/vector_uint2_sized.hpp \
 src/glm/./ext/../ext/scalar_uint_sized.hpp src/glm/vec3.hpp \
 src/glm/./ext/vector_bool3.hpp src/glm/./ext/../detail/type_vec3.hpp \
 src/glm/./ext/../detail/type_vec3.inl \
 src/glm/./ext/vector_bool3_precision.hpp src/glm/./ext/vector_float3.hpp \
 src/glm/./ext/vector_float3_precision.hpp \
 src/glm/./ext/vector_double3.hpp \
 src/glm/./ext/vector_double3_precision.hpp src/glm/./ext/vector_int3.hpp \
 src/glm/./ext/vector_int3_sized.hpp src/glm/./ext/vector_uint3.hpp \
 src/glm/./ext/vector_uint3_sized.hpp src/glm/vec4.hpp \
 src/glm/./ext/vector_bool4.hpp src/glm/./ext/../detail/type_vec4.hpp \
 src/glm/./ext/../detail/type_vec4.inl \
 src/glm/./ext/vector_bool4_precision.hpp src/glm/./ext/vector_float4.hpp \
 src/glm/./ext/vector_float4_precision.hpp \
 src/glm/./ext/vector_double4.hpp \
 src/glm/./ext/vector_double4_precision.hpp \
 src/glm/./ext/../detail/setup.hpp src/glm/./ext/vector_int4.hpp \
 src/glm/./ext/vector_int4_sized.hpp src/glm/./ext/vector_uint4.hpp \
 src/glm/./ext/vector_uint4_sized.hpp src/glm/mat2x2.hpp \
 src/glm/./ext/matrix_double2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.inl \
 src/glm/./ext/../detail/../matrix.hpp \
 src/glm/./ext/../detail/../detail/setup.hpp \
 src/glm/./ext/../detail/../mat2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3_precision.hpp \
 src/glm/./ext/../detail/../mat2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4_precision.hpp \
 src/glm/./ext/../detail/../mat3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2_precision.hpp \
 src/glm/./ext/../detail/../mat3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3_precision.hpp \
 src/glm/./ext/../detail/../mat3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4_precision.hpp \
 src/glm/./ext/../detail/../mat4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2_precision.hpp \
 src/glm/./ext/../detail/../mat4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3_precision.hpp \
 src/glm/./ext/../detail/../mat4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4_precision.hpp \
 src/glm/./ext/../detail/../detail/func_matrix.inl \
 c:\users\mm\desktop\wgl\src\glm\geometric.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_geometric.inl \
 c:\users\mm\desktop\wgl\src\glm\exponential.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/func_exponential.inl \
 c:\users\mm\desktop\wgl\src\glm\vector_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_vector_relational.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/_vectorize.hpp \
 c:\users\mm\desktop\wgl\src\glm\common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/_fixes.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_common.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/compute_common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 src/glm/./ext/matrix_double2x2_precision.hpp \
 src/glm/./ext/matrix_float2x2.hpp \
 src/glm/./ext/matrix_float2x2_precision.hpp src/glm/trigonometric.hpp \
 src/glm/detail/func_trigonometric.inl src/glm/packing.hpp \
 src/glm/detail/func_packing.inl src/glm/detail/type_half.hpp \
 src/glm/detail/type_half.inl src/glm/integer.hpp \
 src/glm/detail/func_integer.inl src/glm/gtc/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_projection.hpp \
 src/glm/gtc/../ext/../gtc/constants.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\setup.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.inl \
 src/glm/gtc/../ext/../gtc/constants.inl \
 src/glm/gtc/../ext/matrix_projection.inl \
 src/glm/gtc/../ext/matrix_clip_space.hpp \
 src/glm/gtc/../ext/matrix_clip_space.inl \
 src/glm/gtc/../ext/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_transform.inl src/glm/gtc/matrix_transform.inl \
 src/glm/gtc/quaternion.hpp src/glm/gtc/../ext/vector_relational.hpp \
 src/glm/gtc/../ext/vector_relational.inl \
 src/glm/gtc/../ext/../detail/type_float.hpp \
 src/glm/gtc/../ext/../detail/setup.hpp \
 src/glm/gtc/../ext/quaternion_common.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.inl \
 src/glm/gtc/../ext/quaternion_common.inl \
 src/glm/gtc/../ext/quaternion_float.hpp \
 src/glm/gtc/../ext/../detail/type_quat.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.inl \
 src/glm/gtc/../ext/../detail/type_quat.inl \
 src/glm/gtc/../ext/quaternion_float_precision.hpp \
 src/glm/gtc/../ext/quaternion_double.hpp \
 src/glm/gtc/../ext/quaternion_double_precision.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.inl \
 src/glm/gtc/../ext/quaternion_transform.hpp \
 src/glm/gtc/../ext/quaternion_transform.inl src/glm/gtc/quaternion.inl \
 src/glm/gtc/epsilon.hpp src/glm/gtc/../detail/setup.hpp \
 src/glm/gtc/epsilon.inl src/camera.hpp
build/key.o: src/key.cpp src/key.hpp src/common.hpp src/glm/glm.hpp \
 src/glm/detail/_fixes.hpp src/glm/detail/setup.hpp \
 src/glm/detail/../simd/platform.h src/glm/fwd.hpp \
 src/glm/detail/qualifier.hpp src/glm/detail/setup.hpp src/glm/vec2.hpp \
 src/glm/./ext/vector_bool2.hpp src/glm/./ext/../detail/type_vec2.hpp \
 src/glm/./ext/../detail/type_vec2.inl \
 src/glm/./ext/../detail/./compute_vector_relational.hpp \
 src/glm/./ext/../detail/./setup.hpp \
 src/glm/./ext/vector_bool2_precision.hpp src/glm/./ext/vector_float2.hpp \
 src/glm/./ext/vector_float2_precision.hpp \
 src/glm/./ext/vector_double2.hpp \
 src/glm/./ext/vector_double2_precision.hpp src/glm/./ext/vector_int2.hpp \
 src/glm/./ext/vector_int2_sized.hpp \
 src/glm/./ext/../ext/scalar_int_sized.hpp \
 src/glm/./ext/../ext/../detail/setup.hpp src/glm/./ext/vector_uint2.hpp \
 src/glm/./ext/vector_uint2_sized.hpp \
 src/glm/./ext/../ext/scalar_uint_sized.hpp src/glm/vec3.hpp \
 src/glm/./ext/vector_bool3.hpp src/glm/./ext/../detail/type_vec3.hpp \
 src/glm/./ext/../detail/type_vec3.inl \
 src/glm/./ext/vector_bool3_precision.hpp src/glm/./ext/vector_float3.hpp \
 src/glm/./ext/vector_float3_precision.hpp \
 src/glm/./ext/vector_double3.hpp \
 src/glm/./ext/vector_double3_precision.hpp src/glm/./ext/vector_int3.hpp \
 src/glm/./ext/vector_int3_sized.hpp src/glm/./ext/vector_uint3.hpp \
 src/glm/./ext/vector_uint3_sized.hpp src/glm/vec4.hpp \
 src/glm/./ext/vector_bool4.hpp src/glm/./ext/../detail/type_vec4.hpp \
 src/glm/./ext/../detail/type_vec4.inl \
 src/glm/./ext/vector_bool4_precision.hpp src/glm/./ext/vector_float4.hpp \
 src/glm/./ext/vector_float4_precision.hpp \
 src/glm/./ext/vector_double4.hpp \
 src/glm/./ext/vector_double4_precision.hpp \
 src/glm/./ext/../detail/setup.hpp src/glm/./ext/vector_int4.hpp \
 src/glm/./ext/vector_int4_sized.hpp src/glm/./ext/vector_uint4.hpp \
 src/glm/./ext/vector_uint4_sized.hpp src/glm/mat2x2.hpp \
 src/glm/./ext/matrix_double2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.inl \
 src/glm/./ext/../detail/../matrix.hpp \
 src/glm/./ext/../detail/../detail/setup.hpp \
 src/glm/./ext/../detail/../mat2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3_precision.hpp \
 src/glm/./ext/../detail/../mat2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4_precision.hpp \
 src/glm/./ext/../detail/../mat3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2_precision.hpp \
 src/glm/./ext/../detail/../mat3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3_precision.hpp \
 src/glm/./ext/../detail/../mat3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4_precision.hpp \
 src/glm/./ext/../detail/../mat4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2_precision.hpp \
 src/glm/./ext/../detail/../mat4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3_precision.hpp \
 src/glm/./ext/../detail/../mat4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4_precision.hpp \
 src/glm/./ext/../detail/../detail/func_matrix.inl \
 c:\users\mm\desktop\wgl\src\glm\geometric.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_geometric.inl \
 c:\users\mm\desktop\wgl\src\glm\exponential.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/func_exponential.inl \
 c:\users\mm\desktop\wgl\src\glm\vector_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_vector_relational.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/_vectorize.hpp \
 c:\users\mm\desktop\wgl\src\glm\common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/_fixes.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_common.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/compute_common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 src/glm/./ext/matrix_double2x2_precision.hpp \
 src/glm/./ext/matrix_float2x2.hpp \
 src/glm/./ext/matrix_float2x2_precision.hpp src/glm/trigonometric.hpp \
 src/glm/detail/func_trigonometric.inl src/glm/packing.hpp \
 src/glm/detail/func_packing.inl src/glm/detail/type_half.hpp \
 src/glm/detail/type_half.inl src/glm/integer.hpp \
 src/glm/detail/func_integer.inl src/glm/gtc/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_projection.hpp \
 src/glm/gtc/../ext/../gtc/constants.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\setup.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.inl \
 src/glm/gtc/../ext/../gtc/constants.inl \
 src/glm/gtc/../ext/matrix_projection.inl \
 src/glm/gtc/../ext/matrix_clip_space.hpp \
 src/glm/gtc/../ext/matrix_clip_space.inl \
 src/glm/gtc/../ext/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_transform.inl src/glm/gtc/matrix_transform.inl \
 src/glm/gtc/quaternion.hpp src/glm/gtc/../ext/vector_relational.hpp \
 src/glm/gtc/../ext/vector_relational.inl \
 src/glm/gtc/../ext/../detail/type_float.hpp \
 src/glm/gtc/../ext/../detail/setup.hpp \
 src/glm/gtc/../ext/quaternion_common.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.inl \
 src/glm/gtc/../ext/quaternion_common.inl \
 src/glm/gtc/../ext/quaternion_float.hpp \
 src/glm/gtc/../ext/../detail/type_quat.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.inl \
 src/glm/gtc/../ext/../detail/type_quat.inl \
 src/glm/gtc/../ext/quaternion_float_precision.hpp \
 src/glm/gtc/../ext/quaternion_double.hpp \
 src/glm/gtc/../ext/quaternion_double_precision.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.inl \
 src/glm/gtc/../ext/quaternion_transform.hpp \
 src/glm/gtc/../ext/quaternion_transform.inl src/glm/gtc/quaternion.inl \
 src/glm/gtc/epsilon.hpp src/glm/gtc/../detail/setup.hpp \
 src/glm/gtc/epsilon.inl
build/main.o: src/main.cpp src/shader.hpp src/common.hpp src/glm/glm.hpp \
 src/glm/detail/_fixes.hpp src/glm/detail/setup.hpp \
 src/glm/detail/../simd/platform.h src/glm/fwd.hpp \
 src/glm/detail/qualifier.hpp src/glm/detail/setup.hpp src/glm/vec2.hpp \
 src/glm/./ext/vector_bool2.hpp src/glm/./ext/../detail/type_vec2.hpp \
 src/glm/./ext/../detail/type_vec2.inl \
 src/glm/./ext/../detail/./compute_vector_relational.hpp \
 src/glm/./ext/../detail/./setup.hpp \
 src/glm/./ext/vector_bool2_precision.hpp src/glm/./ext/vector_float2.hpp \
 src/glm/./ext/vector_float2_precision.hpp \
 src/glm/./ext/vector_double2.hpp \
 src/glm/./ext/vector_double2_precision.hpp src/glm/./ext/vector_int2.hpp \
 src/glm/./ext/vector_int2_sized.hpp \
 src/glm/./ext/../ext/scalar_int_sized.hpp \
 src/glm/./ext/../ext/../detail/setup.hpp src/glm/./ext/vector_uint2.hpp \
 src/glm/./ext/vector_uint2_sized.hpp \
 src/glm/./ext/../ext/scalar_uint_sized.hpp src/glm/vec3.hpp \
 src/glm/./ext/vector_bool3.hpp src/glm/./ext/../detail/type_vec3.hpp \
 src/glm/./ext/../detail/type_vec3.inl \
 src/glm/./ext/vector_bool3_precision.hpp src/glm/./ext/vector_float3.hpp \
 src/glm/./ext/vector_float3_precision.hpp \
 src/glm/./ext/vector_double3.hpp \
 src/glm/./ext/vector_double3_precision.hpp src/glm/./ext/vector_int3.hpp \
 src/glm/./ext/vector_int3_sized.hpp src/glm/./ext/vector_uint3.hpp \
 src/glm/./ext/vector_uint3_sized.hpp src/glm/vec4.hpp \
 src/glm/./ext/vector_bool4.hpp src/glm/./ext/../detail/type_vec4.hpp \
 src/glm/./ext/../detail/type_vec4.inl \
 src/glm/./ext/vector_bool4_precision.hpp src/glm/./ext/vector_float4.hpp \
 src/glm/./ext/vector_float4_precision.hpp \
 src/glm/./ext/vector_double4.hpp \
 src/glm/./ext/vector_double4_precision.hpp \
 src/glm/./ext/../detail/setup.hpp src/glm/./ext/vector_int4.hpp \
 src/glm/./ext/vector_int4_sized.hpp src/glm/./ext/vector_uint4.hpp \
 src/glm/./ext/vector_uint4_sized.hpp src/glm/mat2x2.hpp \
 src/glm/./ext/matrix_double2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.inl \
 src/glm/./ext/../detail/../matrix.hpp \
 src/glm/./ext/../detail/../detail/setup.hpp \
 src/glm/./ext/../detail/../mat2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3_precision.hpp \
 src/glm/./ext/../detail/../mat2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4_precision.hpp \
 src/glm/./ext/../detail/../mat3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2_precision.hpp \
 src/glm/./ext/../detail/../mat3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3_precision.hpp \
 src/glm/./ext/../detail/../mat3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4_precision.hpp \
 src/glm/./ext/../detail/../mat4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2_precision.hpp \
 src/glm/./ext/../detail/../mat4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3_precision.hpp \
 src/glm/./ext/../detail/../mat4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4_precision.hpp \
 src/glm/./ext/../detail/../detail/func_matrix.inl \
 c:\users\mm\desktop\wgl\src\glm\geometric.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_geometric.inl \
 c:\users\mm\desktop\wgl\src\glm\exponential.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/func_exponential.inl \
 c:\users\mm\desktop\wgl\src\glm\vector_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_vector_relational.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/_vectorize.hpp \
 c:\users\mm\desktop\wgl\src\glm\common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/_fixes.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_common.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/compute_common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 src/glm/./ext/matrix_double2x2_precision.hpp \
 src/glm/./ext/matrix_float2x2.hpp \
 src/glm/./ext/matrix_float2x2_precision.hpp src/glm/trigonometric.hpp \
 src/glm/detail/func_trigonometric.inl src/glm/packing.hpp \
 src/glm/detail/func_packing.inl src/glm/detail/type_half.hpp \
 src/glm/detail/type_half.inl src/glm/integer.hpp \
 src/glm/detail/func_integer.inl src/glm/gtc/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_projection.hpp \
 src/glm/gtc/../ext/../gtc/constants.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\setup.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.inl \
 src/glm/gtc/../ext/../gtc/constants.inl \
 src/glm/gtc/../ext/matrix_projection.inl \
 src/glm/gtc/../ext/matrix_clip_space.hpp \
 src/glm/gtc/../ext/matrix_clip_space.inl \
 src/glm/gtc/../ext/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_transform.inl src/glm/gtc/matrix_transform.inl \
 src/glm/gtc/quaternion.hpp src/glm/gtc/../ext/vector_relational.hpp \
 src/glm/gtc/../ext/vector_relational.inl \
 src/glm/gtc/../ext/../detail/type_float.hpp \
 src/glm/gtc/../ext/../detail/setup.hpp \
 src/glm/gtc/../ext/quaternion_common.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.inl \
 src/glm/gtc/../ext/quaternion_common.inl \
 src/glm/gtc/../ext/quaternion_float.hpp \
 src/glm/gtc/../ext/../detail/type_quat.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.inl \
 src/glm/gtc/../ext/../detail/type_quat.inl \
 src/glm/gtc/../ext/quaternion_float_precision.hpp \
 src/glm/gtc/../ext/quaternion_double.hpp \
 src/glm/gtc/../ext/quaternion_double_precision.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.inl \
 src/glm/gtc/../ext/quaternion_transform.hpp \
 src/glm/gtc/../ext/quaternion_transform.inl src/glm/gtc/quaternion.inl \
 src/glm/gtc/epsilon.hpp src/glm/gtc/../detail/setup.hpp \
 src/glm/gtc/epsilon.inl src/vao.hpp src/camera.hpp src/mouse.hpp \
 src/key.hpp src/spline.hpp src/cart.hpp
build/mouse.o: src/mouse.cpp src/mouse.hpp src/common.hpp src/glm/glm.hpp \
 src/glm/detail/_fixes.hpp src/glm/detail/setup.hpp \
 src/glm/detail/../simd/platform.h src/glm/fwd.hpp \
 src/glm/detail/qualifier.hpp src/glm/detail/setup.hpp src/glm/vec2.hpp \
 src/glm/./ext/vector_bool2.hpp src/glm/./ext/../detail/type_vec2.hpp \
 src/glm/./ext/../detail/type_vec2.inl \
 src/glm/./ext/../detail/./compute_vector_relational.hpp \
 src/glm/./ext/../detail/./setup.hpp \
 src/glm/./ext/vector_bool2_precision.hpp src/glm/./ext/vector_float2.hpp \
 src/glm/./ext/vector_float2_precision.hpp \
 src/glm/./ext/vector_double2.hpp \
 src/glm/./ext/vector_double2_precision.hpp src/glm/./ext/vector_int2.hpp \
 src/glm/./ext/vector_int2_sized.hpp \
 src/glm/./ext/../ext/scalar_int_sized.hpp \
 src/glm/./ext/../ext/../detail/setup.hpp src/glm/./ext/vector_uint2.hpp \
 src/glm/./ext/vector_uint2_sized.hpp \
 src/glm/./ext/../ext/scalar_uint_sized.hpp src/glm/vec3.hpp \
 src/glm/./ext/vector_bool3.hpp src/glm/./ext/../detail/type_vec3.hpp \
 src/glm/./ext/../detail/type_vec3.inl \
 src/glm/./ext/vector_bool3_precision.hpp src/glm/./ext/vector_float3.hpp \
 src/glm/./ext/vector_float3_precision.hpp \
 src/glm/./ext/vector_double3.hpp \
 src/glm/./ext/vector_double3_precision.hpp src/glm/./ext/vector_int3.hpp \
 src/glm/./ext/vector_int3_sized.hpp src/glm/./ext/vector_uint3.hpp \
 src/glm/./ext/vector_uint3_sized.hpp src/glm/vec4.hpp \
 src/glm/./ext/vector_bool4.hpp src/glm/./ext/../detail/type_vec4.hpp \
 src/glm/./ext/../detail/type_vec4.inl \
 src/glm/./ext/vector_bool4_precision.hpp src/glm/./ext/vector_float4.hpp \
 src/glm/./ext/vector_float4_precision.hpp \
 src/glm/./ext/vector_double4.hpp \
 src/glm/./ext/vector_double4_precision.hpp \
 src/glm/./ext/../detail/setup.hpp src/glm/./ext/vector_int4.hpp \
 src/glm/./ext/vector_int4_sized.hpp src/glm/./ext/vector_uint4.hpp \
 src/glm/./ext/vector_uint4_sized.hpp src/glm/mat2x2.hpp \
 src/glm/./ext/matrix_double2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.inl \
 src/glm/./ext/../detail/../matrix.hpp \
 src/glm/./ext/../detail/../detail/setup.hpp \
 src/glm/./ext/../detail/../mat2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3_precision.hpp \
 src/glm/./ext/../detail/../mat2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4_precision.hpp \
 src/glm/./ext/../detail/../mat3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2_precision.hpp \
 src/glm/./ext/../detail/../mat3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3_precision.hpp \
 src/glm/./ext/../detail/../mat3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4_precision.hpp \
 src/glm/./ext/../detail/../mat4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2_precision.hpp \
 src/glm/./ext/../detail/../mat4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3_precision.hpp \
 src/glm/./ext/../detail/../mat4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4_precision.hpp \
 src/glm/./ext/../detail/../detail/func_matrix.inl \
 c:\users\mm\desktop\wgl\src\glm\geometric.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_geometric.inl \
 c:\users\mm\desktop\wgl\src\glm\exponential.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/func_exponential.inl \
 c:\users\mm\desktop\wgl\src\glm\vector_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_vector_relational.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/_vectorize.hpp \
 c:\users\mm\desktop\wgl\src\glm\common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/_fixes.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_common.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/compute_common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 src/glm/./ext/matrix_double2x2_precision.hpp \
 src/glm/./ext/matrix_float2x2.hpp \
 src/glm/./ext/matrix_float2x2_precision.hpp src/glm/trigonometric.hpp \
 src/glm/detail/func_trigonometric.inl src/glm/packing.hpp \
 src/glm/detail/func_packing.inl src/glm/detail/type_half.hpp \
 src/glm/detail/type_half.inl src/glm/integer.hpp \
 src/glm/detail/func_integer.inl src/glm/gtc/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_projection.hpp \
 src/glm/gtc/../ext/../gtc/constants.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\setup.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.inl \
 src/glm/gtc/../ext/../gtc/constants.inl \
 src/glm/gtc/../ext/matrix_projection.inl \
 src/glm/gtc/../ext/matrix_clip_space.hpp \
 src/glm/gtc/../ext/matrix_clip_space.inl \
 src/glm/gtc/../ext/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_transform.inl src/glm/gtc/matrix_transform.inl \
 src/glm/gtc/quaternion.hpp src/glm/gtc/../ext/vector_relational.hpp \
 src/glm/gtc/../ext/vector_relational.inl \
 src/glm/gtc/../ext/../detail/type_float.hpp \
 src/glm/gtc/../ext/../detail/setup.hpp \
 src/glm/gtc/../ext/quaternion_common.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.inl \
 src/glm/gtc/../ext/quaternion_common.inl \
 src/glm/gtc/../ext/quaternion_float.hpp \
 src/glm/gtc/../ext/../detail/type_quat.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.inl \
 src/glm/gtc/../ext/../detail/type_quat.inl \
 src/glm/gtc/../ext/quaternion_float_precision.hpp \
 src/glm/gtc/../ext/quaternion_double.hpp \
 src/glm/gtc/../ext/quaternion_double_precision.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.inl \
 src/glm/gtc/../ext/quaternion_transform.hpp \
 src/glm/gtc/../ext/quaternion_transform.inl src/glm/gtc/quaternion.inl \
 src/glm/gtc/epsilon.hpp src/glm/gtc/../detail/setup.hpp \
 src/glm/gtc/epsilon.inl
build/obj_loader.o: src/obj_loader.cpp src/obj_loader.hpp src/vao.hpp \
 src/common.hpp src/glm/glm.hpp src/glm/detail/_fixes.hpp \
 src/glm/detail/setup.hpp src/glm/detail/../simd/platform.h \
 src/glm/fwd.hpp src/glm/detail/qualifier.hpp src/glm/detail/setup.hpp \
 src/glm/vec2.hpp src/glm/./ext/vector_bool2.hpp \
 src/glm/./ext/../detail/type_vec2.hpp \
 src/glm/./ext/../detail/type_vec2.inl \
 src/glm/./ext/../detail/./compute_vector_relational.hpp \
 src/glm/./ext/../detail/./setup.hpp \
 src/glm/./ext/vector_bool2_precision.hpp src/glm/./ext/vector_float2.hpp \
 src/glm/./ext/vector_float2_precision.hpp \
 src/glm/./ext/vector_double2.hpp \
 src/glm/./ext/vector_double2_precision.hpp src/glm/./ext/vector_int2.hpp \
 src/glm/./ext/vector_int2_sized.hpp \
 src/glm/./ext/../ext/scalar_int_sized.hpp \
 src/glm/./ext/../ext/../detail/setup.hpp src/glm/./ext/vector_uint2.hpp \
 src/glm/./ext/vector_uint2_sized.hpp \
 src/glm/./ext/../ext/scalar_uint_sized.hpp src/glm/vec3.hpp \
 src/glm/./ext/vector_bool3.hpp src/glm/./ext/../detail/type_vec3.hpp \
 src/glm/./ext/../detail/type_vec3.inl \
 src/glm/./ext/vector_bool3_precision.hpp src/glm/./ext/vector_float3.hpp \
 src/glm/./ext/vector_float3_precision.hpp \
 src/glm/./ext/vector_double3.hpp \
 src/glm/./ext/vector_double3_precision.hpp src/glm/./ext/vector_int3.hpp \
 src/glm/./ext/vector_int3_sized.hpp src/glm/./ext/vector_uint3.hpp \
 src/glm/./ext/vector_uint3_sized.hpp src/glm/vec4.hpp \
 src/glm/./ext/vector_bool4.hpp src/glm/./ext/../detail/type_vec4.hpp \
 src/glm/./ext/../detail/type_vec4.inl \
 src/glm/./ext/vector_bool4_precision.hpp src/glm/./ext/vector_float4.hpp \
 src/glm/./ext/vector_float4_precision.hpp \
 src/glm/./ext/vector_double4.hpp \
 src/glm/./ext/vector_double4_precision.hpp \
 src/glm/./ext/../detail/setup.hpp src/glm/./ext/vector_int4.hpp \
 src/glm/./ext/vector_int4_sized.hpp src/glm/./ext/vector_uint4.hpp \
 src/glm/./ext/vector_uint4_sized.hpp src/glm/mat2x2.hpp \
 src/glm/./ext/matrix_double2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.inl \
 src/glm/./ext/../detail/../matrix.hpp \
 src/glm/./ext/../detail/../detail/setup.hpp \
 src/glm/./ext/../detail/../mat2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3_precision.hpp \
 src/glm/./ext/../detail/../mat2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4_precision.hpp \
 src/glm/./ext/../detail/../mat3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2_precision.hpp \
 src/glm/./ext/../detail/../mat3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3_precision.hpp \
 src/glm/./ext/../detail/../mat3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4_precision.hpp \
 src/glm/./ext/../detail/../mat4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2_precision.hpp \
 src/glm/./ext/../detail/../mat4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3_precision.hpp \
 src/glm/./ext/../detail/../mat4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4_precision.hpp \
 src/glm/./ext/../detail/../detail/func_matrix.inl \
 c:\users\mm\desktop\wgl\src\glm\geometric.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_geometric.inl \
 c:\users\mm\desktop\wgl\src\glm\exponential.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/func_exponential.inl \
 c:\users\mm\desktop\wgl\src\glm\vector_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_vector_relational.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/_vectorize.hpp \
 c:\users\mm\desktop\wgl\src\glm\common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/_fixes.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_common.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/compute_common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 src/glm/./ext/matrix_double2x2_precision.hpp \
 src/glm/./ext/matrix_float2x2.hpp \
 src/glm/./ext/matrix_float2x2_precision.hpp src/glm/trigonometric.hpp \
 src/glm/detail/func_trigonometric.inl src/glm/packing.hpp \
 src/glm/detail/func_packing.inl src/glm/detail/type_half.hpp \
 src/glm/detail/type_half.inl src/glm/integer.hpp \
 src/glm/detail/func_integer.inl src/glm/gtc/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_projection.hpp \
 src/glm/gtc/../ext/../gtc/constants.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\setup.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.inl \
 src/glm/gtc/../ext/../gtc/constants.inl \
 src/glm/gtc/../ext/matrix_projection.inl \
 src/glm/gtc/../ext/matrix_clip_space.hpp \
 src/glm/gtc/../ext/matrix_clip_space.inl \
 src/glm/gtc/../ext/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_transform.inl src/glm/gtc/matrix_transform.inl \
 src/glm/gtc/quaternion.hpp src/glm/gtc/../ext/vector_relational.hpp \
 src/glm/gtc/../ext/vector_relational.inl \
 src/glm/gtc/../ext/../detail/type_float.hpp \
 src/glm/gtc/../ext/../detail/setup.hpp \
 src/glm/gtc/../ext/quaternion_common.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.inl \
 src/glm/gtc/../ext/quaternion_common.inl \
 src/glm/gtc/../ext/quaternion_float.hpp \
 src/glm/gtc/../ext/../detail/type_quat.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.inl \
 src/glm/gtc/../ext/../detail/type_quat.inl \
 src/glm/gtc/../ext/quaternion_float_precision.hpp \
 src/glm/gtc/../ext/quaternion_double.hpp \
 src/glm/gtc/../ext/quaternion_double_precision.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.inl \
 src/glm/gtc/../ext/quaternion_transform.hpp \
 src/glm/gtc/../ext/quaternion_transform.inl src/glm/gtc/quaternion.inl \
 src/glm/gtc/epsilon.hpp src/glm/gtc/../detail/setup.hpp \
 src/glm/gtc/epsilon.inl
build/shader.o: src/shader.cpp src/common.hpp src/glm/glm.hpp \
 src/glm/detail/_fixes.hpp src/glm/detail/setup.hpp \
 src/glm/detail/../simd/platform.h src/glm/fwd.hpp \
 src/glm/detail/qualifier.hpp src/glm/detail/setup.hpp src/glm/vec2.hpp \
 src/glm/./ext/vector_bool2.hpp src/glm/./ext/../detail/type_vec2.hpp \
 src/glm/./ext/../detail/type_vec2.inl \
 src/glm/./ext/../detail/./compute_vector_relational.hpp \
 src/glm/./ext/../detail/./setup.hpp \
 src/glm/./ext/vector_bool2_precision.hpp src/glm/./ext/vector_float2.hpp \
 src/glm/./ext/vector_float2_precision.hpp \
 src/glm/./ext/vector_double2.hpp \
 src/glm/./ext/vector_double2_precision.hpp src/glm/./ext/vector_int2.hpp \
 src/glm/./ext/vector_int2_sized.hpp \
 src/glm/./ext/../ext/scalar_int_sized.hpp \
 src/glm/./ext/../ext/../detail/setup.hpp src/glm/./ext/vector_uint2.hpp \
 src/glm/./ext/vector_uint2_sized.hpp \
 src/glm/./ext/../ext/scalar_uint_sized.hpp src/glm/vec3.hpp \
 src/glm/./ext/vector_bool3.hpp src/glm/./ext/../detail/type_vec3.hpp \
 src/glm/./ext/../detail/type_vec3.inl \
 src/glm/./ext/vector_bool3_precision.hpp src/glm/./ext/vector_float3.hpp \
 src/glm/./ext/vector_float3_precision.hpp \
 src/glm/./ext/vector_double3.hpp \
 src/glm/./ext/vector_double3_precision.hpp src/glm/./ext/vector_int3.hpp \
 src/glm/./ext/vector_int3_sized.hpp src/glm/./ext/vector_uint3.hpp \
 src/glm/./ext/vector_uint3_sized.hpp src/glm/vec4.hpp \
 src/glm/./ext/vector_bool4.hpp src/glm/./ext/../detail/type_vec4.hpp \
 src/glm/./ext/../detail/type_vec4.inl \
 src/glm/./ext/vector_bool4_precision.hpp src/glm/./ext/vector_float4.hpp \
 src/glm/./ext/vector_float4_precision.hpp \
 src/glm/./ext/vector_double4.hpp \
 src/glm/./ext/vector_double4_precision.hpp \
 src/glm/./ext/../detail/setup.hpp src/glm/./ext/vector_int4.hpp \
 src/glm/./ext/vector_int4_sized.hpp src/glm/./ext/vector_uint4.hpp \
 src/glm/./ext/vector_uint4_sized.hpp src/glm/mat2x2.hpp \
 src/glm/./ext/matrix_double2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.inl \
 src/glm/./ext/../detail/../matrix.hpp \
 src/glm/./ext/../detail/../detail/setup.hpp \
 src/glm/./ext/../detail/../mat2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3_precision.hpp \
 src/glm/./ext/../detail/../mat2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4_precision.hpp \
 src/glm/./ext/../detail/../mat3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2_precision.hpp \
 src/glm/./ext/../detail/../mat3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3_precision.hpp \
 src/glm/./ext/../detail/../mat3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4_precision.hpp \
 src/glm/./ext/../detail/../mat4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2_precision.hpp \
 src/glm/./ext/../detail/../mat4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3_precision.hpp \
 src/glm/./ext/../detail/../mat4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4_precision.hpp \
 src/glm/./ext/../detail/../detail/func_matrix.inl \
 c:\users\mm\desktop\wgl\src\glm\geometric.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_geometric.inl \
 c:\users\mm\desktop\wgl\src\glm\exponential.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/func_exponential.inl \
 c:\users\mm\desktop\wgl\src\glm\vector_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_vector_relational.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/_vectorize.hpp \
 c:\users\mm\desktop\wgl\src\glm\common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/_fixes.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_common.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/compute_common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 src/glm/./ext/matrix_double2x2_precision.hpp \
 src/glm/./ext/matrix_float2x2.hpp \
 src/glm/./ext/matrix_float2x2_precision.hpp src/glm/trigonometric.hpp \
 src/glm/detail/func_trigonometric.inl src/glm/packing.hpp \
 src/glm/detail/func_packing.inl src/glm/detail/type_half.hpp \
 src/glm/detail/type_half.inl src/glm/integer.hpp \
 src/glm/detail/func_integer.inl src/glm/gtc/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_projection.hpp \
 src/glm/gtc/../ext/../gtc/constants.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\setup.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.inl \
 src/glm/gtc/../ext/../gtc/constants.inl \
 src/glm/gtc/../ext/matrix_projection.inl \
 src/glm/gtc/../ext/matrix_clip_space.hpp \
 src/glm/gtc/../ext/matrix_clip_space.inl \
 src/glm/gtc/../ext/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_transform.inl src/glm/gtc/matrix_transform.inl \
 src/glm/gtc/quaternion.hpp src/glm/gtc/../ext/vector_relational.hpp \
 src/glm/gtc/../ext/vector_relational.inl \
 src/glm/gtc/../ext/../detail/type_float.hpp \
 src/glm/gtc/../ext/../detail/setup.hpp \
 src/glm/gtc/../ext/quaternion_common.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.inl \
 src/glm/gtc/../ext/quaternion_common.inl \
 src/glm/gtc/../ext/quaternion_float.hpp \
 src/glm/gtc/../ext/../detail/type_quat.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.inl \
 src/glm/gtc/../ext/../detail/type_quat.inl \
 src/glm/gtc/../ext/quaternion_float_precision.hpp \
 src/glm/gtc/../ext/quaternion_double.hpp \
 src/glm/gtc/../ext/quaternion_double_precision.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.inl \
 src/glm/gtc/../ext/quaternion_transform.hpp \
 src/glm/gtc/../ext/quaternion_transform.inl src/glm/gtc/quaternion.inl \
 src/glm/gtc/epsilon.hpp src/glm/gtc/../detail/setup.hpp \
 src/glm/gtc/epsilon.inl src/shader.hpp
build/spline.o: src/spline.cpp src/spline.hpp src/common.hpp \
 src/glm/glm.hpp src/glm/detail/_fixes.hpp src/glm/detail/setup.hpp \
 src/glm/detail/../simd/platform.h src/glm/fwd.hpp \
 src/glm/detail/qualifier.hpp src/glm/detail/setup.hpp src/glm/vec2.hpp \
 src/glm/./ext/vector_bool2.hpp src/glm/./ext/../detail/type_vec2.hpp \
 src/glm/./ext/../detail/type_vec2.inl \
 src/glm/./ext/../detail/./compute_vector_relational.hpp \
 src/glm/./ext/../detail/./setup.hpp \
 src/glm/./ext/vector_bool2_precision.hpp src/glm/./ext/vector_float2.hpp \
 src/glm/./ext/vector_float2_precision.hpp \
 src/glm/./ext/vector_double2.hpp \
 src/glm/./ext/vector_double2_precision.hpp src/glm/./ext/vector_int2.hpp \
 src/glm/./ext/vector_int2_sized.hpp \
 src/glm/./ext/../ext/scalar_int_sized.hpp \
 src/glm/./ext/../ext/../detail/setup.hpp src/glm/./ext/vector_uint2.hpp \
 src/glm/./ext/vector_uint2_sized.hpp \
 src/glm/./ext/../ext/scalar_uint_sized.hpp src/glm/vec3.hpp \
 src/glm/./ext/vector_bool3.hpp src/glm/./ext/../detail/type_vec3.hpp \
 src/glm/./ext/../detail/type_vec3.inl \
 src/glm/./ext/vector_bool3_precision.hpp src/glm/./ext/vector_float3.hpp \
 src/glm/./ext/vector_float3_precision.hpp \
 src/glm/./ext/vector_double3.hpp \
 src/glm/./ext/vector_double3_precision.hpp src/glm/./ext/vector_int3.hpp \
 src/glm/./ext/vector_int3_sized.hpp src/glm/./ext/vector_uint3.hpp \
 src/glm/./ext/vector_uint3_sized.hpp src/glm/vec4.hpp \
 src/glm/./ext/vector_bool4.hpp src/glm/./ext/../detail/type_vec4.hpp \
 src/glm/./ext/../detail/type_vec4.inl \
 src/glm/./ext/vector_bool4_precision.hpp src/glm/./ext/vector_float4.hpp \
 src/glm/./ext/vector_float4_precision.hpp \
 src/glm/./ext/vector_double4.hpp \
 src/glm/./ext/vector_double4_precision.hpp \
 src/glm/./ext/../detail/setup.hpp src/glm/./ext/vector_int4.hpp \
 src/glm/./ext/vector_int4_sized.hpp src/glm/./ext/vector_uint4.hpp \
 src/glm/./ext/vector_uint4_sized.hpp src/glm/mat2x2.hpp \
 src/glm/./ext/matrix_double2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.inl \
 src/glm/./ext/../detail/../matrix.hpp \
 src/glm/./ext/../detail/../detail/setup.hpp \
 src/glm/./ext/../detail/../mat2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3_precision.hpp \
 src/glm/./ext/../detail/../mat2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4_precision.hpp \
 src/glm/./ext/../detail/../mat3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2_precision.hpp \
 src/glm/./ext/../detail/../mat3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3_precision.hpp \
 src/glm/./ext/../detail/../mat3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4_precision.hpp \
 src/glm/./ext/../detail/../mat4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2_precision.hpp \
 src/glm/./ext/../detail/../mat4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3_precision.hpp \
 src/glm/./ext/../detail/../mat4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4_precision.hpp \
 src/glm/./ext/../detail/../detail/func_matrix.inl \
 c:\users\mm\desktop\wgl\src\glm\geometric.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_geometric.inl \
 c:\users\mm\desktop\wgl\src\glm\exponential.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/func_exponential.inl \
 c:\users\mm\desktop\wgl\src\glm\vector_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_vector_relational.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/_vectorize.hpp \
 c:\users\mm\desktop\wgl\src\glm\common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/_fixes.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_common.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/compute_common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 src/glm/./ext/matrix_double2x2_precision.hpp \
 src/glm/./ext/matrix_float2x2.hpp \
 src/glm/./ext/matrix_float2x2_precision.hpp src/glm/trigonometric.hpp \
 src/glm/detail/func_trigonometric.inl src/glm/packing.hpp \
 src/glm/detail/func_packing.inl src/glm/detail/type_half.hpp \
 src/glm/detail/type_half.inl src/glm/integer.hpp \
 src/glm/detail/func_integer.inl src/glm/gtc/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_projection.hpp \
 src/glm/gtc/../ext/../gtc/constants.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\setup.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.inl \
 src/glm/gtc/../ext/../gtc/constants.inl \
 src/glm/gtc/../ext/matrix_projection.inl \
 src/glm/gtc/../ext/matrix_clip_space.hpp \
 src/glm/gtc/../ext/matrix_clip_space.inl \
 src/glm/gtc/../ext/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_transform.inl src/glm/gtc/matrix_transform.inl \
 src/glm/gtc/quaternion.hpp src/glm/gtc/../ext/vector_relational.hpp \
 src/glm/gtc/../ext/vector_relational.inl \
 src/glm/gtc/../ext/../detail/type_float.hpp \
 src/glm/gtc/../ext/../detail/setup.hpp \
 src/glm/gtc/../ext/quaternion_common.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.inl \
 src/glm/gtc/../ext/quaternion_common.inl \
 src/glm/gtc/../ext/quaternion_float.hpp \
 src/glm/gtc/../ext/../detail/type_quat.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.inl \
 src/glm/gtc/../ext/../detail/type_quat.inl \
 src/glm/gtc/../ext/quaternion_float_precision.hpp \
 src/glm/gtc/../ext/quaternion_double.hpp \
 src/glm/gtc/../ext/quaternion_double_precision.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.inl \
 src/glm/gtc/../ext/quaternion_transform.hpp \
 src/glm/gtc/../ext/quaternion_transform.inl src/glm/gtc/quaternion.inl \
 src/glm/gtc/epsilon.hpp src/glm/gtc/../detail/setup.hpp \
 src/glm/gtc/epsilon.inl src/vao.hpp src/camera.hpp src/mouse.hpp \
 src/obj_loader.hpp
build/track_obj.o: src/track_obj.cpp src/obj_loader.hpp src/vao.hpp \
 src/common.hpp src/glm/glm.hpp src/glm/detail/_fixes.hpp \
 src/glm/detail/setup.hpp src/glm/detail/../simd/platform.h \
 src/glm/fwd.hpp src/glm/detail/qualifier.hpp src/glm/detail/setup.hpp \
 src/glm/vec2.hpp src/glm/./ext/vector_bool2.hpp \
 src/glm/./ext/../detail/type_vec2.hpp \
 src/glm/./ext/../detail/type_vec2.inl \
 src/glm/./ext/../detail/./compute_vector_relational.hpp \
 src/glm/./ext/../detail/./setup.hpp \
 src/glm/./ext/vector_bool2_precision.hpp src/glm/./ext/vector_float2.hpp \
 src/glm/./ext/vector_float2_precision.hpp \
 src/glm/./ext/vector_double2.hpp \
 src/glm/./ext/vector_double2_precision.hpp src/glm/./ext/vector_int2.hpp \
 src/glm/./ext/vector_int2_sized.hpp \
 src/glm/./ext/../ext/scalar_int_sized.hpp \
 src/glm/./ext/../ext/../detail/setup.hpp src/glm/./ext/vector_uint2.hpp \
 src/glm/./ext/vector_uint2_sized.hpp \
 src/glm/./ext/../ext/scalar_uint_sized.hpp src/glm/vec3.hpp \
 src/glm/./ext/vector_bool3.hpp src/glm/./ext/../detail/type_vec3.hpp \
 src/glm/./ext/../detail/type_vec3.inl \
 src/glm/./ext/vector_bool3_precision.hpp src/glm/./ext/vector_float3.hpp \
 src/glm/./ext/vector_float3_precision.hpp \
 src/glm/./ext/vector_double3.hpp \
 src/glm/./ext/vector_double3_precision.hpp src/glm/./ext/vector_int3.hpp \
 src/glm/./ext/vector_int3_sized.hpp src/glm/./ext/vector_uint3.hpp \
 src/glm/./ext/vector_uint3_sized.hpp src/glm/vec4.hpp \
 src/glm/./ext/vector_bool4.hpp src/glm/./ext/../detail/type_vec4.hpp \
 src/glm/./ext/../detail/type_vec4.inl \
 src/glm/./ext/vector_bool4_precision.hpp src/glm/./ext/vector_float4.hpp \
 src/glm/./ext/vector_float4_precision.hpp \
 src/glm/./ext/vector_double4.hpp \
 src/glm/./ext/vector_double4_precision.hpp \
 src/glm/./ext/../detail/setup.hpp src/glm/./ext/vector_int4.hpp \
 src/glm/./ext/vector_int4_sized.hpp src/glm/./ext/vector_uint4.hpp \
 src/glm/./ext/vector_uint4_sized.hpp src/glm/mat2x2.hpp \
 src/glm/./ext/matrix_double2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.inl \
 src/glm/./ext/../detail/../matrix.hpp \
 src/glm/./ext/../detail/../detail/setup.hpp \
 src/glm/./ext/../detail/../mat2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3_precision.hpp \
 src/glm/./ext/../detail/../mat2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4_precision.hpp \
 src/glm/./ext/../detail/../mat3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2_precision.hpp \
 src/glm/./ext/../detail/../mat3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3_precision.hpp \
 src/glm/./ext/../detail/../mat3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4_precision.hpp \
 src/glm/./ext/../detail/../mat4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2_precision.hpp \
 src/glm/./ext/../detail/../mat4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3_precision.hpp \
 src/glm/./ext/../detail/../mat4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4_precision.hpp \
 src/glm/./ext/../detail/../detail/func_matrix.inl \
 c:\users\mm\desktop\wgl\src\glm\geometric.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_geometric.inl \
 c:\users\mm\desktop\wgl\src\glm\exponential.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/func_exponential.inl \
 c:\users\mm\desktop\wgl\src\glm\vector_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_vector_relational.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/_vectorize.hpp \
 c:\users\mm\desktop\wgl\src\glm\common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/_fixes.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_common.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/compute_common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 src/glm/./ext/matrix_double2x2_precision.hpp \
 src/glm/./ext/matrix_float2x2.hpp \
 src/glm/./ext/matrix_float2x2_precision.hpp src/glm/trigonometric.hpp \
 src/glm/detail/func_trigonometric.inl src/glm/packing.hpp \
 src/glm/detail/func_packing.inl src/glm/detail/type_half.hpp \
 src/glm/detail/type_half.inl src/glm/integer.hpp \
 src/glm/detail/func_integer.inl src/glm/gtc/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_projection.hpp \
 src/glm/gtc/../ext/../gtc/constants.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\setup.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.inl \
 src/glm/gtc/../ext/../gtc/constants.inl \
 src/glm/gtc/../ext/matrix_projection.inl \
 src/glm/gtc/../ext/matrix_clip_space.hpp \
 src/glm/gtc/../ext/matrix_clip_space.inl \
 src/glm/gtc/../ext/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_transform.inl src/glm/gtc/matrix_transform.inl \
 src/glm/gtc/quaternion.hpp src/glm/gtc/../ext/vector_relational.hpp \
 src/glm/gtc/../ext/vector_relational.inl \
 src/glm/gtc/../ext/../detail/type_float.hpp \
 src/glm/gtc/../ext/../detail/setup.hpp \
 src/glm/gtc/../ext/quaternion_common.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.inl \
 src/glm/gtc/../ext/quaternion_common.inl \
 src/glm/gtc/../ext/quaternion_float.hpp \
 src/glm/gtc/../ext/../detail/type_quat.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.inl \
 src/glm/gtc/../ext/../detail/type_quat.inl \
 src/glm/gtc/../ext/quaternion_float_precision.hpp \
 src/glm/gtc/../ext/quaternion_double.hpp \
 src/glm/gtc/../ext/quaternion_double_precision.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.inl \
 src/glm/gtc/../ext/quaternion_transform.hpp \
 src/glm/gtc/../ext/quaternion_transform.inl src/glm/gtc/quaternion.inl \
 src/glm/gtc/epsilon.hpp src/glm/gtc/../detail/setup.hpp \
 src/glm/gtc/epsilon.inl
build/vao.o: src/vao.cpp src/vao.hpp src/common.hpp src/glm/glm.hpp \
 src/glm/detail/_fixes.hpp src/glm/detail/setup.hpp \
 src/glm/detail/../simd/platform.h src/glm/fwd.hpp \
 src/glm/detail/qualifier.hpp src/glm/detail/setup.hpp src/glm/vec2.hpp \
 src/glm/./ext/vector_bool2.hpp src/glm/./ext/../detail/type_vec2.hpp \
 src/glm/./ext/../detail/type_vec2.inl \
 src/glm/./ext/../detail/./compute_vector_relational.hpp \
 src/glm/./ext/../detail/./setup.hpp \
 src/glm/./ext/vector_bool2_precision.hpp src/glm/./ext/vector_float2.hpp \
 src/glm/./ext/vector_float2_precision.hpp \
 src/glm/./ext/vector_double2.hpp \
 src/glm/./ext/vector_double2_precision.hpp src/glm/./ext/vector_int2.hpp \
 src/glm/./ext/vector_int2_sized.hpp \
 src/glm/./ext/../ext/scalar_int_sized.hpp \
 src/glm/./ext/../ext/../detail/setup.hpp src/glm/./ext/vector_uint2.hpp \
 src/glm/./ext/vector_uint2_sized.hpp \
 src/glm/./ext/../ext/scalar_uint_sized.hpp src/glm/vec3.hpp \
 src/glm/./ext/vector_bool3.hpp src/glm/./ext/../detail/type_vec3.hpp \
 src/glm/./ext/../detail/type_vec3.inl \
 src/glm/./ext/vector_bool3_precision.hpp src/glm/./ext/vector_float3.hpp \
 src/glm/./ext/vector_float3_precision.hpp \
 src/glm/./ext/vector_double3.hpp \
 src/glm/./ext/vector_double3_precision.hpp src/glm/./ext/vector_int3.hpp \
 src/glm/./ext/vector_int3_sized.hpp src/glm/./ext/vector_uint3.hpp \
 src/glm/./ext/vector_uint3_sized.hpp src/glm/vec4.hpp \
 src/glm/./ext/vector_bool4.hpp src/glm/./ext/../detail/type_vec4.hpp \
 src/glm/./ext/../detail/type_vec4.inl \
 src/glm/./ext/vector_bool4_precision.hpp src/glm/./ext/vector_float4.hpp \
 src/glm/./ext/vector_float4_precision.hpp \
 src/glm/./ext/vector_double4.hpp \
 src/glm/./ext/vector_double4_precision.hpp \
 src/glm/./ext/../detail/setup.hpp src/glm/./ext/vector_int4.hpp \
 src/glm/./ext/vector_int4_sized.hpp src/glm/./ext/vector_uint4.hpp \
 src/glm/./ext/vector_uint4_sized.hpp src/glm/mat2x2.hpp \
 src/glm/./ext/matrix_double2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.hpp \
 src/glm/./ext/../detail/type_mat2x2.inl \
 src/glm/./ext/../detail/../matrix.hpp \
 src/glm/./ext/../detail/../detail/setup.hpp \
 src/glm/./ext/../detail/../mat2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x3_precision.hpp \
 src/glm/./ext/../detail/../mat2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat2x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double2x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float2x4_precision.hpp \
 src/glm/./ext/../detail/../mat3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x2_precision.hpp \
 src/glm/./ext/../detail/../mat3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x3_precision.hpp \
 src/glm/./ext/../detail/../mat3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat3x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double3x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float3x4_precision.hpp \
 src/glm/./ext/../detail/../mat4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x2.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x2_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x2_precision.hpp \
 src/glm/./ext/../detail/../mat4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x3.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x3_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x3_precision.hpp \
 src/glm/./ext/../detail/../mat4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_double4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\type_mat4x4.inl \
 src/glm/./ext/../detail/.././ext/matrix_double4x4_precision.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4.hpp \
 src/glm/./ext/../detail/.././ext/matrix_float4x4_precision.hpp \
 src/glm/./ext/../detail/../detail/func_matrix.inl \
 c:\users\mm\desktop\wgl\src\glm\geometric.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_geometric.inl \
 c:\users\mm\desktop\wgl\src\glm\exponential.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/type_vec1.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/func_exponential.inl \
 c:\users\mm\desktop\wgl\src\glm\vector_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_vector_relational.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/_vectorize.hpp \
 c:\users\mm\desktop\wgl\src\glm\common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/_fixes.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/func_common.inl \
 c:\users\mm\desktop\wgl\src\glm\detail/compute_common.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail/setup.hpp \
 src/glm/./ext/matrix_double2x2_precision.hpp \
 src/glm/./ext/matrix_float2x2.hpp \
 src/glm/./ext/matrix_float2x2_precision.hpp src/glm/trigonometric.hpp \
 src/glm/detail/func_trigonometric.inl src/glm/packing.hpp \
 src/glm/detail/func_packing.inl src/glm/detail/type_half.hpp \
 src/glm/detail/type_half.inl src/glm/integer.hpp \
 src/glm/detail/func_integer.inl src/glm/gtc/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_projection.hpp \
 src/glm/gtc/../ext/../gtc/constants.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.hpp \
 c:\users\mm\desktop\wgl\src\glm\detail\setup.hpp \
 src/glm/gtc/../ext/../gtc/../ext/scalar_constants.inl \
 src/glm/gtc/../ext/../gtc/constants.inl \
 src/glm/gtc/../ext/matrix_projection.inl \
 src/glm/gtc/../ext/matrix_clip_space.hpp \
 src/glm/gtc/../ext/matrix_clip_space.inl \
 src/glm/gtc/../ext/matrix_transform.hpp \
 src/glm/gtc/../ext/matrix_transform.inl src/glm/gtc/matrix_transform.inl \
 src/glm/gtc/quaternion.hpp src/glm/gtc/../ext/vector_relational.hpp \
 src/glm/gtc/../ext/vector_relational.inl \
 src/glm/gtc/../ext/../detail/type_float.hpp \
 src/glm/gtc/../ext/../detail/setup.hpp \
 src/glm/gtc/../ext/quaternion_common.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.hpp \
 src/glm/gtc/../ext/../ext/quaternion_geometric.inl \
 src/glm/gtc/../ext/quaternion_common.inl \
 src/glm/gtc/../ext/quaternion_float.hpp \
 src/glm/gtc/../ext/../detail/type_quat.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.hpp \
 c:\users\mm\desktop\wgl\src\glm\ext\quaternion_relational.inl \
 src/glm/gtc/../ext/../detail/type_quat.inl \
 src/glm/gtc/../ext/quaternion_float_precision.hpp \
 src/glm/gtc/../ext/quaternion_double.hpp \
 src/glm/gtc/../ext/quaternion_double_precision.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.hpp \
 src/glm/gtc/../ext/quaternion_trigonometric.inl \
 src/glm/gtc/../ext/quaternion_transform.hpp \
 src/glm/gtc/../ext/quaternion_transform.inl src/glm/gtc/quaternion.inl \
 src/glm/gtc/epsilon.hpp src/glm/gtc/../detail/setup.hpp \
 src/glm/gtc/epsilon.inl src/shader.hpp
