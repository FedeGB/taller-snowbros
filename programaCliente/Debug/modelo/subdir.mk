################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../modelo/BolaEnemigo.cpp \
../modelo/EnemigoEstandar.cpp \
../modelo/EnemigoTiraFuego.cpp \
../modelo/Fireball.cpp \
../modelo/Metadata.cpp \
../modelo/Personaje.cpp \
../modelo/WorldItem.cpp \
../modelo/poder.cpp 

OBJS += \
./modelo/BolaEnemigo.o \
./modelo/EnemigoEstandar.o \
./modelo/EnemigoTiraFuego.o \
./modelo/Fireball.o \
./modelo/Metadata.o \
./modelo/Personaje.o \
./modelo/WorldItem.o \
./modelo/poder.o 

CPP_DEPS += \
./modelo/BolaEnemigo.d \
./modelo/EnemigoEstandar.d \
./modelo/EnemigoTiraFuego.d \
./modelo/Fireball.d \
./modelo/Metadata.d \
./modelo/Personaje.d \
./modelo/WorldItem.d \
./modelo/poder.d 


# Each subdirectory must supply rules for building sources it contributes
modelo/%.o: ../modelo/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


