# PESFinalProject

# PESFinalProject

Objective: Levelling with the help of MMA8451Q built-in Accelerometer, Touch sensor and
LEDs on FRDM-KL25Z.

Project demo video link: 

https://drive.google.com/file/d/1neGkiC9YEyEod78n5AhJT7nSTV38wvag/view?usp=sharing

Working : Setting baud rate for UART 

<img width="199" alt="Serial Terminal" src="https://user-images.githubusercontent.com/112549892/206834981-8d925abe-2e4f-4778-a89a-bd7087658099.png">

Project proposal design overview 

<img width="519" alt="image" src="https://user-images.githubusercontent.com/112549892/206834999-3ad7acd3-a0c5-4f4b-a8df-993a08584770.png">

1. If the initialization of the sensor and code fails, red led shall glow.
   WORKING: YES
   
   
2. On successful initialization, led color shall change from red to yellow.
   WORKING: YES
   ![1670649522832](https://user-images.githubusercontent.com/112549892/206835086-8d52a832-76df-46d3-ba11-c4226804fc60.jpg)
   
   ![1670649522849](https://user-images.githubusercontent.com/112549892/206835090-5095c680-9694-4dae-944d-551f69791259.jpg)

   
3. For 0° calibration touch sensor shall be used and white led shall glow.
   WORKING: YES
   
   ![1670649522818](https://user-images.githubusercontent.com/112549892/206835107-d2029e24-dd55-432e-9559-bb2948858ba2.jpg)

   
4. After the calibration, user will be asked to input the desired angle.
   WORKING: YES
   
   ![1670649522807](https://user-images.githubusercontent.com/112549892/206835115-c9db5cc8-522d-4b16-ada4-6f69966e4292.jpg)
   
   ![1670649522796](https://user-images.githubusercontent.com/112549892/206835124-387f4dde-584b-4ed8-8096-3fc7f2113232.jpg)

5. If the angle is less than the desired angle then, red led shall glow.
   WORKING: YES
   
   ![1670649522783](https://user-images.githubusercontent.com/112549892/206835133-742464f3-0491-4797-bd46-09624c08137a.jpg)

6. If the angle is more than the desired angle then, blue led shall glow.
   WORKING: YES
   
   ![1670649522762](https://user-images.githubusercontent.com/112549892/206835142-9730bd35-2137-44d4-adff-71c1ae3ef207.jpg)

   
7. Once the desired angle is achieved, green led shall glow.
   WORKING: YES
   
   ![1670649522774](https://user-images.githubusercontent.com/112549892/206835144-35e358c6-53d9-4125-9272-34cfb1e52742.jpg)

   
8. Push button shall be used to generate an interrupt for the feedback to the user.
   WORKING: YES
   
   ![1670649990026](https://user-images.githubusercontent.com/112549892/206835154-be6c76d2-0233-4603-a332-da132e86596e.jpg)
   
   ![1670649990017](https://user-images.githubusercontent.com/112549892/206835158-a3642a89-b7e1-4482-8a74-b10d1845bf9a.jpg)


STATE DIAGRAM API FLOW:

<img width="787" alt="image" src="https://user-images.githubusercontent.com/112549892/206835165-e80ea0fe-2563-4551-90a4-d61ee2b95b06.png">

