################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Contra.cpp \
../src/LTexture.cpp \
../src/Player.cpp \
../src/RapidXmlWrapper.cpp \
../src/Timer.cpp \
../src/main.cpp \
../src/testWrapper.cpp 

OBJS += \
./src/Contra.o \
./src/LTexture.o \
./src/Player.o \
./src/RapidXmlWrapper.o \
./src/Timer.o \
./src/main.o \
./src/testWrapper.o 

CPP_DEPS += \
./src/Contra.d \
./src/LTexture.d \
./src/Player.d \
./src/RapidXmlWrapper.d \
./src/Timer.d \
./src/main.d \
./src/testWrapper.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/lucio/eclipse-workspace/Contraa/headers" -I"/home/lucio/eclipse-workspace/Contraa/rapidXML" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


