################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ComputeShader.cpp \
../src/main.cpp 

OBJS += \
./src/ComputeShader.o \
./src/main.o 

CPP_DEPS += \
./src/ComputeShader.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/mathieu/Documents/eclipse-cpp_workspace/comancheLike/glad/include" -I"/home/mathieu/Documents/eclipse-cpp_workspace/comancheLike/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


