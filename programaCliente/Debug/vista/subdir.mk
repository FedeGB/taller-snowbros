################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../vista/Textura.cpp \
../vista/TextureMap.cpp \
../vista/Window.cpp 

OBJS += \
./vista/Textura.o \
./vista/TextureMap.o \
./vista/Window.o 

CPP_DEPS += \
./vista/Textura.d \
./vista/TextureMap.d \
./vista/Window.d 


# Each subdirectory must supply rules for building sources it contributes
vista/%.o: ../vista/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


