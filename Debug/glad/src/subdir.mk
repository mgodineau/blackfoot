################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../glad/src/glad.c 

OBJS += \
./glad/src/glad.o 

C_DEPS += \
./glad/src/glad.d 


# Each subdirectory must supply rules for building sources it contributes
glad/src/%.o: ../glad/src/%.c glad/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/mathieu/Documents/eclipse-cpp_workspace/comancheLike/glad/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


