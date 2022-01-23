# Digital_safe 	![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)  ![Raspberry Pi](https://img.shields.io/badge/-RaspberryPi-C51A4A?style=for-the-badge&logo=Raspberry-Pi)  ![Vim](https://img.shields.io/badge/VIM-%2311AB00.svg?style=for-the-badge&logo=vim&logoColor=white)
# Raspberry Pi 4 및 부품들을 이용한 스마트 금고 

#### Project nickname : digital_safe
#### Project execution period : 2021.11.20 ~ 2021.12.14
-----------------------
## Description
Raspberry Pi 4에 C와 4x4 Keypad, SG90, HC-SR04를 연결하여 스마트 금고 제작

## 1. 수행 내용 
####  ○ Raspberry Pi 4, 서보모터(SG90), 점퍼케이블, 초음파 센서(HC-SR04), 금고 준비

####  ○ Autodesk Fusion 360 프로그램을 이용하여 금고 디자인

####  ○ Prusa3D i3 MK3S 3D Printer를 이용하여 금고 출력

####   ○ Raspberry Pi 4로 문을 여닫을 수 있는 물체에 금고 역할 부여
####     - 서보모터로 문의 개방과 폐쇄 실행
####     - 초음파 센서로 문의 닫힘 여부 판별
####     -  Keypad로 비밀번호 입력


## 2. Flowchart
![1](https://user-images.githubusercontent.com/49806698/150681130-223f7678-bad3-420a-80f2-aa87d308a640.png)


## 3. 회로도
![2](https://user-images.githubusercontent.com/49806698/150681230-70f0a63a-f61f-4829-b2b3-0aed75bfd6c5.PNG)


## 4. Fusion 360를 이용한 금고 디자인
![1](https://user-images.githubusercontent.com/49806698/150681285-390cdd14-a53e-4e5c-93a4-7d0ba155e84e.png)


## 동작
### 열렸을 때
![3](https://user-images.githubusercontent.com/49806698/150681341-f47ca24b-b1b4-4c76-acd8-89a73a037c7c.png)


### 닫혔을 때
![4](https://user-images.githubusercontent.com/49806698/150681351-03401357-b06b-4153-9cb6-e28cc035beb3.png)


## Environment

> C (Raspberry Pi OS)
> 
> Autodesk fusion 360
> 
> Raspberry Pi 4
> 
> 4x4 Keypad
> 
> SG90 (서보모터)
> 
> HC-SR04 (초음파 센서)



## Prerequisite
> Download source code
> 
> Install Raspberry Pi Os
> 
> Terminal -> "gcc -o [file] [Source code] -lwiringPi
> 
> Execute file 



