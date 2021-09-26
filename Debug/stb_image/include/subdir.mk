################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../stb_image/include/stb_image.cpp 

OBJS += \
./stb_image/include/stb_image.o 

CPP_DEPS += \
./stb_image/include/stb_image.d 


# Each subdirectory must supply rules for building sources it contributes
stb_image/include/%.o: ../stb_image/include/%.cpp stb_image/include/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/mathieu/Documents/eclipse-cpp_workspace/comancheLike/glad/include" -I"/home/mathieu/Documents/eclipse-cpp_workspace/comancheLike/stb_image/include" -I"/home/mathieu/Documents/eclipse-cpp_workspace/comancheLike/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


