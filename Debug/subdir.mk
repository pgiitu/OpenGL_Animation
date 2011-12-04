################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Ball.cpp \
../Camera.cpp \
../Room.cpp \
../Vector.cpp \
../main.cpp \
../main_animation.cpp 

OBJS += \
./Ball.o \
./Camera.o \
./Room.o \
./Vector.o \
./main.o \
./main_animation.o 

CPP_DEPS += \
./Ball.d \
./Camera.d \
./Room.d \
./Vector.d \
./main.d \
./main_animation.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


