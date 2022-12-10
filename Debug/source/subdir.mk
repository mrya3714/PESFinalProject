################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Touch.c \
../source/UART.c \
../source/cbfifo.c \
../source/i2c.c \
../source/line_accumulator.c \
../source/main.c \
../source/mma.c \
../source/mtb.c \
../source/pwm_LED.c \
../source/semihost_hardfault.c \
../source/statemachine.c \
../source/switch.c \
../source/sysclock.c \
../source/test.c 

C_DEPS += \
./source/Touch.d \
./source/UART.d \
./source/cbfifo.d \
./source/i2c.d \
./source/line_accumulator.d \
./source/main.d \
./source/mma.d \
./source/mtb.d \
./source/pwm_LED.d \
./source/semihost_hardfault.d \
./source/statemachine.d \
./source/switch.d \
./source/sysclock.d \
./source/test.d 

OBJS += \
./source/Touch.o \
./source/UART.o \
./source/cbfifo.o \
./source/i2c.o \
./source/line_accumulator.o \
./source/main.o \
./source/mma.o \
./source/mtb.o \
./source/pwm_LED.o \
./source/semihost_hardfault.o \
./source/statemachine.o \
./source/switch.o \
./source/sysclock.o \
./source/test.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I"C:\Users\mruna\PESWORKSPACE\Final_Project\board" -I"C:\Users\mruna\PESWORKSPACE\Final_Project\source" -I"C:\Users\mruna\PESWORKSPACE\Final_Project" -I"C:\Users\mruna\PESWORKSPACE\Final_Project\drivers" -I"C:\Users\mruna\PESWORKSPACE\Final_Project\CMSIS" -I"C:\Users\mruna\PESWORKSPACE\Final_Project\utilities" -I"C:\Users\mruna\PESWORKSPACE\Final_Project\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/Touch.d ./source/Touch.o ./source/UART.d ./source/UART.o ./source/cbfifo.d ./source/cbfifo.o ./source/i2c.d ./source/i2c.o ./source/line_accumulator.d ./source/line_accumulator.o ./source/main.d ./source/main.o ./source/mma.d ./source/mma.o ./source/mtb.d ./source/mtb.o ./source/pwm_LED.d ./source/pwm_LED.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/statemachine.d ./source/statemachine.o ./source/switch.d ./source/switch.o ./source/sysclock.d ./source/sysclock.o ./source/test.d ./source/test.o

.PHONY: clean-source

