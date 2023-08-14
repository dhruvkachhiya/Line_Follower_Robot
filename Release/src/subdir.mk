################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/extApi.c \
../src/extApiPlatform.c 

CPP_SRCS += \
../src/eBot_Sandbox.cpp \
../src/eBot_Sim_Predef.cpp \
../src/lab4_line_follower_robot.cpp 

OBJS += \
./src/eBot_Sandbox.o \
./src/eBot_Sim_Predef.o \
./src/extApi.o \
./src/extApiPlatform.o \
./src/lab4_line_follower_robot.o 

C_DEPS += \
./src/extApi.d \
./src/extApiPlatform.d 

CPP_DEPS += \
./src/eBot_Sandbox.d \
./src/eBot_Sim_Predef.d \
./src/lab4_line_follower_robot.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


