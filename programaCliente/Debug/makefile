################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include vista/pantallas/subdir.mk
-include vista/elementosMenues/subdir.mk
-include vista/subdir.mk
-include utiles/subdir.mk
-include threads/subdir.mk
-include sockets/subdir.mk
-include servicios/subdir.mk
-include parserMensajes/subdir.mk
-include matematica/subdir.mk
-include interfaces/subdir.mk
-include controladorJuego/modeloJuego/tiposDeObjeto/subdir.mk
-include controladorJuego/modeloJuego/subdir.mk
-include controladorJuego/estadoJuego/subdir.mk
-include controladorJuego/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: SnowBrosClienteOtro

# Tool invocations
SnowBrosClienteOtro: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++  -o "SnowBrosClienteOtro" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) SnowBrosClienteOtro
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
