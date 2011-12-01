################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Ball.cpp \
../Camera.cpp \
../Checkerboard.cpp \
../intersection_point.cpp \
../main.cpp \
../main_animation.cpp \
../ray.cpp \
../sound.cpp \
../texture.cpp \
../vector.cpp 

C_SRCS += \
../bmpLoader.c \
../pcxLoader.c \
../tgaLoader.c 

OBJS += \
./Ball.o \
./Camera.o \
./Checkerboard.o \
./bmpLoader.o \
./intersection_point.o \
./main.o \
./main_animation.o \
./pcxLoader.o \
./ray.o \
./sound.o \
./texture.o \
./tgaLoader.o \
./vector.o 

C_DEPS += \
./bmpLoader.d \
./pcxLoader.d \
./tgaLoader.d 

CPP_DEPS += \
./Ball.d \
./Camera.d \
./Checkerboard.d \
./intersection_point.d \
./main.d \
./main_animation.d \
./ray.d \
./sound.d \
./texture.d \
./vector.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


