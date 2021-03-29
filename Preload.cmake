# -----------------------------------------------------------------------------
#  Cmake preload file, for generator setting
#  File Name       :  PreLoad.cmake
#  Generator       :  Ninja
#  Author          :  seven li  
#  Instructions    :  Initial file.             2021/3/28                 V0.1
# 
# -----------------------------------------------------------------------------

# use Ninja as generator
set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "" FORCE)
# do not check asm compiler
set(CMAKE_ASM_COMPILER_ID_RUN TRUE CACHE INTERNAL "" FORCE)