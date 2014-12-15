################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../utiles/Logger.cpp \
../utiles/Timer.cpp 

OBJS += \
./utiles/Logger.o \
./utiles/Timer.o 

CPP_DEPS += \
./utiles/Logger.d \
./utiles/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
utiles/%.o: ../utiles/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


